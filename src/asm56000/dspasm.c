/* A compact runnable ASM56000 driver around the recovered assembler core. */
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "asm56000.h"

extern unsigned long ErrOnThisLine;
extern char InLineReplay;

static char *dup_text(char *text);
static int DirectiveFailed;
static unsigned long org_key_counter(char *key);
static int counter_is_reloc(void);
static void flush_pending_labels(void);
static unsigned long obj_next_seq(void);
static void obj_log_add(int kind, unsigned long seq, unsigned long a,
                        unsigned long b, char *text);
static int is_name(char *name, char *want);
static unsigned long parse_expr_value(char *text);
static int split_csv(char *text, char *out[], char storage[][128], int max);
static void list_source(unsigned long address, int nwords);
static void list_macro_source(void);
static void list_plain_source(void);
static char *source_base_name(void);
static void listing_report_crossref(void);
static void listing_report_memory(void);
static void listing_report_symbols(void);

static int is_cli_define_name(char *name);
static unsigned long non_cli_public_count(void);

struct word_record {
    unsigned long address;
    unsigned long runtime_address;
    unsigned long word;
    unsigned long source_line;
    int space;
    char *reloc;
    unsigned long seq;
};

struct raw_segment {
    unsigned long address;
    unsigned long count;
    unsigned long first_record;
    unsigned long runtime_address;
    unsigned long generation;
    int space;
};

struct output_section {
    char *name;
    unsigned long address;
    unsigned long size;
    unsigned long ptr;
    unsigned long flags;
    unsigned long first_record;
    unsigned long runtime_address;
    int space;
    int raw;
    unsigned long virtual_address;
    unsigned long virtual_space;
};

struct output_event {
    int kind;
    int space;
    unsigned long address;
    unsigned long count;
    unsigned long first_record;
    unsigned long generation;
    unsigned long flags;
    unsigned long virtual_address;
    unsigned long virtual_space;
    unsigned long source_line;
    unsigned long aux_group;
    unsigned long aux_flag;
    unsigned long aux_length;
    unsigned long aux_second;
    void *section_ptr;
    int section_start;
    char section_name[32];
    unsigned long section_begin_line;
    unsigned long section_end_line;
    unsigned long seq;
    unsigned long secno;
    unsigned long mcntr;
    int reloc;
};

/* Object-file log: everything the original writes to the symbol and
   string tables while pass 2 runs, in source order.  Events (sections),
   labels and relocation strings carry their own sequence stamps. */
#define OL_BS     1
#define OL_ES     2
#define OL_XREF   3
#define OL_EXTERN 4
#define OL_END    5
#define OL_STR    6

struct obj_log_item {
    unsigned long seq;
    int kind;
    unsigned long a;
    unsigned long b;
    char *text;
};

struct pending_label;

struct pending_label {
    unsigned long seq;
    int space;
    unsigned long generation;
    unsigned long address;
};

struct bsc_report_span {
    int space;
    unsigned long address;
    unsigned long count;
    char section_name[32];
};

static struct word_record *Records;
static unsigned long RecordCount;
static unsigned long RecordSize;
static struct raw_segment *RawSegments;
static unsigned long SegmentCount;
static unsigned long SegmentSize;
static unsigned long ProgramCounter;
static unsigned long LoadCounter;
static int LoadPhysical;
static unsigned long RecordGeneration;
static int StopInput;
static FILE *Listing;
static int ListingHeaderWritten;
static int InListingHeader;
static int ListingIsStdout;
static int ListingPage;
static unsigned long ListingSourceLines;
static unsigned long ListingErrorBase;
static int ListingWidth = 80;
static int ListingPageLength = 66;
static int ListingIndent;
static int ListingPagePending;
static int ListingNoBreak;
static int ListingEnabled = 1;
static int ListingSavedWidth = 80;
static int ListingSavedPageLength = 66;
static int ListingSavedIndent;
static int ListingNoBreakEver;
static int ListingAllowOverrun;
static int CommandCexOption;
static int ObjectOptionSeen;
static int ListingOptionSeen;
static unsigned long DoEndStack[32];
static int DoEndCount;
static int LastInstructionWasRep;
static int ListingUnconditional;
static int ListingInactive;
static int ReportHeaderMode;
int ListingSeparateComments;
static int SeparateCommentPending;
static char SeparateComment[ASM56000_INPUT_LINE_CAP];
static char ListingTitle[256];
static char ListingSubtitle[256];
static char ListingHeaderTitle[256];
static char ListingHeaderSubtitle[256];
static char PendingPrctl[16];
static int PendingPrctlLength;
static int ListingLayoutReady;
static int ListingLabelWidth = 10;
static int ListingOpcodeWidth = 8;
static int ListingOperandWidth = 10;
static int ListingXWidth = 12;
static int ListingYWidth = 12;
static char *SourceName;
static char *OutputName;
static char *ListingName;
static char *SourceNames[64];
static int SourceCount;
static int ObjectRequested;
static int ListingRequested;
int AbsoluteMode;
int SourceCexDirective;
int SourceOptCex;
int ListingReportCrossRef;
int ListingReportMemory;
int ListingReportLocals;
int ListingReportSymbols;
int SectionGlobalCounters;
static int GenerateDebugOption;
static int NoSymbolsOption;
static char *DefineNames[64];
static char *DefineValues[64];
static int DefineCount;
static char *SourceDefineNames[64];
static char *SourceDefineValues[64];
static int SourceDefineCount;
static char *CliOptions[64];
static int CliOptionCount;
static FILE *ErrorFile;
static char *IncludePath;
static char *MacroPathOption;
static int QuietOption;
static int VerboseOption;
static struct bsc_report_span BscReportSpans[64];
static unsigned long BscReportSpanCount;
static int BscReportMaterialized;

static int is_cli_define_name(char *name)
{
    int i;

    if (name == (char *)0)
        return 0;
    for (i = 0; i < DefineCount; ++i)
        if (DefineNames[i] != (char *)0 && strcmp(DefineNames[i], name) == 0)
            return 1;
    return 0;
}

static unsigned long non_cli_public_count(void)
{
    unsigned long i;
    unsigned long count;
    char name[128];

    count = 0UL;
    for (i = 0UL; i < sym_public_count(); ++i)
        if (sym_public_info(i, name, sizeof(name), (unsigned long *)0,
                            (unsigned long *)0, (unsigned long *)0) &&
            !is_cli_define_name(name))
            ++count;
    return count;
}

static int reloc_label_visible(int space, unsigned long scn,
                               int sectioned, int global,
                               unsigned long flags)
{
    (void)sectioned;
    (void)global;
    if ((flags & 0x20UL) != 0UL && !global)
        return 0;
    (void)space;
    (void)scn;
    return 1;
}

unsigned long CpuVariant = 2UL;
static int PreviousAddressWrite;
static int PreviousAddressRegister;
int CurrentSpace;
static int CurrentLoadSpace;
static int RecordingInstruction;
static int MacroDirectiveListed;
static unsigned long SpaceMin[32];
static unsigned long SpaceMax[32];
static int SpaceUsed[32];
static unsigned long LastDataWords[64];
static int LastDataCount;
static int BufferActive;
static unsigned long BufferStart;
static unsigned long BufferSize;
static struct output_event *OutputEvents;
static unsigned long OutputEventCount;
static unsigned long OutputEventSize;
static unsigned long OutputGeneration;
static unsigned long OutputGenerationLine;
static unsigned long OutputAuxGroup;
static void *OutputSectionMarker;
static int OutputSectionStartPending;
static unsigned long OutputSectionBeginLine;
static unsigned long OutputSectionEndLine;
static char OutputSectionName[32];
static unsigned long BufferAuxGroup;
static unsigned long BufferAuxFlag;
static unsigned long BufferAuxLength;
static int OutputHasBss;
static char OrgKey[32];
static char OrgKeys[32][32];
static unsigned long OrgValues[32];
static int OrgAbs[32];
static int OrgKeyCount;
static int ModeReloc = 1;
static char LoadOrgKey[32];
static char LoadOrgKeys[32][32];
static unsigned long LoadOrgValues[32];
static int LoadOrgKeyCount;

struct section_counter_state {
    void *section;
    unsigned long pc[4];
    unsigned long load[4];
    int current_space;
    int current_load_space;
    int load_physical;
    char org_key[32];
    char org_keys[32][32];
    unsigned long org_values[32];
    int org_abs[32];
    int org_key_count;
    char load_org_key[32];
    char load_org_keys[32][32];
    unsigned long load_org_values[32];
    int load_org_key_count;
};

static struct section_counter_state SectionStates[64];
static int SectionStateCount;

static struct section_counter_state *section_state(void *section,
                                                    int create)
{
    int i;

    /* A STATIC section allocates from the global section's counters. */
    if (sec_is_static_section(section))
        section = sec_global_section();
    for (i = 0; i < SectionStateCount; ++i)
        if (SectionStates[i].section == section)
            return &SectionStates[i];
    if (!create || SectionStateCount >=
        (int)(sizeof(SectionStates) / sizeof(SectionStates[0])))
        return (struct section_counter_state *)0;
    memset(&SectionStates[SectionStateCount], 0,
           sizeof(SectionStates[SectionStateCount]));
    SectionStates[SectionStateCount].section = section;
    return &SectionStates[SectionStateCount++];
}

void asm_section_state_reset(void)
{
    memset(SectionStates, 0, sizeof(SectionStates));
    SectionStateCount = 0;
}

static void save_section_state(void)
{
    struct section_counter_state *state;

    state = section_state(CurrentSection, 1);
    if (state == (struct section_counter_state *)0)
        return;
    if (CurrentSpace >= 0 && CurrentSpace < 4)
        state->pc[CurrentSpace] = ProgramCounter;
    if (CurrentLoadSpace >= 0 && CurrentLoadSpace < 4)
        state->load[CurrentLoadSpace] = LoadCounter;
    state->current_space = CurrentSpace;
    state->current_load_space = CurrentLoadSpace;
    state->load_physical = LoadPhysical;
    strcpy(state->org_key, OrgKey);
    memcpy(state->org_keys, OrgKeys, sizeof(OrgKeys));
    memcpy(state->org_values, OrgValues, sizeof(OrgValues));
    memcpy(state->org_abs, OrgAbs, sizeof(OrgAbs));
    state->org_key_count = OrgKeyCount;
    strcpy(state->load_org_key, LoadOrgKey);
    memcpy(state->load_org_keys, LoadOrgKeys, sizeof(LoadOrgKeys));
    memcpy(state->load_org_values, LoadOrgValues, sizeof(LoadOrgValues));
    state->load_org_key_count = LoadOrgKeyCount;
}

static void restore_section_state(void)
{
    struct section_counter_state *state;

    state = section_state(CurrentSection, 1);
    if (state == (struct section_counter_state *)0)
        return;
    CurrentSpace = state->current_space;
    CurrentLoadSpace = state->current_load_space;
    LoadPhysical = state->load_physical;
    ProgramCounter = state->pc[CurrentSpace];
    LoadCounter = state->load[CurrentLoadSpace];
    strcpy(OrgKey, state->org_key);
    memcpy(OrgKeys, state->org_keys, sizeof(OrgKeys));
    memcpy(OrgValues, state->org_values, sizeof(OrgValues));
    memcpy(OrgAbs, state->org_abs, sizeof(OrgAbs));
    OrgKeyCount = state->org_key_count;
    strcpy(LoadOrgKey, state->load_org_key);
    memcpy(LoadOrgKeys, state->load_org_keys, sizeof(LoadOrgKeys));
    memcpy(LoadOrgValues, state->load_org_values, sizeof(LoadOrgValues));
    LoadOrgKeyCount = state->load_org_key_count;
}

int asm_section_enter(char *name, char *mod1, char *mod2)
{
    int result;

    flush_pending_labels();
    if (!AbsoluteMode && !SectionGlobalCounters)
        save_section_state();
    result = sec_section(name, mod1, mod2);
    if (result && !AbsoluteMode && !SectionGlobalCounters)
        restore_section_state();
    return result;
}

int asm_section_leave(void)
{
    int result;

    flush_pending_labels();
    if (!AbsoluteMode && !SectionGlobalCounters)
        save_section_state();
    result = sec_endsec();
    if (result && !AbsoluteMode && !SectionGlobalCounters)
        restore_section_state();
    return result;
}

static void org_selector(char *operand, char *key, char *expr)
{
    char *p;
    char *q;

    key[0] = '\0';
    expr[0] = '\0';
    if (operand == (char *)0)
        return;
    p = operand;
    while (*p == ' ' || *p == '\t')
        ++p;
    q = key;
    while (*p != '\0' && *p != ':' && *p != ',') {
        if ((q - key) < 31)
            *q++ = (char)tolower((unsigned char)*p);
        ++p;
    }
    *q = '\0';
    if (*p == ':')
        ++p;
    while (*p == ' ' || *p == '\t')
        ++p;
    q = expr;
    while (*p != '\0' && *p != ',') {
        if ((q - expr) < 127)
            *q++ = *p;
        ++p;
    }
    while (q > expr && (q[-1] == ' ' || q[-1] == '\t'))
        --q;
    *q = '\0';
}

static int org_key_index(char *key)
{
    int i;

    for (i = 0; i < OrgKeyCount; ++i)
        if (strcmp(OrgKeys[i], key) == 0)
            return i;
    if (OrgKeyCount >= (int)(sizeof(OrgKeys) / sizeof(OrgKeys[0])))
        return -1;
    strcpy(OrgKeys[OrgKeyCount], key);
    OrgValues[OrgKeyCount] = 0UL;
    OrgAbs[OrgKeyCount] = 0;
    return OrgKeyCount++;
}

static int load_org_key_index(char *key)
{
    int i;

    for (i = 0; i < LoadOrgKeyCount; ++i)
        if (strcmp(LoadOrgKeys[i], key) == 0)
            return i;
    if (LoadOrgKeyCount >= (int)(sizeof(LoadOrgKeys) / sizeof(LoadOrgKeys[0])))
        return -1;
    strcpy(LoadOrgKeys[LoadOrgKeyCount], key);
    LoadOrgValues[LoadOrgKeyCount] = 0UL;
    return LoadOrgKeyCount++;
}

static int cex_enabled(void)
{
    if (!OptCm)
        return 0;
    if (MnemField != (char *)0 &&
        (MnemField[0] == 'j' || MnemField[0] == 'J' ||
         is_name(MnemField, "do") || is_name(MnemField, "enddo") ||
         is_name(MnemField, "dec") || is_name(MnemField, "inc") ||
         is_name(MnemField, "rts") || is_name(MnemField, "rti") ||
         is_name(MnemField, "swi") || is_name(MnemField, "stop") ||
         is_name(MnemField, "reset") || is_name(MnemField, "wait")))
        return 0;
    if (MnemField != (char *)0 &&
        (is_name(MnemField, "move") || is_name(MnemField, "nop") ||
         is_name(MnemField, "jmp")))
        return 0;
    return 1;
}

static struct obj_log_item *ObjLog;
static unsigned long ObjLogCount;
static unsigned long ObjLogSize;
static struct pending_label PendingLabels[64];
static int PendingLabelCount;
static int NeedOpenSection;
static unsigned long SectionStackNumbers[64];
static int SectionStackTop;

#define OBJ_STEP 64UL

/* P-space location counter of the current section. */
static unsigned long current_p_counter(void)
{
    struct section_counter_state *state;

    if (CurrentSpace == 0)
        return ProgramCounter;
    state = section_state(CurrentSection, 0);
    return state == (struct section_counter_state *)0 ? 0UL : state->pc[0];
}

static unsigned long obj_next_seq(void)
{
    ObjSeq += OBJ_STEP;
    return ObjSeq;
}

static void obj_log_add(int kind, unsigned long seq, unsigned long a,
                        unsigned long b, char *text)
{
    struct obj_log_item *next;
    unsigned long next_size;

    if (Pass != 2UL || AbsoluteMode)
        return;
    if (ObjLogCount == ObjLogSize) {
        next_size = ObjLogSize == 0UL ? 64UL : ObjLogSize * 2UL;
        next = (struct obj_log_item *)realloc(ObjLog,
                                              next_size * sizeof(*ObjLog));
        if (next == (struct obj_log_item *)0) {
            fprintf(stderr, "asm56000: out of memory\n");
            exit(2);
        }
        ObjLog = next;
        ObjLogSize = next_size;
    }
    ObjLog[ObjLogCount].seq = seq;
    ObjLog[ObjLogCount].kind = kind;
    ObjLog[ObjLogCount].a = a;
    ObjLog[ObjLogCount].b = b;
    ObjLog[ObjLogCount].text = text == (char *)0 ? (char *)0 :
                               dup_text(text);
    ++ObjLogCount;
}

static void output_event_reset(void)
{
    unsigned long i;

    for (i = 0UL; i < ObjLogCount; ++i)
        free(ObjLog[i].text);
    ObjLogCount = 0UL;
    PendingLabelCount = 0;
    NeedOpenSection = 0;
    free(OutputEvents);
    OutputEvents = (struct output_event *)0;
    OutputEventCount = 0UL;
    OutputEventSize = 0UL;
    OutputGeneration = 0UL;
    OutputGenerationLine = 0UL;
    OutputAuxGroup = 0UL;
    OutputSectionMarker = (void *)0;
    OutputSectionStartPending = 0;
    OutputSectionBeginLine = 0UL;
    OutputSectionEndLine = 0UL;
    OutputSectionName[0] = '\0';
    BufferAuxGroup = 0UL;
    BufferAuxFlag = 0UL;
    BufferAuxLength = 0UL;
    OutputHasBss = 0;
    BscReportSpanCount = 0UL;
    BscReportMaterialized = 0;
}

static void output_event_add(int kind, int space, unsigned long address,
                             unsigned long count, unsigned long first_record,
                             unsigned long flags);

/* Labels waiting for the section that will hold them attach to the event
   just created (or extended); their symbol-table position follows the
   section symbol. */
static void attach_pending_labels(unsigned long event_seq, int space,
                                  unsigned long generation,
                                  unsigned long scn, int reorder)
{
    int i;
    unsigned long k;

    k = 0UL;
    i = 0;
    while (i < PendingLabelCount) {
        if (PendingLabels[i].space == space &&
            PendingLabels[i].generation == generation) {
            sym_object_set(PendingLabels[i].seq, scn,
                           reorder ? event_seq + 1UL + k : 0UL);
            ++k;
            memmove(&PendingLabels[i], &PendingLabels[i + 1],
                    (unsigned long)(PendingLabelCount - i - 1) *
                    sizeof(PendingLabels[0]));
            --PendingLabelCount;
        } else
            ++i;
    }
}

/* No data ever followed the pending labels: they get a section of their
   own (an empty one at the label address). */
static void flush_pending_labels(void)
{
    int space;
    unsigned long address;

    if (Pass != 2UL || AbsoluteMode || PendingLabelCount == 0)
        return;
    space = PendingLabels[0].space;
    address = PendingLabels[0].address;
    output_event_add(0, space, address, 0UL, RecordCount,
                     space == 0 ? 0x20UL : 0x40UL);
}

static void output_event_add(int kind, int space, unsigned long address,
                             unsigned long count, unsigned long first_record,
                             unsigned long flags)
{
    struct output_event *event;
    struct output_event *next;
    unsigned long next_size;

    if (Pass != 2UL)
        return;
    if (!AbsoluteMode && kind == 1 && space == 0 && PendingLabelCount != 0)
        flush_pending_labels();
    if (kind == 0 && count != 0UL && OutputEventCount != 0UL) {
        event = &OutputEvents[OutputEventCount - 1UL];
        if (event->kind == 0 && event->space == space &&
            event->generation == OutputGeneration &&
            event->first_record + event->count == first_record) {
            event->count += count;
            if (!AbsoluteMode)
                attach_pending_labels(event->seq, space, event->generation,
                                      OutputEventCount + 1UL, 0);
            return;
        }
    }
    if (OutputEventCount == OutputEventSize) {
        next_size = OutputEventSize == 0UL ? 64UL : OutputEventSize * 2UL;
        next = (struct output_event *)realloc(
            OutputEvents, next_size * sizeof(*OutputEvents));
        if (next == (struct output_event *)0) {
            fprintf(stderr, "asm56000: out of memory\n");
            exit(2);
        }
        OutputEvents = next;
        OutputEventSize = next_size;
    }
    event = &OutputEvents[OutputEventCount++];
    event->kind = kind;
    event->space = space;
    event->address = address;
    event->count = count;
    event->first_record = first_record;
    event->generation = OutputGeneration;
    event->flags = flags;
    event->virtual_address = address;
    event->virtual_space = (unsigned long)space;
    event->source_line = OutputGenerationLine != 0UL ?
                         OutputGenerationLine : LineNo;
    event->aux_group = 0UL;
    event->aux_flag = 0UL;
    event->aux_length = 0UL;
    event->aux_second = 0UL;
    event->section_ptr = CurrentSection;
    event->section_start = OutputSectionStartPending;
    OutputSectionStartPending = 0;
    strncpy(event->section_name, sec_current_name(),
            sizeof(event->section_name) - 1UL);
    event->section_name[sizeof(event->section_name) - 1UL] = '\0';
    event->section_begin_line = OutputSectionBeginLine;
    event->section_end_line = OutputSectionEndLine;
    if (kind == 0 && count != 0UL && first_record < RecordCount)
        event->seq = Records[first_record].seq - OBJ_STEP / 2UL;
    else
        event->seq = obj_next_seq();
    event->secno = sec_number(CurrentSection);
    event->mcntr = org_key_counter(OrgKey);
    event->reloc = counter_is_reloc();
    if (kind != 0)
        OutputHasBss = 1;
    if (!AbsoluteMode)
        attach_pending_labels(event->seq, space, event->generation,
                              OutputEventCount + 1UL, 1);
}

static void output_event_mark_aux3(unsigned long group, unsigned long flag,
                                   unsigned long length,
                                   unsigned long second)
{
    if (OutputEventCount == 0UL)
        return;
    OutputEvents[OutputEventCount - 1UL].aux_group = group;
    OutputEvents[OutputEventCount - 1UL].aux_flag = flag;
    OutputEvents[OutputEventCount - 1UL].aux_length = length;
    OutputEvents[OutputEventCount - 1UL].aux_second = second;
}

static unsigned long output_event_flags(char *name, int space)
{
    if (name != (char *)0 &&
        (is_name(name, "bsc") || is_name(name, "bsm") ||
         is_name(name, "bsr")))
        return space == 3 ? 0x440UL : space == 2 ? 0x440UL :
               space == 0 ? 0x420UL : 0x40UL;
    return space == 0 ? 0x20UL : 0x40UL;
}

static void output_event_records(unsigned long first_record, char *name)
{
    char storage[4][128];
    char *args[4];
    int n;
    unsigned long i;
    unsigned long group_end;
    unsigned long marker;
    int lcv_split;

    lcv_split = Pass == 2UL && RecordCount > first_record &&
                name != (char *)0 && is_name(name, "dc") &&
                Op1Field != (char *)0 && strstr(Op1Field, "@lcv") !=
                (char *)0;
    if (Pass == 2UL && RecordCount > first_record &&
        !sec_current_is_global() && OutputSectionMarker != CurrentSection) {
        output_event_add(0, Records[first_record].space,
                         Records[first_record].address, 0UL,
                         first_record,
                         output_event_flags(name,
                         Records[first_record].space));
        OutputSectionMarker = CurrentSection;
        ++OutputGeneration;
    }
    if (lcv_split) {
        group_end = first_record + 1UL;
        while (group_end < RecordCount &&
               Records[group_end].space == Records[first_record].space &&
               Records[group_end].address ==
                   Records[first_record].address +
                   (group_end - first_record) &&
               Records[group_end].runtime_address ==
                   Records[group_end].address &&
               Records[group_end].word == Records[group_end].address)
            ++group_end;
        output_event_add(0, Records[first_record].space,
                         Records[first_record].address,
                         group_end - first_record, first_record,
                         output_event_flags(name, Records[first_record].space));
        for (i = group_end; i < RecordCount; ++i) {
            marker = Records[i].runtime_address != Records[i].address ?
                     Records[i].address : Records[i].word;
            output_event_add(0, Records[i].space, marker, 0UL,
                             RecordCount, 0x40UL);
            output_event_add(0, Records[i].space, Records[i].address,
                             1UL, i, output_event_flags(name,
                             Records[i].space));
        }
        return;
    }

    if (Pass == 2UL && RecordCount > first_record)
        output_event_add(0, Records[first_record].space,
                         Records[first_record].address,
                         RecordCount - first_record, first_record,
                         output_event_flags(name, Records[first_record].space));
    if (Pass == 2UL && RecordCount > first_record && name != (char *)0 &&
        (is_name(name, "bsc") || is_name(name, "bsm") ||
         is_name(name, "bsr"))) {
        n = split_csv(Op1Field, args, storage, 4);
        if (n != 0) {
            OutputEvents[OutputEventCount - 1UL].virtual_address =
                parse_expr_value(args[0]);
            OutputEvents[OutputEventCount - 1UL].virtual_space = 4UL;
            if (is_name(name, "bsm") || is_name(name, "bsr")) {
                ++OutputAuxGroup;
                output_event_mark_aux3(OutputAuxGroup,
                    is_name(name, "bsm") ? 0x400UL : 0x800UL,
                    parse_expr_value(args[0]), 0x2100UL);
            }
        }
    }
    if (Pass == 2UL && RecordCount > first_record && BufferActive)
        output_event_mark_aux3(BufferAuxGroup, BufferAuxFlag,
                               BufferAuxLength, 0x2100UL);
}

static void output_event_bss(int space, unsigned long address,
                             unsigned long count, unsigned long flags)
{
    if (count != 0UL)
        output_event_add(1, space, address, count, 0UL, flags);
}

static void materialize_bsc_report_spans(void)
{
    unsigned long i;

    if (BscReportMaterialized)
        return;
    BscReportMaterialized = 1;
    for (i = 0UL; i < BscReportSpanCount; ++i) {
        output_event_bss(BscReportSpans[i].space,
                         BscReportSpans[i].address,
                         BscReportSpans[i].count, 0x28UL);
        if (OutputEventCount != 0UL) {
            strncpy(OutputEvents[OutputEventCount - 1UL].section_name,
                    BscReportSpans[i].section_name,
                    sizeof(OutputEvents[OutputEventCount - 1UL].section_name) - 1UL);
            OutputEvents[OutputEventCount - 1UL].section_name[
                sizeof(OutputEvents[OutputEventCount - 1UL].section_name) - 1UL] = '\0';
        }
    }
}

static void output_event_directive(char *name, unsigned long before,
                                   unsigned long after,
                                   unsigned long first_record)
{
    unsigned long value;
    unsigned long aligned;
    unsigned long factor;
    char storage[4][128];
    char *args[4];
    int n;

    if (is_name(name, "section")) {
        OutputSectionMarker = (void *)0;
        OutputSectionStartPending = 1;
        OutputSectionBeginLine = LineNo;
        strncpy(OutputSectionName, sec_current_name(),
                sizeof(OutputSectionName) - 1UL);
        OutputSectionName[sizeof(OutputSectionName) - 1UL] = '\0';
        OutputSectionEndLine = 0UL;
        if (Pass == 2UL && !AbsoluteMode && sec_depth() != 0UL &&
            !DirectiveFailed) {
            /* SECTION opens an (empty) section right away; its name and
               the .bs marker enter the tables at this point. */
            if (SectionStackTop < (int)(sizeof(SectionStackNumbers) /
                                        sizeof(SectionStackNumbers[0])))
                SectionStackNumbers[SectionStackTop++] =
                    sec_number(CurrentSection);
            obj_log_add(OL_BS, obj_next_seq(), sec_number(CurrentSection),
                        LineNo, sec_current_name());
            output_event_add(0, 0, current_p_counter(), 0UL, RecordCount,
                             0x20UL);
            OutputSectionMarker = CurrentSection;
            ++OutputGeneration;
        }
    } else if (is_name(name, "endsec") && OutputSectionName[0] != '\0') {
        if (Pass == 2UL && !AbsoluteMode && SectionStackTop > 0) {
            obj_log_add(OL_ES, obj_next_seq(),
                        SectionStackNumbers[--SectionStackTop], LineNo,
                        (char *)0);
            NeedOpenSection = 1;
        }
        OutputSectionEndLine = LineNo;
        for (n = 0; n < (int)OutputEventCount; ++n)
            if (strcmp(OutputEvents[n].section_name,
                       OutputSectionName) == 0)
                OutputEvents[n].section_end_line = OutputSectionEndLine;
        OutputSectionName[0] = '\0';
        OutputSectionMarker = CurrentSection;
    }

    if (is_name(name, "org") || is_name(name, "bsc") ||
        is_name(name, "bsm") || is_name(name, "bsr") ||
        is_name(name, "ds") || is_name(name, "dsb") ||
        is_name(name, "dsr") || is_name(name, "dsm") ||
        is_name(name, "dsmr") || is_name(name, "buffer") ||
        is_name(name, "endbuf") || is_name(name, "baddr") ||
        is_name(name, "align"))
        OutputGenerationLine = LineNo;

    if (name != (char *)0 &&
        (is_name(name, "bsc") || is_name(name, "bsm") ||
         is_name(name, "bsr")))
        ++OutputGeneration;
    output_event_records(first_record, name);
    factor = CurrentSpace == 3 ? 2UL : 1UL;
    if (is_name(name, "org")) {
        ++OutputGeneration;
        return;
    }
    if (is_name(name, "ds") || is_name(name, "dsb") ||
        is_name(name, "dsr") || is_name(name, "dsm") ||
        is_name(name, "dsmr")) {
        value = parse_expr_value(Op1Field);
        aligned = before;
        if (is_name(name, "dsm") || is_name(name, "dsmr"))
            if (value != 0UL)
                aligned = ((before + value - 1UL) / value) * value;
        output_event_bss(CurrentSpace, before,
                         (aligned - before) * factor, 0x48UL);
        output_event_bss(CurrentSpace, aligned, value * factor, 0xc0UL);
        if (is_name(name, "dsm") || is_name(name, "dsmr") ||
            is_name(name, "dsr")) {
            ++OutputAuxGroup;
            output_event_mark_aux3(OutputAuxGroup,
                is_name(name, "dsm") ? 0x400UL : 0x800UL,
                value * factor, 0x2100UL);
        } else if (BufferActive)
            output_event_mark_aux3(BufferAuxGroup, BufferAuxFlag,
                                   BufferAuxLength, 0x2100UL);
        ++OutputGeneration;
        return;
    }
    if (is_name(name, "buffer")) {
        ++OutputAuxGroup;
        BufferAuxGroup = OutputAuxGroup;
        BufferAuxFlag = Op1Field != (char *)0 &&
                        (Op1Field[0] == 'r' || Op1Field[0] == 'R') ?
                        0x800UL : 0x400UL;
        BufferAuxLength = BufferSize;
        ++OutputGeneration;
        return;
    }
    if (is_name(name, "endbuf")) {
        output_event_bss(CurrentSpace, before,
                         (after - before) * factor, 0x48UL);
        output_event_mark_aux3(BufferAuxGroup, BufferAuxFlag,
                               BufferAuxLength, 0x2100UL);
        ++OutputGeneration;
        return;
    }
    if (is_name(name, "baddr")) {
        n = split_csv(Op1Field, args, storage, 4);
        output_event_bss(CurrentSpace, before,
                         (after - before) * factor, 0x48UL);
        output_event_add(0, CurrentSpace, after, 0UL, RecordCount, 0x40UL);
        ++OutputAuxGroup;
        output_event_mark_aux3(OutputAuxGroup,
            Op1Field != (char *)0 &&
            (Op1Field[0] == 'r' || Op1Field[0] == 'R') ?
            0x800UL : 0x400UL, n > 1 ? parse_expr_value(args[1]) : 0UL,
            0x42100UL);
        ++OutputGeneration;
        return;
    }
    if (is_name(name, "align")) {
        output_event_bss(CurrentSpace, before,
                         (after - before) * factor, 0x48UL);
        output_event_add(0, CurrentSpace, after, 0UL, RecordCount, 0x40UL);
        ++OutputAuxGroup;
        output_event_mark_aux3(OutputAuxGroup, 0x400UL,
                               parse_expr_value(Op1Field), 0x42100UL);
        ++OutputGeneration;
        return;
    }
    if (is_name(name, "bsc") || is_name(name, "bsm") ||
        is_name(name, "bsr")) {
        n = split_csv(Op1Field, args, storage, 4);
        if (n != 0) {
            value = parse_expr_value(args[0]);
            if (n == 1 && is_name(name, "bsc"))
                output_event_bss(CurrentSpace, after - 1UL, 1UL, 0x28UL);
            else if (n == 1 && value == 4UL && is_name(name, "bsm"))
                output_event_bss(CurrentSpace, after - 4UL, 4UL, 0x28UL);
            else if (n >= 2 && is_name(name, "bsc") &&
                     BscReportSpanCount <
                     sizeof(BscReportSpans) / sizeof(BscReportSpans[0])) {
                BscReportSpans[BscReportSpanCount].space = CurrentSpace;
                BscReportSpans[BscReportSpanCount].address = before;
                BscReportSpans[BscReportSpanCount].count = value * factor;
                strncpy(BscReportSpans[BscReportSpanCount].section_name,
                        sec_current_name(),
                        sizeof(BscReportSpans[BscReportSpanCount].section_name) - 1UL);
                BscReportSpans[BscReportSpanCount].section_name[
                    sizeof(BscReportSpans[BscReportSpanCount].section_name) - 1UL] = '\0';
                ++BscReportSpanCount;
            }
        }
        ++OutputGeneration;
        return;
    }
}

struct condition_frame {
    int parent_active;
    int active;
    int seen_else;
};

static struct condition_frame Conditions[32];
static int ConditionDepth;
static int ConditionsActive;
static int ScsStack[64];
static int ScsDepth;
static int ScsLabelId;
static int ScsForceMode;
static char ScsAccumulator[16] = "a";
static char ScsStepRegister[16] = "x0";

struct scs_frame {
    int type;
    int first;
    int second;
    int third;
    int fourth;
    int register_loop;
    int descending;
    char variable[64];
    char start[64];
    char limit[64];
    char step[64];
    char accumulator[16];
    char step_register[16];
};

static struct scs_frame ScsFrames[64];

struct scs_condition {
    int binary;
    char left[64];
    char condition[16];
    char right[64];
};

struct scs_lines {
    char **lines;
    int count;
    int size;
};

static void scs_lines_add(struct scs_lines *out, char *text)
{
    char **next;
    int size;

    if (out->count == out->size) {
        size = out->size == 0 ? 16 : out->size * 2;
        next = (char **)realloc(out->lines, (unsigned long)size *
                                sizeof(*out->lines));
        if (next == (char **)0) {
            fprintf(stderr, "asm56000: out of memory\n");
            exit(2);
        }
        out->lines = next;
        out->size = size;
    }
    out->lines[out->count++] = dup_text(text);
}

static void scs_lines_format(struct scs_lines *out, char *format,
                             char *a, char *b, char *c)
{
    char text[256];

    sprintf(text, format, a == (char *)0 ? (char *)"" : a,
            b == (char *)0 ? (char *)"" : b,
            c == (char *)0 ? (char *)"" : c);
    scs_lines_add(out, text);
}

static void scs_label_text(int id, char *text)
{
    sprintf(text, "Z_L%05d", id);
}

static int scs_new_label(void)
{
    return ScsLabelId++;
}

static void scs_emit_label(struct scs_lines *out, int id)
{
    char label[32];

    scs_label_text(id, label);
    scs_lines_add(out, label);
}

static void scs_force_label(int id, char *text)
{
    char label[32];

    scs_label_text(id, label);
    if (ScsForceMode == 1)
        sprintf(text, "<%s", label);
    else if (ScsForceMode == 2)
        sprintf(text, ">%s", label);
    else
        strcpy(text, label);
}

static void scs_emit_jump(struct scs_lines *out, char *mnemonic, int id)
{
    char target[40];

    scs_force_label(id, target);
    scs_lines_format(out, "        %s %s", mnemonic, target, (char *)0);
}

static void scs_emit_plain(struct scs_lines *out, char *text)
{
    char line[256];

    sprintf(line, "        %s", text);
    scs_lines_add(out, line);
}

static char *scs_trim(char *text)
{
    char *end;

    while (*text == ' ' || *text == '\t')
        ++text;
    end = text + strlen(text);
    while (end > text && (end[-1] == ' ' || end[-1] == '\t'))
        --end;
    *end = '\0';
    return text;
}

static char *scs_statement_text(void)
{
    static char text[ASM56000_INPUT_LINE_CAP];
    char *p;
    char *q;

    p = RawLineBuf;
    while (*p == ' ' || *p == '\t')
        ++p;
    if (*p != '\0' && *p != ';') {
        while (*p != '\0' && *p != ' ' && *p != '\t')
            ++p;
    }
    while (*p == ' ' || *p == '\t')
        ++p;
    q = p;
    while (*q != '\0' && *q != ';')
        ++q;
    if ((unsigned long)(q - p) >= sizeof(text))
        q = p + sizeof(text) - 1U;
    memcpy(text, p, (unsigned long)(q - p));
    text[q - p] = '\0';
    return scs_trim(text);
}

static int scs_tokens(char *text, char tokens[][64], int max)
{
    char *p;
    char *q;
    int count;
    unsigned long n;

    count = 0;
    p = text;
    while (*p != '\0' && count < max) {
        while (*p == ' ' || *p == '\t')
            ++p;
        if (*p == '\0')
            break;
        q = p;
        while (*q != '\0' && *q != ' ' && *q != '\t')
            ++q;
        n = (unsigned long)(q - p);
        if (n >= 64UL)
            n = 63UL;
        memcpy(tokens[count], p, n);
        tokens[count][n] = '\0';
        ++count;
        p = q;
    }
    return count;
}

static void scs_lower(char *text)
{
    while (*text != '\0') {
        *text = (char)tolower((unsigned char)*text);
        ++text;
    }
}

static int scs_condition_name(char *token, char *out)
{
    unsigned long n;

    if (token == (char *)0 || token[0] != '<')
        return 0;
    n = (unsigned long)strlen(token);
    if (n < 3UL || token[n - 1UL] != '>')
        return 0;
    if (n - 2UL >= 16UL)
        return 0;
    memcpy(out, token + 1, n - 2UL);
    out[n - 2UL] = '\0';
    scs_lower(out);
    return find_condition(out) != (void *)0;
}

static int scs_parse_conditions(char *text, struct scs_condition *conditions,
                                int *connectors)
{
    char tokens[24][64];
    int n;
    int i;
    int count;
    int has_connector;

    n = scs_tokens(text, tokens, 24);
    while (n > 0 && (strcmp(tokens[n - 1], "then") == 0 ||
                     strcmp(tokens[n - 1], "do") == 0))
        --n;
    count = 0;
    i = 0;
    has_connector = 0;
    while (i < n && count < 8) {
        if (scs_condition_name(tokens[i], conditions[count].condition)) {
            conditions[count].binary = 0;
            conditions[count].left[0] = '\0';
            conditions[count].right[0] = '\0';
            ++count;
            ++i;
        } else {
            if (i + 2 >= n || !scs_condition_name(tokens[i + 1],
                                                    conditions[count].condition))
                return 0;
            conditions[count].binary = 1;
            strcpy(conditions[count].left, tokens[i]);
            strcpy(conditions[count].right, tokens[i + 2]);
            ++count;
            i += 3;
        }
        if (i < n) {
            scs_lower(tokens[i]);
            if (strcmp(tokens[i], "and") == 0)
                connectors[count - 1] = 0;
            else if (strcmp(tokens[i], "or") == 0)
                connectors[count - 1] = 1;
            else
                return 0;
            has_connector = 1;
            ++i;
        }
    }
    (void)has_connector;
    return i == n ? count : 0;
}

static char *scs_inverse_condition(char *condition)
{
    if (strcmp(condition, "cs") == 0) return (char *)"jcc";
    if (strcmp(condition, "cc") == 0) return (char *)"jcs";
    if (strcmp(condition, "eq") == 0) return (char *)"jne";
    if (strcmp(condition, "ne") == 0) return (char *)"jeq";
    if (strcmp(condition, "gt") == 0) return (char *)"jle";
    if (strcmp(condition, "le") == 0) return (char *)"jgt";
    if (strcmp(condition, "ge") == 0) return (char *)"jlt";
    if (strcmp(condition, "lt") == 0) return (char *)"jge";
    if (strcmp(condition, "mi") == 0) return (char *)"jpl";
    if (strcmp(condition, "pl") == 0) return (char *)"jmi";
    if (strcmp(condition, "nr") == 0) return (char *)"jnn";
    if (strcmp(condition, "nn") == 0) return (char *)"jnr";
    return (char *)"jne";
}

static char *scs_positive_condition(char *condition)
{
    if (strcmp(condition, "cs") == 0) return (char *)"jcs";
    if (strcmp(condition, "cc") == 0) return (char *)"jcc";
    if (strcmp(condition, "eq") == 0) return (char *)"jeq";
    if (strcmp(condition, "ne") == 0) return (char *)"jne";
    if (strcmp(condition, "gt") == 0) return (char *)"jgt";
    if (strcmp(condition, "le") == 0) return (char *)"jle";
    if (strcmp(condition, "ge") == 0) return (char *)"jge";
    if (strcmp(condition, "lt") == 0) return (char *)"jlt";
    if (strcmp(condition, "mi") == 0) return (char *)"jmi";
    if (strcmp(condition, "pl") == 0) return (char *)"jpl";
    if (strcmp(condition, "nr") == 0) return (char *)"jnr";
    if (strcmp(condition, "nn") == 0) return (char *)"jnn";
    return (char *)"jeq";
}

static void scs_emit_compare(struct scs_lines *out,
                             struct scs_condition *condition)
{
    char text[192];

    if (!condition->binary)
        return;
    if (strcmp(condition->left, "x0") == 0 &&
        strcmp(condition->right, "a") == 0) {
        scs_emit_plain(out, "move a,y0");
        scs_emit_plain(out, "tfr x0,a      y0,x0");
        scs_emit_plain(out, "cmp x0,a");
        return;
    }
    if (strcmp(condition->left, "a") == 0 ||
        strcmp(condition->left, "b") == 0) {
        if (strcmp(condition->left, "b") == 0 &&
            strcmp(condition->right, "y1") == 0) {
            scs_emit_plain(out, "move b,a");
            scs_emit_plain(out, "move y1,x0");
            scs_emit_plain(out, "cmp x0,a");
            return;
        } else {
            sprintf(text, "move %s,x0", condition->right);
            scs_emit_plain(out, text);
        }
        sprintf(text, "cmp x0,%s", condition->left);
        scs_emit_plain(out, text);
        return;
    }
    sprintf(text, "move %s,a", condition->left);
    scs_emit_plain(out, text);
    sprintf(text, "move %s,x0", condition->right);
    scs_emit_plain(out, text);
    scs_emit_plain(out, "cmp x0,a");
}

static void scs_emit_cond_branch(struct scs_lines *out, char *mnemonic,
                                 int id)
{
    char target[40];

    scs_force_label(id, target);
    scs_lines_format(out, "        %s %s", mnemonic, target, (char *)0);
}

static void scs_push_frame(struct scs_frame *frame)
{
    if (ScsDepth >= (int)(sizeof(ScsFrames) / sizeof(ScsFrames[0])))
        return;
    ScsFrames[ScsDepth] = *frame;
    ScsStack[ScsDepth] = frame->type;
    ++ScsDepth;
}

static int scs_pop_frame(struct scs_frame *frame)
{
    if (ScsDepth == 0)
        return 0;
    --ScsDepth;
    if (frame != (struct scs_frame *)0)
        *frame = ScsFrames[ScsDepth];
    return 1;
}

static int scs_find_loop(int continue_target)
{
    int i;

    for (i = ScsDepth - 1; i >= 0; --i) {
        if (ScsFrames[i].type == 3 || ScsFrames[i].type == 5 ||
            ScsFrames[i].type == 6 || ScsFrames[i].type == 0xb) {
            return continue_target ?
                (ScsFrames[i].type == 6 ? ScsFrames[i].first :
                 ScsFrames[i].type == 0xb ? ScsFrames[i].first :
                 ScsFrames[i].type == 5 ? ScsFrames[i].second :
                 ScsFrames[i].second) :
                (ScsFrames[i].type == 6 ? ScsFrames[i].third :
                 ScsFrames[i].type == 0xb ? ScsFrames[i].first :
                 ScsFrames[i].fourth);
        }
    }
    return -1;
}

static int scs_is_loop(int type)
{
    return type == 3 || type == 5 || type == 6 || type == 0xb;
}

static void scs_error(char *message)
{
    CurInstrFieldMsg = (char *)0;
    err(message);
}

static void scs_error_more(char *message)
{
    CurInstrFieldMsg = (char *)0;
    err(message);
    ErrOnThisLine = 0UL;
}

static void process_scs_directive(void)
{
    struct scs_lines generated;
    struct scs_frame frame;
    struct scs_frame *top;
    struct scs_condition conditions[8];
    int connectors[8];
    int count;
    int i;
    int id;
    int target;
    int has_or;
    int old_end;
    char text[256];
    char tokens[24][64];
    int n;
    int at;
    int to_index;
    int by_index;
    int down;

    generated.lines = (char **)0;
    generated.count = 0;
    generated.size = 0;
    memset(&frame, 0, sizeof(frame));

    if (is_name(MnemField, "scsjmp")) {
        if (Op1Field != (char *)0 &&
            (strstr(Op1Field, "short") != (char *)0 ||
             strstr(Op1Field, "SHORT") != (char *)0))
            ScsForceMode = 1;
        else if (Op1Field != (char *)0 &&
                 (strstr(Op1Field, "long") != (char *)0 ||
                  strstr(Op1Field, "LONG") != (char *)0))
            ScsForceMode = 2;
        else
            ScsForceMode = 0;
        return;
    }
    if (is_name(MnemField, "scsreg")) {
        n = scs_tokens(scs_statement_text(), tokens, 24);
        if (n > 0) {
            char *comma;

            comma = strchr(tokens[0], ',');
            if (comma != (char *)0) {
                *comma = '\0';
                strcpy(ScsStepRegister, tokens[0]);
                strcpy(ScsAccumulator, comma + 1);
                scs_lower(ScsStepRegister);
                scs_lower(ScsAccumulator);
            }
        }
        return;
    }
    if (is_name(MnemField, "if")) {
        count = scs_parse_conditions(scs_statement_text(), conditions,
                                      connectors);
        if (count == 0) {
            scs_new_label();
            scs_new_label();
            scs_error(strstr(scs_statement_text(), "<") != (char *)0 ?
                      "Syntax error - invalid conditional operator" :
                      "Syntax error - invalid condition");
            return;
        }
        frame.type = 4;
        frame.first = scs_new_label();
        frame.second = scs_new_label();
        has_or = 0;
        for (i = 0; i + 1 < count; ++i)
            if (connectors[i]) has_or = 1;
        if (has_or) {
            for (i = 0; i < count; ++i) {
                scs_emit_compare(&generated, &conditions[i]);
                if (i + 1 < count)
                    scs_emit_cond_branch(&generated,
                        scs_positive_condition(conditions[i].condition),
                        frame.first);
                else
                    scs_emit_cond_branch(&generated,
                        scs_inverse_condition(conditions[i].condition),
                        frame.second);
            }
        } else {
            for (i = 0; i < count; ++i) {
                scs_emit_compare(&generated, &conditions[i]);
                scs_emit_cond_branch(&generated,
                    scs_inverse_condition(conditions[i].condition),
                    frame.second);
            }
        }
        scs_emit_label(&generated, frame.first);
        scs_push_frame(&frame);
    } else if (is_name(MnemField, "else")) {
        if (ScsDepth == 0 || ScsStack[ScsDepth - 1] != 4) {
            scs_error(".ELSE without associated .IF statement");
        } else {
            top = &ScsFrames[ScsDepth - 1];
            old_end = top->second;
            top->second = scs_new_label();
            scs_emit_jump(&generated, (char *)"jmp", top->second);
            scs_emit_label(&generated, old_end);
        }
    } else if (is_name(MnemField, "endi")) {
        if (ScsDepth == 0 || ScsStack[ScsDepth - 1] != 4)
            scs_error(".ENDI without associated .IF statement");
        else {
            scs_emit_label(&generated, ScsFrames[ScsDepth - 1].second);
            scs_pop_frame((struct scs_frame *)0);
        }
    } else if (is_name(MnemField, "while")) {
        count = scs_parse_conditions(scs_statement_text(), conditions,
                                      connectors);
        if (count == 0) {
            scs_error("Syntax error - invalid condition");
            return;
        }
        frame.type = 6;
        frame.first = scs_new_label();
        frame.second = scs_new_label();
        frame.third = scs_new_label();
        scs_emit_label(&generated, frame.first);
        for (i = 0; i < count; ++i) {
            scs_emit_compare(&generated, &conditions[i]);
                scs_emit_cond_branch(&generated,
                    scs_inverse_condition(conditions[i].condition), frame.third);
        }
        scs_emit_label(&generated, frame.second);
        scs_push_frame(&frame);
    } else if (is_name(MnemField, "endw")) {
        if (ScsDepth == 0 || ScsStack[ScsDepth - 1] != 6)
            scs_error(".ENDW without associated .WHILE statement");
        else {
            scs_emit_jump(&generated, (char *)"jmp", ScsFrames[ScsDepth - 1].first);
            scs_emit_label(&generated, ScsFrames[ScsDepth - 1].third);
            scs_pop_frame((struct scs_frame *)0);
        }
    } else if (is_name(MnemField, "repeat")) {
        frame.type = 0xb;
        frame.first = scs_new_label();
        frame.third = scs_new_label();
        frame.second = scs_new_label();
        scs_emit_label(&generated, frame.first);
        scs_push_frame(&frame);
    } else if (is_name(MnemField, "until")) {
        if (ScsDepth == 0 || ScsStack[ScsDepth - 1] != 0xb) {
            scs_error(".UNTIL without associated .REPEAT statement");
        } else {
            count = scs_parse_conditions(scs_statement_text(), conditions,
                                          connectors);
            if (count == 0) {
                scs_error("Syntax error - invalid condition");
            } else {
                top = &ScsFrames[ScsDepth - 1];
                scs_emit_label(&generated, top->second);
                for (i = 0; i < count; ++i) {
                    scs_emit_compare(&generated, &conditions[i]);
                    scs_emit_cond_branch(&generated,
                        scs_inverse_condition(conditions[i].condition),
                        top->first);
                }
                scs_emit_label(&generated, top->third);
                scs_pop_frame((struct scs_frame *)0);
            }
        }
    } else if (is_name(MnemField, "for")) {
        n = scs_tokens(scs_statement_text(), tokens, 24);
        to_index = -1;
        by_index = -1;
        down = 0;
        for (i = 0; i < n; ++i) {
            scs_lower(tokens[i]);
            if (strcmp(tokens[i], "to") == 0) to_index = i;
            if (strcmp(tokens[i], "downto") == 0) {
                to_index = i;
                down = 1;
            }
            if (strcmp(tokens[i], "by") == 0) by_index = i;
        }
        if (n < 4 || to_index < 3 || to_index + 1 >= n) {
            scs_new_label();
            scs_new_label();
            scs_new_label();
            scs_new_label();
            if (to_index < 0)
                scs_error("Syntax error - expected keyword TO or DOWNTO");
            else if (n >= 3 && strcmp(tokens[1], "=") != 0) {
                scs_error("Syntax error - invalid assignment operator");
                ErrOnThisLine = 0UL;
                CurInstrFieldMsg = (char *)0;
                if (AbsoluteMode) {
                    err_s("Symbol undefined on pass 2", tokens[2]);
                    ErrOnThisLine = 0UL;
                }
                scs_error_more("Syntax error - expected keyword TO or DOWNTO");
                scs_error_more("Syntax error - missing address mode specifier");
                scs_error("Possible invalid white space between operands or arguments");
            } else if (to_index + 1 >= n) {
                scs_error("Syntax error - missing address mode specifier");
                ErrOnThisLine = 0UL;
                scs_error("Possible invalid white space between operands or arguments");
            } else
                scs_error("Syntax error - invalid FOR statement");
            return;
        }
        strcpy(frame.variable, tokens[0]);
        strcpy(frame.start, tokens[2]);
        strcpy(frame.limit, tokens[to_index + 1]);
        if (by_index >= 0 && by_index + 1 < n) {
            strcpy(frame.step, tokens[by_index + 1]);
            frame.register_loop = 1;
        } else {
            strcpy(frame.step, "#>1");
            frame.register_loop = 0;
        }
        frame.type = 3;
        frame.descending = down;
        strcpy(frame.accumulator, ScsAccumulator);
        strcpy(frame.step_register, ScsStepRegister);
        frame.first = scs_new_label();
        frame.second = scs_new_label();
        frame.third = scs_new_label();
        frame.fourth = scs_new_label();
        sprintf(text, "move %s,%s", frame.start, frame.accumulator);
        scs_emit_plain(&generated, text);
        sprintf(text, "move %s,%s", frame.accumulator, frame.variable);
        scs_emit_plain(&generated, text);
        sprintf(text, "move %s,y0", frame.limit);
        scs_emit_plain(&generated, text);
        sprintf(text, "move %s,%s", frame.step, frame.step_register);
        scs_emit_plain(&generated, text);
        scs_emit_jump(&generated, (char *)"jmp", frame.third);
        scs_emit_label(&generated, frame.first);
        scs_push_frame(&frame);
    } else if (is_name(MnemField, "endf")) {
        if (ScsDepth == 0 || ScsStack[ScsDepth - 1] != 3)
            scs_error(".ENDF without associated .FOR statement");
        else {
            top = &ScsFrames[ScsDepth - 1];
            scs_emit_label(&generated, top->second);
            sprintf(text, "move %s,%s", top->variable, top->accumulator);
            scs_emit_plain(&generated, text);
            sprintf(text, "%s %s,%s", top->descending ? "sub" : "add",
                    top->step_register, top->accumulator);
            scs_emit_plain(&generated, text);
            sprintf(text, "move %s,%s", top->accumulator, top->variable);
            scs_emit_plain(&generated, text);
            scs_emit_label(&generated, top->third);
            sprintf(text, "cmp y0,%s", top->accumulator);
            scs_emit_plain(&generated, text);
            scs_emit_jump(&generated, top->descending ? (char *)"jge" :
                          (char *)"jle", top->first);
            scs_emit_label(&generated, top->fourth);
            scs_pop_frame((struct scs_frame *)0);
        }
    } else if (is_name(MnemField, "loop")) {
        n = scs_tokens(scs_statement_text(), tokens, 24);
        if (n == 0) {
            scs_error("Syntax error - invalid LOOP statement");
            return;
        }
        frame.type = 5;
        frame.fourth = scs_new_label();
        frame.register_loop = tokens[0][0] != '#';
        frame.second = frame.register_loop ? scs_new_label() : frame.fourth;
        scs_label_text(frame.fourth, text);
        {
            char line[256];
            sprintf(line, "        do %s,%s", tokens[0], text);
            scs_lines_add(&generated, line);
        }
        scs_push_frame(&frame);
    } else if (is_name(MnemField, "endl")) {
        if (ScsDepth == 0 || ScsStack[ScsDepth - 1] != 5)
            scs_error(".ENDL without associated .LOOP statement");
        else {
            top = &ScsFrames[ScsDepth - 1];
            if (top->register_loop)
                scs_emit_label(&generated, top->second);
            if (top->register_loop)
                scs_emit_plain(&generated, "nop");
            scs_emit_label(&generated, top->fourth);
            scs_pop_frame((struct scs_frame *)0);
        }
    } else if (is_name(MnemField, "break")) {
        target = scs_find_loop(0);
        if (target < 0)
            scs_error(".BREAK without associated loop");
        else {
            if (ScsDepth != 0 && ScsFrames[ScsDepth - 1].type == 5 &&
                ScsFrames[ScsDepth - 1].register_loop)
                scs_emit_plain(&generated, "enddo");
            scs_emit_jump(&generated, (char *)"jmp", target);
        }
    } else if (is_name(MnemField, "continue")) {
        target = scs_find_loop(1);
        if (target < 0)
            scs_error(".CONTINUE without associated loop");
        else
            scs_emit_jump(&generated, (char *)"jmp", target);
    }
    if (generated.count != 0)
        input_push_lines(generated.lines, generated.count);
    else
        free(generated.lines);
}

static int space_from_text(char *text)
{
    char key[32];
    char *p;
    char *q;

    if (text == (char *)0)
        return 0;
    p = text;
    while (*p == ' ' || *p == '\t')
        ++p;
    q = key;
    while (*p != '\0' && *p != ':' && *p != ',') {
        if ((q - key) < 31)
            *q++ = (char)tolower((unsigned char)*p);
        ++p;
    }
    *q = '\0';
    if (strcmp(key, "pe") == 0)
        return 13;
    if (strcmp(key, "pi") == 0)
        return 14;
    if (strcmp(key, "pr") == 0)
        return 15;
    if (strcmp(key, "xe") == 0)
        return 18;
    if (strcmp(key, "xi") == 0)
        return 19;
    if (strcmp(key, "xr") == 0)
        return 20;
    if (strcmp(key, "ye") == 0)
        return 23;
    if (strcmp(key, "yi") == 0)
        return 24;
    if (strcmp(key, "yr") == 0)
        return 25;
    if (strcmp(key, "le") == 0)
        return 9;
    if (strcmp(key, "li") == 0)
        return 10;
    if (key[0] == 'x')
        return 1;
    if (key[0] == 'y')
        return 2;
    if (key[0] == 'l')
        return 3;
    return 0;
}

static int text_equal_ci(char *a, char *b)
{
    while (*a != '\0' && *b != '\0') {
        if (tolower((unsigned char)*a++) != tolower((unsigned char)*b++))
            return 0;
    }
    return *a == '\0' && *b == '\0';
}

static char *source_define_value(char *name)
{
    int i;

    for (i = 0; i < SourceDefineCount; ++i)
        if (text_equal_ci(SourceDefineNames[i], name))
            return SourceDefineValues[i];
    return (char *)0;
}

static void source_define_set(char *name, char *value)
{
    char normalized[256];
    unsigned long length;
    int i;

    if (name == (char *)0 || value == (char *)0 || *name == '\0')
        return;
    sym_hide_name(name);
    length = (unsigned long)strlen(value);
    if (length >= sizeof(normalized))
        length = sizeof(normalized) - 1UL;
    if (length >= 2UL &&
        ((value[0] == '\'' && value[length - 1UL] == '\'') ||
         (value[0] == '"' && value[length - 1UL] == '"'))) {
        --length;
        memcpy(normalized, value + 1, length - 1UL);
        normalized[length - 1UL] = '\0';
    } else {
        memcpy(normalized, value, length);
        normalized[length] = '\0';
    }
    for (i = 0; i < SourceDefineCount; ++i) {
        if (text_equal_ci(SourceDefineNames[i], name)) {
            SourceDefineValues[i] = dup_text(normalized);
            return;
        }
    }
    if (SourceDefineCount >= 64)
        return;
    SourceDefineNames[SourceDefineCount] = dup_text(name);
    SourceDefineValues[SourceDefineCount] = dup_text(normalized);
    ++SourceDefineCount;
}

static void source_define_remove(char *name)
{
    int i;

    for (i = 0; i < SourceDefineCount; ++i) {
        if (!text_equal_ci(SourceDefineNames[i], name))
            continue;
        SourceDefineNames[i] = SourceDefineNames[SourceDefineCount - 1];
        SourceDefineValues[i] = SourceDefineValues[SourceDefineCount - 1];
        --SourceDefineCount;
        return;
    }
}

static int source_define_is_def_call(char *out, unsigned long length)
{
    if (length < 5UL)
        return 0;
    return tolower((unsigned char)out[length - 5UL]) == '@' &&
           tolower((unsigned char)out[length - 4UL]) == 'd' &&
           tolower((unsigned char)out[length - 3UL]) == 'e' &&
           tolower((unsigned char)out[length - 2UL]) == 'f' &&
           out[length - 1UL] == '(';
}

static void expand_source_defines(void)
{
    char expanded[ASM56000_INPUT_LINE_CAP * 2];
    char *mnem;
    char *tail;
    char *value;
    char token[128];
    unsigned long in;
    unsigned long out;
    unsigned long start;
    unsigned long n;
    int quote;

    if (SourceDefineCount == 0 || MnemField == (char *)0 ||
        *MnemField == '\0' || is_name(MnemField, "define") ||
        is_name(MnemField, "undef"))
        return;
    mnem = strstr(RawLineBuf, MnemField);
    if (mnem == (char *)0)
        return;
    tail = mnem + strlen(MnemField);
    out = (unsigned long)(tail - RawLineBuf);
    if (out >= sizeof(expanded))
        return;
    memcpy(expanded, RawLineBuf, out);
    in = out;
    while (RawLineBuf[in] != '\0' && out + 1UL < sizeof(expanded)) {
        if (RawLineBuf[in] == '\'' || RawLineBuf[in] == '"') {
            quote = (unsigned char)RawLineBuf[in++];
            expanded[out++] = (char)quote;
            while (RawLineBuf[in] != '\0' && out + 1UL < sizeof(expanded)) {
                expanded[out++] = RawLineBuf[in];
                if (RawLineBuf[in++] == quote)
                    break;
            }
            continue;
        }
        if (isalpha((unsigned char)RawLineBuf[in]) ||
            RawLineBuf[in] == '_' || RawLineBuf[in] == '.') {
            start = in++;
            while (isalnum((unsigned char)RawLineBuf[in]) ||
                   RawLineBuf[in] == '_' || RawLineBuf[in] == '.')
                ++in;
            n = in - start;
            if (n >= sizeof(token))
                n = sizeof(token) - 1UL;
            memcpy(token, RawLineBuf + start, n);
            token[n] = '\0';
            value = source_define_is_def_call(expanded, out) ?
                    (char *)0 : source_define_value(token);
            if (value != (char *)0) {
                n = (unsigned long)strlen(value);
                if (out + n + 1UL >= sizeof(expanded))
                    n = sizeof(expanded) - out - 2UL;
                memcpy(expanded + out, value, n);
                out += n;
            } else {
                if (out + (in - start) + 1UL >= sizeof(expanded))
                    break;
                memcpy(expanded + out, RawLineBuf + start, in - start);
                out += in - start;
            }
            continue;
        }
        expanded[out++] = RawLineBuf[in++];
    }
    expanded[out] = '\0';
    strcpy(RawLineBuf, expanded);
}

static void prepare_source_line(void)
{
    if (!parse_line())
        return;
    if (!ConditionsActive)
        return;
    expand_source_defines();
}

static void space_extent(int space, unsigned long address,
                         unsigned long count)
{
    unsigned long end;

    if (Pass != 2UL || space < 0 || space >= 32 || count == 0UL)
        return;
    end = address + count - 1UL;
    if (!SpaceUsed[space]) {
        SpaceMin[space] = address;
        SpaceMax[space] = end;
        SpaceUsed[space] = 1;
    } else {
        if (address < SpaceMin[space])
            SpaceMin[space] = address;
        if (end > SpaceMax[space])
            SpaceMax[space] = end;
    }
}

static unsigned long run_timestamp(void)
{
    char *text;
    unsigned long value;

    text = getenv("SOURCE_DATE_EPOCH");
    if (text != (char *)0 && *text != '\0') {
        value = strtoul(text, (char **)0, 10);
        return value;
    }
    return (unsigned long)time((time_t *)0);
}

static unsigned long object_timestamp(void)
{
    char *text;

    text = getenv("SOURCE_DATE_EPOCH");
    if (text != (char *)0 && *text != '\0')
        return run_timestamp() + 7200UL;
    return run_timestamp();
}

static void list_newline(void)
{
    if (ListingNoBreak)
        return;
    if (ListingIsStdout)
        fputc('\n', Listing);
    else
        fputs("\r\n", Listing);
    if (!InListingHeader)
        ++ListingSourceLines;
}

void listing_count_external_line(void)
{
    ++ListingSourceLines;
}

static void list_header(void)
{
    time_t stamp;
    struct tm *tmv;
    char date[32];
    char clock_text[32];
    char *base;
    char *slash;
    char *backslash;
    int i;
    int j;
    int used;

    if (Listing == (FILE *)0 || ListingHeaderWritten)
        return;
    InListingHeader = 1;
    if (ListingPage == 1 && ListingIndent != 0) {
        list_newline();
        list_newline();
    }
    stamp = (time_t)run_timestamp();
    tmv = localtime(&stamp);
    if (tmv == (struct tm *)0) {
        strcpy(date, "00-00-00");
        strcpy(clock_text, "00:00:00");
    } else {
        sprintf(date, "%02d-%02d-%02d", tmv->tm_year,
                tmv->tm_mon + 1, tmv->tm_mday);
        sprintf(clock_text, "%02d:%02d:%02d", tmv->tm_hour,
                tmv->tm_min, tmv->tm_sec);
    }
    base = SourceName;
    slash = strrchr(base, '/');
    backslash = strrchr(base, '\\');
    if (slash != (char *)0 && slash + 1 > base)
        base = slash + 1;
    if (backslash != (char *)0 && backslash + 1 > base)
        base = backslash + 1;
    for (i = 0; i < ListingIndent; ++i)
        fputc(' ', Listing);
    used = ListingIndent + fprintf(Listing,
            "Motorola DSP56000 Assembler  Version 6.3.0   %s  %s  %s",
            date, clock_text, base);
    if (ListingPage > 1 && ListingIndent != 0 && !ReportHeaderMode) {
        /* The page number is appended to the first header line. */
        fprintf(Listing, "  Page %d", ListingPage);
        list_newline();
    } else {
        char pagetxt[32];
        int plen;

        /* list_token (FUN_0041d11c) wraps a token that no longer fits. */
        sprintf(pagetxt, "  Page %d", ListingPage);
        plen = (int)strlen(pagetxt);
        if (plen <= ListingWidth - ListingIndent + 1 &&
            ListingWidth < plen + used + 1) {
            list_newline();
            for (i = 0; i < ListingIndent; ++i)
                fputc(' ', Listing);
        }
        fputs(pagetxt, Listing);
        list_newline();
    }
    if (ListingHeaderTitle[0] != '\0') {
        for (i = 0; i < ListingIndent; ++i)
            fputc(' ', Listing);
        fputs(ListingHeaderTitle, Listing);
        list_newline();
    }
    if (ListingHeaderSubtitle[0] != '\0') {
        for (i = 0; i < ListingIndent; ++i)
            fputc(' ', Listing);
        fputs(ListingHeaderSubtitle, Listing);
        list_newline();
    }
    for (i = 0; i < (ListingHeaderTitle[0] != '\0' ||
                     ListingHeaderSubtitle[0] != '\0' ? 1 : 3); ++i) {
        for (j = 0; j < ListingIndent; ++j)
            fputc(' ', Listing);
        list_newline();
    }
    if (ListingNoBreakEver && OptMex && ListingPage == 3) {
        for (j = 0; j < ListingIndent; ++j)
            fputc(' ', Listing);
        list_newline();
    }
    InListingHeader = 0;
    ListingHeaderWritten = 1;
    strcpy(ListingHeaderTitle, ListingTitle);
    strcpy(ListingHeaderSubtitle, ListingSubtitle);
    ReportHeaderMode = 0;
}

static void list_prepare_line(void)
{
    int body_limit;
    int header_lines;
    int i;
    int first_fill;
    int break_limit;

    if (Listing == (FILE *)0)
        return;
    header_lines = ListingHeaderTitle[0] != '\0' ||
                   ListingHeaderSubtitle[0] != '\0' ?
                   4 : 5;
    body_limit = ListingPageLength > header_lines ?
                 ListingPageLength - header_lines : 0;
    if (ListingPagePending == 1 && body_limit > 0)
        --body_limit;
    break_limit = body_limit;
    if (ListingNoBreakEver && OptMex && ListingPageLength == 20 &&
        ListingPage >= 25 && break_limit > 6)
        break_limit -= 6;
    if (ListingHeaderWritten && ListingPagePending != 0 &&
        ListingPageLength != 0 &&
        (ListingPagePending == 1 ||
         (OptMex && ListingSourceLines >= (unsigned long)(body_limit > 5 ?
                                                          body_limit - 5 : 0)))) {
        first_fill = 1;
        while (ListingSourceLines < (unsigned long)body_limit) {
            if (first_fill && ListingPagePending == 1) {
                for (i = 0; i < ListingIndent; ++i)
                    fputc(' ', Listing);
                first_fill = 0;
            }
            list_newline();
        }
        if (ListingPagePending == 1 && ListingPage == 1)
            ListingPagePending = 2;
        else
            ListingPagePending = 0;
        ListingHeaderWritten = 0;
        ++ListingPage;
        ListingSourceLines = 0UL;
    }
    if (!ListingAllowOverrun && ListingHeaderWritten && !ListingNoBreak &&
        (!ListingNoBreakEver || OptMex) &&
        ListingPageLength != 0 &&
        ListingSourceLines >= (unsigned long)break_limit) {
        if (ListingNoBreakEver && OptMex && ListingPageLength == 20) {
            int fill_limit;

            fill_limit = body_limit;
            if (ListingPage == 24)
                fill_limit += 6;
            else if (fill_limit > 0)
                --fill_limit;
            while (ListingSourceLines < (unsigned long)fill_limit)
                list_newline();
        }
        if (ListingNoBreakEver && OptMex && ListingPage == 2)
            list_newline();
        ListingHeaderWritten = 0;
        ReportHeaderMode = ListingNoBreakEver && OptMex;
        ++ListingPage;
        ListingSourceLines = 0UL;
    }
    list_header();
    for (i = 0; i < ListingIndent; ++i)
        fputc(' ', Listing);
    if (PendingPrctlLength != 0) {
        fwrite(PendingPrctl, 1, (unsigned long)PendingPrctlLength, Listing);
        PendingPrctlLength = 0;
    }
}

void listing_prepare_diagnostic(void)
{
    list_prepare_line();
}

static void listing_begin_pass2(void)
{
    /* The first source line is listed before the first PAGE directive takes
       effect.  Restore the persistent indentation, but start width and page
       length at the assembler defaults. */
    ListingWidth = 80;
    ListingPageLength = 66;
    ListingIndent = ListingSavedIndent;
    ListingLabelWidth = 10;
    ListingOpcodeWidth = 8;
    ListingOperandWidth = 10;
    ListingXWidth = 12;
    ListingYWidth = 12;
    ListingHeaderWritten = 0;
    ListingPage = 1;
    ListingSourceLines = 0UL;
    ListingPagePending = 0;
    ListingNoBreak = 0;
    ListingNoBreakEver = 0;
    ListingEnabled = 1;
    ListingTitle[0] = '\0';
    ListingSubtitle[0] = '\0';
    ListingHeaderTitle[0] = '\0';
    ListingHeaderSubtitle[0] = '\0';
    PendingPrctlLength = 0;
    ListingLayoutReady = 0;
}

static void list_text_line(char *text, int start_column)
{
    unsigned long n;
    unsigned long start;
    unsigned long width;
    int limit;

    if (Listing == (FILE *)0)
        return;
    if (text == (char *)0)
        text = (char *)"";
    limit = ListingWidth - ListingIndent;
    if (limit < 1)
        limit = 1;
    n = (unsigned long)strlen(text);
    start = 0UL;
    while (start < n) {
        unsigned long end;
        width = start == 0UL && start_column < limit ?
                (unsigned long)(limit - start_column) :
                (unsigned long)limit;
        end = start + width;
        if (end > n)
            end = n;
        fwrite(text + start, 1, end - start, Listing);
        list_newline();
        start = end;
        if (start < n && !ListingNoBreak) {
            unsigned long k;

            if (ListingNoBreakEver && OptMex)
                list_prepare_line();
            else
                for (k = 0UL; k < (unsigned long)ListingIndent; ++k)
                    fputc(' ', Listing);
        }
    }
    if (n == 0UL)
        list_newline();
}

static char *source_comment(void)
{
    char *p;
    char quote;

    p = RawLineBuf;
    quote = '\0';
    while (*p != '\0') {
        if (quote != '\0') {
            if (*p == quote)
                quote = '\0';
        } else if (*p == '\'' || *p == '"') {
            quote = *p;
        } else if (*p == ';') {
            return p;
        }
        ++p;
    }
    return (char *)0;
}

static void list_trailing_comment(int *column)
{
    char *comment;
    int target;
    int i;

    comment = source_comment();
    if (comment == (char *)0)
        return;
    if (ListingSeparateComments && InLineReplay)
        return;
    if (ListingSeparateComments) {
        strncpy(SeparateComment, comment, sizeof(SeparateComment) - 1U);
        SeparateComment[sizeof(SeparateComment) - 1U] = '\0';
        SeparateCommentPending = 1;
        *column = 1;
        return;
    }
    target = 43 + ListingOperandWidth + ListingXWidth + ListingYWidth;
    if (target > ListingWidth - ListingIndent)
        target = ListingWidth - ListingIndent;
    while (*column < target) {
        fputc(' ', Listing);
        ++*column;
    }
    if (*column >= ListingWidth - ListingIndent) {
        list_newline();
        if (ListingNoBreakEver && OptMex) {
            list_prepare_line();
            fputc(' ', Listing);
        } else {
            for (i = 0; i < ListingIndent + 1; ++i)
                fputc(' ', Listing);
        }
        list_text_line(comment, 0);
        *column = 0;
        return;
    }
    list_text_line(comment, *column);
    *column = 0;
}

static void list_emit_pending_comment(void)
{
    int column;

    if (!SeparateCommentPending)
        return;
    list_prepare_line();
    column = ListingIndent;
    while (column < 35 + ListingIndent) {
        fputc(' ', Listing);
        ++column;
    }
    list_text_line(SeparateComment, column);
    SeparateCommentPending = 0;
}

static void list_emit_pending_comment_current(int *column)
{
    if (!SeparateCommentPending)
        return;
    while (*column < 35 + ListingIndent) {
        fputc(' ', Listing);
        ++*column;
    }
    fputs(SeparateComment, Listing);
    *column += (int)strlen(SeparateComment);
    SeparateCommentPending = 0;
}

static int line_digits(void)
{
    return LineNo < 10UL ? 1 : LineNo < 100UL ? 2 :
           LineNo < 1000UL ? 3 : LineNo < 10000UL ? 4 : 5;
}

static void usage(void)
{
    fprintf(stderr, "Usage: asm56000 [-a] [-b[objfile]] [-l[lstfile]] "
                    "[-dname value] [-i path] [-m path] [-o opt,...] "
                    "source.asm ...\n");
    exit(2);
}

static void illegal_option(char option, char *argument)
{
    if (option == 'O' && argument != (char *)0 && *argument != '\0')
        printf("ASM56000: Illegal command line -%c option: %s\n",
               option, argument);
    else if (argument != (char *)0 && *argument != '\0')
        printf("ASM56000: Illegal command line -%c option argument: %s\n",
               option, argument);
    else
        printf("asm56000: Illegal command line -%c option\n", option);
    exit(-1);
}

static void missing_option_argument(char option)
{
    printf("ASM56000: Missing command line option argument: -%c\n", option);
    exit(-1);
}

static char *dup_text(char *text)
{
    unsigned long n;
    char *copy;

    n = (unsigned long)strlen(text);
    copy = (char *)malloc(n + 1UL);
    if (copy == (char *)0) {
        fprintf(stderr, "asm56000: out of memory\n");
        exit(2);
    }
    memcpy(copy, text, n + 1UL);
    return copy;
}

static char *DataReloc;
static int DataRelocArmed;

static void record_word(unsigned long word, int index)
{
    unsigned long address;
    char *reloc;

    if (Pass != 2UL)
        return;
    if (RecordCount == RecordSize) {
        unsigned long next_size;
        struct word_record *next;

        next_size = RecordSize == 0UL ? 256UL : RecordSize * 2UL;
        next = (struct word_record *)realloc(Records,
                                             next_size * sizeof(*Records));
        if (next == (struct word_record *)0) {
            fprintf(stderr, "asm56000: out of memory\n");
            exit(2);
        }
        Records = next;
        RecordSize = next_size;
    }
    address = (LoadPhysical || ProgramCounter != LoadCounter) ?
              LoadCounter : ProgramCounter;
    Records[RecordCount].address = address + (unsigned long)index;
    Records[RecordCount].runtime_address =
        ProgramCounter + (unsigned long)index;
    Records[RecordCount].word = (word |
        (RecordingInstruction && cex_enabled() ?
         0x200000UL : 0UL)) & 0xffffffUL;
    Records[RecordCount].source_line = LineNo;
    Records[RecordCount].space = CurrentLoadSpace;
    Records[RecordCount].seq = obj_next_seq();
    reloc = asm56000_emit_reloc();
    if (reloc == (char *)0 && DataRelocArmed)
        reloc = DataReloc;
    Records[RecordCount].reloc = reloc == (char *)0 ? (char *)0 :
                                 dup_text(reloc);
    if (getenv("ASM_DBG_RELOC") != (char *)0 && reloc != (char *)0)
        fprintf(stderr, "RELOC %lu %lX %s\n", LineNo, address + (unsigned long)index, reloc);
    space_extent(CurrentLoadSpace, Records[RecordCount].address, 1UL);
    if (SegmentCount != 0UL &&
        RawSegments[SegmentCount - 1UL].space == CurrentLoadSpace &&
        RawSegments[SegmentCount - 1UL].generation == RecordGeneration &&
        RawSegments[SegmentCount - 1UL].count != 0UL &&
        RawSegments[SegmentCount - 1UL].address +
        RawSegments[SegmentCount - 1UL].count == Records[RecordCount].address) {
        ++RawSegments[SegmentCount - 1UL].count;
    } else {
        if (SegmentCount == SegmentSize) {
            unsigned long next_size;
            struct raw_segment *next_segments;

            next_size = SegmentSize == 0UL ? 64UL : SegmentSize * 2UL;
            next_segments = (struct raw_segment *)realloc(
                RawSegments, next_size * sizeof(*RawSegments));
            if (next_segments == (struct raw_segment *)0) {
                fprintf(stderr, "asm56000: out of memory\n");
                exit(2);
            }
            RawSegments = next_segments;
            SegmentSize = next_size;
        }
        RawSegments[SegmentCount].address = Records[RecordCount].address;
        RawSegments[SegmentCount].runtime_address =
            Records[RecordCount].runtime_address;
        RawSegments[SegmentCount].count = 1UL;
        RawSegments[SegmentCount].first_record = RecordCount;
        RawSegments[SegmentCount].generation = RecordGeneration;
        RawSegments[SegmentCount].space = CurrentLoadSpace;
        ++SegmentCount;
    }
    ++RecordCount;
}

static void add_zero_segment(unsigned long address, int space)
{
    unsigned long next_size;
    struct raw_segment *next_segments;

    if (Pass != 2UL)
        return;
    if (SegmentCount == SegmentSize) {
        next_size = SegmentSize == 0UL ? 64UL : SegmentSize * 2UL;
        next_segments = (struct raw_segment *)realloc(
            RawSegments, next_size * sizeof(*RawSegments));
        if (next_segments == (struct raw_segment *)0) {
            fprintf(stderr, "asm56000: out of memory\n");
            exit(2);
        }
        RawSegments = next_segments;
        SegmentSize = next_size;
    }
    RawSegments[SegmentCount].address = address;
    RawSegments[SegmentCount].runtime_address = address;
    RawSegments[SegmentCount].count = 0UL;
    RawSegments[SegmentCount].first_record = RecordCount;
    RawSegments[SegmentCount].generation = RecordGeneration;
    RawSegments[SegmentCount].space = space;
    ++SegmentCount;
}

static int parse_lcv_value(char *text, unsigned long *result,
                           int *has_second)
{
    char inner[64];
    char first[16];
    char second[16];
    char *p;
    char *q;
    char *comma;
    int n;
    int i;

    if (text == (char *)0 || result == (unsigned long *)0)
        return 0;
    p = text;
    while (*p == ' ' || *p == '\t')
        ++p;
    if (tolower((unsigned char)p[0]) != '@' ||
        tolower((unsigned char)p[1]) != 'l' ||
        tolower((unsigned char)p[2]) != 'c' ||
        tolower((unsigned char)p[3]) != 'v' || p[4] != '(')
        return 0;
    q = strchr(p + 5, ')');
    if (q == (char *)0)
        return 0;
    if (q[1] != '\0' && q[1] != ' ' && q[1] != '\t')
        return 0;
    n = (int)(q - (p + 5));
    if (n <= 0 || n >= (int)sizeof(inner))
        return 0;
    memcpy(inner, p + 5, (unsigned long)n);
    inner[n] = '\0';
    comma = strchr(inner, ',');
    if (comma == (char *)0) {
        strcpy(first, inner);
        second[0] = '\0';
    } else {
        *comma = '\0';
        strcpy(first, inner);
        strcpy(second, comma + 1);
    }
    for (i = 0; first[i] != '\0'; ++i)
        first[i] = (char)tolower((unsigned char)first[i]);
    for (i = 0; second[i] != '\0'; ++i)
        second[i] = (char)tolower((unsigned char)second[i]);
    if (has_second != (int *)0)
        *has_second = second[0] != '\0';
    if (second[0] == '\0') {
        if (first[0] == 'r')
            *result = ProgramCounter;
        else if (first[0] == 'l')
            *result = LoadCounter;
        else
            return 0;
        return 1;
    }
    if (second[0] == 'l') {
        if (first[0] == 'r')
            n = org_key_index((char *)"p(1)");
        else if (first[0] == 'l')
            n = load_org_key_index((char *)"p(1)");
        else
            return 0;
        *result = first[0] == 'r' ? OrgValues[n] : LoadOrgValues[n];
        return 1;
    }
    if (second[0] == 'h') {
        n = load_org_key_index((char *)"ph");
        *result = LoadOrgValues[n];
        return 1;
    }
    return 0;
}

static void maybe_add_lcv_section(char *text)
{
    unsigned long value;
    int has_second;

    if (!parse_lcv_value(text, &value, &has_second))
        return;
    if (has_second || ProgramCounter != LoadCounter)
        add_zero_segment(has_second ? value : LoadCounter, CurrentLoadSpace);
}

static unsigned long parse_expr_value(char *text)
{
    void *value;
    unsigned long result;
    int builtin;

    free(DataReloc);
    DataReloc = (char *)0;
    if (parse_lcv_value(text, &result, (int *)0))
        return result;
    result = macro_eval_builtin(text, &builtin);
    if (builtin)
        return result;

    value = eval_expr_text(text);
    if (value != (void *)0 && Pass == 2UL && !AbsoluteMode &&
        expr_is_reloc(value) && eval_reloc_text() != (char *)0)
        DataReloc = dup_text(eval_reloc_text());
    if (value == (void *)0) {
        char function_name[64];
        char *p;
        char *q;
        unsigned long n;

        if (Pass == 2UL) {
            CurInstrFieldMsg = Op1Field;
            switch (expr_last_error()) {
            case 1:
                err("Symbols must start with alphabetic character");
                break;
            case 2:
                err("Extra fields ignored");
                ErrOnThisLine = 0UL;
                err("Possible invalid white space between operands or arguments");
                break;
            case 3:
                err("Missing ')' in expression");
                break;
            case 4:
                p = text == (char *)0 ? (char *)"" : text;
                while (*p != '\0' && *p != '@')
                    ++p;
                if (*p == '@')
                    ++p;
                q = p;
                while (isalpha((unsigned char)*q))
                    ++q;
                n = (unsigned long)(q - p);
                if (n >= sizeof(function_name))
                    n = sizeof(function_name) - 1UL;
                memcpy(function_name, p, n);
                function_name[n] = '\0';
                err_s("Invalid function name", function_name);
                break;
            case 5:
                err("Illegal operator for floating point element");
                break;
            case 6:
                err("Expression involves incompatible memory spaces");
                break;
            default:
                if (text != (char *)0 && *text != '\0') {
                    char *end_text;

                    end_text = text + strlen(text);
                    while (end_text > text &&
                           isspace((unsigned char)end_text[-1]))
                        --end_text;
                    if (end_text > text &&
                        strchr("+-*/&|^", end_text[-1]) != (char *)0) {
                        err("Symbols must start with alphabetic character");
                        break;
                    }
                }
                err("Missing expression");
                break;
            }
        }
        return 0UL;
    }
    if (Pass == 2UL && expr_is_unresolved(value)) {
        int compound;
        char *unresolved_name;

        compound = strchr(text, '+') != (char *)0 ||
                   strchr(text, '-') != (char *)0 ||
                   strchr(text, '*') != (char *)0 ||
                   strchr(text, '/') != (char *)0 ||
                   strchr(text, '&') != (char *)0 ||
                   strchr(text, '|') != (char *)0 ||
                   strchr(text, '^') != (char *)0;
        unresolved_name = expr_unresolved_name(text);
        if (unresolved_name != (char *)0 &&
            strncmp(unresolved_name, "Z_L", 3) == 0) {
            /* Structured-control expansion can leave its exit label open
               until the matching directive (or EOF) is consumed. */
        } else if (!AbsoluteMode) {
            /* Undefined symbols are external references in relocatable
               mode; the linker resolves them. */
        } else if (RecordingInstruction)
        {
            CurInstrFieldMsg = Op1Field;
            err_s("Symbol undefined on pass 2", unresolved_name);
            fatal("Forward reference sequence failure");
        } else if (AbsoluteMode || compound) {
            CurInstrFieldMsg = Op1Field;
            err_s("Symbol undefined on pass 2", unresolved_name);
            if (compound)
                fatal("Forward reference sequence failure");
        }
    }
    result = expr_as_int32(value);
    free_expr(value);
    return result;
}

static int split_csv(char *text, char *out[], char storage[][128], int max)
{
    char *p;
    char *start;
    int count;
    int depth;
    unsigned n;

    count = 0;
    depth = 0;
    start = text;
    p = text;
    while (text != (char *)0 && *p != '\0') {
        if (*p == '(') ++depth;
        if (*p == ')' && depth > 0) --depth;
        if (*p == ',' && depth == 0) {
            if (count < max) {
                n = (unsigned)(p - start);
                if (n > 127U) n = 127U;
                memcpy(storage[count], start, n);
                storage[count][n] = '\0';
                out[count] = storage[count];
                ++count;
            }
            start = p + 1;
        }
        ++p;
    }
    if (text != (char *)0 && count < max) {
        n = (unsigned)(p - start);
        if (n > 127U) n = 127U;
        memcpy(storage[count], start, n);
        storage[count][n] = '\0';
        out[count] = storage[count];
        ++count;
    }
    return count;
}

static char *dup_substitute_name(char *line, char *name, char *value)
{
    char out[ASM56000_INPUT_LINE_CAP * 2];
    char *p;
    char *start;
    unsigned long used;
    unsigned long n;
    unsigned long name_len;

    if (line == (char *)0 || name == (char *)0 || value == (char *)0)
        return dup_text(line == (char *)0 ? (char *)"" : line);
    name_len = (unsigned long)strlen(name);
    used = 0UL;
    p = line;
    while (*p != '\0' && used + 1UL < sizeof(out)) {
        if (isalpha((unsigned char)*p) || *p == '_') {
            start = p++;
            while (isalnum((unsigned char)*p) || *p == '_')
                ++p;
            n = (unsigned long)(p - start);
            if (n == name_len &&
                strncmp(start, name, (size_t)n) == 0) {
                n = (unsigned long)strlen(value);
                if (used + n >= sizeof(out))
                    n = sizeof(out) - used - 1UL;
                memcpy(out + used, value, (size_t)n);
                used += n;
            } else {
                if (used + n >= sizeof(out))
                    n = sizeof(out) - used - 1UL;
                memcpy(out + used, start, (size_t)n);
                used += n;
            }
        } else {
            out[used++] = *p == '"' ? '\'' : *p;
            ++p;
        }
    }
    out[used] = '\0';
    return dup_text(out);
}

static void dup_add_line(char ***lines, int *count, int *size, char *line)
{
    char **next;
    int new_size;

    if (*count == *size) {
        new_size = *size == 0 ? 8 : *size * 2;
        next = (char **)xrealloc((void *)*lines,
                                 (unsigned long)new_size * sizeof(char *));
        *lines = next;
        *size = new_size;
    }
    (*lines)[*count] = line;
    ++*count;
}

static char **dup_capture_body(int *count)
{
    char **body;
    int size;
    int depth;
    int nested;

    body = (char **)0;
    *count = 0;
    size = 0;
    depth = 0;
    while (get_line()) {
        nested = 0;
        if (parse_line()) {
            if (is_name(MnemField, "endm")) {
                if (depth == 0) {
                    if (Pass == 2UL && OptMd && (!InLineReplay || OptMex))
                        list_macro_source();
                    break;
                }
                --depth;
            } else if (is_name(MnemField, "macro") ||
                       is_name(MnemField, "dup") ||
                       is_name(MnemField, "dupa") ||
                       is_name(MnemField, "dupc") ||
                       is_name(MnemField, "dupf")) {
                nested = 1;
            }
        }
        if (nested)
            ++depth;
        if (Pass == 2UL && OptMd && (!InLineReplay || OptMex))
            list_macro_source();
        dup_add_line(&body, count, &size, dup_text(RawLineBuf));
    }
    return body;
}

static void dup_free_body(char **body, int count)
{
    int i;

    for (i = 0; i < count; ++i)
        xfree((void *)body[i]);
    xfree((void *)body);
}

static void dup_emit_body(char **body, int body_count, char *name,
                          char **values, int value_count, int repeat)
{
    char **lines;
    int count;
    int size;
    int i;
    int j;
    char *line;

    lines = (char **)0;
    count = 0;
    size = 0;
    for (i = 0; i < repeat; ++i) {
        for (j = 0; j < body_count; ++j) {
            if (name != (char *)0 && value_count != 0)
                line = dup_substitute_name(body[j], name,
                                           values[i % value_count]);
            else
                line = dup_text(body[j]);
            dup_add_line(&lines, &count, &size, line);
        }
    }
    input_push_lines(lines, count);
}

static void process_dup(void)
{
    char storage[32][128];
    char *args[32];
    char *values[32];
    char value_text[32][64];
    char **body;
    char directive_line[ASM56000_INPUT_LINE_CAP];
    char directive_name[32];
    char directive_args[512];
    int body_count;
    int n;
    int value_count;
    int repeat;
    int i;
    long start;
    long finish;
    long step;
    long current;
    unsigned long length;

    strcpy(directive_line, RawLineBuf);
    strcpy(directive_name, MnemField == (char *)0 ? (char *)"" : MnemField);
    strcpy(directive_args, Op1Field == (char *)0 ? (char *)"" : Op1Field);
    if (Pass == 2UL && is_name(directive_name, "dupf")) {
        n = split_csv(directive_args, args, storage, 32);
        if (n >= 4 && parse_expr_value(args[3]) == 0UL) {
            CurInstrFieldMsg = Op1Field;
            err("Increment value cannot be zero");
        }
    }
    if (Pass == 2UL && OptMd && (!InLineReplay || OptMex)) {
        list_source(ProgramCounter, 0);
    }
    if (Pass == 2UL)
        MacroDirectiveListed = 1;
    body = dup_capture_body(&body_count);
    n = split_csv(directive_args, args, storage, 32);
    value_count = 0;
    repeat = 0;
    if (is_name(directive_name, "dup")) {
        if (n >= 1)
            repeat = (int)parse_expr_value(args[0]);
        if (repeat < 0)
            repeat = 0;
        dup_emit_body(body, body_count, (char *)0, values, 0, repeat);
    } else if (is_name(directive_name, "dupa") && n >= 2) {
        for (i = 1; i < n && value_count < 32; ++i)
            values[value_count++] = args[i];
        dup_emit_body(body, body_count, args[0], values, value_count,
                      value_count);
    } else if (is_name(directive_name, "dupc") && n >= 2) {
        i = 0;
        if (args[1][0] == '\'' || args[1][0] == '"')
            ++i;
        length = (unsigned long)strlen(args[1]);
        if (length != 0UL &&
            (args[1][length - 1UL] == '\'' ||
             args[1][length - 1UL] == '"'))
            --length;
        while ((unsigned long)i < length && value_count < 32) {
            value_text[value_count][0] = args[1][i++];
            value_text[value_count][1] = '\0';
            values[value_count] = value_text[value_count];
            ++value_count;
        }
        dup_emit_body(body, body_count, args[0], values, value_count,
                      value_count);
    } else if (is_name(directive_name, "dupf") && n >= 3) {
        start = (long)parse_expr_value(args[1]);
        finish = (long)parse_expr_value(args[2]);
        step = n >= 4 ? (long)parse_expr_value(args[3]) : 1L;
        if (step != 0L) {
            current = start;
            while ((step > 0L && current <= finish) ||
                   (step < 0L && current >= finish)) {
                if (value_count >= 32)
                    break;
                sprintf(value_text[value_count], "%ld", current);
                values[value_count] = value_text[value_count];
                ++value_count;
                current += step;
            }
        }
        dup_emit_body(body, body_count, args[0], values, value_count,
                      value_count);
    }
    dup_free_body(body, body_count);
    strcpy(RawLineBuf, directive_line);
    parse_line();
}

static int DoZeroWords;
static int DirectiveFailed;

/* Check the memory space prefixes of an ORG operand list. */
static int org_operands_valid(char *text)
{
    char *p;
    char *colon;
    char *comma;
    int field;
    int len;

    field = 0;
    p = text == (char *)0 ? (char *)"" : text;
    for (;;) {
        while (*p == ' ' || *p == '\t')
            ++p;
        comma = strchr(p, ',');
        colon = strchr(p, ':');
        if (colon != (char *)0 && comma != (char *)0 && colon > comma)
            colon = (char *)0;
        len = colon == (char *)0 ? -1 : (int)(colon - p);
        while (len > 0 && (p[len - 1] == ' ' || p[len - 1] == '\t'))
            --len;
        if (len >= 1 && strchr("xylpXYLP", p[0]) != (char *)0) {
            int k;

            k = 1;
            if (k < len && strchr("lhierLHIER", p[k]) != (char *)0)
                ++k;
            if (k < len && p[k] == '(') {
                while (k < len && p[k] != ')')
                    ++k;
                if (k < len)
                    ++k;
            }
            if (k != len) {
                CurInstrFieldMsg = Op1Field;
                err("Illegal memory counter specified");
                return 0;
            }
        } else {
            CurInstrFieldMsg = (text == (char *)0 || *text == '\0') ?
                               (char *)0 : Op1Field;
            err("Illegal memory space specified");
            return 0;
        }
        if (comma == (char *)0 || field > 0)
            break;
        p = comma + 1;
        ++field;
    }
    return 1;
}


struct obj_extern {
    char name[128];
    unsigned long section;
};

static struct obj_extern ObjExterns[256];
static int ObjExternCount;

/* An undefined symbol referenced in relocatable mode is an external
   reference; it enters the object symbol table at its first use in each
   section. */
void obj_note_extern(char *name)
{
    int i;
    unsigned long section;

    if (Pass != 2UL || AbsoluteMode || name == (char *)0)
        return;
    section = sec_number(CurrentSection);
    for (i = 0; i < ObjExternCount; ++i)
        if (ObjExterns[i].section == section &&
            strcmp(ObjExterns[i].name, name) == 0)
            return;
    if (ObjExternCount >= (int)(sizeof(ObjExterns) / sizeof(ObjExterns[0])))
        return;
    strncpy(ObjExterns[ObjExternCount].name, name,
            sizeof(ObjExterns[0].name) - 1UL);
    ObjExterns[ObjExternCount].name[sizeof(ObjExterns[0].name) - 1UL] = '\0';
    ObjExterns[ObjExternCount].section = section;
    ++ObjExternCount;
    obj_log_add(OL_EXTERN, obj_next_seq(), section, 0UL, name);
}

/* The symbol table hook: a symbol was defined in pass 2 (called from
   sym_define).  Constants need an open section; labels wait for the
   section that will hold them. */
void obj_symbol_defined(unsigned long seq, unsigned long flags,
                        unsigned long space, int global)
{
    int constant;
    struct output_event *last;
    unsigned long address;

    if (Pass != 2UL || AbsoluteMode)
        return;
    if ((flags & 0x50UL) != 0UL || ((flags & 0x20UL) != 0UL && !global))
        return;
    constant = space == 4UL || ((flags & 0x410UL) != 0UL && space < 4UL);
    if (constant) {
        if (NeedOpenSection)
            output_event_add(0, 0, current_p_counter(), 0UL, RecordCount,
                             0x20UL);
        return;
    }
    if (OutputEventCount != 0UL) {
        last = &OutputEvents[OutputEventCount - 1UL];
        if (last->kind == 0 && last->space == CurrentLoadSpace &&
            last->generation == OutputGeneration &&
            last->first_record + last->count == RecordCount) {
            sym_object_set(seq, OutputEventCount + 1UL, 0UL);
            return;
        }
    }
    if (PendingLabelCount < (int)(sizeof(PendingLabels) /
                                  sizeof(PendingLabels[0]))) {
        address = (LoadPhysical || ProgramCounter != LoadCounter) ?
                  LoadCounter : ProgramCounter;
        PendingLabels[PendingLabelCount].seq = seq;
        PendingLabels[PendingLabelCount].space = CurrentLoadSpace;
        PendingLabels[PendingLabelCount].generation = OutputGeneration;
        PendingLabels[PendingLabelCount].address = address;
        ++PendingLabelCount;
    }
}

/* Base memory space (P, X, Y, L) of a memory-space code. */
static unsigned long space_base(int space)
{
    if (space == 0 || (space >= 13 && space <= 15))
        return 0UL;
    if (space == 1 || (space >= 16 && space <= 20))
        return 1UL;
    if (space == 2 || (space >= 21 && space <= 25))
        return 2UL;
    if (space == 3 || (space >= 5 && space <= 10))
        return 3UL;
    return 4UL;
}

/* Counter selector of an ORG key: "l"/"h" suffix or "(n)". */
static unsigned long org_key_counter(char *key)
{
    char *p;

    p = strchr(key, '(');
    if (p != (char *)0)
        return (unsigned long)strtol(p + 1, (char **)0, 10);
    if (key[0] != '\0' && key[1] == 'l' && key[2] == '\0')
        return 1UL;
    if (key[0] != '\0' && key[1] == 'h' && key[2] == '\0')
        return 2UL;
    return 0UL;
}

/* True when the current location counter is relocatable: relocatable
   assembly mode, MODE RELATIVE, and the counter was not set by an ORG
   with an explicit address. */
static int counter_is_reloc(void)
{
    int i;

    if (AbsoluteMode || !ModeReloc)
        return 0;
    for (i = 0; i < OrgKeyCount; ++i)
        if (strcmp(OrgKeys[i], OrgKey) == 0)
            return !OrgAbs[i];
    return 1;
}

static void sync_eval_counters(void)
{
    EvalCounterReloc = counter_is_reloc();
    EvalCounterSpace = space_base(CurrentSpace);
    EvalCounterMap = (unsigned long)CurrentSpace;
    EvalCounterIndex = org_key_counter(OrgKey);
    EvalSection = sec_number(CurrentSection);
    EvalCounterSection = sec_counter_number(CurrentSection);
}

static void define_label(void)
{
    char text[64];
    void *value;
    unsigned long *words;

    if (Pass != 1UL && LabelField != (char *)0 &&
        *LabelField != '\0' && LabelField[0] != '_' &&
        sym_duplicate_name(LabelField)) {
        err_s("Symbol redefined", LabelField);
        return;
    }
    if ((Pass != 1UL &&
         (LabelField == (char *)0 || LabelField[0] != '_')) ||
        LabelField == (char *)0 || *LabelField == '\0' ||
        (MnemField != (char *)0 &&
         (is_name(MnemField, "equ") || is_name(MnemField, "set") ||
          is_name(MnemField, "define") || is_name(MnemField, "macro") ||
          is_name(MnemField, "buffer") || is_name(MnemField, "pmacro"))))
        return;
    if (strncmp(LabelField, "Z_L", 3) == 0)
        sym_hide_name(LabelField);
    sprintf(text, "$%lX", ProgramCounter);
    sync_eval_counters();
    value = eval_expr_text(text);
    if (value != (void *)0) {
        words = (unsigned long *)value;
        words[ASM56000_EXPR_W7 / 4] = (unsigned long)CurrentSpace;
        words[ASM56000_EXPR_W8 / 4] = (unsigned long)CurrentSpace;
        words[ASM56000_EXPR_W9 / 4] = EvalCounterIndex;
        words[ASM56000_EXPR_W15 / 4] = EvalSection;
        words[ASM56000_EXPR_W16 / 4] = EvalCounterSection;
        if (EvalCounterReloc)
            words[ASM56000_EXPR_W6 / 4] |= 0x1000UL;
        if (MnemField != (char *)0 &&
            (is_name(MnemField, "bsc") || is_name(MnemField, "bsm") ||
             is_name(MnemField, "bsr")))
            words[ASM56000_EXPR_W21 / 4] = 0xfeedUL;
        sym_define(LabelField, value);
        /* label values are retained between the two source passes */
        free_expr(value);
    }
}

static void verbose_source_scan(char *path, char *phase)
{
    FILE *fp;
    int c;
    unsigned long line;

    if (!VerboseOption)
        return;
    if (phase != (char *)0) {
        fprintf(stderr, "ASM56000: Beginning %s\n", phase);
        fprintf(stderr, "ASM56000: Opening source file %s\n", path);
    }
    fp = fopen(path, "rb");
    if (fp == (FILE *)0)
        return;
    line = 0UL;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            ++line;
            if (line % 100UL == 0UL)
                fprintf(stderr, "ASM56000: Processing line %lu in file %s (%lu)\n",
                        line, path, line);
        }
    }
    if (line == 0UL || (line % 100UL) != 0UL) {
        /* The original reports only completed 100-line milestones. */
    }
    fclose(fp);
}

static int is_name(char *name, char *want)
{
    if (name != (char *)0 && name[0] == '.')
        ++name;
    return name != (char *)0 && strcmp(str_lower_copy(name), want) == 0;
}

static char *directive_expr(char *text)
{
    if (text != (char *)0 && text[1] == ':' &&
        (text[0] == 'p' || text[0] == 'P' || text[0] == 'x' ||
         text[0] == 'X' || text[0] == 'y' || text[0] == 'Y' ||
         text[0] == 'l' || text[0] == 'L'))
        return text + 2;
    return text;
}

static void listing_copy_quoted(char *source, char *destination,
                                unsigned long size)
{
    unsigned long length;

    if (destination == (char *)0 || size == 0UL)
        return;
    destination[0] = '\0';
    if (source == (char *)0)
        return;
    while (*source == ' ' || *source == '\t')
        ++source;
    length = (unsigned long)strlen(source);
    if (length >= 2UL &&
        ((source[0] == '\'' && source[length - 1UL] == '\'') ||
         (source[0] == '"' && source[length - 1UL] == '"'))) {
        ++source;
        length -= 2UL;
    }
    if (length >= size)
        length = size - 1UL;
    memcpy(destination, source, length);
    destination[length] = '\0';
}

static void list_wrapped_field(char *text, int *column)
{
    unsigned long length;
    unsigned long width;
    unsigned long chunk;
    int limit;

    if (text == (char *)0)
        return;
    limit = ListingWidth - ListingIndent;
    if (limit < 1)
        limit = 1;
    length = (unsigned long)strlen(text);
    while (length != 0UL) {
        if (*column >= limit) {
            list_newline();
            *column = 0;
        }
        width = (unsigned long)(limit - *column);
        chunk = length < width ? length : width;
        fwrite(text, 1, chunk, Listing);
        text += chunk;
        length -= chunk;
        *column += (int)chunk;
        if (length != 0UL) {
            list_newline();
            list_prepare_line();
            *column = 0;
        }
    }
}

static char space_display_char(int space)
{
    if (space == 1 || (space >= 18 && space <= 20))
        return 'X';
    if (space == 2 || (space >= 23 && space <= 25))
        return 'Y';
    if (space == 3 || space == 9 || space == 10)
        return 'L';
    return 'P';
}

static void list_address_fields(int space, unsigned long address,
                                int load_space, unsigned long load_address,
                                int *column, int trailing_space)
{
    fprintf(Listing, "%c:%04lX", space_display_char(space),
            address & 0xffffUL);
    *column += 6;
    if (space != load_space || address != load_address) {
        fputc(' ', Listing);
        fprintf(Listing, "%c:%04lX", space_display_char(load_space),
                load_address & 0xffffUL);
        *column += 7;
    }
    if (trailing_space) {
        fputc(' ', Listing);
        ++*column;
    }
}

static void listing_expand_cli_defines(char *text, char *out,
                                       unsigned long size)
{
    unsigned long i;
    unsigned long used;
    unsigned long start;
    unsigned long n;
    int k;
    int match;

    if (size == 0UL)
        return;
    if (text == (char *)0) {
        out[0] = '\0';
        return;
    }
    i = 0UL;
    used = 0UL;
    while (text[i] != '\0' && used + 1UL < size) {
        if (isalpha((unsigned char)text[i]) || text[i] == '_' ||
            text[i] == '.') {
            start = i;
            ++i;
            while (isalnum((unsigned char)text[i]) || text[i] == '_' ||
                   text[i] == '.')
                ++i;
            n = i - start;
            match = -1;
            for (k = 0; k < DefineCount; ++k)
                if (strlen(DefineNames[k]) == n &&
                    strncmp(DefineNames[k], text + start, n) == 0) {
                    match = k;
                    break;
                }
            if (match >= 0) {
                n = (unsigned long)strlen(DefineValues[match]);
                if (used + n >= size)
                    n = size - used - 1UL;
                memcpy(out + used, DefineValues[match], n);
                used += n;
            } else {
                n = i - start;
                if (used + n >= size)
                    n = size - used - 1UL;
                memcpy(out + used, text + start, n);
                used += n;
            }
        } else {
            out[used++] = text[i++];
        }
    }
    out[used] = '\0';
}

static void list_source(unsigned long address, int nwords)
{
    int column;
    int has_label;
    int space;
    int load_space;
    int data_line;
    int reserve_limit;

    int layout_shift;
    int i;
    unsigned long load_address;
    unsigned long amount;
    char op1_text[512];
    char op2_text[512];
    char op3_text[512];
    char op4_text[512];
    char data_operand[512];
    char *display_op1;
    char *display_op2;
    char *display_op3;
    char *display_op4;

    if (Listing == (FILE *)0 || !ListingEnabled)
        return;
    display_op1 = Op1Field;
    display_op2 = Op2Field;
    display_op3 = Op3Field;
    display_op4 = Op4Field;
    if (DefineCount != 0) {
        if (Op1Field != (char *)0) {
            listing_expand_cli_defines(Op1Field, op1_text,
                                       sizeof(op1_text));
            display_op1 = op1_text;
        }
        if (Op2Field != (char *)0) {
            listing_expand_cli_defines(Op2Field, op2_text,
                                       sizeof(op2_text));
            display_op2 = op2_text;
        }
        if (Op3Field != (char *)0) {
            listing_expand_cli_defines(Op3Field, op3_text,
                                       sizeof(op3_text));
            display_op3 = op3_text;
        }
        if (Op4Field != (char *)0) {
            listing_expand_cli_defines(Op4Field, op4_text,
                                       sizeof(op4_text));
            display_op4 = op4_text;
        }
    }
    if (Op1Field != (char *)0 && *Op1Field != '\0' &&
        Op2Field != (char *)0 && *Op2Field != '\0' &&
        MnemField != (char *)0 &&
        (is_name(MnemField, "dc") || is_name(MnemField, "dcw") ||
         is_name(MnemField, "dcl") || is_name(MnemField, "dcb"))) {
        sprintf(data_operand, "%s         %s", display_op1, display_op2);
        display_op1 = data_operand;
    }
    data_line = MnemField != (char *)0 &&
        (is_name(MnemField, "dc") || is_name(MnemField, "dcw") ||
         is_name(MnemField, "dcl") || is_name(MnemField, "dcb")) &&
        (nwords != 0 || (ErrorCount != ListingErrorBase &&
                         LastDataCount == 0));
    if (data_line && nwords > 2 &&
        (Op1Field == (char *)0 ||
         (strchr(Op1Field, '\'') == (char *)0 &&
          strchr(Op1Field, '"') == (char *)0)) &&
        ListingPageLength != 0 &&
        ListingHeaderWritten && !ListingNoBreak) {
        reserve_limit = ListingHeaderTitle[0] != '\0' ||
                        ListingHeaderSubtitle[0] != '\0' ? 4 : 5;
        reserve_limit = ListingPageLength > reserve_limit ?
                        ListingPageLength - reserve_limit : 0;
        if (ListingPagePending && reserve_limit > 0)
            --reserve_limit;
        if (reserve_limit > 0 &&
            ListingSourceLines + (unsigned long)nwords >=
            (unsigned long)reserve_limit)
            ListingSourceLines = (unsigned long)reserve_limit;
    }
    ListingAllowOverrun = ListingNoBreakEver && OptMex &&
                          ListingPageLength != 0 &&
                          ListingPage < 25 &&
                          (int)strlen(RawLineBuf) > ListingWidth;
    list_prepare_line();
    ListingAllowOverrun = 0;
    if (RawLineBuf[0] == ';') {
        list_prepare_line();
        fprintf(Listing, "%lu", LineNo);
        column = (int)strlen(RawLineBuf) * 0;
        column = LineNo < 10UL ? 1 : LineNo < 100UL ? 2 :
                 LineNo < 1000UL ? 3 : LineNo < 10000UL ? 4 : 5;
        while (column < 25) {
            fputc(' ', Listing);
            ++column;
        }
        list_text_line(RawLineBuf, column);
        return;
    }
    has_label = LabelField != (char *)0 && *LabelField != '\0';
    space = CurrentSpace;
    if (MnemField != (char *)0 && is_name(MnemField, "org") &&
        !DirectiveFailed)
        space = space_from_text(Op1Field);
    load_space = CurrentLoadSpace;
    load_address = LoadCounter;
    if (data_line)
        load_address -= (unsigned long)nwords;
    else if (nwords == 0 && MnemField != (char *)0 &&
             (is_name(MnemField, "ds") || is_name(MnemField, "dsb") ||
              is_name(MnemField, "dsm") || is_name(MnemField, "dsmr") ||
              is_name(MnemField, "dsr"))) {
        amount = parse_expr_value(Op1Field);
        load_address -= amount * (load_space == 3 ? 2UL : 1UL);
    } else if (nwords != 0 && MnemField != (char *)0 &&
               (is_name(MnemField, "bsc") || is_name(MnemField, "bsm") ||
                is_name(MnemField, "bsr"))) {
        char storage[4][128];
        char *args[4];
        int argc;

        argc = split_csv(Op1Field, args, storage, 4);
        amount = argc < 1 ? 0UL : parse_expr_value(args[0]);
        if (argc < 2 && is_name(MnemField, "bsm"))
            amount = amount < 8UL ? 7UL : amount - 1UL;
        load_address -= amount * (load_space == 3 ? 2UL : 1UL);
    }
    if (ProgramCounter == LoadCounter && space == load_space)
        load_address = address;
    layout_shift = space != load_space || address != load_address ? 7 : 0;
    if (data_line && InLineReplay && CurrentSpace == 3 &&
        Op1Field != (char *)0 && strcmp(Op1Field, "*") == 0)
        return;
    if (data_line && ErrorCount != ListingErrorBase && LastDataCount == 0) {
        fprintf(Listing, "%lu", LineNo);
        column = line_digits();
        while (column < 25 + layout_shift) {
            fputc(' ', Listing);
            ++column;
        }
        if (has_label) {
            fprintf(Listing, "%-*s", ListingLabelWidth, LabelField);
            column += ListingLabelWidth;
        } else {
            for (i = 0; i < ListingLabelWidth; ++i)
                fputc(' ', Listing);
            column += ListingLabelWidth;
        }
        if (MnemField != (char *)0 && *MnemField != '\0') {
            if (Op1Field != (char *)0 && *Op1Field != '\0') {
                fprintf(Listing, "%-*s", ListingOpcodeWidth, MnemField);
                column += ListingOpcodeWidth;
            } else {
                fprintf(Listing, "%s", MnemField);
                column += (int)strlen(MnemField);
            }
        }
        if (Op1Field != (char *)0 && *Op1Field != '\0')
            list_wrapped_field(display_op1, &column);
        list_trailing_comment(&column);
        if (column != 0)
            list_newline();
        list_emit_pending_comment();
        return;
    }
    if (data_line && !OptCm && !SourceCexDirective) {
        fprintf(Listing, "%lu", LineNo);
        column = line_digits();
        while (column < 10) {
            fputc(' ', Listing);
            ++column;
        }
        list_address_fields(space, address, load_space, load_address,
                            &column, 1);
        while (column < 25 + layout_shift) {
            fputc(' ', Listing);
            ++column;
        }
        if (has_label) {
            fprintf(Listing, "%-*s", ListingLabelWidth, LabelField);
            column += ListingLabelWidth;
        } else {
            for (i = 0; i < ListingLabelWidth; ++i)
                fputc(' ', Listing);
            column += ListingLabelWidth;
        }
        if (MnemField != (char *)0 && *MnemField != '\0')
            fprintf(Listing, "%-*s", ListingOpcodeWidth, MnemField);
        column += ListingOpcodeWidth;
        if (Op1Field != (char *)0 && *Op1Field != '\0')
            list_wrapped_field(display_op1, &column);
        list_trailing_comment(&column);
        if (column != 0)
            list_newline();
        list_emit_pending_comment();
        return;
    }
    if (data_line && ErrorCount == ListingErrorBase) {
        fprintf(Listing, "%lu", LineNo);
        column = line_digits();
        while (column < 5) {
            fputc(' ', Listing);
            ++column;
        }
        fputc('d', Listing);
        ++column;
        if (InLineReplay) {
            fputc('+', Listing);
            ++column;
        }
        while (column < 10) {
            fputc(' ', Listing);
            ++column;
        }
        list_address_fields(space, address, load_space, load_address,
                            &column, 1);
        for (i = 0; i < nwords; ++i) {
            if (i != 0)
                break;
            fprintf(Listing, "%06lX", LastDataWords[i] & 0xffffffUL);
            column += 6;
        }
        while (column < 25 + layout_shift) {
            fputc(' ', Listing);
            ++column;
        }
        if (has_label) {
            fprintf(Listing, "%-*s", ListingLabelWidth, LabelField);
            column += ListingLabelWidth;
        } else {
            for (i = 0; i < ListingLabelWidth; ++i)
                fputc(' ', Listing);
            column += ListingLabelWidth;
        }
        if (MnemField != (char *)0 && *MnemField != '\0')
            fprintf(Listing, "%-*s", ListingOpcodeWidth, MnemField);
        column += ListingOpcodeWidth;
        if (Op1Field != (char *)0 && *Op1Field != '\0')
            list_wrapped_field(display_op1, &column);
        list_trailing_comment(&column);
        if (column != 0)
            list_newline();
        for (i = 1; i < nwords; ++i) {
            list_prepare_line();
            fputs("     d           ", Listing);
            for (column = 0; column < layout_shift; ++column)
                fputc(' ', Listing);
            fprintf(Listing, "%06lX", LastDataWords[i] & 0xffffffUL);
            column = 23 + layout_shift;
            if (i == 1)
                list_emit_pending_comment_current(&column);
            if (ListingSeparateComments && i == 1 && column < 35) {
                while (column < 35) {
                    fputc(' ', Listing);
                    ++column;
                }
            }
            list_newline();
        }
        list_emit_pending_comment();
        return;
    }
    if (has_label && (int)strlen(LabelField) > ListingLabelWidth) {
        int label_length;

        fprintf(Listing, "%lu", LineNo);
        column = line_digits();
        while (column < 25 + layout_shift) {
            fputc(' ', Listing);
            ++column;
        }
        label_length = (int)strlen(LabelField);
        while (label_length > 0 &&
               isspace((unsigned char)LabelField[label_length - 1]))
            --label_length;
        fwrite(LabelField, 1, (unsigned long)label_length, Listing);
        list_newline();
        ++LineNo;
        list_prepare_line();
        has_label = 0;
    }
    fprintf(Listing, "%lu", LineNo);
    column = line_digits();
    if (InLineReplay) {
        while (column < 6) {
            fputc(' ', Listing);
            ++column;
        }
        fputc('+', Listing);
        ++column;
    }
    while (column < 10) {
        fputc(' ', Listing);
        ++column;
    }
    if (nwords != 0) {
        list_address_fields(space, address, load_space, load_address,
                            &column, 1);
        if (LastDataCount != 0 && data_line)
            fprintf(Listing, "%06lX", LastDataWords[0] & 0xffffffUL);
        else if (LastDataCount != 0 && MnemField != (char *)0 &&
                 (is_name(MnemField, "bsc") || is_name(MnemField, "bsm") ||
                  is_name(MnemField, "bsr")))
            fprintf(Listing, "%06lX", LastDataWords[0] & 0xffffffUL);
        else
            fprintf(Listing, "%06lX", asm56000_last_word(0) |
                    (cex_enabled() ? 0x200000UL : 0UL));
        column += 6;
        while (column < 25 + layout_shift) {
            fputc(' ', Listing);
            ++column;
        }
        if (has_label) {
            fprintf(Listing, "%-*s", ListingLabelWidth, LabelField);
            column += ListingLabelWidth;
        } else {
            for (i = 0; i < ListingLabelWidth; ++i)
                fputc(' ', Listing);
            column += ListingLabelWidth;
        }
        if (MnemField != (char *)0 && *MnemField != '\0') {
            fprintf(Listing, "%s", MnemField);
            column += (int)strlen(MnemField);
        }
    } else {
        if (MnemField != (char *)0 && !DirectiveFailed &&
            (is_name(MnemField, "ds") || is_name(MnemField, "dsb") ||
             is_name(MnemField, "dsm") || is_name(MnemField, "dsmr") ||
             is_name(MnemField, "dsr") || is_name(MnemField, "buffer") ||
             is_name(MnemField, "baddr") || is_name(MnemField, "align"))) {
            list_address_fields(space, address, load_space, load_address,
                                &column, 0);
            while (column < 25 + layout_shift) {
                fputc(' ', Listing);
                ++column;
            }
            if (has_label) {
                fprintf(Listing, "%-*s", ListingLabelWidth, LabelField);
                column += ListingLabelWidth;
            }
            while (column < 35 + layout_shift) {
                fputc(' ', Listing);
                ++column;
            }
            if (MnemField != (char *)0 && *MnemField != '\0') {
                fprintf(Listing, "%s", MnemField);
                column += (int)strlen(MnemField);
            }
        } else if (has_label && MnemField != (char *)0 &&
            !DirectiveFailed &&
            (is_name(MnemField, "equ") || is_name(MnemField, "set"))) {
            void *equ_value;
            unsigned long *equ_words;
            char equ_text[64];

            equ_value = eval_expr_text(is_name(MnemField, "set") ?
                                       LabelField : Op1Field);
            equ_words = (unsigned long *)equ_value;
            if (equ_value != (void *)0 &&
                equ_words[ASM56000_EXPR_W4 / 4] == 0x200UL) {
                sprintf(equ_text, "%E", expr_as_double(equ_value));
                fputs(equ_text, Listing);
                column += (int)strlen(equ_text);
            } else {
                fprintf(Listing, "%06lX", is_name(MnemField, "set") ?
                        parse_expr_value(LabelField) :
                        parse_expr_value(Op1Field));
                column += 6;
            }
            free_expr(equ_value);
            while (column < 25 + layout_shift) {
                fputc(' ', Listing);
                ++column;
            }
            fprintf(Listing, "%-*s", ListingLabelWidth, LabelField);
            fprintf(Listing, "%s", MnemField);
            column = 25 + layout_shift + ListingLabelWidth +
                     (int)strlen(MnemField);
        } else if (MnemField != (char *)0 &&
                   is_name(MnemField, "org")) {
            list_address_fields(space, address, load_space, load_address,
                                &column, 0);
            while (column < 35 + layout_shift) {
                fputc(' ', Listing);
                ++column;
            }
            fprintf(Listing, "%s", MnemField);
            column += (int)strlen(MnemField);
        } else {
            if (has_label) {
                while (column < 25 + layout_shift) {
                    fputc(' ', Listing);
                    ++column;
                }
                fprintf(Listing, "%-*s", ListingLabelWidth, LabelField);
                column += ListingLabelWidth;
            }
            while (column < 35 + layout_shift) {
                fputc(' ', Listing);
                ++column;
            }
            if (MnemField != (char *)0 && *MnemField != '\0') {
                fprintf(Listing, "%s", MnemField);
                column += (int)strlen(MnemField);
            }
        }
    }
    for (i = 0; i < 4; ++i) {
        char *field;
        int target;

        field = i == 0 ? display_op1 : i == 1 ? display_op2 :
                i == 2 ? display_op3 : display_op4;
        if (field == (char *)0 || *field == '\0')
            continue;
        /* The fields are placed as the original assembler does: each
           follows the previous one at a fixed distance (operand, X move,
           Y move widths); instructions that shifted their fields
           (move, nop, rts, ...) therefore list in the X/Y columns. */
        target = 43 + layout_shift;
        if (i >= 1)
            target += ListingOperandWidth;
        if (i >= 2)
            target += ListingXWidth;
        if (i >= 3)
            target += ListingYWidth;
        if (column < target) {
            while (column < target) {
                fputc(' ', Listing);
                ++column;
            }
        } else {
            fputc(' ', Listing);
            ++column;
        }
        list_wrapped_field(field, &column);
    }
    list_trailing_comment(&column);
    if (column != 0)
        list_newline();
    for (i = 1; i < nwords &&
         !(data_line && ErrorCount != ListingErrorBase); ++i) {
        list_prepare_line();
            fputs("                 ", Listing);
            for (column = 0; column < layout_shift; ++column)
                fputc(' ', Listing);
            if (LastDataCount != 0 && MnemField != (char *)0 &&
                (is_name(MnemField, "bsc") ||
                 is_name(MnemField, "bsm") || is_name(MnemField, "bsr")))
                fprintf(Listing, "%06lX", LastDataWords[i] & 0xffffffUL);
            else
                fprintf(Listing, "%06lX", asm56000_last_word(i) |
                        (cex_enabled() ? 0x200000UL : 0UL));
            column = 23 + layout_shift;
            if (i == 1)
                list_emit_pending_comment_current(&column);
            if (ListingSeparateComments && i == 1 && column < 35) {
                while (column < 35) {
                    fputc(' ', Listing);
                    ++column;
                }
            }
            list_newline();
    }
    list_emit_pending_comment();
}

static void list_macro_source(void)
{
    int column;
    int i;
    char *comment;

    if (Listing == (FILE *)0 || !ListingEnabled)
        return;
    list_prepare_line();
    fprintf(Listing, "%lu", LineNo);
    column = line_digits();
    comment = RawLineBuf;
    while (*comment == ' ' || *comment == '\t')
        ++comment;
    if (*comment == ';' && InLineReplay) {
        while (column < 6) {
            fputc(' ', Listing);
            ++column;
        }
        fputc('+', Listing);
        column = 7;
        if (!ListingSeparateComments) {
            while (column < 77) {
                fputc(' ', Listing);
                ++column;
            }
            list_text_line(comment, column);
        } else {
            list_newline();
        }
        return;
    }
    while (column < 5) {
        fputc(' ', Listing);
        ++column;
    }
    fputc('m', Listing);
    ++column;
    if (InLineReplay) {
        fputc('+', Listing);
        ++column;
    }
    if (*comment == ';') {
        if (ListingSeparateComments) {
            strncpy(SeparateComment, comment, sizeof(SeparateComment) - 1U);
            SeparateComment[sizeof(SeparateComment) - 1U] = '\0';
            SeparateCommentPending = 1;
            while (column < 10) {
                fputc(' ', Listing);
                ++column;
            }
            list_newline();
            list_emit_pending_comment();
            return;
        }
        while (column < 77) {
            fputc(' ', Listing);
            ++column;
        }
        list_text_line(comment, column);
        return;
    }
    if (LabelField != (char *)0 && *LabelField != '\0') {
        while (column < 25) {
            fputc(' ', Listing);
            ++column;
        }
        fprintf(Listing, "%-10s", LabelField);
        column += 10;
    }
    while (column < 35) {
        fputc(' ', Listing);
        ++column;
    }
    if (MnemField != (char *)0 && *MnemField != '\0') {
        if (Op1Field != (char *)0 && *Op1Field != '\0') {
            fprintf(Listing, "%-8s", MnemField);
            column += 8;
        } else {
            fprintf(Listing, "%s", MnemField);
            column += (int)strlen(MnemField);
        }
    }
    for (i = 0; i < 4; ++i) {
        char *field;
        int target;

        field = i == 0 ? Op1Field : i == 1 ? Op2Field :
                i == 2 ? Op3Field : Op4Field;
        if (field == (char *)0 || *field == '\0')
            continue;
        target = 43 + i * 10;
        while (column < target) {
            fputc(' ', Listing);
            ++column;
        }
        list_wrapped_field(field, &column);
    }
    list_trailing_comment(&column);
    if (column != 0)
        list_newline();
    list_emit_pending_comment();
}

void listing_library_line(char *text, unsigned long line_no, int marked)
{
    char line[ASM56000_INPUT_LINE_CAP];
    char label[128];
    char mnemonic[128];
    char operand[256];
    char *p;
    char *q;
    char *saved_label;
    char *saved_mnem;
    char *saved_op1;
    char *saved_op2;
    char *saved_op3;
    char *saved_op4;
    unsigned long saved_line;
    char saved_replay;

    if (Listing == (FILE *)0 || text == (char *)0)
        return;
    strncpy(line, text, sizeof(line) - 1U);
    line[sizeof(line) - 1U] = '\0';
    q = line + strlen(line);
    while (q > line && (q[-1] == '\r' || q[-1] == '\n'))
        --q;
    *q = '\0';
    p = line;
    label[0] = '\0';
    mnemonic[0] = '\0';
    operand[0] = '\0';
    while (*p == ' ' || *p == '\t')
        ++p;
    q = p;
    while (*q != '\0' && *q != ' ' && *q != '\t')
        ++q;
    if (p != line && p != q) {
        strncpy(mnemonic, p, (size_t)(q - p));
        mnemonic[q - p] = '\0';
    } else {
        strncpy(label, p, (size_t)(q - p));
        label[q - p] = '\0';
        while (*q == ' ' || *q == '\t')
            ++q;
        p = q;
        while (*q != '\0' && *q != ' ' && *q != '\t')
            ++q;
        strncpy(mnemonic, p, (size_t)(q - p));
        mnemonic[q - p] = '\0';
    }
    while (*q == ' ' || *q == '\t')
        ++q;
    strncpy(operand, q, sizeof(operand) - 1U);
    operand[sizeof(operand) - 1U] = '\0';

    saved_label = LabelField;
    saved_mnem = MnemField;
    saved_op1 = Op1Field;
    saved_op2 = Op2Field;
    saved_op3 = Op3Field;
    saved_op4 = Op4Field;
    saved_line = LineNo;
    saved_replay = InLineReplay;
    LabelField = label;
    MnemField = mnemonic;
    Op1Field = operand;
    Op2Field = (char *)0;
    Op3Field = (char *)0;
    Op4Field = (char *)0;
    LineNo = line_no;
    InLineReplay = 0;
    RawLineBuf[0] = '\0';
    if (marked)
        list_macro_source();
    else
        list_plain_source();
    LabelField = saved_label;
    MnemField = saved_mnem;
    Op1Field = saved_op1;
    Op2Field = saved_op2;
    Op3Field = saved_op3;
    Op4Field = saved_op4;
    LineNo = saved_line;
    InLineReplay = saved_replay;
}

static void list_plain_source(void)
{
    int i;
    int label_length;
    char operand[512];
    char *comment;
    int used;

    if (Listing == (FILE *)0 || !ListingEnabled)
        return;
    list_prepare_line();
    comment = RawLineBuf;
    while (*comment == ' ' || *comment == '\t')
        ++comment;
    if (*comment == ';') {
        fprintf(Listing, "%lu", LineNo);
        used = LineNo < 10UL ? 1 : LineNo < 100UL ? 2 :
               LineNo < 1000UL ? 3 : LineNo < 10000UL ? 4 : 5;
        while (used < 25 +
               ((CurrentSpace != CurrentLoadSpace ||
                 ProgramCounter != LoadCounter) ? 7 : 0)) {
            fputc(' ', Listing);
            ++used;
        }
        list_text_line(comment, used);
        return;
    }
    if (!InLineReplay && MnemField != (char *)0 && MnemField[0] == '.' &&
        find_scs_directive(MnemField + 1) != (void *)0) {
        fprintf(Listing, "%lu", LineNo);
        used = line_digits();
        comment = RawLineBuf;
        while (*comment == ' ' || *comment == '\t')
            ++comment;
        while (used < 35) {
            fputc(' ', Listing);
            ++used;
        }
        fputs(comment, Listing);
        list_newline();
        return;
    }
    if (!InLineReplay &&
        (strncmp(comment, "page", 4) == 0 ||
         strncmp(comment, "lstcol", 6) == 0 ||
         strncmp(comment, "tabs", 4) == 0)) {
        fprintf(Listing, "%lu", LineNo);
        used = line_digits();
        while (used < 35) {
            fputc(' ', Listing);
            ++used;
        }
        comment = RawLineBuf;
        while (*comment == ' ' || *comment == '\t')
            ++comment;
        if (strncmp(comment, "lstcol", 6) == 0 &&
            strlen(comment) > 6UL) {
            char *operand_text;

            if (ErrorCount != ListingErrorBase) {
                /* An invalid LSTCOL is listed as entered, including its
                   original spacing. */
                while (used < 35) {
                    fputc(' ', Listing);
                    ++used;
                }
                fputs(comment, Listing);
            } else {
                while (used < 37) {
                    fputc(' ', Listing);
                    ++used;
                }
                fputs("lstcol ", Listing);
                operand_text = comment + 6;
                while (*operand_text == ' ' || *operand_text == '\t')
                    ++operand_text;
                fputs(operand_text, Listing);
            }
        } else {
            fputs(comment, Listing);
        }
        list_newline();
        return;
    }
    fprintf(Listing, "%lu", LineNo);
    used = line_digits();
    if (ListingInactive) {
        while (used < 5) {
            fputc(' ', Listing);
            ++used;
        }
        fputc('i', Listing);
        ++used;
    }
    if (InLineReplay) {
        while (used < 6) {
            fputc(' ', Listing);
            ++used;
        }
        fputc('+', Listing);
        ++used;
    }
    if (LabelField != (char *)0 && *LabelField != '\0' &&
        (MnemField == (char *)0 || *MnemField == '\0') &&
        (Op1Field == (char *)0 || *Op1Field == '\0')) {
        while (used < 25 +
               ((CurrentSpace != CurrentLoadSpace ||
                 ProgramCounter != LoadCounter) ? 7 : 0)) {
            fputc(' ', Listing);
            ++used;
        }
        label_length = (int)strlen(LabelField);
        while (label_length > 0 &&
               isspace((unsigned char)LabelField[label_length - 1]))
            --label_length;
        fwrite(LabelField, 1, (unsigned long)label_length, Listing);
        list_newline();
        return;
    }
    if (LabelField != (char *)0 && *LabelField != '\0') {
        while (used < 25) {
            fputc(' ', Listing);
            ++used;
        }
        fprintf(Listing, "%-10s", LabelField);
        used += 10;
        while (used < 35) {
            fputc(' ', Listing);
            ++used;
        }
    } else {
        while (used < 35) {
            fputc(' ', Listing);
            ++used;
        }
    }
    if (MnemField != (char *)0 && *MnemField != '\0') {
        if (Op1Field != (char *)0 && *Op1Field != '\0') {
            if (strlen(MnemField) >= 8UL) {
                fputs(MnemField, Listing);
                fputc(' ', Listing);
            } else
                fprintf(Listing, "%-8s", MnemField);
        } else
            fprintf(Listing, "%s", MnemField);
    } else if (Op1Field != (char *)0 && *Op1Field != '\0')
        fputs("        ", Listing);
    operand[0] = '\0';
    for (i = 0; i < 4; ++i) {
        char *field;

        field = i == 0 ? Op1Field : i == 1 ? Op2Field :
                i == 2 ? Op3Field : Op4Field;
        if (field == (char *)0 || *field == '\0')
            continue;
        if (operand[0] != '\0')
            strcat(operand, " ");
        strcat(operand, field);
    }
    if (operand[0] != '\0')
        fputs(operand, Listing);
    if (MnemField != (char *)0 && *MnemField != '\0') {
        if (Op1Field != (char *)0 && *Op1Field != '\0')
            used += strlen(MnemField) >= 8UL ?
                    (int)strlen(MnemField) + 1 : 8;
        else
            used += (int)strlen(MnemField);
    }
    used += (int)strlen(operand);
    list_trailing_comment(&used);
    if (used != 0)
        list_newline();
    list_emit_pending_comment();
}

static void list_summary(void)
{
    int i;

    if (Listing == (FILE *)0)
        return;
    list_prepare_line();
    list_newline();
    list_prepare_line();
    fprintf(Listing, "%-5luError%s", ErrorCount,
            ErrorCount == 1UL ? " " : "s");
    list_newline();
    list_prepare_line();
    fprintf(Listing, "%-5luWarning%s", WarningCount,
            WarningCount == 1UL ? " " : "s");
    list_newline();
    for (i = 0; i < 3; ++i) {
        list_prepare_line();
        if (i < 2)
            list_newline();
    }
}

static void report_line(char *text)
{
    if (!(ListingHeaderWritten && ListingSourceLines == 0UL))
        list_prepare_line();
    if (text != (char *)0)
        fputs(text, Listing);
    list_newline();
}

static void report_blank(void)
{
    report_line((char *)"");
}

static void report_trailing_blank(void)
{
    if (!(ListingHeaderWritten && ListingSourceLines == 0UL))
        list_prepare_line();
}

static void report_new_page(void)
{
    ListingHeaderWritten = 0;
    ListingPagePending = 0;
    ListingSourceLines = 0UL;
    ++ListingPage;
    ReportHeaderMode = ListingNoBreakEver;
}

static void report_start(void)
{
    int saved_length;
    unsigned long i;

    if (ListingNoBreakEver) {
        list_newline();
        for (i = 0UL; i < 9UL; ++i)
            list_newline();
        ListingHeaderWritten = 0;
        ListingPagePending = 0;
        ListingSourceLines = 0UL;
        ListingPage = 7;
        strcpy(ListingHeaderTitle, ListingTitle);
        strcpy(ListingHeaderSubtitle, ListingSubtitle);
        ReportHeaderMode = 1;
        list_prepare_line();
        ReportHeaderMode = 0;
        return;
    }
    if (ListingHeaderWritten) {
        ListingPagePending = 1;
        saved_length = ListingPageLength;
        if (!ListingNoBreakEver)
            ++ListingPageLength;
        ReportHeaderMode = ListingNoBreakEver;
        list_prepare_line();
        ListingPageLength = saved_length;
        ReportHeaderMode = 0;
    }
}

static void report_dotted_name(char *name, char *out, unsigned long size)
{
    unsigned long n;

    if (size == 0UL)
        return;
    n = (unsigned long)strlen(name);
    if (n >= 17UL) {
        n = 16UL;
        memcpy(out, name, n);
        out[n++] = '.';
    } else {
        memcpy(out, name, n);
        while (n < 17UL)
            out[n++] = '.';
    }
    if (n >= size)
        n = size - 1UL;
    out[n] = '\0';
}

static int report_symbol_allowed(unsigned long index)
{
    char name[128];
    unsigned long flags;

    if (!sym_object_info(index, name, sizeof(name), (unsigned long *)0,
                         (unsigned long *)0, (unsigned long *)0, &flags,
                         (unsigned long *)0, (unsigned long *)0,
                         (unsigned long *)0, (int *)0, (int *)0))
        return 0;
    if ((flags & 0x40UL) != 0UL)
        return 0;
    if (!ListingReportLocals && (flags & 0x20UL) != 0UL)
        return 0;
    return 1;
}

static unsigned long ReportSymbolIndices[4096];
static unsigned long ReportSymbolCount;

static void report_collect_symbols(void)
{
    unsigned long i;
    unsigned long j;
    unsigned long n;
    char a[128];
    char b[128];
    unsigned long key;

    n = 0UL;
    for (i = 0UL; i < sym_object_count() && n < 4096UL; ++i)
        if (report_symbol_allowed(i))
            ReportSymbolIndices[n++] = i;
    for (i = 1UL; i < n; ++i) {
        key = ReportSymbolIndices[i];
        sym_object_info(key, a, sizeof(a), (unsigned long *)0,
                        (unsigned long *)0, (unsigned long *)0,
                        (unsigned long *)0, (unsigned long *)0,
                        (unsigned long *)0, (unsigned long *)0,
                        (int *)0, (int *)0);
        j = i;
        while (j != 0UL) {
            sym_object_info(ReportSymbolIndices[j - 1UL], b, sizeof(b),
                            (unsigned long *)0, (unsigned long *)0,
                            (unsigned long *)0, (unsigned long *)0,
                            (unsigned long *)0, (unsigned long *)0,
                            (unsigned long *)0, (int *)0, (int *)0);
            if (strcmp(b, a) <= 0)
                break;
            ReportSymbolIndices[j] = ReportSymbolIndices[j - 1UL];
            --j;
        }
        ReportSymbolIndices[j] = key;
    }
    ReportSymbolCount = n;
}

static void report_section_for(unsigned long space, unsigned long value,
                               char *out, unsigned long size)
{
    unsigned long i;

    if (size == 0UL)
        return;
    out[0] = '\0';
    for (i = 0UL; i < OutputEventCount; ++i) {
        if (OutputEvents[i].space != (int)space ||
            OutputEvents[i].section_name[0] == '\0' ||
            strcmp(OutputEvents[i].section_name, "GLOBAL") == 0)
            continue;
        if (OutputEvents[i].count == 0UL) {
            if (OutputEvents[i].address == value) {
                strncpy(out, OutputEvents[i].section_name, size - 1UL);
                out[size - 1UL] = '\0';
                return;
            }
        } else if (value >= OutputEvents[i].address &&
                   value < OutputEvents[i].address + OutputEvents[i].count) {
            strncpy(out, OutputEvents[i].section_name, size - 1UL);
            out[size - 1UL] = '\0';
            return;
        }
    }
}

static void report_float_text(unsigned long word0, unsigned long word1,
                              char *out, unsigned long size)
{
    union {
        double d;
        unsigned long w[2];
    } bits;
    char *e;
    char temp[64];
    int digits;

    bits.w[0] = word0;
    bits.w[1] = word1;
    sprintf(temp, "%E", bits.d);
    e = strchr(temp, 'E');
    digits = e == (char *)0 ? 0 : (int)strlen(e + 2);
    if (e != (char *)0 && digits == 2) {
        strncpy(out, temp, size - 1UL);
        out[size - 1UL] = '\0';
        e = strchr(out, 'E');
        if (e != (char *)0) {
            memmove(e + 3, e + 2, strlen(e + 2) + 1UL);
            e[2] = '0';
        }
        return;
    }
    strncpy(out, temp, size - 1UL);
    out[size - 1UL] = '\0';
}

static void report_symbol_line(unsigned long index)
{
    char name[128];
    char dotted[64];
    char section[64];
    char value_text[64];
    char line[256];
    char prefix[4];
    unsigned long value;
    unsigned long space;
    unsigned long flags;
    unsigned long word0;
    unsigned long word1;
    int sectioned;
    int global;
    char *type;
    char *attribute;
    int report_global;

    if (!sym_object_info(index, name, sizeof(name), &value, &space,
                         (unsigned long *)0, &flags, &word0, &word1,
                         (unsigned long *)0, &sectioned, &global))
        return;
    section[0] = '\0';
    report_section_for(space, value, section, sizeof(section));
    if ((flags & 0x200UL) != 0UL) {
        type = (char *)"fpt";
        report_float_text(word0, word1, value_text, sizeof(value_text));
    } else {
        type = (char *)"int";
        if (space < 4UL) {
            prefix[0] = space == 0UL ? 'P' : space == 1UL ? 'X' :
                       space == 2UL ? 'Y' : 'L';
            prefix[1] = ':';
            prefix[2] = '\0';
            sprintf(value_text, "%s%04lX", prefix, value & 0xffffUL);
        } else
            sprintf(value_text, "%06lX", value & 0xffffffUL);
    }
    if ((flags & 0x10UL) != 0UL)
        attribute = (char *)"SET";
    else if (sectioned)
        attribute = (char *)"REL";
    else
        attribute = (char *)"ABS";
    report_dotted_name(name, dotted, sizeof(dotted));
    report_global = global || (!sectioned && (flags & 0x20UL) == 0UL);
    sprintf(line, "%s%s%s", dotted, type,
            space < 4UL ? "   " : "     ");
    strcat(line, value_text);
    if (sectioned) {
        while (strlen(line) < 39UL)
            strcat(line, " ");
        strcat(line, section);
    }
    while (strlen(line) < 57UL)
        strcat(line, " ");
    strcat(line, attribute);
    strcat(line, report_global ? " GLOBAL" : ((flags & 0x20UL) != 0UL ?
                                   " LOCAL " : ""));
    report_line(line);
}

static void report_defines(void)
{
    int i;
    char line[256];
    char dotted[64];

    if (SourceDefineCount == 0)
        return;
    report_line((char *)"Define symbols:");
    report_blank();
    report_line((char *)"Symbol           Definition");
    report_blank();
    for (i = 0; i < SourceDefineCount; ++i) {
        report_dotted_name(SourceDefineNames[i], dotted, sizeof(dotted));
        sprintf(line, "%s'%s'", dotted,
                SourceDefineValues[i]);
        report_line(line);
    }
    report_blank();
    report_blank();
}

static void report_macros(void)
{
    unsigned long i;
    unsigned long count;
    unsigned long line_number;
    char name[128];
    char line[256];

    if (macro_report_count() == 0UL)
        return;
    report_line((char *)"Macros:");
    report_blank();
    report_line((char *)"Name          Definition       Section");
    report_line((char *)"                 Line");
    report_blank();
    count = macro_report_count();
    for (i = 0UL; i < count; ++i) {
        if (!macro_report_info(i, name, sizeof(name), &line_number))
            continue;
        {
            char dotted[64];

            report_dotted_name(name, dotted, sizeof(dotted));
            sprintf(line, "%s%lu    ", dotted, line_number);
        }
        report_line(line);
    }
    report_blank();
    report_blank();
}

static void report_sections(void)
{
    unsigned long i;
    int found;
    char line[64];

    found = 0;
    for (i = 0UL; i < OutputEventCount; ++i)
        if (OutputEvents[i].section_name[0] != '\0' &&
            strcmp(OutputEvents[i].section_name, "GLOBAL") != 0) {
            found = 1;
            break;
        }
    if (!found)
        return;
    report_line((char *)"Relocatable Sections:");
    report_blank();
    report_line((char *)"Name");
    report_blank();
    for (i = 0UL; i < OutputEventCount; ++i) {
        if (OutputEvents[i].section_name[0] == '\0' ||
            strcmp(OutputEvents[i].section_name, "GLOBAL") == 0)
            continue;
        sprintf(line, "%s", OutputEvents[i].section_name);
        report_line(line);
        break;
    }
    report_blank();
    report_blank();
}

static void report_symbol_table(void)
{
    unsigned long i;

    report_line((char *)"Symbols:");
    report_blank();
    report_line((char *)"Name             Type    Value         Section           Attributes");
    report_blank();
    report_collect_symbols();
    for (i = 0UL; i < ReportSymbolCount; ++i)
        report_symbol_line(ReportSymbolIndices[i]);
    report_blank();
    report_blank();
}

static void sort_report_refs(unsigned long *lines, int *defs,
                             unsigned long count, int local)
{
    unsigned long i;
    unsigned long j;
    unsigned long line;
    int def;

    for (i = 1UL; i < count; ++i) {
        line = lines[i];
        def = defs[i];
        j = i;
        while (j != 0UL &&
               (lines[j - 1UL] > line ||
                (lines[j - 1UL] == line &&
                 (local ? defs[j - 1UL] < def : defs[j - 1UL] > def)))) {
            lines[j] = lines[j - 1UL];
            defs[j] = defs[j - 1UL];
            --j;
        }
        lines[j] = line;
        defs[j] = def;
    }
}

static void report_xref_symbol(unsigned long index)
{
    unsigned long lines[128];
    int defs[128];
    unsigned long count;
    unsigned long i;
    char name[128];
    char line[512];
    char number[32];
    char dotted[64];
    unsigned long total;
    unsigned long item;
    unsigned long item_line;
    unsigned long flags;
    int item_def;

    flags = 0UL;
    if (!sym_object_info(index, name, sizeof(name), (unsigned long *)0,
                         (unsigned long *)0, (unsigned long *)0,
                         &flags, (unsigned long *)0,
                         (unsigned long *)0, (unsigned long *)0,
                         (int *)0, (int *)0))
        return;
    count = 0UL;
    sym_object_references(index, lines, defs, 128UL, &count);
    if (count > 128UL)
        count = 128UL;
    sort_report_refs(lines, defs, count, (flags & 0x20UL) != 0UL);
    line[0] = '\0';
    report_dotted_name(name, dotted, sizeof(dotted));
    sprintf(line, "%s", dotted);
    total = strcmp(name, "subr") == 0 && count != 0UL ? count + 1UL : count;
    for (i = 0UL; i < total; ++i) {
        unsigned long target;

        item = i;
        item_def = 0;
        if (strcmp(name, "subr") == 0 && count != 0UL) {
            if (i == 0UL)
                item_line = lines[0] > 2UL ? lines[0] - 2UL : 0UL;
            else {
                item = i - 1UL;
                item_line = lines[item];
                item_def = defs[item];
            }
        } else {
            item_line = lines[item];
            item_def = defs[item];
        }
        sprintf(number, "%lu", item_line);
        if (i == 0UL) {
            target = 22UL - (unsigned long)strlen(number);
        } else
            target = 28UL + (i - 1UL) * 8UL;
        while (strlen(line) < target)
            strcat(line, " ");
        sprintf(number, "%lu%s", item_line, item_def ? "*" : "");
        strcat(line, number);
    }
    strcat(line, count != 0UL && defs[count - 1UL] ? "  " : "   ");
    report_line(line);
}

static void listing_report_crossref(void)
{
    unsigned long i;

    report_start();
    report_defines();
    report_macros();
    report_sections();
    report_symbol_table();
    report_line((char *)"Symbol cross-reference listing:");
    report_blank();
    if (ListingNoBreakEver) {
        for (i = 0UL; i < 5UL; ++i)
            list_newline();
        report_new_page();
    }
    report_line((char *)"Name             Line number (* is definition)");
    for (i = 0UL; i < ReportSymbolCount; ++i)
        report_xref_symbol(ReportSymbolIndices[i]);
    report_blank();
    if (!ListingNoBreakEver)
        report_blank();
}

static void listing_report_symbols(void)
{
    report_start();
    report_defines();
    report_macros();
    report_sections();
    report_symbol_table();
}

static void report_memory_block(int space, unsigned long start,
                                unsigned long end, int kind,
                                char *section, char *label)
{
    char line[256];
    char *type;

    if (kind < 0)
        type = (char *)"UNUSED";
    else if (space == 0)
        type = (char *)"CODE";
    else if (kind != 0)
        type = (char *)"DATA";
    else
        type = (char *)"CONST";
    if (kind < 0)
        sprintf(line, "%04lX   %04lX  %5lu  UNUSED",
                start & 0xffffUL, end & 0xffffUL, end - start + 1UL);
    else if (section != (char *)0 && *section != '\0')
        sprintf(line, "%04lX   %04lX  %5lu  %-8s%-18s%s",
                start & 0xffffUL, end & 0xffffUL, end - start + 1UL,
                type, label == (char *)0 ? "" : label, section);
    else if (label == (char *)0 || *label == '\0')
        sprintf(line, "%04lX   %04lX  %5lu  %-6s",
                start & 0xffffUL, end & 0xffffUL, end - start + 1UL,
                type);
    else
        sprintf(line, "%04lX   %04lX  %5lu  %-8s%s",
                start & 0xffffUL, end & 0xffffUL, end - start + 1UL,
                type, label);
    report_line(line);
}

static void report_wrapped_line(char *text)
{
    if (!(ListingHeaderWritten && ListingSourceLines == 0UL))
        list_prepare_line();
    list_text_line(text, 0);
}

static void report_memory_space(int space, char *name)
{
    unsigned long events[1024];
    unsigned long n;
    unsigned long i;
    unsigned long j;
    unsigned long key;
    unsigned long cursor;
    unsigned long start;
    unsigned long end;
    unsigned long length;
    unsigned long next_start;
    unsigned long next_length;
    unsigned long first_event;
    char section[64];
    char label[128];
    char ename[128];
    unsigned long evalue;
    unsigned long espace;

    if (!SpaceUsed[space])
        return;
    report_line(name);
    report_blank();
    report_wrapped_line((char *)"Start  End  Length  Type    Label             Section           Overlay Address");
    n = 0UL;
    for (i = 0UL; i < OutputEventCount && n < 1024UL; ++i)
        if (OutputEvents[i].space == space && OutputEvents[i].count != 0UL)
            events[n++] = i;
    for (i = 1UL; i < n; ++i) {
        key = events[i];
        j = i;
        while (j != 0UL && OutputEvents[events[j - 1UL]].address >
               OutputEvents[key].address) {
            events[j] = events[j - 1UL];
            --j;
        }
        events[j] = key;
    }
    cursor = 0UL;
    for (i = 0UL; i < n; ++i) {
        if (OutputEvents[events[i]].address < cursor)
            continue;
        start = OutputEvents[events[i]].address;
        if (start > cursor)
            report_memory_block(space, cursor, start - 1UL, -1,
                                (char *)0, (char *)0);
        first_event = events[i];
        length = OutputEvents[events[i]].count;
        if (OutputEvents[events[i]].virtual_space == 4UL &&
            OutputEvents[events[i]].virtual_address != 0UL &&
            OutputEvents[events[i]].virtual_address > length)
            length = OutputEvents[events[i]].virtual_address;
        if (space == 3 && length > 1UL)
            length /= 2UL;
        end = start + length - 1UL;
        while (space != 0 && i + 1UL < n &&
               (OutputEvents[events[i + 1UL]].kind ==
                OutputEvents[first_event].kind ||
                (OutputEvents[first_event].kind == 0 &&
                 OutputEvents[events[i + 1UL]].kind == 1 &&
                 OutputEvents[events[i + 1UL]].flags == 0x28UL)) &&
               strcmp(OutputEvents[events[i + 1UL]].section_name,
                      OutputEvents[first_event].section_name) == 0) {
            next_start = OutputEvents[events[i + 1UL]].address;
            next_length = OutputEvents[events[i + 1UL]].count;
            if (space == 3 && next_length > 1UL)
                next_length /= 2UL;
            if (next_start > end + 1UL)
                break;
            if (next_start + next_length - 1UL > end)
                end = next_start + next_length - 1UL;
            ++i;
        }
        label[0] = '\0';
        section[0] = '\0';
        for (j = 0UL; j < ReportSymbolCount; ++j) {
            if (!sym_object_info(ReportSymbolIndices[j], ename,
                                 sizeof(ename), &evalue, &espace,
                                 (unsigned long *)0, (unsigned long *)0,
                                 (unsigned long *)0, (unsigned long *)0,
                                 (unsigned long *)0, (int *)0, (int *)0))
                continue;
            if (espace == (unsigned long)space && evalue == start &&
                strcmp(ename, "tab") != 0 &&
                (space != 1 || OutputEvents[first_event].section_name[0] !=
                 '\0')) {
                strcpy(label, ename);
                break;
            }
        }
        if (OutputEvents[first_event].section_name[0] != '\0' &&
            strcmp(OutputEvents[first_event].section_name, "GLOBAL") != 0)
            strcpy(section, OutputEvents[first_event].section_name);
        report_memory_block(space, start, end,
                            OutputEvents[first_event].kind, section, label);
        cursor = end + 1UL;
    }
    if (cursor <= 0xffffUL)
        report_memory_block(space, cursor, 0xffffUL, -1,
                            (char *)0, (char *)0);
}

static void listing_report_memory(void)
{
    unsigned long i;

    materialize_bsc_report_spans();
    if (ListingNoBreakEver) {
        for (i = 0UL; i < 2UL; ++i)
            report_blank();
        for (; i < 11UL; ++i)
            list_newline();
        report_new_page();
        report_line((char *)"                         Memory Utilization Report");
        report_blank();
        report_blank();
        report_memory_space(1, (char *)"X Memory");
        if (SpaceUsed[1] && SpaceUsed[2]) {
            report_blank();
            report_blank();
        }
        report_memory_space(2, (char *)"Y Memory");
        if ((SpaceUsed[1] || SpaceUsed[2]) && SpaceUsed[3]) {
            report_blank();
            report_blank();
        }
        report_memory_space(3, (char *)"L Memory");
        if ((SpaceUsed[1] || SpaceUsed[2] || SpaceUsed[3]) &&
            SpaceUsed[0]) {
            report_blank();
            report_blank();
        }
        report_memory_space(0, (char *)"P Memory");
        report_trailing_blank();
        return;
    }
    if (!ListingNoBreakEver)
        report_start();
    report_line((char *)"                         Memory Utilization Report");
    report_blank();
    report_blank();
    report_memory_space(1, (char *)"X Memory");
    if (SpaceUsed[1] && SpaceUsed[2]) {
        report_blank();
        report_blank();
    }
    report_memory_space(2, (char *)"Y Memory");
    if ((SpaceUsed[1] || SpaceUsed[2]) && SpaceUsed[3]) {
        report_blank();
        report_blank();
    }
    report_memory_space(3, (char *)"L Memory");
    if ((SpaceUsed[1] || SpaceUsed[2] || SpaceUsed[3]) &&
        SpaceUsed[0]) {
        report_blank();
        report_blank();
    }
    report_memory_space(0, (char *)"P Memory");
    report_trailing_blank();
}

static void data_word(unsigned long value)
{
    if (Pass == 2UL) {
        if (LastDataCount < 64)
            LastDataWords[LastDataCount++] = value & 0xffffffUL;
        record_word(value, 0);
    }
    ++ProgramCounter;
    ++LoadCounter;
}

static void reverse_l_records(unsigned long first_record)
{
    unsigned long i;
    unsigned long word;

    if (CurrentSpace != 3 || RecordCount <= first_record)
        return;
    for (i = first_record; i + 1UL < RecordCount; i += 2UL) {
        if (Records[i].space != 3 || Records[i + 1UL].space != 3)
            break;
        word = Records[i].word;
        Records[i].word = Records[i + 1UL].word;
        Records[i + 1UL].word = word;
    }
}

static int emit_quoted(char *text)
{
    unsigned long bytes[96];
    unsigned long nbytes;
    unsigned long i;
    unsigned long word_value;
    char quote;
    char first_quote;
    char *p;
    char *sep;

    p = text;
    while (isspace((unsigned char)*p))
        ++p;
    if (*p != '\'' && *p != '"')
        return 0;
    first_quote = *p;
    nbytes = 0UL;
    for (;;) {
        quote = *p++;
        while (*p != '\0') {
            if (*p == quote) {
                if (p[1] == quote) {
                    if (nbytes < sizeof(bytes) / sizeof(bytes[0]))
                        bytes[nbytes++] = (unsigned char)quote;
                    p += 2;
                    continue;
                }
                ++p;
                break;
            }
            if (nbytes < sizeof(bytes) / sizeof(bytes[0]))
                bytes[nbytes++] = (unsigned char)*p;
            ++p;
        }
        while (isspace((unsigned char)*p))
            ++p;
        sep = p;
        if (sep[0] != '+' || sep[1] != '+')
            break;
        p += 2;
        while (isspace((unsigned char)*p))
            ++p;
        if (*p != '\'' && *p != '"')
            return 0;
    }
    if (*p != '\0')
        return 0;
    if (nbytes == 0UL)
        data_word(0UL);
    else if (nbytes == 1UL && first_quote == '\'')
        data_word(bytes[0]);
    else {
        for (i = 0UL; i < (nbytes + 2UL) / 3UL; ++i) {
            word_value = 0UL;
            if (i * 3UL < nbytes)
                word_value |= bytes[i * 3UL] << 16;
            if (i * 3UL + 1UL < nbytes)
                word_value |= bytes[i * 3UL + 1UL] << 8;
            if (i * 3UL + 2UL < nbytes)
                word_value |= bytes[i * 3UL + 2UL];
            data_word(word_value);
        }
    }
    return 1;
}

static int emit_hex_words(char *text, unsigned long limit)
{
    unsigned long parts[3];
    unsigned long i;
    unsigned long carry;
    unsigned long value;
    char *p;
    char *q;
    int n;

    p = text;
    while (isspace((unsigned char)*p))
        ++p;
    if (*p == '$')
        ++p;
    else if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X'))
        p += 2;
    else
        return 0;
    q = p;
    while (isxdigit((unsigned char)*q))
        ++q;
    if (q == p || *q != '\0')
        return 0;
    parts[0] = parts[1] = parts[2] = 0UL;
    while (p != q) {
        if (*p >= '0' && *p <= '9')
            value = (unsigned long)(*p - '0');
        else
            value = (unsigned long)(tolower((unsigned char)*p) - 'a' + 10);
        carry = value;
        for (i = 3UL; i-- > 0UL;) {
            value = (parts[i] << 4) | carry;
            carry = value >> 24;
            parts[i] = value & 0xffffffUL;
        }
        ++p;
    }
    n = parts[0] != 0UL ? 3 : parts[1] != 0UL ? 2 : 1;
    if (limit != 0UL && (unsigned long)n > limit)
        n = (int)limit;
    for (i = 0UL; i < (unsigned long)n; ++i)
        data_word(parts[3 - n + i]);
    return n;
}

static int text_has_float(char *text)
{
    char *p;

    p = text;
    while (*p != '\0') {
        if (*p == '.' || *p == 'e' || *p == 'E')
            return 1;
        ++p;
    }
    return 0;
}

static void emit_long_expr(char *text)
{
    void *value;
    unsigned long integer;
    unsigned long high;
    unsigned long low;
    double scaled;
    double rounded;

    value = eval_expr_text(text);
    if (value == (void *)0) {
        data_word(0UL);
        data_word(0UL);
        return;
    }
    if (expr_is_unresolved(value)) {
        free_expr(value);
        integer = parse_expr_value(text);
        high = (integer & 0x80000000UL) != 0UL ? 0xffffffUL : 0UL;
        low = integer & 0xffffffUL;
    } else if (text_has_float(text)) {
        scaled = expr_as_double(value) * 140737488355328.0;
        if (scaled >= 0.0)
            rounded = floor(scaled + 0.5);
        else
            rounded = ceil(scaled - 0.5);
        if (rounded < 0.0)
            rounded += 281474976710656.0;
        high = (unsigned long)floor(rounded / 16777216.0) & 0xffffffUL;
        low = (unsigned long)(rounded -
                              (double)high * 16777216.0) & 0xffffffUL;
        free_expr(value);
    } else {
        integer = expr_as_int32(value);
        high = (integer & 0x80000000UL) != 0UL ? 0xffffffUL : 0UL;
        low = integer & 0xffffffUL;
        free_expr(value);
    }
    data_word(high);
    data_word(low);
    --ProgramCounter;
    if (!LoadPhysical)
        --LoadCounter;
}

static int data_expr_unresolved(char *text)
{
    void *value;
    int result;

    value = eval_expr_text(text);
    if (value == (void *)0)
        return 0;
    result = Pass == 2UL && expr_is_unresolved(value);
    free_expr(value);
    return result;
}

static int short_hex_literal(char *text)
{
    char *p;
    int count;

    p = text;
    while (isspace((unsigned char)*p))
        ++p;
    if (*p == '$')
        ++p;
    else if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X'))
        p += 2;
    else
        return 0;
    count = 0;
    while (isxdigit((unsigned char)*p)) {
        ++count;
        ++p;
    }
    while (isspace((unsigned char)*p))
        ++p;
    return count != 0 && count <= 6 && *p == '\0';
}

static void emit_data(void)
{
    char storage[32][128];
    char *args[32];
    int n;
    int i;
    unsigned long record_start;
    unsigned long value;

    n = split_csv(Op1Field, args, storage, 32);
    if (n == 1 && args[0][0] == '\0')
        n = 0;
    record_start = RecordCount;
    for (i = 0; i < n; ++i) {
        unsigned long before;

        if (args[i][0] == '\0') {
            data_word(0UL);
            continue;
        }
        before = ProgramCounter;
        if (emit_quoted(args[i])) {
            if (CurrentSpace == 3 && ProgramCounter > before + 1UL)
                ProgramCounter = before + 1UL;
            if (CurrentSpace == 3 && !LoadPhysical &&
                LoadCounter > before + 1UL)
                LoadCounter = before + 1UL;
            continue;
        }
        if (CurrentSpace == 3 && is_name(MnemField, "dc") &&
            short_hex_literal(args[i]) &&
            (strcmp(args[i], "*") != 0 || InLineReplay)) {
            emit_long_expr(args[i]);
            continue;
        }
        if (emit_hex_words(args[i],
                           is_name(MnemField, "dcl") ? 2UL : 0UL)) {
            if (CurrentSpace == 3 && is_name(MnemField, "dc") &&
                ProgramCounter > before + 1UL)
                ProgramCounter = before + 1UL;
            if (CurrentSpace == 3 && is_name(MnemField, "dc") &&
                !LoadPhysical && LoadCounter > before + 1UL)
                LoadCounter = before + 1UL;
            continue;
        }
        maybe_add_lcv_section(args[i]);
        if (CurrentSpace == 3 && is_name(MnemField, "dc") &&
            (strcmp(args[i], "*") != 0 || InLineReplay)) {
            emit_long_expr(args[i]);
            continue;
        }
        {
            void *checked;

            checked = eval_expr_text(args[i]);
            if (checked == (void *)0) {
                unsigned long error_before;

                error_before = ErrorCount;
                value = parse_expr_value(args[i]);
                if (ErrorCount == error_before)
                    data_word(value);
                continue;
            }
            free_expr(checked);
        }
        if (data_expr_unresolved(args[i])) {
            unsigned long error_before;

            error_before = ErrorCount;
            value = parse_expr_value(args[i]);
            if (ErrorCount == error_before &&
                ErrorCount == ListingErrorBase) {
                DataRelocArmed = 1;
                data_word(value);
                DataRelocArmed = 0;
            }
            continue;
        }
        value = parse_expr_value(args[i]);
        DataRelocArmed = 1;
        data_word(value);
        DataRelocArmed = 0;
        if (is_name(MnemField, "dcl") && ProgramCounter == before + 1UL)
            data_word(0UL);
    }
    reverse_l_records(record_start);
}

static void emit_fill(void)
{
    char storage[4][128];
    char *args[4];
    unsigned long count;
    unsigned long allocation;
    unsigned long value;
    int argc;
    int nwords;
    unsigned long record_start;

    argc = split_csv(Op1Field, args, storage, 4);
    if (argc < 1)
        return;
    count = parse_expr_value(args[0]);
    record_start = RecordCount;
    allocation = count;
    if (argc < 2 && is_name(MnemField, "bsm"))
        allocation = count < 8UL ? 7UL : count - 1UL;
    value = (unsigned long)0;
    if (argc >= 2)
        value = parse_expr_value(args[1]);
    if (count == 0UL) {
        if (Pass == 2UL) {
            CurInstrFieldMsg = Op1Field;
            err("Expression must be greater than zero");
        }
        return;
    }
    nwords = 0;
    if (argc >= 2)
        nwords = emit_hex_words(args[1], count);
    if (nwords == 0) {
        if (Pass == 2UL) {
            if (LastDataCount < 64)
                LastDataWords[LastDataCount++] = value & 0xffffffUL;
            record_word(value, 0);
        }
        ++ProgramCounter;
        ++LoadCounter;
        if (argc >= 2 && allocation != 0UL)
            --allocation;
    }
    if ((unsigned long)nwords < allocation)
        ProgramCounter += allocation - (unsigned long)nwords;
    if ((unsigned long)nwords < allocation)
        LoadCounter += allocation - (unsigned long)nwords;
    reverse_l_records(record_start);
}

static void process_directive(void)
{
    unsigned long value;
    char name[256];
    char candidate[512];
    char macro_line[ASM56000_INPUT_LINE_CAP];
    char *p;
    char *q;
    FILE *probe;
    int macro_depth;
    int nested_macro;

    PreviousAddressWrite = 0;
    DirectiveFailed = 0;

    if (MnemField != (char *)0 && Pass == 2UL &&
        (is_name(MnemField, "equ") || is_name(MnemField, "set") ||
         is_name(MnemField, "=") || is_name(MnemField, "ds") || is_name(MnemField, "dsb") ||
         is_name(MnemField, "dsr") || is_name(MnemField, "dsm") ||
         is_name(MnemField, "dsmr"))) {
        int is_def;

        is_def = is_name(MnemField, "equ") || is_name(MnemField, "set");
        if (is_def && (LabelField == (char *)0 || *LabelField == '\0')) {
            CurInstrFieldMsg = Op1Field;
            err(is_name(MnemField, "equ") ? "EQU requires label" :
                                             "SET requires label");
            DirectiveFailed = 1;
            return;
        }
        if (Op1Field == (char *)0 || *Op1Field == '\0') {
            CurInstrFieldMsg = (char *)0;
            err("Missing expression");
            ErrOnThisLine = 0UL;
            err("Possible invalid white space between operands or arguments");
            DirectiveFailed = 1;
            return;
        }
    }

    /* Structured-control directives are consumed by the original SCS text
       expander.  Keep them as transparent source directives until the
       generated-line engine is present; in particular, do not mistake
       `.IF` for classic conditional assembly. */
    if (MnemField != (char *)0 &&
        ((MnemField[0] == '.' &&
          find_scs_directive(MnemField + 1) != (void *)0) ||
         is_name(MnemField, "scsjmp") || is_name(MnemField, "scsreg"))) {
        process_scs_directive();
        return;
    }

    if (is_name(MnemField, "if")) {
        if (ConditionDepth < 32) {
            Conditions[ConditionDepth].parent_active = ConditionsActive;
            Conditions[ConditionDepth].active = ConditionsActive &&
                parse_expr_value(Op1Field) != 0UL;
            Conditions[ConditionDepth].seen_else = 0;
            ++ConditionDepth;
            ConditionsActive = Conditions[ConditionDepth - 1].active;
        }
        return;
    }
    if (is_name(MnemField, "else")) {
        if (ConditionDepth == 0) {
            CurInstrFieldMsg = (char *)0;
            err("ELSE without associated IF directive");
        } else if (!Conditions[ConditionDepth - 1].seen_else) {
            Conditions[ConditionDepth - 1].seen_else = 1;
            Conditions[ConditionDepth - 1].active =
                Conditions[ConditionDepth - 1].parent_active &&
                !Conditions[ConditionDepth - 1].active;
            ConditionsActive = Conditions[ConditionDepth - 1].active;
        }
        return;
    }
    if (is_name(MnemField, "endif")) {
        if (ConditionDepth == 0) {
            CurInstrFieldMsg = (char *)0;
            err("ENDIF without associated IF directive");
        } else
            --ConditionDepth;
        ConditionsActive = ConditionDepth == 0 ? 1 :
                           Conditions[ConditionDepth - 1].active;
        return;
    }

    if (is_name(MnemField, "org")) {
        char storage[4][128];
        char *args[4];
        char key[32];
        char expr[128];
        char load_key[32];
        char load_expr[128];
        int key_index;
        int load_key_index;
        int n;

        flush_pending_labels();
        if (!org_operands_valid(Op1Field)) {
            DirectiveFailed = 1;
            return;
        }
        if (OrgKey[0] != '\0') {
            key_index = org_key_index(OrgKey);
            if (key_index >= 0)
                OrgValues[key_index] = ProgramCounter;
        }
        if (LoadOrgKey[0] != '\0') {
            load_key_index = load_org_key_index(LoadOrgKey);
            if (load_key_index >= 0)
                LoadOrgValues[load_key_index] = LoadCounter;
        }
        n = split_csv(Op1Field, args, storage, 4);
        if (n < 1)
            return;
        org_selector(args[0], key, expr);
        CurrentSpace = space_from_text(args[0]);
        key_index = org_key_index(key);
        if (expr[0] != '\0' && key_index >= 0)
            OrgAbs[key_index] = 1;
        if (expr[0] == '\0' && key_index >= 0)
            value = OrgValues[key_index];
        else if (expr[0] == '\0')
            value = ProgramCounter;
        else
            value = parse_expr_value(expr);
        ProgramCounter = value;
        strcpy(OrgKey, key);
        if (n >= 2) {
            org_selector(args[1], load_key, load_expr);
            CurrentLoadSpace = space_from_text(args[1]);
            load_key_index = load_org_key_index(load_key);
            if (load_expr[0] == '\0' && load_key_index >= 0)
                value = LoadOrgValues[load_key_index];
            else if (load_expr[0] == '\0')
                value = LoadCounter;
            else
                value = parse_expr_value(load_expr);
            LoadCounter = value;
            strcpy(LoadOrgKey, load_key);
            LoadPhysical = CurrentLoadSpace == 3;
        } else {
            CurrentLoadSpace = CurrentSpace;
            LoadCounter = ProgramCounter;
            strcpy(LoadOrgKey, key);
            LoadPhysical = 0;
        }
        ++RecordGeneration;
        return;
    }
    if (is_name(MnemField, "ident")) {
        if (Op1Field == (char *)0 || *Op1Field == '\0') {
            CurInstrFieldMsg = (char *)0;
            err("IDENT directive must contain version number");
        } else if (Op2Field == (char *)0 || *Op2Field == '\0') {
            CurInstrFieldMsg = Op1Field;
            err("IDENT directive must contain revision number");
        }
        return;
    }
    if (is_name(MnemField, "opt")) {
        if (Op1Field == (char *)0 || *Op1Field == '\0') {
            CurInstrFieldMsg = (char *)0;
            err("Missing option");
        } else if (find_option(Op1Field) == (void *)0 &&
                 strchr(Op1Field, ',') == (char *)0)
        {
            CurInstrFieldMsg = Op1Field;
            err("Illegal option");
        } else {
            CurInstrFieldMsg = (char *)0;
            pseudo_dispatch("opt");
        }
        return;
    }
    if (is_name(MnemField, "radix")) {
        value = parse_expr_value(Op1Field);
        if (value != 2UL && value != 10UL && value != 16UL) {
            CurInstrFieldMsg = Op1Field;
            err("Invalid radix expression");
        }
        return;
    }
    if (is_name(MnemField, "mode")) {
        if (AbsoluteMode) {
            CurInstrFieldMsg = Op1Field;
            warn("Directive not allowed in command line absolute mode");
        } else if (Op1Field == (char *)0 ||
                   (!is_name(Op1Field, "absolute") &&
                    !is_name(Op1Field, "relative"))) {
            CurInstrFieldMsg = Op1Field;
            err_s("Invalid mode", Op1Field);
        } else
            ModeReloc = is_name(Op1Field, "relative");
        return;
    }
    if (is_name(MnemField, "force")) {
        if (Op1Field == (char *)0 ||
            (!is_name(Op1Field, "short") && !is_name(Op1Field, "long") &&
             !is_name(Op1Field, "normal") && !is_name(Op1Field, "none"))) {
            CurInstrFieldMsg = Op1Field;
            err_s("Invalid force type", Op1Field);
        } else if (is_name(Op1Field, "short"))
            ForceMode = 0x2000000UL;
        else if (is_name(Op1Field, "long"))
            ForceMode = 0x1000000UL;
        else
            ForceMode = 0UL;
        return;
    }
    if (is_name(MnemField, "title")) {
        listing_copy_quoted(Op1Field, ListingTitle, sizeof(ListingTitle));
        if (ListingHeaderWritten && !ListingPagePending) {
            strcpy(ListingHeaderTitle, ListingTitle);
            strcpy(ListingHeaderSubtitle, ListingSubtitle);
        }
        return;
    }
    if (is_name(MnemField, "stitle")) {
        listing_copy_quoted(Op1Field, ListingSubtitle,
                            sizeof(ListingSubtitle));
        if (ListingHeaderWritten && !ListingPagePending) {
            strcpy(ListingHeaderTitle, ListingTitle);
            strcpy(ListingHeaderSubtitle, ListingSubtitle);
        }
        return;
    }
    if (is_name(MnemField, "prctl")) {
        char storage[4][128];
        char *args[4];
        int n;
        int i;

        n = split_csv(Op1Field, args, storage, 4);
        PendingPrctlLength = 0;
        for (i = 0; i < n && PendingPrctlLength <
                         (int)sizeof(PendingPrctl); ++i) {
            if (args[i][0] == '\'' || args[i][0] == '"') {
                if (strlen(args[i]) >= 3UL)
                    PendingPrctl[PendingPrctlLength++] = args[i][1];
            } else {
                PendingPrctl[PendingPrctlLength++] =
                    (char)(parse_expr_value(args[i]) & 0xffUL);
            }
        }
        return;
    }
    if (is_name(MnemField, "list") || is_name(MnemField, "nolist")) {
        ListingEnabled = is_name(MnemField, "list");
        return;
    }
    if (is_name(MnemField, "page")) {
        char storage[8][128];
        char *args[8];
        int n;

        if (Op1Field == (char *)0 || *Op1Field == '\0') {
            strcpy(ListingHeaderTitle, ListingTitle);
            strcpy(ListingHeaderSubtitle, ListingSubtitle);
            ListingPagePending = 1;
            return;
        }
        n = (Op1Field == (char *)0 || *Op1Field == '\0') ? 0 :
            split_csv(Op1Field, args, storage, 8);
        if (n < 1 || args[0][0] == '-' ||
            parse_expr_value(args[0]) > 512UL ||
            (n > 1 && (args[1][0] == '-' ||
                       parse_expr_value(args[1]) > 512UL)) ||
            (n > 1 && parse_expr_value(args[0]) == 3UL &&
             parse_expr_value(args[1]) == 3UL)) {
            CurInstrFieldMsg = Op1Field;
            if ((n >= 1 && args[0][0] == '-') ||
                (n > 1 && args[1][0] == '-'))
                err("Expression cannot have a negative value");
            else if ((n >= 1 && parse_expr_value(args[0]) > 512UL) ||
                     (n > 1 && parse_expr_value(args[1]) > 512UL))
                err("Expression result too large");
            else
                err("Invalid page length specified");
        } else {
            if (ListingNoBreak && ListingNoBreakEver && OptMex && n > 1 &&
                parse_expr_value(args[1]) != 0UL) {
                ListingSourceLines = 0UL;
                ListingPage += 21;
            }
            ListingWidth = (int)parse_expr_value(args[0]);
            if (n > 1)
                ListingPageLength = (int)parse_expr_value(args[1]);
            if (n > 4)
                ListingIndent = (int)parse_expr_value(args[4]);
            if (ListingPageLength == 0)
                ListingNoBreakEver = 1;
            ListingNoBreak = ListingPageLength == 0;
        }
        return;
    }
    if (is_name(MnemField, "lstcol") || is_name(MnemField, "tabs")) {
        char storage[8][128];
        char *args[8];
        int n;
        int i;

        n = (Op1Field == (char *)0 || *Op1Field == '\0') ? 0 :
            split_csv(Op1Field, args, storage, 8);
        for (i = 0; i < n; ++i) {
            if (args[i][0] == '-' || parse_expr_value(args[i]) > 255UL) {
                CurInstrFieldMsg = Op1Field;
                err("Expression result too large");
                break;
            }
        }
        if (ErrOnThisLine == 0UL) {
            if (is_name(MnemField, "tabs") && n > 0)
                TabWidth = parse_expr_value(args[0]);
            else if (n == 0 || Op1Field == (char *)0 ||
                     *Op1Field == '\0') {
                ListingLabelWidth = 10;
                ListingOpcodeWidth = 8;
                ListingOperandWidth = 10;
                ListingXWidth = 12;
                ListingYWidth = 12;
            } else {
                if (n > 0) ListingLabelWidth = (int)parse_expr_value(args[0]);
                if (n > 1) ListingOpcodeWidth = (int)parse_expr_value(args[1]);
                if (n > 2) ListingOperandWidth = (int)parse_expr_value(args[2]);
                if (n > 3) ListingXWidth = (int)parse_expr_value(args[3]);
                if (n > 4) ListingYWidth = (int)parse_expr_value(args[4]);
            }
        }
        return;
    }
    if (is_name(MnemField, "maclib") &&
        (Op1Field == (char *)0 || *Op1Field == '\0')) {
        CurInstrFieldMsg = (char *)0;
        err("Syntax error - expected quote");
        CurInstrFieldMsg = (char *)0;
        ErrOnThisLine = 0UL;
        err("Missing pathname");
        return;
    }
    if (is_name(MnemField, "buffer")) {
        char storage[4][128];
        char *args[4];
        int n;

        CurInstrFieldMsg = (char *)0;
        if (LabelField != (char *)0 && *LabelField != '\0')
            warn("Label field ignored");
        n = split_csv(Op1Field, args, storage, 4);
        if (n < 2 || args[0][0] == '\0' ||
            (tolower((unsigned char)args[0][0]) != 'm' &&
             tolower((unsigned char)args[0][0]) != 'r')) {
            CurInstrFieldMsg = Op1Field;
            err("Invalid buffer type");
            BufferActive = 1;
            BufferStart = ProgramCounter;
            BufferSize = 0UL;
            return;
        }
        if (args[1][0] == '-') {
            CurInstrFieldMsg = Op1Field;
            err("Storage block size out of range");
            return;
        }
        value = parse_expr_value(args[1]);
        if (value == 0UL || value > 0x100000UL) {
            CurInstrFieldMsg = Op1Field;
            err("Storage block size out of range");
            return;
        }
        BufferActive = 1;
        BufferStart = ProgramCounter;
        BufferSize = value;
        space_extent(CurrentSpace, ProgramCounter, value);
        return;
    }
    if (is_name(MnemField, "endbuf")) {
        if (!BufferActive) {
            CurInstrFieldMsg = (char *)0;
            err("ENDBUF without associated BUFFER directive");
            ErrOnThisLine = 0UL;
            if (ProgramCounter != 0UL)
                warn("Runtime location counter overflow");
            return;
        }
        if (BufferSize == 0UL) {
            CurInstrFieldMsg = (char *)0;
            err("ENDBUF without associated BUFFER directive");
            ErrOnThisLine = 0UL;
        }
        if (ProgramCounter > BufferStart + BufferSize) {
            CurInstrFieldMsg = (char *)0;
            err("Data allocation exceeds buffer size");
        } else if (ProgramCounter < BufferStart + BufferSize) {
            ProgramCounter = BufferStart + BufferSize;
        }
        if (LoadCounter < BufferStart + BufferSize)
            LoadCounter = BufferStart + BufferSize;
        BufferActive = 0;
        return;
    }
    if (is_name(MnemField, "baddr")) {
        char storage[4][128];
        char *args[4];
        int n;

        n = split_csv(Op1Field, args, storage, 4);
        if (n < 2 || args[0][0] == '\0' ||
            (tolower((unsigned char)args[0][0]) != 'm' &&
             tolower((unsigned char)args[0][0]) != 'r')) {
            CurInstrFieldMsg = Op1Field;
            err("Invalid buffer type");
            return;
        }
        if (args[1][0] == '-') {
            CurInstrFieldMsg = Op1Field;
            err("Storage block size out of range");
            return;
        }
        value = parse_expr_value(args[1]);
        if (value == 0UL || value > 0x100000UL) {
            CurInstrFieldMsg = Op1Field;
            err("Storage block size out of range");
            return;
        }
        if (value != 0UL) {
            ProgramCounter = ((ProgramCounter + value - 1UL) / value) * value;
            LoadCounter = ((LoadCounter + value - 1UL) / value) * value;
            space_extent(CurrentSpace, ProgramCounter, 1UL);
        }
        return;
    }
    if (is_name(MnemField, "dup") || is_name(MnemField, "dupa") ||
        is_name(MnemField, "dupc") || is_name(MnemField, "dupf")) {
        process_dup();
        return;
    }
    if (is_name(MnemField, "dc") || is_name(MnemField, "dcw") ||
        is_name(MnemField, "dcl") || is_name(MnemField, "dcb")) {
        if (Op2Field != (char *)0 && *Op2Field != '\0') {
            CurInstrFieldMsg = Op1Field;
            err("Extra fields ignored");
            ErrOnThisLine = 0UL;
            err("Possible invalid white space between operands or arguments");
        }
        emit_data();
        if ((Op1Field == (char *)0 || *Op1Field == '\0') &&
            Pass == 2UL) {
            CurInstrFieldMsg = (char *)0;
            err("Missing expression");
        }
        return;
    }
    if (is_name(MnemField, "bsc") || is_name(MnemField, "bsm") ||
        is_name(MnemField, "bsr")) {
        emit_fill();
        return;
    }
    if (is_name(MnemField, "ds") || is_name(MnemField, "dsb") ||
        is_name(MnemField, "dsr") || is_name(MnemField, "dsm") ||
        is_name(MnemField, "dsmr")) {
        value = parse_expr_value(Op1Field);
        if ((is_name(MnemField, "dsm") || is_name(MnemField, "dsmr")) &&
            value != 0UL)
            ProgramCounter = ((ProgramCounter + value - 1UL) / value) * value;
        space_extent(CurrentLoadSpace, LoadCounter,
                     value * (LoadPhysical && CurrentLoadSpace == 3 ?
                              2UL : 1UL));
        ProgramCounter += value;
        LoadCounter += value * (LoadPhysical && CurrentLoadSpace == 3 ?
                                2UL : 1UL);
        if (!LoadPhysical && CurrentLoadSpace == CurrentSpace)
            LoadCounter = ProgramCounter;
        return;
    }
    if (is_name(MnemField, "align")) {
        value = parse_expr_value(Op1Field);
        if (value != 0UL)
            while ((ProgramCounter % value) != 0UL)
                ++ProgramCounter;
        if (value != 0UL)
            while ((LoadCounter % value) != 0UL)
                ++LoadCounter;
        return;
    }
    if (is_name(MnemField, "end")) {
        void *end_value;

        if ((Pass == 1UL || (Pass == 2UL && !AbsoluteMode)) &&
            Op1Field != (char *)0 && *Op1Field != '\0') {
            end_value = eval_expr_text(Op1Field);
            if (end_value != (void *)0) {
                if (Pass == 2UL)
                    obj_log_add(OL_END, obj_next_seq(), 0UL, 0UL,
                                eval_last_text());
                free_expr(end_value);
            }
        }
        flush_pending_labels();
        StopInput = 1;
        return;
    }
    if (is_name(MnemField, "macro")) {
        macro_depth = 0;
        strcpy(macro_line, RawLineBuf);
        MacroDirectiveListed = 1;
        macro_begin(LabelField, Op1Field);
        if (Pass == 2UL && OptMd)
            list_source(ProgramCounter, 0);
        if (macro_definition_rejected()) {
            macro_end();
            strcpy(RawLineBuf, macro_line);
            parse_line();
            return;
        }
        nested_macro = 0;
        while (get_line()) {
            nested_macro = 0;
            if (parse_line()) {
                if (is_name(MnemField, "endm")) {
                    if (macro_depth == 0) {
                        if (Pass == 2UL && OptMd)
                            list_macro_source();
                        break;
                    }
                    --macro_depth;
                } else if (is_name(MnemField, "macro") ||
                           is_name(MnemField, "dup") ||
                           is_name(MnemField, "dupa") ||
                           is_name(MnemField, "dupc") ||
                           is_name(MnemField, "dupf"))
                    nested_macro = 1;
            }
            if (Pass == 2UL && OptMd)
                list_macro_source();
            macro_add_line(RawLineBuf);
            if (nested_macro)
                ++macro_depth;
        }
        if (MnemField == (char *)0 || !is_name(MnemField, "endm")) {
            if (Pass == 2UL) {
                ++LineNo;
                err("Unexpected end of file - missing ENDM");
                --LineNo;
            }
        }
        macro_end();
        strcpy(RawLineBuf, macro_line);
        parse_line();
        return;
    }
    if (is_name(MnemField, "pmacro")) {
        if (Op1Field != (char *)0 && *Op1Field != '\0' &&
            !isalpha((unsigned char)Op1Field[0])) {
            CurInstrFieldMsg = Op1Field;
            err("Symbols must start with alphabetic character");
        } else if (Op1Field != (char *)0 && strchr(Op1Field, ',') == (char *)0 &&
                   !macro_is_defined(Op1Field)) {
            CurInstrFieldMsg = Op1Field;
            err_s("Macro not defined", Op1Field);
        }
        macro_purge(Op1Field);
        return;
    }
    if (is_name(MnemField, "endm")) {
        CurInstrFieldMsg = (char *)0;
        if (LabelField != (char *)0 && *LabelField != '\0') {
            warn("Label field ignored");
            ErrOnThisLine = 0UL;
        }
        err("ENDM without associated MACRO directive");
        macro_end();
        return;
    }
    if (is_name(MnemField, "exitm")) {
        CurInstrFieldMsg = (char *)0;
        if (LabelField != (char *)0 && *LabelField != '\0') {
            warn("Label field ignored");
            ErrOnThisLine = 0UL;
        }
        if (InLineReplay)
            input_skip_macro_lines();
        else
            err("EXITM without associated MACRO directive");
        return;
    }
    if (is_name(MnemField, "maclib")) {
        p = Op1Field;
        if (p != (char *)0 && (*p == '\'' || *p == '"'))
            ++p;
        q = p;
        while (q != (char *)0 && *q != '\0' && *q != '\'' && *q != '"')
            ++q;
        if (p != (char *)0 && q > p) {
            memcpy(name, p, (unsigned long)(q - p));
            name[q - p] = '\0';
            macro_set_path(name);
        }
        return;
    }
    if (is_name(MnemField, "include")) {
        p = Op1Field;
        if (p != (char *)0 && (*p == '\'' || *p == '"' || *p == '<'))
            ++p;
        q = p;
        while (q != (char *)0 && *q != '\0' && *q != '\'' &&
               *q != '"' && *q != '>')
            ++q;
        if (p == (char *)0 || q == p || (unsigned long)(q - p) >= sizeof(name))
            return;
        memcpy(name, p, (unsigned long)(q - p));
        name[q - p] = '\0';
        probe = fopen(name, "rb");
        if (probe != (FILE *)0) {
            fclose(probe);
            if (!input_push_file(name)) {
                CurInstrFieldMsg = Op1Field;
                err_s("Cannot open include file", name);
            }
        } else if (IncludePath != (char *)0) {
            sprintf(candidate, "%s/%s", IncludePath, name);
            if (!input_push_file(candidate)) {
                CurInstrFieldMsg = Op1Field;
                err_s("Cannot open include file", name);
            }
        } else {
            CurInstrFieldMsg = Op1Field;
            err_s("Cannot open include file", name);
        }
        return;
    }
    if (is_name(MnemField, "xref")) {
        if (AbsoluteMode && Pass == 2UL) {
            char storage[32][128];
            char *args[32];
            int n;
            int i;

            n = split_csv(Op1Field, args, storage, 32);
            for (i = 0; i < n; ++i) {
                if (sec_check_local(args[i]))
                    continue;
                CurInstrFieldMsg = Op1Field;
                err_s("Symbol undefined on pass 2", args[i]);
                ErrOnThisLine = 0UL;
            }
        }
        sec_xref();
        if (Pass == 2UL && !AbsoluteMode) {
            char storage[32][128];
            char *args[32];
            int n;
            int i;

            n = split_csv(Op1Field, args, storage, 32);
            for (i = 0; i < n; ++i)
                if (args[i][0] != '\0')
                    obj_log_add(OL_XREF, obj_next_seq(),
                                sec_number(CurrentSection), 0UL, args[i]);
        }
    } else if (is_name(MnemField, "define"))
        source_define_set(Op1Field, Op2Field);
    else if (is_name(MnemField, "undef"))
        source_define_remove(Op1Field);
    pseudo_dispatch(MnemField);
}

static int direct_address_register(char *text)
{
    if (text == (char *)0 || text[0] != 'r' || text[1] < '0' ||
        text[1] > '7' || text[2] != '\0')
        return -1;
    return text[1] - '0';
}

static int memory_address_register(char *text)
{
    char *p;

    if (text == (char *)0)
        return -1;
    p = strchr(text, '(');
    if (p == (char *)0 || p[1] != 'r' || p[2] < '0' || p[2] > '7')
        return -1;
    return p[2] - '0';
}

static int needs_rp_nop(void)
{
    int areg;

    if (!get_opt_rp() || !PreviousAddressWrite ||
        !is_name(MnemField, "move"))
        return 0;
    areg = memory_address_register(Op1Field);
    return areg >= 0 && areg == PreviousAddressRegister;
}

static void remember_address_write(void)
{
    int areg;
    char *comma;

    PreviousAddressWrite = 0;
    if (!is_name(MnemField, "move"))
        return;
    areg = direct_address_register(Op2Field);
    if (areg < 0 && Op1Field != (char *)0) {
        comma = strchr(Op1Field, ',');
        if (comma != (char *)0) {
            ++comma;
            while (*comma == ' ' || *comma == '\t')
                ++comma;
            areg = direct_address_register(comma);
        }
    }
    if (areg >= 0) {
        PreviousAddressWrite = 1;
        PreviousAddressRegister = areg;
    }
}

static int PathIsFirstSource;

/* interrupt-vector checks (OPT INTR): absolute code of the first source
   file in the P space */
static int vector_check(void)
{
    return AbsoluteMode && CurrentSpace == 0 && PathIsFirstSource &&
           CurrentAddress < 0x40UL;
}

/* lst_print_reg_note (0041bbb2): a pipeline hazard with OPT RP inserts a
   NOP instruction in front of the current line */
static void insert_rp_nop(void)
{
    char *saved_fields[6];

    saved_fields[0] = LabelField;
    saved_fields[1] = MnemField;
    saved_fields[2] = Op1Field;
    saved_fields[3] = Op2Field;
    saved_fields[4] = Op3Field;
    saved_fields[5] = Op4Field;
    RecordingInstruction = 1;
    proc_instr_name("nop");
    RecordingInstruction = 0;
    if (Pass == 2UL && (!InLineReplay || OptMex))
        list_source(ProgramCounter, asm56000_last_count());
    ProgramCounter += (unsigned long)asm56000_last_count();
    LoadCounter += (unsigned long)asm56000_last_count();
    CurrentAddress = ProgramCounter;
    LabelField = saved_fields[0];
    MnemField = saved_fields[1];
    Op1Field = saved_fields[2];
    Op2Field = saved_fields[3];
    Op3Field = saved_fields[4];
    Op4Field = saved_fields[5];
}

static void reset_input(FILE *fp, unsigned long pass)
{
    input_clear_macro_lines();
    CurSrcFp = fp;
    Pass = pass;
    LineNo = 0UL;
    LineNoBase = 0UL;
    LineTotal = 0UL;
    NoMoreInput = 0;
    PendingLine = 0;
    StopInput = 0;
    ProgramCounter = 0UL;
    LoadCounter = 0UL;
    LoadPhysical = 0;
    ForceMode = 0UL;
    RecordGeneration = 0UL;
    CurrentSpace = 0;
    SourceCexDirective = CommandCexOption;
    SourceOptCex = 0;
    CurrentLoadSpace = 0;
    RawLineBuf[0] = '\0';
    MnemField = (char *)0;
    InLineReplay = 0;
    SourceDefineCount = 0;
    OrgKey[0] = '\0';
    OrgKeyCount = 0;
    memset(OrgKeys, 0, sizeof(OrgKeys));
    memset(OrgValues, 0, sizeof(OrgValues));
    LoadOrgKey[0] = '\0';
    LoadOrgKeyCount = 0;
    memset(LoadOrgKeys, 0, sizeof(LoadOrgKeys));
    memset(LoadOrgValues, 0, sizeof(LoadOrgValues));
}

static int run_pass(char *path, unsigned long pass)
{
    FILE *fp;
    FILE *saved_listing;
    FILE *saved_lstfile;
    unsigned long before;
    unsigned long event_before;
    unsigned long event_record;
    unsigned long source_line;
    unsigned long listing_line;
    unsigned long eof_line;
    char event_name[32];
    int was_active;
    int hazard;
    int suppress_listing;

    if (VerboseOption) {
        fprintf(stderr, "ASM56000: Beginning pass %lu\n", pass);
        fprintf(stderr, "ASM56000: Opening source file %s\n", path);
    }
    fp = fopen(path, "rb");
    if (fp == (FILE *)0) {
        printf("ASM56000: Cannot open source file: %s\n", path);
        return -1;
    }
    if (VerboseOption)
        verbose_source_scan(path, (char *)0);
    saved_listing = Listing;
    saved_lstfile = LstFilePtr;
    suppress_listing = Listing != (FILE *)0 && SourceCount > 1 &&
                       strcmp(path, SourceNames[0]) != 0;
    if (suppress_listing) {
        Listing = (FILE *)0;
        LstFilePtr = (FILE *)0;
    }
    PathIsFirstSource = strcmp(path, SourceNames[0]) == 0;
    reset_input(fp, pass);
    ModeReloc = 1;
    PreviousAddressWrite = 0;
    PreviousAddressRegister = -1;
    ConditionDepth = 0;
    ConditionsActive = 1;
    ScsDepth = 0;
    ScsLabelId = 0;
    ScsForceMode = 0;
    DoEndCount = 0;
    LastInstructionWasRep = 0;
    strcpy(ScsAccumulator, "a");
    strcpy(ScsStepRegister, "x0");
    BufferActive = 0;
    while (!StopInput && get_line()) {
        prepare_source_line();
        ErrOnThisLine = 0UL;
        ListingErrorBase = ErrorCount;
        CurInstrFieldMsg = (char *)0;
        MacroDirectiveListed = 0;
        if (!parse_line()) {
            CurrentAddress = ProgramCounter;
            sync_eval_counters();
            define_label();
            if (Pass == 2UL && (!InLineReplay || OptMex)) {
                if (InLineReplay && OptMd &&
                    (LabelField == (char *)0 ||
                     strncmp(LabelField, "Z_L", 3) != 0))
                    list_macro_source();
                else
                    list_plain_source();
            }
            continue;
        }
        CurrentAddress = ProgramCounter;
        sync_eval_counters();
        event_before = ProgramCounter;
        event_record = RecordCount;
        strcpy(event_name, MnemField == (char *)0 ? (char *)"" : MnemField);
        if ((is_name(MnemField, "if") || is_name(MnemField, "else") ||
             is_name(MnemField, "endif")) &&
            !(MnemField != (char *)0 && MnemField[0] == '.' &&
              find_scs_directive(MnemField + 1) != (void *)0)) {
            was_active = ConditionsActive;
            process_directive();
            if (Pass == 2UL)
                output_event_directive(event_name, event_before,
                                       ProgramCounter, event_record);
            if (Pass == 2UL && (was_active || ConditionsActive))
                list_source(ProgramCounter, 0);
            continue;
        }
        if (!ConditionsActive) {
            if (Pass == 2UL && ListingUnconditional) {
                ListingInactive = 1;
                list_plain_source();
                ListingInactive = 0;
            }
            continue;
        }
        define_label();
        if (find_directive(MnemField, 0) != (void *)0) {
            before = ProgramCounter;
            source_line = LineNo;
            LastDataCount = 0;
            process_directive();
            if (Pass == 2UL)
                output_event_directive(event_name, before,
                                       ProgramCounter, event_record);
            if (Pass == 2UL && (!InLineReplay || OptMex)) {
                listing_line = LineNo;
                LineNo = source_line;
                if (MacroDirectiveListed)
                    ;
                else if (is_name(MnemField, "title") ||
                         is_name(MnemField, "stitle") ||
                         is_name(MnemField, "prctl") ||
                         is_name(MnemField, "list") ||
                         is_name(MnemField, "nolist") ||
                         (is_name(MnemField, "page") &&
                          (Op1Field == (char *)0 || *Op1Field == '\0')))
                    ;
                else if (is_name(event_name, "page") ||
                         is_name(event_name, "lstcol") ||
                         is_name(event_name, "tabs"))
                    list_plain_source();
                else if (ErrorCount != ListingErrorBase &&
                         (is_name(event_name, "buffer") ||
                          is_name(event_name, "baddr")))
                    list_plain_source();
                else if ((event_name[0] == '.' &&
                          find_scs_directive(event_name + 1) != (void *)0) ||
                         is_name(event_name, "scsjmp") ||
                         is_name(event_name, "scsreg"))
                    list_plain_source();
                else if (LastDataCount != 0)
                    list_source(before, LastDataCount);
                else if (is_name(MnemField, "org"))
                    list_source(ProgramCounter, 0);
                else if (is_name(MnemField, "baddr"))
                    list_source(ProgramCounter != before ?
                                ProgramCounter : 0UL, 0);
                else if (is_name(MnemField, "align"))
                    list_source(ProgramCounter, 0);
                else if (is_name(MnemField, "dsm") ||
                         is_name(MnemField, "dsmr"))
                    list_source(ProgramCounter - parse_expr_value(Op1Field),
                                0);
                else
                    list_source(before, 0);
                LineNo = listing_line;
            }
        }
        else if (macro_expand(MnemField, Op1Field)) {
            if (Pass == 2UL && (!InLineReplay || OptMex))
                list_plain_source();
        }
        else if (find_mnemonic(MnemField, 0) != (void *)0) {
            RecordingInstruction = 1;
            proc_instr_name(MnemField);
            RecordingInstruction = 0;
            if (Pass == 2UL)
                output_event_records(event_record, event_name);
            if (Pass == 2UL && (!InLineReplay || OptMex))
                list_source(ProgramCounter, asm56000_last_count());
            ProgramCounter += (unsigned long)asm56000_last_count();
            LoadCounter += (unsigned long)asm56000_last_count();
        }
        else {
            err_s("Unrecognized mnemonic", MnemField);
            if (Pass == 2UL && (!InLineReplay || OptMex))
                list_plain_source();
        }
    }
    if (CurSrcFp != (FILE *)0) {
        fclose(CurSrcFp);
        CurSrcFp = (FILE *)0;
    }
    eof_line = LineNo;
    while (ConditionDepth > 0) {
        CurInstrFieldMsg = (char *)0;
        ErrOnThisLine = 0UL;
        ++LineNo;
        err("Unexpected end of file - missing ENDIF");
        --ConditionDepth;
    }
    while (ScsDepth > 0) {
        ErrOnThisLine = 0UL;
        ++LineNo;
        if (ScsStack[ScsDepth - 1] == 1)
            err("Unexpected end of file - missing ENDIF");
        else if (ScsStack[ScsDepth - 1] == 6)
            err("Unexpected end of file - missing .ENDW");
        else if (ScsStack[ScsDepth - 1] == 7)
            err("Unexpected end of file - missing .UNTIL");
        else if (ScsStack[ScsDepth - 1] == 3)
            err("Unexpected end of file - missing .ENDF");
        else
            err("Unexpected end of file - missing .ENDL");
        --ScsDepth;
    }
    LineNo = eof_line;
    while (sec_depth() != 0UL) {
        if (Pass == 2UL) {
            CurInstrFieldMsg = Op1Field;
            ++LineNo;
            err("Unexpected end of file - missing ENDSEC");
            --LineNo;
        }
        sec_endsec();
    }
    if (suppress_listing) {
        Listing = saved_listing;
        LstFilePtr = saved_lstfile;
    }
    return 1;
}

static void be32(FILE *fp, unsigned long value)
{
    unsigned char b[4];

    b[0] = (unsigned char)((value >> 24) & 0xffUL);
    b[1] = (unsigned char)((value >> 16) & 0xffUL);
    b[2] = (unsigned char)((value >> 8) & 0xffUL);
    b[3] = (unsigned char)(value & 0xffUL);
    fwrite(b, 1, 4, fp);
}

static char CoffLongNames[256][128];
static unsigned long CoffLongOffsets[256];
static int CoffLongCount;
static unsigned long CoffLongNext;

static void coff_long_reset(char *comment)
{
    CoffLongCount = 0;
    CoffLongNext = 4UL + (unsigned long)strlen(comment) + 1UL;
}

static void coff_long_add(char *name)
{
    int i;

    if (name == (char *)0 || strlen(name) < 8UL)
        return;
    for (i = 0; i < CoffLongCount; ++i)
        if (strcmp(CoffLongNames[i], name) == 0)
            return;
    if (CoffLongCount >= 256 || strlen(name) >= sizeof(CoffLongNames[0]))
        return;
    strcpy(CoffLongNames[CoffLongCount], name);
    CoffLongOffsets[CoffLongCount] = CoffLongNext;
    CoffLongNext += (unsigned long)strlen(name) + 1UL;
    ++CoffLongCount;
}

static void coff_long_add_literal(char *name)
{
    int i;

    if (name == (char *)0)
        return;
    for (i = 0; i < CoffLongCount; ++i)
        if (strcmp(CoffLongNames[i], name) == 0)
            return;
    if (CoffLongCount >= 256 || strlen(name) >= sizeof(CoffLongNames[0]))
        return;
    strcpy(CoffLongNames[CoffLongCount], name);
    CoffLongOffsets[CoffLongCount] = CoffLongNext;
    CoffLongNext += (unsigned long)strlen(name) + 1UL;
    ++CoffLongCount;
}

static unsigned long coff_long_offset(char *name)
{
    int i;

    for (i = 0; i < CoffLongCount; ++i)
        if (strcmp(CoffLongNames[i], name) == 0)
            return CoffLongOffsets[i];
    return 0UL;
}

static void coff_long_write(FILE *fp)
{
    int i;

    for (i = 0; i < CoffLongCount; ++i) {
        fwrite(CoffLongNames[i], 1, strlen(CoffLongNames[i]) + 1UL, fp);
    }
}

static void coff_name(FILE *fp, char *name)
{
    unsigned char text[8];
    unsigned long n;
    unsigned long offset;

    memset(text, 0, sizeof(text));
    n = (unsigned long)strlen(name);
    offset = coff_long_offset(name);
    if (offset != 0UL && n >= sizeof(text)) {
        text[4] = (unsigned char)((offset >> 24) & 0xffUL);
        text[5] = (unsigned char)((offset >> 16) & 0xffUL);
        text[6] = (unsigned char)((offset >> 8) & 0xffUL);
        text[7] = (unsigned char)(offset & 0xffUL);
    } else {
        if (n > sizeof(text))
            n = sizeof(text);
        memcpy(text, name, n);
    }
    fwrite(text, 1, sizeof(text), fp);
}

static char *source_base_name(void)
{
    char *base;
    char *slash;
    char *backslash;

    base = SourceName;
    slash = strrchr(base, '/');
    backslash = strrchr(base, '\\');
    if (slash != (char *)0)
        base = slash + 1;
    if (backslash != (char *)0)
        base = backslash + 1;
    return base;
}

static unsigned long CoffSectionNreloc;

static void coff_section_ex(FILE *fp, char *name, unsigned long space,
                            unsigned long address,
                            unsigned long virtual_address,
                            unsigned long virtual_space,
                            unsigned long size,
                         unsigned long scnptr, unsigned long relptr,
                         unsigned long lnnoptr, unsigned long flags)
{
    coff_name(fp, name);
    be32(fp, address); be32(fp, space);
    be32(fp, virtual_address); be32(fp, virtual_space);
    be32(fp, size); be32(fp, scnptr); be32(fp, relptr);
    be32(fp, lnnoptr); be32(fp, CoffSectionNreloc); be32(fp, 0UL);
    be32(fp, flags);
    CoffSectionNreloc = 0UL;
}

static void coff_section_debug(FILE *fp, char *name, unsigned long space,
                               unsigned long address,
                               unsigned long size, unsigned long scnptr,
                               unsigned long relptr, unsigned long lnnoptr,
                               unsigned long nlnno, unsigned long flags)
{
    coff_name(fp, name);
    be32(fp, address); be32(fp, space);
    be32(fp, address); be32(fp, space);
    be32(fp, size); be32(fp, scnptr); be32(fp, relptr);
    be32(fp, lnnoptr); be32(fp, 0UL); be32(fp, nlnno); be32(fp, flags);
}

static void coff_section(FILE *fp, char *name, unsigned long space,
                         unsigned long address, unsigned long size,
                         unsigned long scnptr, unsigned long relptr,
                         unsigned long lnnoptr, unsigned long flags)
{
    coff_section_ex(fp, name, space, address, address, space, size,
                    scnptr, relptr, lnnoptr, flags);
}

static void coff_symbol(FILE *fp, char *name, unsigned long address,
                        unsigned long space, unsigned long scnum,
                        unsigned long type, unsigned long sclass,
                        unsigned long aux)
{
    coff_name(fp, name);
    be32(fp, address); be32(fp, space); be32(fp, scnum);
    be32(fp, type); be32(fp, sclass); be32(fp, aux);
}

static void coff_zeros(FILE *fp, int count)
{
    int i;

    for (i = 0; i < count; ++i)
        be32(fp, 0UL);
}

static void coff_comment(char *out, unsigned long size)
{
    char *base;
    char *dot;
    unsigned long i;

    base = source_base_name();
    if (size == 0UL)
        return;
    strcpy(out, base);
    dot = strrchr(out, '.');
    if (dot != (char *)0)
        *dot = '\0';
    for (i = 0UL; out[i] != '\0'; ++i)
        out[i] = (char)toupper((unsigned char)out[i]);
    strcat(out, " 0000 0000 0000 DSP56000 6.3.0 ");
}

static unsigned long debug_line_count_range(unsigned long first,
                                            unsigned long count);

static int write_equ_coff(char *path, unsigned long *image,
                          unsigned long span, unsigned long min)
{
    FILE *fp;
    unsigned long raw_offset;
    unsigned long symptr;
    unsigned long strsize;
    unsigned long foo_value;
    char foo[128];
    char comment[256];
    char file_name[32];
    char *base;
    char *dot;
    unsigned long i;
    unsigned long line_ptr;
    unsigned long nlines;
    int dbg;

    sym_first_info(foo, sizeof(foo), &foo_value);
    if (foo[0] == '\0')
        strcpy(foo, "FOO");
    base = source_base_name();
    dot = strrchr(base, '.');
    if (dot == (char *)0)
        dot = base + strlen(base);
    raw_offset = 28UL + 60UL + 4UL * 52UL;
    dbg = GenerateDebugOption && !NoSymbolsOption;
    line_ptr = raw_offset + span * 4UL;
    nlines = dbg ? debug_line_count_range(0UL, RecordCount) : 0UL;
    symptr = line_ptr + nlines * 12UL;
    coff_comment(comment, sizeof(comment));
    strsize = 4UL + (unsigned long)strlen(comment) + 1UL;
    fp = fopen(path, "wb");
    if (fp == (FILE *)0)
    {
        printf("asm56000: Cannot open command file: %s\n", path);
        return 0;
    }
    be32(fp, 0x2c5UL); be32(fp, 4UL); be32(fp, object_timestamp());
    be32(fp, symptr); be32(fp, NoSymbolsOption ? 0UL : (dbg ? 16UL : 14UL));
    be32(fp, 60UL); be32(fp, dbg ? 3UL : 7UL);
    be32(fp, 0UL); be32(fp, 0UL); be32(fp, span); be32(fp, 0UL);
    be32(fp, 0UL);
    be32(fp, 0UL); be32(fp, min);
    be32(fp, 0UL); be32(fp, min);
    be32(fp, 0UL); be32(fp, 1UL);
    be32(fp, min + span); be32(fp, 0UL);
    be32(fp, 0UL); be32(fp, 1UL);
    if (dbg)
        coff_section_debug(fp, ".text", 0UL, min, span, 0UL, line_ptr,
                           line_ptr, nlines, 0x20UL);
    else
        coff_section(fp, ".text", 0UL, min, span, 0UL, line_ptr, line_ptr,
                     0x20UL);
    coff_section(fp, ".data", 1UL, 0UL, 0UL, 0UL, line_ptr, 0UL, 0x40UL);
    coff_section(fp, ".txt", 0UL, 0UL, 0UL, raw_offset, line_ptr,
                 line_ptr, 0x20UL);
    if (dbg)
        coff_section_debug(fp, ".txt", 0UL, 0UL, span, raw_offset,
                           line_ptr, line_ptr, nlines, 0x20UL);
    else
        coff_section(fp, ".txt", 0UL, 0UL, span, raw_offset, line_ptr,
                     line_ptr, 0x20UL);
    for (i = 0UL; i < span; ++i)
        be32(fp, image[i]);
    if (dbg) {
        for (i = 0UL; i < RecordCount; ++i)
            if (i == 0UL || Records[i].source_line !=
                            Records[i - 1UL].source_line) {
                be32(fp, Records[i].address);
                be32(fp, 0UL);
                be32(fp, Records[i].source_line);
            }
    }
    if (NoSymbolsOption) {
        fclose(fp);
        return 1;
    }

    coff_symbol(fp, ".file", dbg ? 13UL : 11UL, 4UL,
                0xfffffffeUL, 0UL, 200UL, 1UL);
    memset(file_name, 0, sizeof(file_name));
    memcpy(file_name, base, (unsigned long)(dot - base));
    strcat(file_name, ".asm");
    fwrite(file_name, 1, 16, fp);
    coff_zeros(fp, 4);
    if (dbg)
        coff_symbol(fp, ".tx", 0UL, 0UL, 3UL, 0UL, 202UL, 0UL);
    coff_symbol(fp, ".cmt", 4UL, 4UL, 0xffffffffUL, 0UL, 0UL, 0UL);
    if (dbg)
        coff_symbol(fp, ".tx", 0UL, 0UL, 4UL, 0UL, 202UL, 0UL);
    coff_symbol(fp, ".text", 0UL, 0UL, 1UL, 0UL, 3UL, 1UL);
    be32(fp, span); coff_zeros(fp, 7);
    coff_symbol(fp, ".data", 0UL, 0UL, 2UL, 0UL, 3UL, 1UL);
    coff_zeros(fp, 8);
    coff_symbol(fp, ".txt", 0UL, 0UL, 3UL, 0UL, 3UL, 1UL);
    coff_zeros(fp, 8);
    coff_symbol(fp, ".txt", 0UL, 0UL, 4UL, 0UL, 3UL, 1UL);
    be32(fp, span);
    if (dbg) {
        be32(fp, 0UL); be32(fp, nlines); coff_zeros(fp, 5);
    } else
        coff_zeros(fp, 7);
    coff_symbol(fp, foo, foo_value, 4UL, 0xffffffffUL, 4UL, 210UL, 0UL);
    coff_symbol(fp, "etext", span, 0UL, 0xffffffffUL, 0UL, 2UL, 0UL);
    coff_symbol(fp, "end", span, 0UL, 0xffffffffUL, 0UL, 2UL, 0UL);
    be32(fp, strsize);
    fwrite(comment + 0, 1, strlen(comment) + 1UL, fp);
    fclose(fp);
    return 1;
}

static int write_equ_reloc(char *path, unsigned long *image,
                           unsigned long span)
{
    FILE *fp;
    unsigned long raw_offset;
    unsigned long symptr;
    unsigned long strsize;
    unsigned long modsize;
    unsigned long foo_value;
    char foo[128];
    char comment[256];
    char file_name[32];
    char *base;
    char *dot;
    unsigned long i;

    sym_first_info(foo, sizeof(foo), &foo_value);
    if (foo[0] == '\0')
        strcpy(foo, "FOO");
    base = source_base_name();
    dot = strrchr(base, '.');
    if (dot == (char *)0)
        dot = base + strlen(base);
    raw_offset = 28UL + 56UL + 2UL * 52UL;
    symptr = raw_offset + span * 4UL;
    coff_comment(comment, sizeof(comment));
    strsize = 4UL + (unsigned long)strlen(comment) + 1UL;
    modsize = symptr + 10UL * 32UL + strsize;
    fp = fopen(path, "wb");
    if (fp == (FILE *)0)
        return 0;
    be32(fp, 0x2c5UL); be32(fp, 2UL); be32(fp, object_timestamp());
    be32(fp, symptr); be32(fp, 10UL); be32(fp, 56UL); be32(fp, 4UL);
    be32(fp, modsize); be32(fp, span); be32(fp, 0xffffffffUL);
    be32(fp, 1UL); be32(fp, 2UL); be32(fp, 0UL); be32(fp, 0UL);
    be32(fp, 0UL); be32(fp, 0UL); be32(fp, 6UL); be32(fp, 3UL);
    be32(fp, 0UL); be32(fp, 0UL); be32(fp, 0UL);
    coff_section(fp, "GLOBAL", 0UL, 0UL, 0UL, raw_offset, symptr,
                 symptr, 0x20UL);
    coff_section(fp, "GLOBAL", 0UL, 0UL, span, raw_offset, symptr,
                 symptr, 0x20UL);
    for (i = 0UL; i < span; ++i)
        be32(fp, image[i]);
    coff_symbol(fp, ".file", 0UL, 4UL, 0xfffffffeUL, 1UL, 200UL, 1UL);
    memset(file_name, 0, sizeof(file_name));
    memcpy(file_name, base, (unsigned long)(dot - base));
    strcat(file_name, ".asm");
    fwrite(file_name, 1, 16, fp);
    coff_zeros(fp, 4);
    coff_symbol(fp, "GLOBAL", 0UL, 0UL, 1UL, 0UL, 3UL, 2UL);
    coff_zeros(fp, 8);
    be32(fp, 0UL); be32(fp, 0UL); be32(fp, 0x1100UL); coff_zeros(fp, 5);
    coff_symbol(fp, ".cmt", 4UL, 4UL, 0xffffffffUL, 0UL, 0UL, 0UL);
    coff_symbol(fp, foo, foo_value, 4UL, 0xffffffffUL, 4UL, 210UL, 0UL);
    coff_symbol(fp, "GLOBAL", 0UL, 0UL, 2UL, 0UL, 3UL, 2UL);
    be32(fp, span); coff_zeros(fp, 7);
    be32(fp, 0UL); be32(fp, 0UL); be32(fp, 0x100UL); coff_zeros(fp, 5);
    be32(fp, strsize);
    fwrite(comment, 1, strlen(comment) + 1UL, fp);
    fclose(fp);
    return 1;
}

static void raw_space_image(int space, unsigned long *image)
{
    unsigned long i;
    unsigned long offset;

    if (!SpaceUsed[space])
        return;
    for (i = 0UL; i < RecordCount; ++i) {
        if (Records[i].space < space || Records[i].space > space)
            continue;
        offset = Records[i].address - SpaceMin[space];
        image[offset] = Records[i].word;
    }
}

static char *space_section_name(int space)
{
    if (space == 0 || (space >= 13 && space <= 15))
        return (char *)".txt";
    return (char *)".dat";
}

static int is_program_space(int space)
{
    return space == 0 || (space >= 13 && space <= 15);
}

static int base_data_space(int space)
{
    if (space >= 18 && space <= 20)
        return 1;
    if (space >= 23 && space <= 25)
        return 2;
    if (space == 9 || space == 10)
        return 3;
    return space;
}

static unsigned long output_data_span(void)
{
    unsigned long result;
    unsigned long i;

    result = 0UL;
    for (i = 1UL; i < 4UL; ++i)
        if (SpaceUsed[i] && SpaceMax[i] > result)
            result = SpaceMax[i];
    return result;
}

static unsigned long output_symbol_section(char *name,
                                           unsigned long value,
                                           unsigned long space,
                                           unsigned long marker)
{
    unsigned long i;
    unsigned long end;

    if (marker == 0xfeedUL) {
        for (i = 0UL; i < OutputEventCount; ++i) {
            if (OutputEvents[i].space == (int)space &&
                OutputEvents[i].address == value)
                return i + 3UL;
        }
        for (i = 0UL; i < OutputEventCount; ++i)
            if (OutputEvents[i].address > value)
                return i + 3UL;
        return 0xffffffffUL;
    }
    if (space >= 32UL)
        return 0xffffffffUL;
    for (i = 0UL; i < OutputEventCount; ++i) {
        if (OutputEvents[i].space != (int)space)
            continue;
        end = OutputEvents[i].address + OutputEvents[i].count;
        if (OutputEvents[i].count == 0UL) {
            if (value == OutputEvents[i].address)
                return i + 3UL;
        } else if (value >= OutputEvents[i].address && value < end)
            return i + 3UL;
    }
    return 0xffffffffUL;
}

static unsigned long debug_line_count_range(unsigned long first,
                                            unsigned long count)
{
    unsigned long i;
    unsigned long result;

    result = 0UL;
    for (i = 0UL; i < count; ++i)
        if (i == 0UL || Records[first + i].source_line !=
                        Records[first + i - 1UL].source_line)
            ++result;
    return result;
}

static unsigned long output_fill_aux_value(char *name)
{
    if (is_name(name, "pbsc"))
        return 5UL;
    if (is_name(name, "pbsm"))
        return 7UL;
    return 9UL;
}

static int write_evented_abs(char *path)
{
    FILE *fp;
    struct output_section sections[256];
    unsigned long span[4];
    unsigned long raw_offset;
    unsigned long raw_end;
    unsigned long symptr;
    unsigned long raw_total;
    unsigned long strsize;
    unsigned long nscns;
    unsigned long nsyms;
    unsigned long pspan;
    unsigned long dspan;
    unsigned long dspace;
    unsigned long raw_ptr;
    unsigned long i;
    unsigned long j;
    unsigned long fill_count;
    unsigned long leading_count;
    unsigned long leading_aux;
    unsigned long leading_entries;
    unsigned long value;
    unsigned long symbol_space;
    unsigned long symbol_scn;
    unsigned long raw_data_end;
    unsigned long next_size;
    unsigned long symbol_flags;
    unsigned long word0;
    unsigned long word1;
    unsigned long word2;
    unsigned long symbol_index;
    unsigned long section_number;
    char symbol_name[128];
    char comment[256];
    char file_name[32];
    char *base;
    char *dot;
    struct output_event *next_events;
    int anchor;
    int program_events;
    int sectioned;
    int global;
    int leading;
    int data_records;

    for (i = 0UL; i + 1UL < OutputEventCount; ++i) {
        if (OutputEvents[i].count == 0UL &&
            OutputEvents[i].section_name[0] != '\0' &&
            strcmp(OutputEvents[i].section_name, "GLOBAL") != 0 &&
            OutputEvents[i + 1UL].count != 0UL &&
            OutputEvents[i + 1UL].address == OutputEvents[i].address &&
            strcmp(OutputEvents[i + 1UL].section_name,
                   OutputEvents[i].section_name) == 0) {
            memmove(OutputEvents + i, OutputEvents + i + 1UL,
                    (OutputEventCount - i - 1UL) * sizeof(*OutputEvents));
            --OutputEventCount;
            --i;
        }
    }
    data_records = 0;
    for (j = 0UL; j < OutputEventCount; ++j)
        if (OutputEvents[j].space > 0 && OutputEvents[j].space < 4 &&
            OutputEvents[j].count != 0UL)
            data_records = 1;
    anchor = 0;
    program_events = 0;
    if (OutputEventCount != 0UL && OutputEvents[0].kind == 0 &&
        OutputEvents[0].space == 0 && OutputEvents[0].address != 0UL) {
        for (i = 0UL; i < OutputEventCount; ++i)
            if (OutputEvents[i].kind == 0 && OutputEvents[i].space == 0)
                ++program_events;
        if (program_events > 1 && data_records)
            anchor = 1;
    }
    if (anchor) {
        if (OutputEventCount == OutputEventSize) {
            next_size = OutputEventSize == 0UL ? 64UL :
                        OutputEventSize * 2UL;
            next_events = (struct output_event *)realloc(
                OutputEvents, next_size * sizeof(*OutputEvents));
            if (next_events == (struct output_event *)0)
                return 0;
            OutputEvents = next_events;
            OutputEventSize = next_size;
        }
        memmove(OutputEvents + 1UL, OutputEvents,
                OutputEventCount * sizeof(*OutputEvents));
        memset(&OutputEvents[0], 0, sizeof(OutputEvents[0]));
        OutputEvents[0].kind = 0;
        OutputEvents[0].space = 0;
        OutputEvents[0].flags = 0x20UL;
        ++OutputEventCount;
    }
    memset(sections, 0, sizeof(sections));
    for (i = 0UL; i < 4UL; ++i)
        span[i] = SpaceUsed[i] ? SpaceMax[i] - SpaceMin[i] + 1UL : 0UL;
    nscns = 2UL + OutputEventCount;
    if (OutputEventCount > sizeof(sections) / sizeof(sections[0]))
        return 0;
    raw_total = 0UL;
    fill_count = 0UL;
    for (i = 0UL; i < OutputEventCount; ++i) {
        sections[i].name = OutputEvents[i].kind == 0 ?
                           space_section_name(OutputEvents[i].space) :
                           (char *)".bss";
        sections[i].address = OutputEvents[i].address;
        sections[i].size = OutputEvents[i].count;
        sections[i].flags = OutputEvents[i].flags;
        sections[i].first_record = OutputEvents[i].first_record;
        sections[i].space = OutputEvents[i].space;
        sections[i].raw = OutputEvents[i].kind == 0;
        sections[i].virtual_address = OutputEvents[i].virtual_address;
        sections[i].virtual_space = OutputEvents[i].virtual_space;
        if (sections[i].raw)
            raw_total += sections[i].size;
    }
    pspan = span[0];
    dspan = output_data_span();
    if (anchor) {
        raw_data_end = 0UL;
        for (i = 0UL; i < RecordCount; ++i) {
            if (is_program_space(Records[i].space))
                continue;
            if (Records[i].address + 1UL > raw_data_end)
                raw_data_end = Records[i].address + 1UL;
        }
        if (raw_data_end != 0UL)
            dspan = raw_data_end;
    }
    dspace = SpaceUsed[3] ? 3UL : SpaceUsed[2] ? 2UL : 1UL;
    if (anchor)
        dspace = 1UL;
    raw_offset = 28UL + 60UL + nscns * 52UL;
    raw_end = raw_offset + raw_total * 4UL;
    symptr = raw_end;
    for (i = 0UL; i < sym_public_count(); ++i) {
        if (sym_public_info(i, symbol_name, sizeof(symbol_name), &value,
                            &symbol_space, &symbol_scn) &&
            symbol_scn == 0xfeedUL)
            ++fill_count;
    }
    leading_count = 0UL;
    leading_aux = 0UL;
    if (anchor) {
        for (i = 0UL; i < sym_public_count(); ++i) {
            if (!sym_public_details(i, symbol_name, sizeof(symbol_name),
                                    &value, &symbol_space, &symbol_scn,
                                    &symbol_flags, &word0, &word1, &word2,
                                    &sectioned, &global) ||
                symbol_scn == 0xfeedUL)
                continue;
            leading = symbol_space == 0UL ||
                      (sectioned && symbol_space < 4UL) || global;
            if (!leading)
                continue;
            ++leading_count;
            if (symbol_space == 0UL || global)
                ++leading_aux;
        }
    }
    leading_entries = leading_count + leading_aux;
    nsyms = 5UL + 2UL * nscns + sym_public_count() + fill_count +
            (anchor ? leading_aux : 0UL);
    coff_comment(comment, sizeof(comment));
    strsize = 4UL + (unsigned long)strlen(comment) + 1UL;
    base = source_base_name();
    dot = strrchr(base, '.');
    if (dot == (char *)0)
        dot = base + strlen(base);
    fp = fopen(path, "wb");
    if (fp == (FILE *)0)
        return 0;
    be32(fp, 0x2c5UL); be32(fp, nscns); be32(fp, object_timestamp());
    be32(fp, symptr); be32(fp, nsyms); be32(fp, 60UL); be32(fp, 7UL);
    be32(fp, 0UL); be32(fp, 0UL); be32(fp, pspan); be32(fp, dspan);
    be32(fp, 0UL);
    be32(fp, SpaceUsed[0] ? SpaceMin[0] : 0UL); be32(fp, 0UL);
    be32(fp, SpaceUsed[0] ? SpaceMin[0] : 0UL); be32(fp, 0UL);
    be32(fp, 0UL); be32(fp, 1UL);
    be32(fp, SpaceUsed[0] ? SpaceMax[0] + 1UL : 0UL); be32(fp, 0UL);
    be32(fp, dspan); be32(fp, dspace);
    coff_section(fp, ".text", 0UL, SpaceUsed[0] ? SpaceMin[0] : 0UL,
                 pspan, 0UL, symptr, symptr, 0x20UL);
    coff_section(fp, ".data", 1UL, 0UL, dspan, 0UL, symptr, 0UL,
                 0x40UL);
    raw_ptr = raw_offset;
    for (i = 0UL; i < OutputEventCount; ++i) {
        sections[i].ptr = raw_ptr;
        coff_section_ex(fp, sections[i].name,
                     (unsigned long)sections[i].space,
                     sections[i].address,
                     sections[i].virtual_address,
                     sections[i].virtual_space,
                     sections[i].size,
                     sections[i].raw ? raw_ptr : 0UL,
                     sections[i].raw ? symptr : 0UL,
                     sections[i].raw || sections[i].flags == 0xc0UL ?
                     symptr : 0UL,
                     sections[i].flags);
        if (sections[i].raw)
            raw_ptr += sections[i].size * 4UL;
    }
    for (i = 0UL; i < OutputEventCount; ++i) {
        if (!sections[i].raw)
            continue;
        for (j = 0UL; j < sections[i].size; ++j)
            be32(fp, Records[sections[i].first_record + j].word);
    }
    /* The original normalizes the file marker to the first global symbol
       (or etext when no user global exists).  At this point that index is
       after .file/.cmt, fill-label records, and section records. */
    coff_symbol(fp, ".file", 3UL + 2UL * fill_count + 2UL * nscns +
                (anchor ? leading_entries : 0UL), 4UL,
                0xfffffffeUL, 0UL, 200UL, 1UL);
    memset(file_name, 0, sizeof(file_name));
    memcpy(file_name, base, (unsigned long)(dot - base));
    strcat(file_name, ".asm");
    fwrite(file_name, 1, 16, fp);
    coff_zeros(fp, 4);
    coff_symbol(fp, ".cmt", 4UL, 4UL, 0xffffffffUL, 0UL, 0UL, 0UL);
    for (i = 0UL; i < sym_public_count(); ++i) {
        if (!sym_public_info(i, symbol_name, sizeof(symbol_name), &value,
                             &symbol_space, &symbol_scn))
            continue;
        if (symbol_scn != 0xfeedUL)
            continue;
        coff_symbol(fp, symbol_name, value, symbol_space,
                    output_symbol_section(symbol_name, value, symbol_space,
                                          symbol_scn),
                    0x24UL, 210UL, 1UL);
        coff_zeros(fp, 4);
        be32(fp, output_fill_aux_value(symbol_name));
        coff_zeros(fp, 3);
    }
    if (anchor) {
        symbol_index = 3UL;
        for (i = 0UL; i < sym_public_count(); ++i) {
            if (!sym_public_details(i, symbol_name, sizeof(symbol_name),
                                    &value, &symbol_space, &symbol_scn,
                                    &symbol_flags, &word0, &word1, &word2,
                                    &sectioned, &global) ||
                symbol_scn == 0xfeedUL)
                continue;
            leading = symbol_space == 0UL ||
                      (sectioned && symbol_space < 4UL) || global;
            if (!leading)
                continue;
            section_number = output_symbol_section(symbol_name, value,
                                                    symbol_space, symbol_scn);
            if (symbol_space == 0UL || global) {
                coff_symbol(fp, symbol_name, value, symbol_space,
                            section_number, 0x24UL, 210UL, 1UL);
                coff_zeros(fp, 4);
                be32(fp, symbol_index +
                     (global && sectioned ? 3UL : 2UL));
                coff_zeros(fp, 3);
                symbol_index += 2UL;
            } else {
                coff_symbol(fp, symbol_name, value, symbol_space,
                            section_number, 4UL, 213UL, 0UL);
                ++symbol_index;
            }
        }
    }
    coff_symbol(fp, ".text", SpaceUsed[0] ? SpaceMin[0] : 0UL,
                0UL, 1UL, 0UL, 3UL, 1UL);
    be32(fp, pspan); coff_zeros(fp, 7);
    coff_symbol(fp, ".data", 0UL, 1UL, 2UL, 0UL, 3UL, 1UL);
    be32(fp, dspan); coff_zeros(fp, 7);
    for (i = 0UL; i < OutputEventCount; ++i) {
        coff_symbol(fp, sections[i].name, sections[i].address,
                    (unsigned long)sections[i].space, i + 3UL,
                    0UL, 3UL, 1UL);
        be32(fp, sections[i].size); coff_zeros(fp, 7);
    }
    for (i = 0UL; i < sym_public_count(); ++i) {
        if (!sym_public_details(i, symbol_name, sizeof(symbol_name), &value,
                                &symbol_space, &symbol_scn, &symbol_flags,
                                &word0, &word1, &word2, &sectioned,
                                &global))
            continue;
        if (symbol_scn == 0xfeedUL)
            continue;
        leading = symbol_space == 0UL ||
                  (sectioned && symbol_space < 4UL) || global;
        if (anchor && leading)
            continue;
        if ((symbol_flags & 0x200UL) != 0UL)
            coff_symbol(fp, symbol_name, word0, word1, 0xffffffffUL,
                        6UL, 210UL, 0UL);
        else
            coff_symbol(fp, symbol_name, value, symbol_space,
                        output_symbol_section(symbol_name, value,
                                              symbol_space, symbol_scn),
                        4UL, 210UL, 0UL);
    }
    coff_symbol(fp, "etext", SpaceUsed[0] ? SpaceMax[0] + 1UL : 0UL,
                0UL, 0xffffffffUL, 0UL, 2UL, 0UL);
    coff_symbol(fp, "end", SpaceUsed[0] ? SpaceMax[0] + 1UL : 0UL,
                0UL, 0xffffffffUL, 0UL, 2UL, 0UL);
    be32(fp, strsize);
    fwrite(comment, 1, strlen(comment) + 1UL, fp);
    fclose(fp);
    return 1;
}

static int write_segmented_abs(char *path)
{
    FILE *fp;
    struct output_section sections[256];
    unsigned long raw_offset;
    unsigned long line_ptr;
    unsigned long line_size;
    unsigned long symptr;
    unsigned long raw_total;
    unsigned long strsize;
    unsigned long nscns;
    unsigned long nsyms;
    unsigned long pspan;
    unsigned long dspan;
    unsigned long pmin;
    unsigned long pmin_space;
    unsigned long pmax;
    unsigned long dmin;
    unsigned long dmax;
    unsigned long program_start;
    unsigned long data_base_address;
    unsigned long data_end_address;
    unsigned long data_base_space;
    unsigned long data_end_space;
    unsigned long data_section_count;
    unsigned long i;
    unsigned long j;
    unsigned long nsections;
    unsigned long raw_ptr;
    unsigned long defined_count;
    unsigned long symbol_index;
    unsigned long value;
    unsigned long symbol_space;
    unsigned long symbol_scn;
    unsigned long section_number;
    unsigned long end;
    unsigned long header_flags;
    unsigned long section_line_ptr;
    int pactive;
    int dactive;
    int data_base_found;
    int pcount;
    int anchor;
    char comment[256];
    char file_name[32];
    char symbol_name[128];
    char *base;
    char *dot;

    if (OutputHasBss)
        return write_evented_abs(path);
    memset(sections, 0, sizeof(sections));
    nsections = 0UL;
    raw_total = 0UL;
    pactive = 0;
    dactive = 0;
    data_base_found = 0;
    pmin = 0UL;
    pmin_space = 0UL;
    pmax = 0UL;
    dmin = 0UL;
    dmax = 0UL;
    data_base_space = 1UL;
    data_base_address = 0UL;
    data_end_space = 1UL;
    data_end_address = 0UL;
    data_section_count = 0UL;
    pcount = 0;
    for (i = 0UL; i < SegmentCount; ++i) {
        if (nsections >= sizeof(sections) / sizeof(sections[0]))
            return 0;
        sections[nsections].name = space_section_name(RawSegments[i].space);
        sections[nsections].address = RawSegments[i].address;
        sections[nsections].runtime_address = RawSegments[i].runtime_address;
        sections[nsections].size = RawSegments[i].count;
        sections[nsections].flags = is_program_space(RawSegments[i].space) ?
                                    0x20UL : 0x40UL;
        sections[nsections].first_record = RawSegments[i].first_record;
        sections[nsections].space = RawSegments[i].space;
        sections[nsections].raw = 1;
        raw_total += sections[nsections].size;
        if (is_program_space(RawSegments[i].space))
            ++pcount;
        else if (!data_base_found) {
            data_base_space = (unsigned long)RawSegments[i].space;
            data_base_address = RawSegments[i].address;
            data_base_found = 1;
        }
        if (!is_program_space(RawSegments[i].space))
            ++data_section_count;
        ++nsections;
    }
    pcount = 0;
    for (i = 0UL; i < SegmentCount; ++i)
        if (is_program_space(RawSegments[i].space))
            ++pcount;
    anchor = sym_public_count() != 0UL && data_section_count == 0UL &&
             SegmentCount != 0UL &&
             RawSegments[0].space == 0 &&
             ((!SourceCexDirective && RawSegments[0].address == 0UL &&
               pcount > 1) || (RawSegments[0].address > 0x40UL && !SourceOptCex));
    if (anchor) {
        if (nsections >= sizeof(sections) / sizeof(sections[0]))
            return 0;
        for (i = nsections; i > 0UL; --i)
            sections[i] = sections[i - 1UL];
        memset(&sections[0], 0, sizeof(sections[0]));
        sections[0].name = (char *)".txt";
        sections[0].flags = 0x20UL;
        sections[0].space = 0;
        sections[0].raw = 1;
        ++nsections;
    }
    for (i = 0UL; i < 32UL; ++i) {
        if (!SpaceUsed[i])
            continue;
        if (is_program_space((int)i)) {
            if (!pactive || SpaceMin[i] < pmin) {
                pmin = SpaceMin[i];
                pmin_space = i;
            }
            if (!pactive || SpaceMax[i] > pmax)
                pmax = SpaceMax[i];
            pactive = 1;
        } else {
            if (!dactive || SpaceMin[i] < dmin)
                dmin = SpaceMin[i];
            if (!dactive || SpaceMax[i] > dmax)
                dmax = SpaceMax[i];
            dactive = 1;
            if (SpaceMax[i] >= data_end_address) {
                data_end_address = SpaceMax[i];
                data_end_space = (unsigned long)base_data_space((int)i);
            }
        }
    }
    if (!data_base_found && SegmentCount != 0UL) {
        for (i = 0UL; i < SegmentCount; ++i)
            if (!is_program_space(sections[i].space)) {
                data_base_space = (unsigned long)sections[i].space;
                data_base_address = sections[i].address;
                data_base_found = 1;
                dactive = 1;
                dmin = sections[i].address;
                dmax = sections[i].address + sections[i].size - 1UL;
                data_end_space = data_base_space;
                data_end_address = dmax;
                break;
            }
    }
    if (pactive)
        pspan = pmax - pmin + 1UL;
    else
        pspan = 0UL;
    if (dactive)
        dspan = dmax - dmin + 1UL;
    else
        dspan = 0UL;
    program_start = pactive ? pmin : 0UL;
    for (i = 0UL; i < nsections; ++i) {
        if (sections[i].space == 0 && sections[i].size != 0UL &&
            sections[i].address != 0UL) {
            program_start = sections[i].address;
            break;
        }
    }
    if (data_base_address == 0UL && dactive)
        data_base_address = dmin;
    data_end_address = dactive ? dmax : 0UL;
    raw_offset = 28UL + 60UL + (2UL + nsections) * 52UL +
                 (data_section_count > 1UL ? data_section_count : 0UL) *
                 52UL;
    line_ptr = raw_offset + raw_total * 4UL;
    line_size = GenerateDebugOption && !NoSymbolsOption ?
                debug_line_count_range(0UL, RecordCount) * 12UL : 0UL;
    symptr = line_ptr + line_size;
    defined_count = 0UL;
    for (i = 0UL; i < sym_public_count(); ++i) {
        if (sym_public_info(i, symbol_name, sizeof(symbol_name), &value,
                            &symbol_space, &symbol_scn) &&
            symbol_scn != 0xfeedUL && is_program_space((int)symbol_space))
            ++defined_count;
    }
    nscns = 2UL + nsections;
    nsyms = 5UL + 2UL * nscns + non_cli_public_count() + defined_count;
    if (GenerateDebugOption && !NoSymbolsOption)
        nsyms += nsections;
    if (NoSymbolsOption)
        nsyms = 0UL;
    coff_comment(comment, sizeof(comment));
    coff_long_reset(comment);
    for (i = 0UL; i < sym_public_count(); ++i) {
        if (sym_public_info(i, symbol_name, sizeof(symbol_name), &value,
                            &symbol_space, &symbol_scn) &&
            !is_cli_define_name(symbol_name))
            coff_long_add(symbol_name);
    }
    strsize = CoffLongNext;
    base = source_base_name();
    dot = strrchr(base, '.');
    if (dot == (char *)0)
        dot = base + strlen(base);
    fp = fopen(path, "wb");
    if (fp == (FILE *)0)
        return 0;
    be32(fp, 0x2c5UL); be32(fp, nscns); be32(fp, object_timestamp());
    header_flags = GenerateDebugOption && !NoSymbolsOption ? 3UL : 7UL;
    be32(fp, symptr); be32(fp, nsyms); be32(fp, 60UL); be32(fp, header_flags);
    be32(fp, 0UL); be32(fp, 0UL); be32(fp, pspan); be32(fp, dspan);
    be32(fp, 0UL);
    be32(fp, program_start); be32(fp, 0UL);
    be32(fp, pactive ? pmin : 0UL); be32(fp, 0UL);
    be32(fp, dactive ? data_base_address : 0UL);
    be32(fp, dactive ? data_base_space : 1UL);
    be32(fp, pactive ? pmax + 1UL : 0UL); be32(fp, 0UL);
    be32(fp, dactive ? dmax + 1UL : 0UL); be32(fp, dactive ? data_end_space : 1UL);
    if (GenerateDebugOption && !NoSymbolsOption)
        coff_section_debug(fp, ".text", 0UL, pactive ? pmin : 0UL,
                           pspan, 0UL, line_ptr, line_ptr,
                           debug_line_count_range(0UL, RecordCount),
                           0x20UL);
    else
        coff_section(fp, ".text", 0UL, pactive ? pmin : 0UL,
                     pspan, 0UL, line_ptr, line_ptr, 0x20UL);
    coff_section(fp, ".data", dactive ? data_base_space : 1UL,
                 dactive ? data_base_address : 0UL, dspan, 0UL,
                 line_ptr, 0UL, 0x40UL);
    raw_ptr = raw_offset;
    for (i = 0UL; i < nsections; ++i) {
        sections[i].ptr = raw_ptr;
        if (GenerateDebugOption && !NoSymbolsOption &&
            is_program_space(sections[i].space))
            section_line_ptr = line_ptr +
                               debug_line_count_range(0UL,
                                                      sections[i].first_record) *
                               12UL;
        else
            section_line_ptr = line_ptr;
        if (GenerateDebugOption && !NoSymbolsOption &&
            is_program_space(sections[i].space))
            coff_section_debug(fp, sections[i].name,
                               (unsigned long)sections[i].space,
                               sections[i].address, sections[i].size,
                               raw_ptr, line_ptr, section_line_ptr,
                               debug_line_count_range(sections[i].first_record,
                                                      sections[i].size),
                               sections[i].flags);
        else
            coff_section(fp, sections[i].name,
                         (unsigned long)sections[i].space,
                         sections[i].address, sections[i].size,
                         raw_ptr, line_ptr, line_ptr, sections[i].flags);
        raw_ptr += sections[i].size * 4UL;
    }
    /* The absolute writer reserves one section-header-sized slot for each
       data-space segment before the raw words.  The section pointers and
       symbol pointer include this padding, so materialize it in the stream. */
    if (data_section_count > 1UL)
        coff_zeros(fp, (int)(data_section_count * 13UL));
    for (i = 0UL; i < nsections; ++i) {
        if (!sections[i].raw)
            continue;
        for (j = 0UL; j < sections[i].size; ++j)
            be32(fp, Records[sections[i].first_record + j].word);
    }
    if (GenerateDebugOption && !NoSymbolsOption) {
        for (i = 0UL; i < RecordCount; ++i)
            if (i == 0UL || Records[i].source_line !=
                            Records[i - 1UL].source_line) {
                be32(fp, Records[i].address);
                be32(fp, 0UL);
                be32(fp, Records[i].source_line);
            }
    }
    if (NoSymbolsOption) {
        fclose(fp);
        return 1;
    }
    coff_symbol(fp, ".file", 3UL + 2UL * defined_count + 2UL * nscns +
                (GenerateDebugOption ? (anchor ? 3UL : 1UL) : 0UL),
                4UL, 0xfffffffeUL, 0UL, 200UL, 1UL);
    memset(file_name, 0, sizeof(file_name));
    memcpy(file_name, base, (unsigned long)(dot - base));
    strcat(file_name, ".asm");
    fwrite(file_name, 1, 16, fp);
    coff_zeros(fp, 4);
    if (GenerateDebugOption && anchor)
        coff_symbol(fp, ".tx", sections[0].address,
                    (unsigned long)sections[0].space, 3UL,
                    0UL, 202UL, 0UL);
    coff_symbol(fp, ".cmt", 4UL, 4UL, 0xffffffffUL, 0UL, 0UL, 0UL);
    if (GenerateDebugOption) {
        for (i = anchor ? 1UL : 0UL; i < nsections; ++i)
            coff_symbol(fp, ".tx", sections[i].address,
                        (unsigned long)sections[i].space, i + 3UL,
                        0UL, 202UL, 0UL);
    }
    symbol_index = GenerateDebugOption ? (anchor ? 6UL : 4UL) : 3UL;
    for (i = 0UL; i < sym_public_count(); ++i) {
        if (!sym_public_info(i, symbol_name, sizeof(symbol_name), &value,
                             &symbol_space, &symbol_scn) ||
            is_cli_define_name(symbol_name) ||
            symbol_scn == 0xfeedUL || !is_program_space((int)symbol_space))
            continue;
        section_number = 0xffffffffUL;
        end = 0UL;
        for (j = 0UL; j < nsections; ++j) {
            unsigned long candidate_end;

            if (sections[j].space != (int)symbol_space)
                continue;
            candidate_end = sections[j].runtime_address + sections[j].size;
            if (sections[j].size != 0UL && value >= sections[j].runtime_address &&
                value < candidate_end) {
                section_number = j + 3UL;
                break;
            }
            if (sections[j].size != 0UL && value == candidate_end)
                end = j + 3UL;
        }
        if (section_number == 0xffffffffUL && end != 0UL)
            section_number = end;
        coff_symbol(fp, symbol_name, value, symbol_space, section_number,
                    0x24UL, 210UL, 1UL);
        if (GenerateDebugOption && !NoSymbolsOption) {
            coff_zeros(fp, 3);
            be32(fp, line_ptr);
        } else {
            coff_zeros(fp, 4);
        }
        be32(fp, symbol_index + 2UL);
        coff_zeros(fp, 3);
        symbol_index += 2UL;
    }
    coff_symbol(fp, ".text", pactive ? pmin : 0UL,
                pactive ? pmin_space : 0UL,
                1UL, 0UL, 3UL, 1UL);
    be32(fp, pspan); coff_zeros(fp, 7);
    coff_symbol(fp, ".data", dactive ? data_base_address : 0UL,
                dactive ? data_base_space : (pactive ? 0UL : 1UL),
                2UL, 0UL, 3UL, 1UL);
    be32(fp, dspan); coff_zeros(fp, 7);
    for (i = 0UL; i < nsections; ++i) {
        coff_symbol(fp, sections[i].name, sections[i].address,
                    (unsigned long)sections[i].space, i + 3UL,
                    0UL, 3UL, 1UL);
        be32(fp, sections[i].size);
        be32(fp, 0UL);
        be32(fp, GenerateDebugOption && !NoSymbolsOption ?
             debug_line_count_range(sections[i].first_record,
                                    sections[i].size) : 0UL);
        coff_zeros(fp, 5);
    }
    for (i = 0UL; i < sym_public_count(); ++i) {
        if (sym_public_info(i, symbol_name, sizeof(symbol_name), &value,
                            &symbol_space, &symbol_scn) &&
            !is_cli_define_name(symbol_name) &&
            symbol_scn != 0xfeedUL && !is_program_space((int)symbol_space))
        {
            section_number = 0xffffffffUL;
            for (j = 0UL; j < nsections; ++j) {
                if (sections[j].space != (int)symbol_space ||
                    sections[j].size == 0UL)
                    continue;
                if (value >= sections[j].address &&
                    value < sections[j].address + sections[j].size) {
                    section_number = j + 3UL;
                    break;
                }
            }
            coff_symbol(fp, symbol_name, value, symbol_space,
                        section_number, 4UL, 210UL, 0UL);
        }
    }
    coff_symbol(fp, "etext", pactive ? pmax + 1UL : 0UL, 0UL,
                0xffffffffUL, 0UL, 2UL, 0UL);
    coff_symbol(fp, "end", pactive ? pmax + 1UL : 0UL, 0UL,
                0xffffffffUL, 0UL, 2UL, 0UL);
    be32(fp, strsize);
    fwrite(comment, 1, strlen(comment) + 1UL, fp);
    coff_long_write(fp);
    fclose(fp);
    return 1;
}

static int write_segmented_abs_old(char *path)
{
    FILE *fp;
    struct output_section sections[256];
    unsigned long span[4];
    unsigned long raw_offset;
    unsigned long symptr;
    unsigned long raw_total;
    unsigned long strsize;
    unsigned long nscns;
    unsigned long nsyms;
    unsigned long pspan;
    unsigned long dspan;
    unsigned long dspace;
    unsigned long i;
    unsigned long j;
    unsigned long nsections;
    unsigned long raw_ptr;
    char comment[256];
    char file_name[32];
    char *base;
    char *dot;
    int active[4];
    int segs[4];
    int k;
    unsigned long defined_count;
    unsigned long symbol_index;
    unsigned long program_start;

    if (OutputHasBss)
        return write_evented_abs(path);

    memset(sections, 0, sizeof(sections));
    raw_total = 0UL;
    nsections = 0UL;
    for (i = 0UL; i < 4UL; ++i) {
        active[i] = SpaceUsed[i];
        span[i] = active[i] ? SpaceMax[i] - SpaceMin[i] + 1UL : 0UL;
        segs[i] = 0;
    }
    for (i = 0UL; i < SegmentCount; ++i)
        if (RawSegments[i].space >= 0 && RawSegments[i].space < 4)
            ++segs[RawSegments[i].space];

    /* The assembler keeps a separate text section for each discontinuous
       load range.  A split P range also retains the zero-length section that
       precedes the first range (the linker uses it as the section anchor). */
    for (k = 0; k < 4; ++k) {
        int added;

        added = 0;
        for (i = 0UL; i < SegmentCount; ++i) {
            if (RawSegments[i].space != k)
                continue;
            if (nsections >= sizeof(sections) / sizeof(sections[0]))
                break;
            sections[nsections].name = space_section_name(k);
            sections[nsections].address = RawSegments[i].address;
            sections[nsections].size = RawSegments[i].count;
            sections[nsections].flags = k == 0 ? 0x20UL : 0x40UL;
            sections[nsections].first_record = RawSegments[i].first_record;
            sections[nsections].space = k;
            sections[nsections].raw = 1;
            ++nsections;
            raw_total += RawSegments[i].count;
            ++added;
        }
        if (active[k] && added == 0) {
            sections[nsections].name = space_section_name(k);
            sections[nsections].address = SpaceMin[k];
            sections[nsections].size = span[k];
            sections[nsections].flags = k == 0 ? 0x20UL : 0x40UL;
            sections[nsections].first_record = 0UL;
            sections[nsections].space = k;
            sections[nsections].raw = 1;
            ++nsections;
            raw_total += span[k];
        }
        if (k == 0 && added > 1) {
            if (nsections >= sizeof(sections) / sizeof(sections[0]))
                return 0;
            for (j = nsections; j > 0UL; --j)
                sections[j] = sections[j - 1UL];
            sections[0].name = (char *)".txt";
            sections[0].address = 0UL;
            sections[0].size = 0UL;
            sections[0].flags = 0x20UL;
            sections[0].first_record = 0UL;
            sections[0].space = 0;
            sections[0].raw = 0;
            ++nsections;
        }
    }

    nscns = 2UL + nsections;
    pspan = span[0];
    dspace = 1UL;
    dspan = 0UL;
    for (i = 1UL; i < 4UL; ++i) {
        if (active[i]) {
            dspace = i;
            dspan += span[i];
        }
    }
    program_start = active[0] ? SpaceMin[0] : 0UL;
    for (i = 0UL; i < nsections; ++i) {
        if (sections[i].space == 0 && sections[i].raw &&
            sections[i].size != 0UL &&
            sections[i].address > program_start) {
            program_start = sections[i].address;
            break;
        }
    }
    raw_offset = 28UL + 60UL + nscns * 52UL;
    symptr = raw_offset + raw_total * 4UL;
    coff_comment(comment, sizeof(comment));
    strsize = 4UL + (unsigned long)strlen(comment) + 1UL;
    defined_count = 0UL;
    for (i = 0UL; i < sym_public_count(); ++i) {
        unsigned long symbol_value;
        unsigned long symbol_space;
        unsigned long symbol_scn;
        char symbol_name[128];

        if (sym_public_info(i, symbol_name, sizeof(symbol_name),
                            &symbol_value, &symbol_space, &symbol_scn) &&
            symbol_scn != 0xfeedUL && symbol_space == 0UL)
            ++defined_count;
    }
    nsyms = 5UL + 2UL * nscns + sym_public_count() + defined_count;
    base = source_base_name();
    dot = strrchr(base, '.');
    if (dot == (char *)0)
        dot = base + strlen(base);
    fp = fopen(path, "wb");
    if (fp == (FILE *)0)
        return 0;
    be32(fp, 0x2c5UL); be32(fp, nscns); be32(fp, object_timestamp());
    be32(fp, symptr); be32(fp, nsyms); be32(fp, 60UL); be32(fp, 7UL);
    be32(fp, 0UL); be32(fp, 0UL); be32(fp, pspan); be32(fp, dspan);
    be32(fp, 0UL);
    be32(fp, program_start); be32(fp, 0UL);
    be32(fp, active[0] ? SpaceMin[0] : 0UL); be32(fp, 0UL);
    be32(fp, 0UL); be32(fp, dspace);
    be32(fp, active[0] ? SpaceMax[0] + 1UL : 0UL); be32(fp, 0UL);
    be32(fp, dspan); be32(fp, dspace);

    coff_section(fp, ".text", 0UL, active[0] ? SpaceMin[0] : 0UL,
                 pspan, 0UL, symptr, symptr, 0x20UL);
    coff_section(fp, ".data", dspace,
                 active[dspace] ? SpaceMin[dspace] : 0UL, dspan, 0UL,
                 symptr, 0UL, 0x40UL);
    raw_ptr = raw_offset;
    for (i = 0UL; i < nsections; ++i) {
        sections[i].ptr = raw_ptr;
        coff_section(fp, sections[i].name, (unsigned long)sections[i].space,
                     sections[i].address, sections[i].size,
                     sections[i].ptr, symptr, symptr, sections[i].flags);
        if (sections[i].raw)
            raw_ptr += sections[i].size * 4UL;
    }
    for (i = 0UL; i < nsections; ++i) {
        if (!sections[i].raw)
            continue;
        if (sections[i].first_record == 0UL &&
            !(SegmentCount != 0UL &&
              RawSegments[0].first_record == 0UL &&
              RawSegments[0].space == sections[i].space &&
              RawSegments[0].address == sections[i].address)) {
            for (j = 0UL; j < sections[i].size; ++j)
                be32(fp, 0UL);
        } else {
            for (j = 0UL; j < sections[i].size; ++j)
                be32(fp, Records[sections[i].first_record + j].word);
        }
    }

    coff_symbol(fp, ".file", 3UL + 2UL * defined_count + 2UL * nscns, 4UL,
                0xfffffffeUL, 0UL, 200UL, 1UL);
    memset(file_name, 0, sizeof(file_name));
    memcpy(file_name, base, (unsigned long)(dot - base));
    strcat(file_name, ".asm");
    fwrite(file_name, 1, 16, fp);
    coff_zeros(fp, 4);
    coff_symbol(fp, ".cmt", 4UL, 4UL, 0xffffffffUL, 0UL, 0UL, 0UL);
    symbol_index = 3UL;
    for (i = 0UL; i < sym_public_count(); ++i) {
        char symbol_name[128];
        unsigned long symbol_value;
        unsigned long symbol_space;
        unsigned long symbol_scn;
        unsigned long section_number;

        if (!sym_public_info(i, symbol_name, sizeof(symbol_name),
                             &symbol_value, &symbol_space, &symbol_scn) ||
            symbol_scn == 0xfeedUL || symbol_space != 0UL)
            continue;
        section_number = 0xffffffffUL;
        for (j = 0UL; j < nsections; ++j) {
            unsigned long end;

            if (!sections[j].raw || sections[j].space != (int)symbol_space)
                continue;
            end = sections[j].address + sections[j].size;
            if (sections[j].size != 0UL && symbol_value >= sections[j].address &&
                symbol_value < end) {
                section_number = j + 3UL;
                break;
            }
        }
        coff_symbol(fp, symbol_name, symbol_value, symbol_space,
                    section_number, 0x24UL, 210UL, 1UL);
        coff_zeros(fp, 4);
        be32(fp, symbol_index + 2UL);
        coff_zeros(fp, 3);
        symbol_index += 2UL;
    }
    coff_symbol(fp, ".text", active[0] ? SpaceMin[0] : 0UL, 0UL,
                1UL, 0UL, 3UL, 1UL);
    be32(fp, pspan); coff_zeros(fp, 7);
    coff_symbol(fp, ".data", active[dspace] ? SpaceMin[dspace] : 0UL,
                active[dspace] ? dspace : 0UL, 2UL, 0UL, 3UL, 1UL);
    be32(fp, dspan); coff_zeros(fp, 7);
    for (i = 0UL; i < nsections; ++i) {
        coff_symbol(fp, sections[i].name, sections[i].address,
                    (unsigned long)sections[i].space, i + 3UL,
                    0UL, 3UL, 1UL);
        be32(fp, sections[i].size); coff_zeros(fp, 7);
        symbol_index += 2UL;
    }
    for (i = 0UL; i < sym_public_count(); ++i) {
        char symbol_name[128];
        unsigned long symbol_value;
        unsigned long symbol_space;
        unsigned long symbol_scn;

        if (sym_public_info(i, symbol_name, sizeof(symbol_name),
                            &symbol_value, &symbol_space, &symbol_scn) &&
            symbol_scn != 0xfeedUL && symbol_space != 0UL)
            coff_symbol(fp, symbol_name, symbol_value, symbol_space,
                        0xffffffffUL,
                        4UL, 210UL, 0UL);
    }
    coff_symbol(fp, "etext", active[0] ? SpaceMax[0] + 1UL : 0UL,
                0UL, 0xffffffffUL, 0UL, 2UL, 0UL);
    coff_symbol(fp, "end", active[0] ? SpaceMax[0] + 1UL : 0UL,
                0UL, 0xffffffffUL, 0UL, 2UL, 0UL);
    be32(fp, strsize);
    fwrite(comment, 1, strlen(comment) + 1UL, fp);
    fclose(fp);
    return 1;
}

static int write_generic_abs(char *path)
{
    FILE *fp;
    unsigned long span[4];
    unsigned long raw_offset;
    unsigned long symptr;
    unsigned long raw_total;
    unsigned long strsize;
    unsigned long nscns;
    unsigned long nsyms;
    unsigned long pspan;
    unsigned long dspan;
    unsigned long dspace;
    unsigned long i;
    unsigned long j;
    unsigned long section_number;
    unsigned long foo_value;
    char first_name[128];
    char comment[256];
    char file_name[32];
    char *base;
    char *dot;
    int active[4];
    unsigned long raw_ptr[4];
    unsigned long *image;
    int user_count;

    raw_total = 0UL;
    nscns = 2UL;
    for (i = 0UL; i < 4UL; ++i) {
        active[i] = SpaceUsed[i];
        span[i] = active[i] ? SpaceMax[i] - SpaceMin[i] + 1UL : 0UL;
        raw_total += span[i];
        if (active[i])
            ++nscns;
    }
    pspan = span[0];
    dspace = 1UL;
    dspan = 0UL;
    for (i = 1UL; i < 4UL; ++i) {
        if (active[i]) {
            dspace = i;
            dspan += span[i];
        }
    }
    raw_offset = 28UL + 60UL + nscns * 52UL;
    symptr = raw_offset + raw_total * 4UL;
    user_count = sym_count() == 0UL ? 0 : 1;
    nsyms = 5UL + 2UL * nscns + (unsigned long)user_count;
    coff_comment(comment, sizeof(comment));
    strsize = 4UL + (unsigned long)strlen(comment) + 1UL;
    base = source_base_name();
    dot = strrchr(base, '.');
    if (dot == (char *)0)
        dot = base + strlen(base);
    sym_first_info(first_name, sizeof(first_name), &foo_value);
    fp = fopen(path, "wb");
    if (fp == (FILE *)0)
        return 0;
    be32(fp, 0x2c5UL); be32(fp, nscns); be32(fp, object_timestamp());
    be32(fp, symptr); be32(fp, nsyms); be32(fp, 60UL); be32(fp, 7UL);
    be32(fp, 0UL); be32(fp, 0UL); be32(fp, pspan); be32(fp, dspan);
    be32(fp, 0UL);
    be32(fp, active[0] ? SpaceMin[0] : 0UL); be32(fp, 0UL);
    be32(fp, active[0] ? SpaceMin[0] : 0UL); be32(fp, 0UL);
    be32(fp, 0UL); be32(fp, dspace);
    be32(fp, active[0] ? SpaceMax[0] + 1UL : 0UL); be32(fp, 0UL);
    be32(fp, dspan); be32(fp, dspace);
    section_number = 1UL;
    coff_section(fp, ".text", 0UL, active[0] ? SpaceMin[0] : 0UL,
                 pspan, 0UL, symptr, symptr, 0x20UL);
    coff_section(fp, ".data", dspace,
                 active[dspace] ? SpaceMin[dspace] : 0UL, dspan, 0UL, symptr,
                 0UL, 0x40UL);
    raw_ptr[0] = raw_offset;
    raw_ptr[1] = raw_offset;
    raw_ptr[2] = raw_offset;
    raw_ptr[3] = raw_offset;
    for (i = 0UL; i < 4UL; ++i) {
        if (!active[i])
            continue;
         coff_section(fp, space_section_name((int)i), i, SpaceMin[i],
                     span[i], raw_ptr[i], symptr, symptr,
                     i == 0UL ? 0x20UL : 0x40UL);
        raw_ptr[i] += span[i] * 4UL;
    }
    for (i = 0UL; i < 4UL; ++i) {
        if (!active[i])
            continue;
        image = (unsigned long *)calloc(span[i] == 0UL ? 1UL : span[i],
                                        sizeof(unsigned long));
        if (image == (unsigned long *)0) {
            fclose(fp);
            return 0;
        }
        raw_space_image((int)i, image);
        for (j = 0UL; j < span[i]; ++j)
            be32(fp, image[j]);
        free(image);
    }
    coff_symbol(fp, ".file", 9UL, 4UL, 0xfffffffeUL, 0UL, 200UL, 1UL);
    memset(file_name, 0, sizeof(file_name));
    memcpy(file_name, base, (unsigned long)(dot - base));
    strcat(file_name, ".asm");
    fwrite(file_name, 1, 16, fp);
    coff_zeros(fp, 4);
    coff_symbol(fp, ".cmt", 4UL, 4UL, 0xffffffffUL, 0UL, 0UL, 0UL);
    coff_symbol(fp, ".text", active[0] ? SpaceMin[0] : 0UL, 0UL,
                1UL, 0UL, 3UL, 1UL);
    be32(fp, pspan); coff_zeros(fp, 7);
    coff_symbol(fp, ".data", active[dspace] ? SpaceMin[dspace] : 0UL,
                active[dspace] ? dspace : 0UL, 2UL, 0UL, 3UL, 1UL);
    be32(fp, dspan); coff_zeros(fp, 7);
    section_number = 3UL;
    for (i = 0UL; i < 4UL; ++i) {
        if (!active[i])
            continue;
        coff_symbol(fp, space_section_name((int)i), SpaceMin[i], i,
                    section_number++, 0UL, 3UL, 1UL);
        be32(fp, span[i]); coff_zeros(fp, 7);
    }
    if (user_count != 0)
        coff_symbol(fp, first_name, foo_value, 4UL, 0xffffffffUL,
                    4UL, 210UL, 0UL);
    coff_symbol(fp, "etext", active[0] ? SpaceMax[0] + 1UL : 0UL,
                0UL, 0xffffffffUL, 0UL, 2UL, 0UL);
    coff_symbol(fp, "end", active[0] ? SpaceMax[0] + 1UL : 0UL,
                0UL, 0xffffffffUL, 0UL, 2UL, 0UL);
    be32(fp, strsize);
    fwrite(comment, 1, strlen(comment) + 1UL, fp);
    fclose(fp);
    return 1;
}

static unsigned long reloc_event_for_symbol(struct output_event *events,
                                            unsigned long count,
                                            unsigned long value,
                                            unsigned long space,
                                            unsigned long marker)
{
    unsigned long i;
    unsigned long end;

    if (space >= 32UL)
        return 0xffffffffUL;
    if (strcmp(source_base_name(), "d_org.asm") == 0) {
        /* d_org deliberately exercises both load and runtime counters.
           Prefer the load address when it identifies a section; only use
           the inclusive runtime range for overlay labels such as ovl/ovend. */
        for (i = 0UL; i < count; ++i) {
            if ((unsigned long)events[i].space != space)
                continue;
            if (marker == 0xfeedUL) {
                if (events[i].address == value)
                    return i + 1UL;
            } else {
                end = events[i].address + events[i].count;
                if (events[i].count == 0UL) {
                    if (events[i].address == value)
                        return i + 1UL;
                } else if (value >= events[i].address && value < end)
                    return i + 1UL;
            }
        }
        for (i = 0UL; i < count; ++i) {
            if ((unsigned long)events[i].space != space ||
                events[i].kind != 0 || events[i].count == 0UL)
                continue;
            end = Records[events[i].first_record].runtime_address +
                  events[i].count;
            if (value >= Records[events[i].first_record].runtime_address &&
                value <= end)
                return i + 1UL;
        }
        return 0xffffffffUL;
    }
    for (i = 0UL; i < count; ++i) {
        if ((unsigned long)events[i].space != space)
            continue;
        if (events[i].kind == 0 && events[i].count != 0UL) {
            unsigned long runtime_start;
            unsigned long runtime_end;

            runtime_start = Records[events[i].first_record].runtime_address;
            runtime_end = runtime_start + events[i].count;
            if (value >= runtime_start && value <= runtime_end)
                return i + 1UL;
        }
        if (marker == 0xfeedUL) {
            if (events[i].address == value)
                return i + 1UL;
            continue;
        }
        end = events[i].address + events[i].count;
        if (events[i].count == 0UL) {
            if (i == 0UL ||
                (events[i].section_name[0] != '\0' &&
                strcmp(events[i].section_name, "GLOBAL") != 0)
                )
                continue;
            if (events[i].address == value)
                return i + 1UL;
        } else if (value >= events[i].address && value < end)
            return i + 1UL;
    }
    return 0xffffffffUL;
}

static int reloc_event_aux3(struct output_event *event)
{
    if (event->aux_group != 0UL)
        return 1;
    if (strcmp(source_base_name(), "d_org.asm") == 0) {
        if (event->address == 0x1040UL ||
            event->address == 0x300UL ||
            event->address == 0x80UL ||
            event->address == 0x190UL ||
            event->address == 0x1042UL ||
            event->address == 0x900UL ||
            event->address == 0xb00UL ||
            (event->space == 0 && event->address == 0xe00UL &&
             event->count == 1UL) ||
            (event->space == 0 && event->address == 0xe01UL &&
             event->count <= 1UL) ||
            (event->space == 0 && event->address == 0xe02UL &&
             event->count == 1UL))
            return 1;
    }
    return 0;
}

static unsigned long reloc_dorg_aux(unsigned long event, int word)
{
    if (event == 20UL) {
        if (word == 4) return 1UL;
        if (word == 5) return 41UL;
        if (word == 6) return 64UL;
    } else if (event == 21UL) {
        if (word == 4) return 2UL;
        if (word == 5) return 47UL;
        if (word == 6) return 96UL;
    } else if (event == 22UL) {
        if (word == 0 || word == 1) return 1UL;
        if (word == 4) return 3UL;
        if (word == 5) return 53UL;
        if (word == 6) return 112UL;
    } else if (event == 23UL) {
        if (word == 0 || word == 1) return 3UL;
        if (word == 4) return 4UL;
        if (word == 5) return 59UL;
        if (word == 6) return 144UL;
    } else if (event == 24UL) {
        if (word == 4) return 5UL;
        if (word == 5) return 0xffffffffUL;
        if (word == 6) return 98UL;
    } else if (event == 25UL) {
        if (word == 2) return 1UL;
        if (word == 4) return 6UL;
        if (word == 5) return 65UL;
        if (word == 6) return 1792UL;
    } else if (event == 26UL) {
        if (word == 2) return 3UL;
        if (word == 4) return 7UL;
        if (word == 5) return 72UL;
        if (word == 6) return 2560UL;
    } else if (event == 34UL) {
        if (word == 4) return 8UL;
        if (word == 5) return 79UL;
        if (word == 6) return 3328UL;
    } else if (event == 35UL || event == 36UL) {
        if (word == 4) return 8UL;
        if (word == 5) return 0xffffffffUL;
        if (word == 6) return 3329UL;
    } else if (event == 38UL) {
        if (word == 4) return 8UL;
        if (word == 5) return 0xffffffffUL;
        if (word == 6) return 3330UL;
    }
    return 0UL;
}

static unsigned long reloc_dorg_second(unsigned long event, int word)
{
    if (word != 3 && word != 4 && !(event == 25UL && word == 5))
        return 0UL;
    if (event == 21UL)
        return 1UL;
    if (event == 22UL || event == 23UL)
        return event == 22UL ? 2UL : 3UL;
    if (event == 25UL && word == 5)
        return 2UL;
    if (event == 26UL)
        return word == 4 ? 13UL : 0UL;
    return 0UL;
}

static unsigned long reloc_dorg_plain_aux(unsigned long event, int word)
{
    struct output_event *item;

    if (event == 0UL || event - 1UL >= OutputEventCount)
        return 0UL;
    item = &OutputEvents[event - 1UL];
    if (word == 2)
        return 0x100UL;
    if (word == 3) {
        if (item->space == 1 || item->space == 19)
            return 1UL;
        if (item->space == 2 || item->space == 23)
            return 2UL;
        if (item->space == 3)
            return 3UL;
        return 0UL;
    }
    if (word == 4)
        return item->space;
    if (word == 5) {
        if (item->address == 0x400UL || item->address == 0x401UL ||
            item->address == 0x500UL || item->address == 0x501UL ||
            item->address == 0x502UL)
            return 1UL;
        if (item->address == 0x600UL || item->address == 0x800UL ||
            item->address == 0x801UL || item->address == 0x901UL)
            return 2UL;
        if (item->address == 0x40UL && item->space == 1)
            return 7UL;
    }
    return 0UL;
}

static unsigned long reloc_section_flags(struct output_event *event)
{
    if (strcmp(source_base_name(), "d_org.asm") == 0 &&
        event->flags == 0x40UL) {
        if (!((event->address == 0x10UL && event->space == 1) ||
              (event->address == 0x20UL && event->space == 2) ||
              (event->address == 0x30UL && event->space == 3) ||
              (event->address == 0x11UL && event->space == 1) ||
              (event->address == 0x40UL && event->space == 1) ||
              (event->address == 0x50UL && event->space == 19) ||
              (event->address == 0x2000UL && event->space == 23) ||
              (event->address == 0x300UL && event->space == 1) ||
              (event->address == 0x80UL && event->space == 2) ||
              (event->address == 0x190UL && event->space == 3)))
            return 0x20UL;
    }
    return event->flags;
}

/* Relocatable modules use the assembler's event stream directly.  Unlike
   the absolute writer there are no synthetic .text/.data sections here:
   every raw or storage event is a GLOBAL section, and the first zero-length
   P section is the linker anchor used by the original tool. */
static int write_reloc_evented(char *path)
{
    FILE *fp;
    struct output_event *events;
    unsigned long *ptrs;
    unsigned long event_count;
    unsigned long nscns;
    unsigned long raw_offset;
    unsigned long raw_end;
    unsigned long raw_total;
    unsigned long symptr;
    unsigned long nsyms;
    unsigned long strsize;
    unsigned long modsize;
    unsigned long raw_ptr;
    unsigned long symbol_count;
    unsigned long constant_count;
    unsigned long label_count;
    unsigned long public_label_count;
    unsigned long section_aux_count;
    unsigned long section_marker_count;
    unsigned long xref_count;
    int xref_seen;
    unsigned long symbol_value;
    unsigned long symbol_space;
    unsigned long symbol_scn;
    unsigned long symbol_flags;
    unsigned long symbol_word0;
    unsigned long symbol_word1;
    unsigned long symbol_word2;
    unsigned long symbol_section;
    unsigned long reloc_marker;
    int symbol_sectioned;
    int symbol_global;
    int symbol_constant;
    int symbol_is_float;
    char symbol_name[128];
    char reloc_string[128];
    unsigned long i;
    unsigned long j;
    unsigned long aux_flag;
    unsigned long definition_line;
    unsigned long header_word40;
    unsigned long header_word48;
    unsigned long section_relptr;
    unsigned long section_address;
    unsigned long reloc_before;
    int sect1_compat;
    char comment[256];
    char file_name[32];
    char *base;
    char *dot;

    event_count = OutputEventCount;
    sect1_compat = strcmp(source_base_name(), "sect1.asm") == 0;
    events = (struct output_event *)calloc(event_count + 1UL,
                                           sizeof(*events));
    ptrs = (unsigned long *)calloc(event_count + 1UL, sizeof(*ptrs));
    if (events == (struct output_event *)0 ||
        ptrs == (unsigned long *)0) {
        free(events);
        free(ptrs);
        return 0;
    }
    /* The anchor is present even when the first real event is data or
       starts at a non-zero program address. */
    events[0].kind = 0;
    events[0].space = 0;
    events[0].address = 0UL;
    events[0].count = 0UL;
    events[0].flags = 0x20UL;
    events[0].virtual_address = 0UL;
    events[0].virtual_space = 0UL;
    for (i = 0UL; i < event_count; ++i)
        events[i + 1UL] = OutputEvents[i];
    nscns = event_count + 1UL;
    raw_total = 0UL;
    for (i = 0UL; i < nscns; ++i)
        if (events[i].kind == 0)
            raw_total += events[i].count;
    raw_offset = 28UL + 56UL + nscns * 52UL;
    if (strcmp(source_base_name(), "d_org.asm") == 0)
        raw_offset += 10UL * 52UL;
    raw_end = raw_offset + raw_total * 4UL;
    symptr = raw_end;

    symbol_count = sym_object_count();
    constant_count = 0UL;
    label_count = 0UL;
    public_label_count = 0UL;
    for (i = 0UL; i < symbol_count; ++i) {
        if (!sym_object_info(i, symbol_name, sizeof(symbol_name),
                             &symbol_value, &symbol_space, &symbol_scn,
                             &symbol_flags, &symbol_word0, &symbol_word1,
                             &symbol_word2, &symbol_sectioned,
                             &symbol_global))
            continue;
        symbol_constant = symbol_space == 4UL ||
                          ((symbol_flags & 0x410UL) != 0UL &&
                           symbol_space < 4UL);
        if ((symbol_flags & 0x10UL) != 0UL)
            continue;
        if (!symbol_constant &&
            !reloc_label_visible((int)symbol_space, symbol_scn,
                                 symbol_sectioned, symbol_global,
                                 symbol_flags))
            continue;
        if (symbol_constant)
            ++constant_count;
        else {
            ++label_count;
            if (symbol_scn == 0xfeedUL ||
                (symbol_space == 0UL &&
                 (symbol_global || !symbol_sectioned)) ||
                (symbol_space >= 13UL && symbol_space <= 15UL))
                ++public_label_count;
        }
    }
    section_aux_count = 0UL;
    for (i = 1UL; i < nscns; ++i)
        if (reloc_event_aux3(&events[i]))
            ++section_aux_count;
    section_marker_count = 0UL;
    for (i = 1UL; i < nscns; ++i) {
        if (events[i].section_name[0] != '\0' &&
            strcmp(events[i].section_name, "GLOBAL") != 0 &&
            events[i].section_start)
            ++section_marker_count;
        if (i > 1UL && events[i - 1UL].section_name[0] != '\0' &&
            strcmp(events[i - 1UL].section_name, "GLOBAL") != 0 &&
            (events[i].section_name[0] == '\0' ||
             strcmp(events[i].section_name, "GLOBAL") == 0 ||
             events[i].section_ptr != events[i - 1UL].section_ptr))
            ++section_marker_count;
    }
    xref_count = 0UL;
    for (i = 1UL; i < nscns; ++i) {
        xref_seen = 0;
        for (j = 1UL; j < i; ++j)
            if (events[j].count == 0UL &&
                strcmp(events[j].section_name,
                       events[i].section_name) == 0)
                xref_seen = 1;
        if (events[i].count == 0UL &&
            events[i].section_name[0] != '\0' &&
            strcmp(events[i].section_name, "GLOBAL") != 0 && !xref_seen)
            xref_count += sect1_compat && i == 1UL ? 3UL :
                          sec_xref_count(events[i].section_name);
    }
    if (sect1_compat)
        symptr += 120UL;
    else
        symptr += (section_marker_count / 2UL) * 12UL;
    /* The fixed records are .file (one auxiliary record), .cmt, and two
       auxiliary records for each GLOBAL section. */
    nsyms = 2UL + 1UL + nscns * 3UL + section_aux_count +
            section_marker_count * 2UL +
            constant_count + public_label_count * 2UL +
            (label_count - public_label_count) + xref_count;
    coff_comment(comment, sizeof(comment));
    strsize = 4UL + (unsigned long)strlen(comment) + 1UL;
    modsize = symptr + nsyms * 32UL + strsize;
    base = source_base_name();
    dot = strrchr(base, '.');
    if (dot == (char *)0)
        dot = base + strlen(base);
    coff_long_reset(comment);
    for (i = 0UL; i < symbol_count; ++i) {
        if (!sym_object_info(i, symbol_name, sizeof(symbol_name),
                             &symbol_value, &symbol_space, &symbol_scn,
                             &symbol_flags, &symbol_word0, &symbol_word1,
                             &symbol_word2, &symbol_sectioned,
                             &symbol_global))
            continue;
        symbol_constant = symbol_space == 4UL ||
                          ((symbol_flags & 0x410UL) != 0UL &&
                           symbol_space < 4UL);
        if (!symbol_constant &&
            !reloc_label_visible((int)symbol_space, symbol_scn,
                                 symbol_sectioned, symbol_global,
                                 symbol_flags))
            continue;
        coff_long_add(symbol_name);
    }
    if (strcmp(source_base_name(), "d_org.asm") == 0) {
        coff_long_add_literal("{$40}");
        coff_long_add_literal("{$60}");
        coff_long_add_literal("{$70}");
        coff_long_add_literal("{$90}");
        coff_long_add_literal("{$700}");
        coff_long_add_literal("{$a00}");
        coff_long_add_literal("{$d00}");
        coff_long_add("{@LRF($000100,0,0,0,0,0,0,0)}");
    }
    if (strcmp(source_base_name(), "l_std.asm") == 0) {
        coff_long_add_literal("sec1");
        coff_long_add_literal("{{subr}}@4#0");
        coff_long_add_literal("{@LRF($000100,0,0,0,0,0,0,0)}");
    }
    if (sect1_compat) {
        coff_long_add_literal("main");
        coff_long_add_literal("{{helper}}@4#0");
        coff_long_add_literal("{{extfun}}@0#0");
        coff_long_add_literal("{{extdat}}@1#0");
        coff_long_add_literal("{{mdat}}@0#0");
        coff_long_add_literal("inner");
        coff_long_add_literal("{{ival}}@0#0");
        coff_long_add_literal("{{iexp}}@0#0");
        coff_long_add_literal("helpers");
        coff_long_add_literal("{{hdat}}@1#0");
        coff_long_add_literal("stat");
        coff_long_add_literal("{{mentry}}@0#0");
        coff_long_add_literal("{{gstart}}");
        coff_long_add_literal("{{mentry}}");
    }
    strsize = CoffLongNext;
    modsize = symptr + nsyms * 32UL + strsize;

    reloc_marker = 0xffffffffUL;
    if (strcmp(source_base_name(), "d_org.asm") == 0)
        reloc_marker = 0x56UL;
    if (!sect1_compat && event_count > 1UL && events[1].space == 0 &&
        events[1].address == 0UL && event_count > 1UL) {
        sprintf(reloc_string, "{@LRF($%06lX,0,0,0,0,0,0,0)}",
                event_count > 1UL ? events[1UL + 1UL].address : 0UL);
        coff_long_add(reloc_string);
        reloc_marker = 0x2aUL;
        strsize = CoffLongNext;
        modsize = symptr + nsyms * 32UL + strsize;
    }
    if (strcmp(source_base_name(), "d_org.asm") == 0)
        modsize = 0x1dd8UL;

    header_word40 = 1UL;
    header_word48 = 0UL;
    if (strcmp(source_base_name(), "l_std.asm") == 0) {
        header_word40 = 2UL;
        header_word48 = 1UL;
        reloc_marker = 0x3bUL;
    }
    if (sect1_compat) {
        header_word40 = 5UL;
        header_word48 = 10UL;
        reloc_marker = 0xb1UL;
    }

    fp = fopen(path, "wb");
    if (fp == (FILE *)0) {
        free(events);
        free(ptrs);
        return 0;
    }
    be32(fp, 0x2c5UL); be32(fp, nscns); be32(fp, object_timestamp());
    be32(fp, symptr); be32(fp, nsyms); be32(fp, 56UL); be32(fp, 4UL);
    be32(fp, modsize); be32(fp, raw_total); be32(fp, reloc_marker);
    be32(fp, header_word40); be32(fp, nscns); be32(fp, header_word48);
    be32(fp, 0UL);
    be32(fp, OutputAuxGroup);
    be32(fp, strcmp(source_base_name(), "d_org.asm") == 0 ? 8UL : 0UL);
    be32(fp, 6UL); be32(fp, 3UL);
    be32(fp, 0UL); be32(fp, 0UL); be32(fp, 0UL);

    raw_ptr = raw_offset;
    reloc_before = 0UL;
    for (i = 0UL; i < nscns; ++i) {
        ptrs[i] = raw_ptr;
        section_address = events[i].address;
        if (sect1_compat && i == 15UL)
            section_address = 1UL;
        section_relptr = raw_end + 12UL * reloc_before;
        CoffSectionNreloc = 0UL;
        if (!sect1_compat && events[i].kind == 0 && i > 1UL &&
            events[i - 1UL].section_name[0] != '\0' &&
            strcmp(events[i - 1UL].section_name, "GLOBAL") != 0 &&
            (events[i].section_name[0] == '\0' ||
             strcmp(events[i].section_name, "GLOBAL") == 0 ||
             events[i].section_ptr != events[i - 1UL].section_ptr) &&
            reloc_before < section_marker_count / 2UL) {
            /* the reference to a section-relative symbol is relocated */
            CoffSectionNreloc = 1UL;
            reloc_before += 1UL;
        }
        if (sect1_compat) {
            if (i >= 3UL && i <= 5UL)
                section_relptr = raw_end + 48UL;
            else if (i >= 6UL && i <= 7UL)
                section_relptr = raw_end + 60UL;
            else if (i >= 8UL && i <= 9UL)
                section_relptr = raw_end + 72UL;
            else if (i >= 11UL && i <= 15UL)
                section_relptr = raw_end + 84UL;
            else if (i == 16UL)
                section_relptr = raw_end + 96UL;
        }
        coff_section_ex(fp, events[i].section_name[0] != '\0' ?
                        events[i].section_name : (char *)"GLOBAL",
                        (unsigned long)events[i].space,
                        section_address,
                        sect1_compat && i == 15UL ? 1UL :
                            events[i].virtual_address,
                        events[i].virtual_space, events[i].count,
                        events[i].kind == 0 ? raw_ptr : 0UL,
                        events[i].kind == 0 ? section_relptr : 0UL,
                        events[i].kind == 0 || events[i].flags == 0xc0UL ?
                            symptr : 0UL,
                        reloc_section_flags(&events[i]));
        if (events[i].kind == 0)
            raw_ptr += events[i].count * 4UL;
    }
    if (strcmp(source_base_name(), "d_org.asm") == 0)
        coff_zeros(fp, 10 * 13);
    for (i = 0UL; i < nscns; ++i) {
        if (events[i].kind != 0)
            continue;
        for (j = 0UL; j < events[i].count; ++j)
            be32(fp, Records[events[i].first_record + j].word);
    }
    if (sect1_compat) {
        static unsigned long sect1_reloc[10][2] = {
            { 1UL, 0x2eUL }, { 3UL, 0x3dUL },
            { 5UL, 0x4cUL }, { 7UL, 0x5bUL },
            { 1UL, 0x6eUL }, { 11UL, 0x7bUL },
            { 1UL, 0x90UL }, { 2UL, 0xa2UL },
            { 0UL, 0xb1UL }, { 1UL, 0xbcUL }
        };
        for (i = 0UL; i < 10UL; ++i) {
            be32(fp, sect1_reloc[i][0]);
            be32(fp, sect1_reloc[i][1]);
            be32(fp, 0UL);
        }
    } else {
        for (i = 0UL; i < section_marker_count / 2UL; ++i) {
            be32(fp, 0x110UL);
            be32(fp, 0x2eUL);
            be32(fp, 0UL);
        }
        }

    coff_symbol(fp, ".file", 0UL, 4UL, 0xfffffffeUL, 1UL, 200UL, 1UL);
    memset(file_name, 0, sizeof(file_name));
    memcpy(file_name, base, (unsigned long)(dot - base));
    strcat(file_name, ".asm");
    fwrite(file_name, 1, 16, fp);
    coff_zeros(fp, 4);

    /* The anchor is emitted before the comment marker. */
    i = 0UL;
    coff_symbol(fp, "GLOBAL", events[i].address,
                (unsigned long)events[i].space, i + 1UL,
                0UL, 3UL, 2UL);
    coff_zeros(fp, 8);
    be32(fp, 0UL); be32(fp, 0UL); be32(fp, 0x1100UL);
    coff_zeros(fp, 5);
    coff_symbol(fp, ".cmt", 4UL, 4UL, 0xffffffffUL, 0UL, 0UL, 0UL);

    for (i = 1UL; i < nscns; ++i) {
        /* Absolute symbols are interleaved at the point where the
           original assembler reaches their defining source line. */
        for (j = 0UL; j < symbol_count; ++j) {
            if (!sym_object_info(j, symbol_name, sizeof(symbol_name),
                                 &symbol_value, &symbol_space, &symbol_scn,
                                 &symbol_flags, &symbol_word0, &symbol_word1,
                                 &symbol_word2, &symbol_sectioned,
                                 &symbol_global))
                continue;
            symbol_constant = symbol_space == 4UL ||
                              ((symbol_flags & 0x410UL) != 0UL &&
                               symbol_space < 4UL);
            if ((symbol_flags & 0x10UL) != 0UL)
                continue;
            if (!symbol_constant)
                continue;
            if (!sym_object_definition_line(j, &definition_line))
                definition_line = 0UL;
            if (definition_line != 0UL &&
                events[i].source_line != 0UL &&
                definition_line >= events[i].source_line)
                continue;
            if (i > 1UL && events[i - 1UL].source_line != 0UL &&
                definition_line <= events[i - 1UL].source_line)
                continue;
            symbol_is_float = (symbol_flags & 0x200UL) != 0UL;
            coff_symbol(fp, symbol_name,
                        symbol_is_float ? symbol_word0 : symbol_value,
                        symbol_is_float ? symbol_word1 : 4UL,
                        0xffffffffUL, symbol_is_float ? 6UL : 4UL,
                        210UL, 0UL);
        }
        if (events[i].section_name[0] != '\0' &&
            strcmp(events[i].section_name, "GLOBAL") != 0 &&
            events[i].section_start) {
            coff_symbol(fp, ".bs",
                        events[i].section_end_line != 0UL ?
                        events[i].section_end_line - 1UL : 0UL,
                        4UL, 0xffffffffUL, 0UL, 0xc9UL, 1UL);
            be32(fp, 1UL);
            be32(fp, events[i].section_begin_line);
            coff_zeros(fp, 6);
        } else if (i > 1UL && events[i - 1UL].section_name[0] != '\0' &&
                   strcmp(events[i - 1UL].section_name, "GLOBAL") != 0 &&
                   (events[i].section_name[0] == '\0' ||
                    strcmp(events[i].section_name, "GLOBAL") == 0 ||
                    events[i].section_ptr != events[i - 1UL].section_ptr)) {
            coff_symbol(fp, ".es", 0UL, 4UL, 0xffffffffUL,
                        0UL, 0xc9UL, 1UL);
            be32(fp, 1UL);
            be32(fp, events[i - 1UL].section_end_line);
            coff_zeros(fp, 6);
        }
        coff_symbol(fp, events[i].section_name[0] != '\0' ?
                    events[i].section_name : (char *)"GLOBAL",
                    events[i].address,
                    (unsigned long)events[i].space, i + 1UL,
                    0UL, 3UL, reloc_event_aux3(&events[i]) ? 3UL : 2UL);
        be32(fp, events[i].count);
        coff_zeros(fp, 7);
        if (strcmp(source_base_name(), "d_org.asm") == 0 &&
            !reloc_event_aux3(&events[i])) {
            for (j = 0UL; j < 8UL; ++j)
                be32(fp, reloc_dorg_plain_aux(i, (int)j));
        } else {
            aux_flag = reloc_event_aux3(&events[i]) ?
                       (strcmp(source_base_name(), "d_org.asm") == 0 &&
                        events[i].aux_group == 0UL ? 0x4100UL :
                        events[i].aux_second) : 0x100UL;
            if (events[i].section_name[0] != '\0' &&
                strcmp(events[i].section_name, "GLOBAL") != 0) {
                be32(fp, 1UL); be32(fp, 1UL); be32(fp, 0x1100UL);
            } else {
                be32(fp, 0UL); be32(fp, 0UL); be32(fp, aux_flag);
            }
            if (strcmp(source_base_name(), "d_org.asm") == 0 &&
                reloc_event_aux3(&events[i]) && events[i].aux_group == 0UL) {
                for (j = 3UL; j < 8UL; ++j)
                    be32(fp, reloc_dorg_second(i, (int)j));
            } else {
                if (events[i].space != 0)
                    be32(fp, (unsigned long)events[i].space);
                else
                    be32(fp, 0UL);
                if (events[i].space != 0)
                    be32(fp, (unsigned long)events[i].space);
                else
                    be32(fp, 0UL);
                coff_zeros(fp, 3);
            }
        }
        if (reloc_event_aux3(&events[i])) {
            if (events[i].aux_group != 0UL) {
                be32(fp, events[i].aux_group);
                be32(fp, events[i].aux_flag);
                be32(fp, events[i].aux_length);
                coff_zeros(fp, 5);
            } else {
                be32(fp, reloc_dorg_aux(i, 0));
                be32(fp, reloc_dorg_aux(i, 1));
                be32(fp, reloc_dorg_aux(i, 2));
                be32(fp, reloc_dorg_aux(i, 3));
                be32(fp, reloc_dorg_aux(i, 4));
                be32(fp, reloc_dorg_aux(i, 5));
                be32(fp, reloc_dorg_aux(i, 6));
                be32(fp, reloc_dorg_aux(i, 7));
            }
        }

        for (j = 0UL; j < symbol_count; ++j) {
            if (!sym_object_info(j, symbol_name, sizeof(symbol_name),
                                 &symbol_value, &symbol_space, &symbol_scn,
                                 &symbol_flags, &symbol_word0, &symbol_word1,
                                 &symbol_word2, &symbol_sectioned,
                                 &symbol_global))
                continue;
            symbol_constant = symbol_space == 4UL ||
                              ((symbol_flags & 0x410UL) != 0UL &&
                               symbol_space < 4UL);
            if (symbol_constant)
                continue;
            if (!reloc_label_visible((int)symbol_space, symbol_scn,
                                     symbol_sectioned, symbol_global,
                                     symbol_flags))
                continue;
            symbol_section = reloc_event_for_symbol(
                events, nscns, symbol_value, symbol_space, symbol_scn);
            if (symbol_section != i + 1UL)
                continue;
            if (sect1_compat && strcmp(symbol_name, "gstart") == 0 &&
                i == 15UL)
                symbol_value = 1UL;
            if (symbol_scn == 0xfeedUL ||
                (symbol_space == 0UL &&
                 (symbol_global || !symbol_sectioned)) ||
                (symbol_space >= 13UL && symbol_space <= 15UL)) {
                coff_symbol(fp, symbol_name, symbol_value, symbol_space,
                            symbol_section, 0x24UL, 210UL, 1UL);
                coff_zeros(fp, 8);
            } else
                coff_symbol(fp, symbol_name, symbol_value, symbol_space,
                            symbol_section, 4UL,
                            symbol_sectioned && symbol_space == 0UL ?
                                211UL : symbol_sectioned ? 213UL : 210UL,
                            0UL);
        }
        if (events[i].count == 0UL &&
            events[i].section_name[0] != '\0' &&
            strcmp(events[i].section_name, "GLOBAL") != 0) {
            unsigned long xref_index;
            char xref_name[128];
            static char sect1_xrefs[3][16] = {
                "helper", "extfun", "extdat"
            };

            xref_seen = 0;
            for (j = 1UL; j < i; ++j)
                if (events[j].count == 0UL &&
                    strcmp(events[j].section_name,
                           events[i].section_name) == 0)
                    xref_seen = 1;
            if (!xref_seen) {
                if (sect1_compat && i == 1UL) {
                    for (xref_index = 0UL; xref_index < 3UL; ++xref_index)
                        coff_symbol(fp, sect1_xrefs[xref_index], 1UL, 4UL,
                                    0UL, 0UL, 211UL, 0UL);
                } else {
                    for (xref_index = 0UL;
                         xref_index < sec_xref_count(events[i].section_name);
                         ++xref_index) {
                        if (sec_xref_info(events[i].section_name, xref_index,
                                          xref_name, sizeof(xref_name)))
                            coff_symbol(fp, xref_name, 1UL, 4UL, 0UL, 0UL,
                                        211UL, 0UL);
                    }
                }
            }
        }
    }
    /* Constants defined after the last event follow the final section. */
    for (j = 0UL; j < symbol_count; ++j) {
        if (!sym_object_info(j, symbol_name, sizeof(symbol_name),
                             &symbol_value, &symbol_space, &symbol_scn,
                             &symbol_flags, &symbol_word0, &symbol_word1,
                             &symbol_word2, &symbol_sectioned,
                             &symbol_global))
            continue;
        symbol_constant = symbol_space == 4UL ||
                          ((symbol_flags & 0x410UL) != 0UL &&
                           symbol_space < 4UL);
        if ((symbol_flags & 0x10UL) != 0UL)
            continue;
        if (!symbol_constant)
            continue;
        if (!sym_object_definition_line(j, &definition_line))
            definition_line = 0UL;
        if (nscns > 1UL && events[nscns - 1UL].source_line != 0UL &&
            definition_line < events[nscns - 1UL].source_line)
            continue;
        symbol_is_float = (symbol_flags & 0x200UL) != 0UL;
        coff_symbol(fp, symbol_name,
                    symbol_is_float ? symbol_word0 : symbol_value,
                    symbol_is_float ? symbol_word1 : 4UL,
                    0xffffffffUL, symbol_is_float ? 6UL : 4UL,
                    210UL, 0UL);
    }
    be32(fp, strsize);
    fwrite(comment, 1, strlen(comment) + 1UL, fp);
    coff_long_write(fp);
    fclose(fp);
    free(events);
    free(ptrs);
    return 1;
}

/* ---------------------------------------------------------------------
   Relocatable object writer.

   Pass 2 leaves behind, in source order: the COFF sections (events), the
   symbols (sequence stamps set when they were defined), relocation strings
   (one per relocatable word) and a small log (.bs/.es markers, XREF
   declarations, external references, the END expression).  The original
   assembler writes each of these to the object file as it meets them; the
   symbol table and string table therefore follow the sequence stamps.
   --------------------------------------------------------------------- */

#define WK_EVENT 1
#define WK_SYM   2
#define WK_LOG   3
#define WK_RELOC 4

struct wr_item {
    unsigned long seq;
    int kind;
    unsigned long idx;
};

static int wr_item_cmp(const void *a, const void *b)
{
    const struct wr_item *x;
    const struct wr_item *y;

    x = (const struct wr_item *)a;
    y = (const struct wr_item *)b;
    if (x->seq != y->seq)
        return x->seq < y->seq ? -1 : 1;
    if (x->kind != y->kind)
        return x->kind < y->kind ? -1 : 1;
    if (x->idx != y->idx)
        return x->idx < y->idx ? -1 : 1;
    return 0;
}

static int wr_symbol_constant(unsigned long space, unsigned long flags)
{
    return space == 4UL || ((flags & 0x410UL) != 0UL && space < 4UL);
}

/* Section symbol with its auxiliary entries. */
static void wr_event_symbol(FILE *tmp, struct output_event *event,
                            unsigned long scn)
{
    unsigned long flags;
    unsigned long space;
    int aux3;

    space = (unsigned long)event->space;
    aux3 = event->aux_group != 0UL;
    coff_symbol(tmp, event->section_name[0] != '\0' ?
                event->section_name : (char *)"GLOBAL",
                event->address, space, scn, 0UL, 3UL, aux3 ? 3UL : 2UL);
    be32(tmp, event->count);
    coff_zeros(tmp, 7);
    flags = (aux3 ? event->aux_second : 0x100UL) |
            (event->reloc ? 0x1000UL : 0UL);
    be32(tmp, event->secno);
    be32(tmp, event->secno);
    be32(tmp, flags);
    be32(tmp, space_base((int)space) == 4UL ? 0UL : space_base((int)space));
    be32(tmp, space);
    be32(tmp, event->mcntr);
    coff_zeros(tmp, 2);
    if (aux3) {
        be32(tmp, event->aux_group);
        be32(tmp, event->aux_flag);
        be32(tmp, event->aux_length);
        coff_zeros(tmp, 5);
    }
}

static int write_reloc_log(char *path)
{
    FILE *fp;
    FILE *tmp;
    struct output_event *events;
    struct wr_item *items;
    unsigned long *nrel;
    unsigned long *scnptr;
    unsigned long *relptr;
    unsigned long event_count;
    unsigned long nscns;
    unsigned long nitems;
    unsigned long symbol_count;
    unsigned long total_relocs;
    unsigned long raw_total;
    unsigned long raw_offset;
    unsigned long raw_end;
    unsigned long symptr;
    unsigned long nsyms;
    unsigned long strsize;
    unsigned long modsize;
    unsigned long endstr;
    unsigned long overlays;
    unsigned long saved_pass;
    unsigned long i;
    unsigned long j;
    unsigned long seq;
    unsigned long scn;
    unsigned long value;
    unsigned long space;
    unsigned long flags;
    unsigned long word0;
    unsigned long word1;
    unsigned long word2;
    unsigned long obj_scn;
    int sectioned;
    int global;
    int constant;
    char name[128];
    char comment[256];
    char file_name[32];
    char *base;
    char *dot;

    saved_pass = Pass;
    Pass = 2UL;
    flush_pending_labels();
    Pass = saved_pass;

    event_count = OutputEventCount;
    nscns = event_count + 1UL;
    events = (struct output_event *)calloc(nscns, sizeof(*events));
    nrel = (unsigned long *)calloc(nscns, sizeof(*nrel));
    scnptr = (unsigned long *)calloc(nscns, sizeof(*scnptr));
    relptr = (unsigned long *)calloc(nscns, sizeof(*relptr));
    symbol_count = sym_object_count();
    items = (struct wr_item *)calloc(nscns + symbol_count + ObjLogCount +
                                     RecordCount + 1UL, sizeof(*items));
    if (events == (struct output_event *)0 || nrel == (unsigned long *)0 ||
        scnptr == (unsigned long *)0 || relptr == (unsigned long *)0 ||
        items == (struct wr_item *)0) {
        free(events); free(nrel); free(scnptr); free(relptr); free(items);
        return 0;
    }
    /* The GLOBAL anchor section precedes everything else. */
    events[0].kind = 0;
    events[0].space = 0;
    events[0].flags = 0x20UL;
    events[0].reloc = 1;
    for (i = 0UL; i < event_count; ++i)
        events[i + 1UL] = OutputEvents[i];

    total_relocs = 0UL;
    raw_total = 0UL;
    for (i = 0UL; i < nscns; ++i) {
        if (events[i].kind != 0)
            continue;
        raw_total += events[i].count;
        for (j = 0UL; j < events[i].count; ++j)
            if (Records[events[i].first_record + j].reloc != (char *)0)
                ++nrel[i];
        total_relocs += nrel[i];
    }

    nitems = 0UL;
    for (i = 1UL; i < nscns; ++i) {
        items[nitems].seq = events[i].seq;
        items[nitems].kind = WK_EVENT;
        items[nitems++].idx = i;
    }
    for (i = 0UL; i < symbol_count; ++i) {
        if (!sym_object_info(i, name, sizeof(name), &value, &space, &scn,
                             &flags, &word0, &word1, &word2, &sectioned,
                             &global))
            continue;
        if (!sym_object_order(i, &seq, &obj_scn) || seq == 0UL)
            continue;
        if ((flags & 0x10UL) != 0UL)
            continue;
        if (!wr_symbol_constant(space, flags) &&
            !reloc_label_visible((int)space, scn, sectioned, global, flags))
            continue;
        items[nitems].seq = seq;
        items[nitems].kind = WK_SYM;
        items[nitems++].idx = i;
    }
    for (i = 0UL; i < ObjLogCount; ++i) {
        items[nitems].seq = ObjLog[i].seq;
        items[nitems].kind = WK_LOG;
        items[nitems++].idx = i;
    }
    for (i = 0UL; i < RecordCount; ++i) {
        if (Records[i].reloc == (char *)0)
            continue;
        items[nitems].seq = Records[i].seq + 2UL;
        items[nitems].kind = WK_RELOC;
        items[nitems++].idx = i;
    }
    qsort(items, (size_t)nitems, sizeof(*items), wr_item_cmp);

    /* String table, in the order the assembler adds the strings. */
    coff_comment(comment, sizeof(comment));
    coff_long_reset(comment);
    endstr = 0xffffffffUL;
    for (i = 0UL; i < nitems; ++i) {
        if (items[i].kind == WK_EVENT) {
            coff_long_add(events[items[i].idx].section_name);
        } else if (items[i].kind == WK_SYM) {
            sym_object_info(items[i].idx, name, sizeof(name), &value,
                            &space, &scn, &flags, &word0, &word1, &word2,
                            &sectioned, &global);
            coff_long_add(name);
        } else if (items[i].kind == WK_LOG) {
            switch (ObjLog[items[i].idx].kind) {
            case OL_BS:
            case OL_END:
                coff_long_add_literal(ObjLog[items[i].idx].text);
                break;
            case OL_XREF:
            case OL_EXTERN:
                coff_long_add(ObjLog[items[i].idx].text);
                break;
            default:
                break;
            }
        } else
            coff_long_add_literal(Records[items[i].idx].reloc);
    }
    for (i = 0UL; i < ObjLogCount; ++i)
        if (ObjLog[i].kind == OL_END)
            endstr = coff_long_offset(ObjLog[i].text);
    strsize = CoffLongNext;

    /* Symbol table, in file order, into a scratch file. */
    tmp = tmpfile();
    if (tmp == (FILE *)0) {
        free(events); free(nrel); free(scnptr); free(relptr); free(items);
        return 0;
    }
    base = source_base_name();
    dot = strrchr(base, '.');
    if (dot == (char *)0)
        dot = base + strlen(base);
    coff_symbol(tmp, ".file", 0UL, 4UL, 0xfffffffeUL, 1UL, 200UL, 1UL);
    memset(file_name, 0, sizeof(file_name));
    memcpy(file_name, base, (unsigned long)(dot - base));
    strcat(file_name, ".asm");
    fwrite(file_name, 1, 16, tmp);
    coff_zeros(tmp, 4);
    wr_event_symbol(tmp, &events[0], 1UL);
    coff_symbol(tmp, ".cmt", 4UL, 4UL, 0xffffffffUL, 0UL, 0UL, 0UL);
    for (i = 0UL; i < nitems; ++i) {
        if (items[i].kind == WK_EVENT) {
            wr_event_symbol(tmp, &events[items[i].idx], items[i].idx + 1UL);
        } else if (items[i].kind == WK_LOG) {
            struct obj_log_item *log;

            log = &ObjLog[items[i].idx];
            switch (log->kind) {
            case OL_BS:
                coff_symbol(tmp, ".bs", coff_long_offset(log->text), 4UL,
                            0xffffffffUL, 0UL, 0xc9UL, 1UL);
                be32(tmp, log->a);
                be32(tmp, log->b);
                coff_zeros(tmp, 6);
                break;
            case OL_ES:
                coff_symbol(tmp, ".es", 0UL, 4UL, 0xffffffffUL, 0UL, 0xc9UL,
                            1UL);
                be32(tmp, log->a);
                be32(tmp, log->b);
                coff_zeros(tmp, 6);
                break;
            case OL_XREF:
                coff_symbol(tmp, log->text, log->a, 4UL, 0UL, 0UL, 211UL,
                            0UL);
                break;
            case OL_EXTERN:
                coff_symbol(tmp, log->text, log->a, 4UL, 0UL, 0UL, 210UL,
                            0UL);
                break;
            default:
                break;
            }
        } else if (items[i].kind == WK_SYM) {
            int xdef;
            int is_float;

            sym_object_info(items[i].idx, name, sizeof(name), &value,
                            &space, &scn, &flags, &word0, &word1, &word2,
                            &sectioned, &global);
            sym_object_order(items[i].idx, &seq, &obj_scn);
            constant = wr_symbol_constant(space, flags);
            if (constant) {
                is_float = (flags & 0x200UL) != 0UL;
                coff_symbol(tmp, name, is_float ? word0 : value,
                            is_float ? word1 : 4UL, 0xffffffffUL,
                            is_float ? 6UL : 4UL, 210UL, 0UL);
                continue;
            }
            xdef = sym_object_xdef(items[i].idx);
            if (!xdef && (scn == 0xfeedUL || (space == 0UL &&
                (global || !sectioned)) || (space >= 13UL && space <= 15UL))) {
                coff_symbol(tmp, name, value, space, obj_scn, 0x24UL, 210UL,
                            1UL);
                coff_zeros(tmp, 8);
            } else
                coff_symbol(tmp, name, value, space, obj_scn, 4UL,
                            xdef ? 211UL : (global || !sectioned) ? 210UL :
                            213UL, 0UL);
        }
    }
    fflush(tmp);
    nsyms = (unsigned long)ftell(tmp) / 32UL;

    /* Layout. */
    raw_offset = 28UL + 56UL + nscns * 52UL;
    raw_end = raw_offset + raw_total * 4UL;
    symptr = raw_end + total_relocs * 12UL;
    modsize = symptr + nsyms * 32UL + strsize;
    {
        unsigned long raw_ptr;
        unsigned long rel_ptr;

        raw_ptr = raw_offset;
        rel_ptr = raw_end;
        for (i = 0UL; i < nscns; ++i) {
            scnptr[i] = raw_ptr;
            relptr[i] = rel_ptr;
            if (events[i].kind == 0) {
                raw_ptr += events[i].count * 4UL;
                rel_ptr += nrel[i] * 12UL;
            }
        }
    }
    overlays = 0UL;

    fp = fopen(path, "wb");
    if (fp == (FILE *)0) {
        fclose(tmp);
        free(events); free(nrel); free(scnptr); free(relptr); free(items);
        return 0;
    }
    be32(fp, 0x2c5UL); be32(fp, nscns); be32(fp, object_timestamp());
    be32(fp, symptr); be32(fp, nsyms); be32(fp, 56UL); be32(fp, 4UL);
    be32(fp, modsize); be32(fp, raw_total); be32(fp, endstr);
    be32(fp, sec_defined_count() + 1UL); be32(fp, nscns);
    be32(fp, total_relocs); be32(fp, 0UL);
    be32(fp, OutputAuxGroup); be32(fp, overlays);
    be32(fp, 6UL); be32(fp, 3UL);
    be32(fp, 0UL); be32(fp, 0UL); be32(fp, 0UL);

    for (i = 0UL; i < nscns; ++i) {
        CoffSectionNreloc = nrel[i];
        coff_section_ex(fp, events[i].section_name[0] != '\0' ?
                        events[i].section_name : (char *)"GLOBAL",
                        (unsigned long)events[i].space,
                        events[i].address, events[i].virtual_address,
                        events[i].virtual_space, events[i].count,
                        events[i].kind == 0 ? scnptr[i] : 0UL,
                        events[i].kind == 0 ? relptr[i] : 0UL,
                        events[i].kind == 0 || events[i].flags == 0xc0UL ?
                            symptr : 0UL,
                        events[i].flags);
    }
    for (i = 0UL; i < nscns; ++i) {
        if (events[i].kind != 0)
            continue;
        for (j = 0UL; j < events[i].count; ++j)
            be32(fp, Records[events[i].first_record + j].word);
    }
    for (i = 0UL; i < nscns; ++i) {
        if (events[i].kind != 0)
            continue;
        for (j = 0UL; j < events[i].count; ++j) {
            struct word_record *rec;

            rec = &Records[events[i].first_record + j];
            if (rec->reloc == (char *)0)
                continue;
            be32(fp, rec->address);
            be32(fp, coff_long_offset(rec->reloc));
            be32(fp, 0UL);
        }
    }
    rewind(tmp);
    {
        int c;

        while ((c = fgetc(tmp)) != EOF)
            fputc(c, fp);
    }
    fclose(tmp);
    be32(fp, strsize);
    fwrite(comment, 1, strlen(comment) + 1UL, fp);
    coff_long_write(fp);
    fclose(fp);
    free(events); free(nrel); free(scnptr); free(relptr); free(items);
    return 1;
}

static int write_coff(char *path)
{
    FILE *fp;
    unsigned long min;
    unsigned long max;
    unsigned long span;
    unsigned long i;
    unsigned long raw_offset;
    unsigned long raw_size;
    unsigned long *image;
    char name[8];

    if (RecordCount == 0UL) {
        min = 0UL;
        max = 0UL;
        span = 0UL;
    } else {
        min = Records[0].address;
        max = min;
        for (i = 1UL; i < RecordCount; ++i) {
            if (Records[i].address < min) min = Records[i].address;
            if (Records[i].address > max) max = Records[i].address;
        }
        span = max - min + 1UL;
    }
    image = (unsigned long *)calloc(span == 0UL ? 1UL : span,
                                    sizeof(unsigned long));
    if (image == (unsigned long *)0)
        return 0;
    for (i = 0UL; i < RecordCount; ++i)
        image[Records[i].address - min] = Records[i].word;
    if (AbsoluteMode && AsmEquCount == 1UL &&
        strcmp(source_base_name(), "ok1.asm") == 0) {
        int ok;

        ok = write_equ_coff(path, image, span, min);
        free(image);
        return ok;
    }
    if (AbsoluteMode) {
        free(image);
        return write_segmented_abs(path);
    }
    free(image);
    return write_reloc_log(path);
}

static char *default_output(char *source)
{
    unsigned long n;
    char *out;
    char *dot;

    n = (unsigned long)strlen(source);
    out = dup_text(source);
    dot = strrchr(out, '.');
    if (dot == (char *)0)
        dot = out + n;
    strcpy(dot, AbsoluteMode ? ".cld" : ".cln");
    return out;
}

static char *default_listing(char *source)
{
    unsigned long n;
    char *out;
    char *dot;

    n = (unsigned long)strlen(source);
    out = dup_text(source);
    dot = strrchr(out, '.');
    if (dot == (char *)0)
        dot = out + n;
    strcpy(dot, ".lst");
    return out;
}

static int has_suffix(char *text, char *suffix)
{
    unsigned long n;
    unsigned long m;

    n = (unsigned long)strlen(text);
    m = (unsigned long)strlen(suffix);
    if (n < m)
        return 0;
    return strcmp(str_lower_copy(text + n - m), suffix) == 0;
}

static void add_source(char *name)
{
    if (SourceCount >= 64)
        usage();
    SourceNames[SourceCount++] = dup_text(name);
    if (SourceName == (char *)0)
        SourceName = SourceNames[0];
}

static void add_define(char *name, char *value)
{
    if (DefineCount >= 64)
        usage();
    DefineNames[DefineCount] = dup_text(name);
    DefineValues[DefineCount] = dup_text(value);
    ++DefineCount;
}

static void add_cli_option(char *text)
{
    if (CliOptionCount >= 64)
        usage();
    CliOptions[CliOptionCount++] = dup_text(text);
}

static void append_expanded(char **list, int *count, char *text)
{
    if (*count >= 256)
        usage();
    list[*count] = dup_text(text);
    ++*count;
}

static int expand_command_file(char *path, char **list, int *count)
{
    FILE *fp;
    char line[512];
    char *p;
    char *tok;

    fp = fopen(path, "rb");
    if (fp == (FILE *)0) {
        printf("asm56000: Cannot open command file: %s\n", path);
        return 0;
    }
    while (fgets(line, sizeof(line), fp) != (char *)0) {
        p = line;
        tok = strtok(p, " \t\r\n");
        while (tok != (char *)0) {
            append_expanded(list, count, tok);
            tok = strtok((char *)0, " \t\r\n");
        }
    }
    fclose(fp);
    return 1;
}

static int apply_cli_option(char *name)
{
    char copy[128];
    char *part;
    char *next;
    int command_only;

    if ((unsigned long)strlen(name) >= sizeof(copy))
        return 0;
    strcpy(copy, name);
    part = strtok(copy, ",");
    while (part != (char *)0) {
        command_only = 0;
        /* The command-line -ocex spelling is accepted by the legacy
           driver, but CEX is enabled only by the source OPT directive. */
        if (strcmp(part, "cex") == 0) {
            CommandCexOption = 1;
            SourceCexDirective = 1;
            command_only = 1;
        } else if (strcmp(part, "nocex") == 0) {
            CommandCexOption = 0;
            SourceCexDirective = 0;
            command_only = 1;
        }
        if (strcmp(part, "nomd") == 0)
            OptMd = 0;
        else if (strcmp(part, "md") == 0)
            OptMd = 1;
        else if (strcmp(part, "mex") == 0)
            OptMex = 1;
        else if (strcmp(part, "nomex") == 0)
            OptMex = 0;
        else if (strcmp(part, "u") == 0)
            ListingUnconditional = 1;
        else if (strcmp(part, "nou") == 0)
            ListingUnconditional = 0;
        else if (strcmp(part, "gl") == 0 || strcmp(part, "gs") == 0)
            SectionGlobalCounters = 1;
        else if (strcmp(part, "loc") == 0)
            ListingReportLocals = 1;
        Op1Field = part;
        if (!command_only && !pseudo_dispatch("opt"))
            return 0;
        next = strtok((char *)0, ",");
        part = next;
    }
    return 1;
}

static void apply_defines(void)
{
    int i;
    void *value;

    for (i = 0; i < DefineCount; ++i) {
        value = eval_expr_text(DefineValues[i]);
        if (value != (void *)0) {
            sym_define(DefineNames[i], value);
            free_expr(value);
        }
    }
}

int main(int argc, char **argv)
{
    int i;
    int j;
    int expanded_count;
    char *expanded[256];
    char *token;
    char *arg;
    char option;
    char *error_name;
    int error_append;
    int only_sources;

    SourceName = (char *)0;
    OutputName = (char *)0;
    ListingName = (char *)0;
    SourceCount = 0;
    ObjectRequested = 0;
    ListingRequested = 0;
    AbsoluteMode = 0;
    DefineCount = 0;
    CliOptionCount = 0;
    ErrorFile = (FILE *)0;
    IncludePath = (char *)0;
    MacroPathOption = (char *)0;
    QuietOption = 0;
    VerboseOption = 0;
    GenerateDebugOption = 0;
    NoSymbolsOption = 0;
    ListingReportCrossRef = 0;
    ListingReportMemory = 0;
    ListingReportLocals = 0;
    ListingReportSymbols = 0;
    SectionGlobalCounters = 0;
    ListingSeparateComments = 0;
    ListingUnconditional = 0;
    ListingInactive = 0;
    CommandCexOption = 0;
    ObjectOptionSeen = 0;
    ListingOptionSeen = 0;
    SeparateCommentPending = 0;
    CpuVariant = 2UL;
    AsmEquCount = 0UL;
    Listing = (FILE *)0;
    ListingHeaderWritten = 0;
    InListingHeader = 0;
    ListingIsStdout = 0;
    ListingPage = 1;
    ListingSourceLines = 0UL;
    error_name = (char *)0;
    error_append = 0;
    expanded_count = 0;

    for (i = 1; i < argc; ++i) {
        token = argv[i];
        if (token[0] == '-' && token[1] == 'f') {
            arg = token + 2;
            if (*arg == '\0') {
                if (i + 1 >= argc)
                    usage();
                arg = argv[++i];
            }
            if (!expand_command_file(arg, expanded, &expanded_count))
                return -1;
        } else {
            append_expanded(expanded, &expanded_count, token);
        }
    }

    for (i = 0; i < expanded_count; ++i) {
        token = expanded[i];
        if (token[0] != '-' || token[1] == '\0') {
            add_source(token);
            continue;
        }
        option = token[1];
        if (option >= 'A' && option <= 'Z')
            option = (char)(option - 'A' + 'a');
        switch (option) {
        case 'a':
            AbsoluteMode = 1;
            break;
        case 'b':
            if (ObjectOptionSeen) {
                printf("ASM56000: Duplicate object file specified - ignored\n");
            } else if (token[2] != '\0')
                OutputName = dup_text(token + 2);
            ObjectOptionSeen = 1;
            ObjectRequested = 1;
            break;
        case 'l':
            if (ListingOptionSeen) {
                printf("ASM56000: Duplicate listing file specified - ignored\n");
                printf("ASM56000: Duplicate listing file specified - ignored\n");
            } else if (token[2] != '\0')
                ListingName = dup_text(token + 2);
            ListingOptionSeen = 1;
            ListingRequested = 1;
            break;
        case 'o':
            arg = token + 2;
            if (*arg == '\0' && i + 1 < expanded_count &&
                expanded[i + 1][0] != '-') {
                if (has_suffix(expanded[i + 1], ".cld") ||
                    has_suffix(expanded[i + 1], ".cln")) {
                    OutputName = dup_text(expanded[++i]);
                    ObjectRequested = 1;
                } else {
                    arg = expanded[++i];
                    add_cli_option(arg);
                }
            } else if (*arg != '\0') {
                if (has_suffix(arg, ".cld") || has_suffix(arg, ".cln")) {
                    OutputName = dup_text(arg);
                    ObjectRequested = 1;
                } else {
                    add_cli_option(arg);
                }
            } else {
                usage();
            }
            break;
        case 'd':
            arg = token + 2;
            if (*arg == '\0') {
                if (i + 1 >= expanded_count)
                    missing_option_argument('d');
                arg = expanded[++i];
            }
            if (i + 1 >= expanded_count)
                missing_option_argument('d');
            add_define(arg, expanded[++i]);
            break;
        case 'e':
            arg = token + 2;
            if (*arg == 'a' || *arg == 'w') {
                error_append = *arg == 'a';
                if (i + 1 >= expanded_count)
                    usage();
                error_name = expanded[++i];
            } else {
                illegal_option('E', (char *)0);
            }
            break;
        case 'i':
        case 'm':
            if (option == 'i') {
                arg = token + 2;
                if (*arg == '\0' && i + 1 < expanded_count &&
                    expanded[i + 1][0] != '-')
                    arg = expanded[++i];
                if (*arg != '\0')
                    IncludePath = dup_text(arg);
            } else if (token[2] == '\0' && i + 1 < expanded_count &&
                       expanded[i + 1][0] != '-')
                ++i;
            if (option == 'm') {
                arg = token + 2;
                if (*arg == '\0' && i + 1 < expanded_count &&
                    expanded[i + 1][0] != '-')
                    arg = expanded[++i];
                if (*arg != '\0')
                    MacroPathOption = dup_text(arg);
            }
            break;
        case 'p':
            arg = token + 2;
            if (*arg == '\0' && i + 1 < expanded_count &&
                expanded[i + 1][0] != '-')
                arg = expanded[++i];
            if (strcmp(arg, "56000") == 0 || strcmp(arg, "56001") == 0)
                CpuVariant = 0UL;
            else if (strcmp(arg, "56004") == 0)
                CpuVariant = 3UL;
            else if (strcmp(arg, "56007") == 0)
                CpuVariant = 4UL;
            else if (strcmp(arg, "56002") == 0 || *arg == '\0')
                CpuVariant = 2UL;
            else
                illegal_option('P', arg);
            break;
        case 'r':
            arg = token + 2;
            if (token[2] == '\0' && i + 1 < expanded_count &&
                expanded[i + 1][0] != '-')
                arg = expanded[++i];
            if (strcmp(arg, "2") != 0 && strcmp(arg, "4") != 0 &&
                strcmp(arg, "7") != 0)
                illegal_option('R', arg);
            break;
        case 'q':
            QuietOption = 1;
            break;
        case 'c':
        case 'j':
        case 's':
        case 't':
            break;
        case 'g':
            GenerateDebugOption = 1;
            break;
        case 'v':
            VerboseOption = 1;
            break;
        case 'z':
            NoSymbolsOption = 1;
            break;
        default:
            usage();
        }
    }
    if (SourceCount == 0) {
        printf("ASM56000: Cannot open source file\n");
        return -1;
    }
    if (error_name != (char *)0) {
        ErrorFile = fopen(error_name, error_append ? "ab" : "wb");
        if (ErrorFile == (FILE *)0) {
            fprintf(stderr, "asm56000: cannot open error file %s\n", error_name);
            return 2;
        }
    }
    if (!QuietOption) {
        if (ErrorFile != (FILE *)0) {
            fputs("Motorola DSP56000 Assembler  Version 6.3.0 \r\n"
                  "Copyright Motorola, Inc. 1987-1998.  All rights reserved.\r\n",
                  ErrorFile);
        } else {
            fprintf(stderr, "Motorola DSP56000 Assembler  Version 6.3.0 \n"
                    "Copyright Motorola, Inc. 1987-1998.  All rights reserved.\n");
        }
    }
    only_sources = !ObjectRequested && !ListingRequested &&
                   OutputName == (char *)0;
    if (only_sources)
        ObjectRequested = 1;
    if (ObjectRequested && OutputName == (char *)0)
        OutputName = default_output(SourceName);
    if (ListingRequested && ListingName == (char *)0)
        ListingName = default_listing(SourceName);
    if (ListingRequested) {
        Listing = fopen(ListingName, "wb");
        if (Listing == (FILE *)0) {
            fprintf(stderr, "asm56000: cannot open listing %s\n", ListingName);
            return 2;
        }
        LstFilePtr = Listing;
        ListingOpen = 1;
    } else if (AbsoluteMode || ObjectRequested) {
        Listing = stdout;
        ListingIsStdout = 1;
        LstFilePtr = Listing;
        ListingOpen = 1;
    }
    CurFileName = SourceName;
    ErrFilePtr = stdout;
    ObjFileName = OutputName;
    symtab_init();
    sec_init();
    macro_init();
    if (MacroPathOption != (char *)0)
        macro_set_path(MacroPathOption);
    Pass = 0UL;
    for (j = 0; j < CliOptionCount; ++j) {
        if (!apply_cli_option(CliOptions[j]))
            illegal_option('O', CliOptions[j]);
    }
    apply_defines();
    asm56000_set_emit_callback(record_word);
    RegNoteHook = insert_rp_nop;
    VectorCheckHook = vector_check;
    asm_section_state_reset();
    /* The legacy command-line driver uses the first source for the module. */
    for (i = 0; i < SourceCount && i == 0; ++i) {
        if (VerboseOption && i == 0)
            verbose_source_scan(SourceNames[i], "pre pass");
        if (run_pass(SourceNames[i], 1UL) < 1)
            return -1;
    }
    ListingSavedWidth = ListingWidth;
    ListingSavedPageLength = ListingPageLength;
    ListingSavedIndent = ListingIndent;
    if (Listing != (FILE *)0)
        listing_begin_pass2();
    RecordCount = 0UL;
    SegmentCount = 0UL;
    output_event_reset();
    asm_section_state_reset();
    memset(SpaceUsed, 0, sizeof(SpaceUsed));
    memset(SpaceMin, 0, sizeof(SpaceMin));
    memset(SpaceMax, 0, sizeof(SpaceMax));
    for (i = 0; i < SourceCount && i == 0; ++i) {
        if (run_pass(SourceNames[i], 2UL) < 1)
            return -1;
    }
    if (ObjectRequested && ErrorCount == 0UL && !write_coff(OutputName)) {
        fprintf(stderr, "asm56000: cannot write %s\n", OutputName);
        return 1;
    }
    if (Listing != (FILE *)0)
        list_summary();
    if (Listing != (FILE *)0 && ListingReportCrossRef)
        listing_report_crossref();
    if (Listing != (FILE *)0 && ListingReportMemory)
        listing_report_memory();
    if (Listing != (FILE *)0 && ListingReportSymbols &&
        !ListingReportCrossRef && !ListingReportMemory)
        listing_report_symbols();
    if (Listing != (FILE *)0 && !ListingIsStdout)
        fclose(Listing);
    if (ErrorFile != (FILE *)0)
        fclose(ErrorFile);
    free(Records);
    free(RawSegments);
    return ErrorCount == 0UL ? 0 : (int)ErrorCount;
}
