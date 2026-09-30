/* Recovered sorted lookup tables from mchglb/asmglb. */
#include <string.h>

#include "asm56000.h"

struct name_id {
    char *name;
    unsigned long id;
};

static struct name_id InstrTab[] = {
    {"abs",0},{"adc",1},{"add",2},{"addl",3},{"addr",4},
    {"and",5},{"andi",6},{"asl",7},{"asr",8},{"bchg",9},
    {"bclr",10},{"bset",11},{"btst",12},{"clr",13},{"cmp",14},
    {"cmpm",15},{"debug",16},{"debuga",17},{"debugal",18},
    {"debugcc",19},{"debugcs",20},{"debugec",21},{"debugeq",22},
    {"debuges",23},{"debugge",24},{"debuggt",25},{"debughs",26},
    {"debuglc",27},{"debugle",28},{"debuglo",29},{"debugls",30},
    {"debuglt",31},{"debugmi",32},{"debugne",33},{"debugneq",34},
    {"debugnn",35},{"debugnr",36},{"debugpl",37},{"dec",38},
    {"div",39},{"do",40},{"enddo",41},{"eor",42},{"illegal",43},
    {"inc",44},{"jcc",45},{"jclr",46},{"jcs",47},{"jec",48},
    {"jeq",49},{"jes",50},{"jge",51},{"jgt",52},{"jhs",53},
    {"jlc",54},{"jle",55},{"jlo",56},{"jls",57},{"jlt",58},
    {"jmi",59},{"jmp",60},{"jne",61},{"jneq",62},{"jnn",63},
    {"jnr",64},{"jpl",65},{"jscc",66},{"jsclr",67},{"jscs",68},
    {"jsec",69},{"jseq",70},{"jses",71},{"jset",72},{"jsge",73},
    {"jsgt",74},{"jshs",75},{"jslc",76},{"jsle",77},{"jslo",78},
    {"jsls",79},{"jslt",80},{"jsmi",81},{"jsne",82},{"jsneq",83},
    {"jsnn",84},{"jsnr",85},{"jspl",86},{"jsr",87},{"jsset",88},
    {"lea",89},{"lsl",90},{"lsr",91},{"lua",92},{"mac",93},
    {"macr",94},{"move",95},{"movec",96},{"movem",97},{"movep",98},
    {"mpy",99},{"mpyr",100},{"neg",101},{"nop",102},{"norm",103},
    {"not",104},{"or",105},{"ori",106},{"rep",107},{"reset",108},
    {"rnd",109},{"rol",110},{"ror",111},{"rti",112},{"rts",113},
    {"sbc",114},{"stop",115},{"sub",116},{"subl",117},{"subr",118},
    {"swi",119},{"tcc",120},{"tcs",121},{"tec",122},{"teq",123},
    {"tes",124},{"tfr",125},{"tge",126},{"tgt",127},{"ths",128},
    {"tlc",129},{"tle",130},{"tlo",131},{"tls",132},{"tlt",133},
    {"tmi",134},{"tne",135},{"tneq",136},{"tnn",137},{"tnr",138},
    {"tpl",139},{"tst",140},{"wait",141}
};

static struct name_id PseudoTab[] = {
    {"=",0x132},{"align",1},{"baddr",2},{"baddrr",0x48},
    {"bsb",0x103},{"bsc",0x104},{"bscb",0x143},{"bscl",0x145},
    {"bscw",0x144},{"bsm",0x105},{"bsmr",0x146},{"bsr",0x103},
    {"buffer",6},{"cobj",7},{"comment",8},{"dc",0x209},
    {"dcb",0x23b},{"dcl",0x142},{"dcw",0x141},{"define",0x10a},
    {"ds",0x10d},{"dsb",0x10c},{"dsm",0x10b},{"dsmr",0x147},
    {"dsr",0x10c},{"dup",0x20e},{"dupa",0x20f},{"dupc",0x210},
    {"dupf",0x211},{"else",0x12},{"end",0x13},{"endbuf",0x14},
    {"endif",0x15},{"endm",0x16},{"endsec",0x17},{"equ",0x118},
    {"exitm",0x19},{"fail",0x1a},{"force",0x3c},{"global",0x1b},
    {"gset",0x140},{"himem",0x1c},{"ident",0x11d},{"if",0x1e},
    {"include",0x1f},{"list",0x21},{"local",0x20},{"lomem",0x22},
    {"lstcol",0x23},{"maclib",0x24},{"macro",0x125},{"mode",0x26},
    {"msg",0x27},{"nolist",0x28},{"opt",0x29},{"org",0x2a},
    {"page",0x2b},{"pmacro",0x2c},{"prctl",0x2d},{"proc",0x3f},
    {"radix",0x2e},{"rdirect",0x2f},{"rev",0x30},{"scsjmp",0x3d},
    {"scsreg",0x3e},{"section",0x131},{"set",0x132},{"stitle",0x33},
    {"symobj",0x34},{"tabs",0x35},{"title",0x36},{"undef",0x37},
    {"warn",0x38},{"xdef",0x39},{"xref",0x3a}
};

static struct name_id OptTab[] = {
    {"ae",0x4a},{"aec",0x70},{"al",0x66},{"cc",1},{"cex",6},
    {"ck",0x43},{"cl",2},{"cm",3},{"const",0x48},{"contc",4},
    {"contck",0x45},{"cre",5},{"dex",0x2b},{"dld",0x5a},{"dxl",0x4f},
    {"fc",0x16},{"ff",0x58},{"fm",0x46},{"gl",0x4d},{"gs",0x2f},
    {"hdr",0x51},{"ic",0x28},{"il",0x18},{"intr",0x1e},{"lb",0x29},
    {"lbx",0x2a},{"ldb",0x55},{"loc",0x1a},{"mc",7},{"md",8},
    {"mex",9},{"mi",0x22},{"msw",0x2d},{"mu",0x19},{"nde",0x5c},
    {"nl",0x31},{"noae",0x4b},{"noaec",0x71},{"noal",0x67},
    {"nocc",0xa},{"nocex",0xd},{"nock",0x44},{"nocl",0xb},
    {"nocm",0xc},{"noconst",0x49},{"nodex",0x2c},{"nodld",0x5b},
    {"nodxl",0x50},{"nofc",0x17},{"noff",0x59},{"nofm",0x47},
    {"nogs",0x30},{"nohdr",0x52},{"nointr",0x1f},{"nomc",0xe},
    {"nomd",0xf},{"nomex",0x10},{"nomi",0x23},{"nomsw",0x2e},
    {"nonde",0x5d},{"nonl",0x32},{"nons",0x34},{"nopp",0x36},
    {"nops",0x25},{"nopsb",0x63},{"norc",0x1d},{"norp",0x3a},
    {"noscl",0x40},{"nosi",0x3c},{"nosms",0x6b},{"nou",0x11},
    {"nour",0x42},{"now",0x12},{"ns",0x33},{"pp",0x35},{"ps",0x24},
    {"psb",0x62},{"rc",0x1c},{"rp",0x39},{"s",0x13},{"scl",0x3f},
    {"sco",0x54},{"si",0x3b},{"sms",0x6a},{"so",0x1b},{"svo",0x53},
    {"u",0x14},{"ur",0x41},{"w",0x15},{"wex",0x4c},{"xll",0x4e},
    {"xr",0x20}
};

static struct name_id RevTab[] = {
    {"2",2},{"4",3},{"7",4},{"c",1}
};

static struct name_id ProcTab[] = {
    {"56000",0},{"56001",0},{"56001c",1},{"56002",2},
    {"56004",3},{"56007",4},{"68356",0x2000}
};

static struct name_id CondTab[] = {
    {"",0},{"cc",0x201},{"cs",0x102},{"ec",0x503},
    {"eq",0xf04},{"es",0x305},{"ge",0xd06},{"gt",0xa07},
    {"hs",0xb08},{"lc",0xc09},{"le",0x70a},{"lo",0x80b},
    {"ls",0x90c},{"lt",0x60d},{"mi",0x120e},{"ne",0x40f},
    {"nn",0x1110},{"nr",0x1011},{"pl",0xe12}
};

static struct name_id ScsTab[] = {
    {"break",1},{"continue",13},{"else",2},{"endf",3},
    {"endi",4},{"endl",5},{"endw",6},{"for",7},{"if",8},
    {"loop",9},{"repeat",10},{"until",11},{"while",12}
};

static struct name_id DebugTab[] = {
    {"bb",13},{"bf",11},{"def",3},{"dim",10},{"eb",14},{"ef",12},
    {"enddef",4},{"endef",4},{"file",1},{"line",2},{"ln",15},
    {"scl",6},{"size",9},{"tag",8},{"type",7},{"val",5}
};

unsigned long table_entry_id(void *entry)
{
    return entry == (void *)0 ? 0xffffffffUL :
        ((struct name_id *)entry)->id;
}

static int name_cmp(void *key_ptr, void *entry)
{
    return strcmp((char *)key_ptr, ((struct name_id *)entry)->name);
}

int mnemonic_cmp(char *key, void *entry) { return name_cmp((void *)key, entry); }
int directive_cmp(char *key, void *entry) { return name_cmp((void *)key, entry); }
int option_cmp(char *key, void *entry) { return name_cmp((void *)key, entry); }
int revision_cmp(char *key, void *entry) { return name_cmp((void *)key, entry); }
int processor_cmp(char *key, void *entry) { return name_cmp((void *)key, entry); }
int condition_cmp(char *key, void *entry) { return name_cmp((void *)key, entry); }

static void *lookup(char *name, struct name_id *table, int count,
                    int hidden_rev)
{
    char *key;
    struct name_id *entry;

    if (name == (char *)0)
        return (void *)0;
    if (name[0] == '.')
        ++name;
    key = str_lower_copy(name);
    entry = (struct name_id *)tab_search((void *)key, (void *)table, count,
                                         (int)sizeof(struct name_id), name_cmp);
    if (entry != (struct name_id *)0 && hidden_rev &&
        entry->id == 0x30UL && !OptT)
        return (void *)0;
    return (void *)entry;
}

void *find_mnemonic(char *name, int chk_macro)
{
    (void)chk_macro;
    return lookup(name, InstrTab, (int)(sizeof(InstrTab) /
                                        sizeof(InstrTab[0])), 0);
}

void *find_directive(char *name, int chk_macro)
{
    void *entry;

    (void)chk_macro;
    entry = lookup(name, PseudoTab, (int)(sizeof(PseudoTab) /
                                         sizeof(PseudoTab[0])), 1);
    if (entry == (void *)0)
        entry = lookup(name, ScsTab, (int)(sizeof(ScsTab) /
                                          sizeof(ScsTab[0])), 0);
    return entry;
}

void *find_option(char *name)
{
    return lookup(name, OptTab, (int)(sizeof(OptTab) / sizeof(OptTab[0])), 0);
}

void *find_revision(char *name)
{
    return lookup(name, RevTab, (int)(sizeof(RevTab) / sizeof(RevTab[0])), 0);
}

void *find_processor(char *name)
{
    return lookup(name, ProcTab, (int)(sizeof(ProcTab) / sizeof(ProcTab[0])), 0);
}

void *find_scs_directive(char *name)
{
    return lookup(name, ScsTab, (int)(sizeof(ScsTab) / sizeof(ScsTab[0])), 0);
}

void *find_debug_directive(char *name)
{
    return lookup(name, DebugTab, (int)(sizeof(DebugTab) / sizeof(DebugTab[0])), 0);
}

void *find_condition(char *name)
{
    return lookup(name, CondTab, (int)(sizeof(CondTab) / sizeof(CondTab[0])), 0);
}
