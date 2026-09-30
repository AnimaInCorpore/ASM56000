/*
 * Public interfaces shared by the reconstructed ASM56000 modules.
 *
 * The original assembler keeps INSN and OPERAND as packed 32-bit records.
 * They are deliberately opaque here: the accessors below document the
 * recovered offsets without making the host pointer size part of the file
 * format or the target ABI.
 */
#ifndef ASM56000_H
#define ASM56000_H

#include <stdio.h>

#ifndef __cdecl
# define __cdecl
#endif

#define ASM56000_INSN_NWORDS 0x00
#define ASM56000_INSN_WORD0  0x04
#define ASM56000_INSN_WORD1  0x08
#define ASM56000_INSN_CFORM0 0x40
#define ASM56000_INSN_CFORM1 0x48

#define ASM56000_OP_MODE   0x00
#define ASM56000_OP_SPACE  0x04
#define ASM56000_OP_FWD    0x08
#define ASM56000_OP_FORCE  0x0c
#define ASM56000_OP_VALUE  0x10
#define ASM56000_OP_REG    0x14
#define ASM56000_OP_SECT   0x18
#define ASM56000_OP_CFORM  0x20

#define ASM56000_INPUT_LINE_CAP 512

extern void fatal(char *msg);
extern void warning(char *msg);
extern void warn(char *msg);
extern void err(char *msg);
extern void err_s(char *msg, char *arg);
extern FILE *ErrFilePtr;
extern FILE *LstFilePtr;
extern char *ObjFileName;
extern char *CurInstrFieldMsg;
extern unsigned long LineTotal;
extern char LineBuf[512];
extern unsigned long ErrorCount;
extern unsigned long WarningCount;
extern char ListingOpen;

/* Recovered expression-value word offsets (the evaluator's 0x5c-byte value). */
#define ASM56000_EXPR_W0  0x00
#define ASM56000_EXPR_W1  0x04
#define ASM56000_EXPR_W2  0x08
#define ASM56000_EXPR_W4  0x10
#define ASM56000_EXPR_W5  0x14
#define ASM56000_EXPR_W6  0x18
#define ASM56000_EXPR_W7  0x1c
#define ASM56000_EXPR_W8  0x20
#define ASM56000_EXPR_W9  0x24
#define ASM56000_EXPR_W10 0x28
#define ASM56000_EXPR_W11 0x2c
#define ASM56000_EXPR_W12 0x30
#define ASM56000_EXPR_W13 0x34
#define ASM56000_EXPR_W14 0x38
#define ASM56000_EXPR_W15 0x3c
#define ASM56000_EXPR_W16 0x40
#define ASM56000_EXPR_W17 0x44
#define ASM56000_EXPR_W18 0x48
#define ASM56000_EXPR_W19 0x4c
#define ASM56000_EXPR_W20 0x50
#define ASM56000_EXPR_W21 0x54
#define ASM56000_EXPR_W22 0x58

extern void *xmalloc(unsigned long size);
extern void *xrealloc(void *p, unsigned long size);
extern void xfree(void *p);

extern unsigned long insert_bits(unsigned long word, unsigned long val,
                                  int pos, int width);
extern char *insert_bits_expr(char *word, char *val, int pos, int width);
extern void encode_field(void *code, void *op, int pos, int width);
extern void encode_field2(void *code, void *op,
                          unsigned long mask1, int shift1, int pos1,
                          int width1, unsigned long mask2, int shift2,
                          int pos2, int width2);
extern unsigned long insert_bits2(unsigned long word, unsigned long val,
                                   unsigned long mask1, int shift1, int pos1,
                                   int width1, unsigned long mask2, int shift2,
                                   int pos2, int width2);
extern char *insert_bits2_expr(char *word, char *val,
                               unsigned long mask1, int shift1, int pos1,
                               int width1, unsigned long mask2, int shift2,
                               int pos2, int width2);

extern void set_ext_word(void *insn, void *op, int minus1);
extern void enc_pm_ry(void *insn, void *s1, void *d1, void *yreg,
                      void *ymem);

extern int d_code(int reg);
extern int ee_code(int reg);
extern int jjj_code(int reg);
extern int rrr_code(int mode, int reg);
extern int mmm_code(int mode);
extern int s_code(int space);
extern int d6_code(int reg);
extern int ddddd_code(int reg);
extern int dd_code(int reg);
extern int ddd_code(int reg);
extern int fff_code(int reg);
extern int nnn_code(int reg);
extern int ccc_code(int reg);
extern int xx_code(int reg);
extern int yy_code(int reg);
extern int x_code(int reg);
extern int y_code(int reg);
extern int lll_code(int reg);
extern int qq_code(int reg);

extern void enc_andi(void *insn, void *imm, void *dst);
extern void enc_div(void *insn, void *src, void *dst);
extern void enc_norm(void *insn, void *src, void *dst);
extern void enc_loop_ea(void *insn, void *op);
extern void enc_loop_abs(void *insn, void *op);
extern void enc_loop_reg(void *insn, void *op);
extern void enc_loop_imm(void *insn, void *op);
extern void enc_do_ea(void *insn, void *op, void *target);
extern void enc_do_abs(void *insn, void *op, void *target);
extern void enc_do_reg(void *insn, void *op, void *target);
extern void enc_do_imm(void *insn, void *op, void *target);
extern void enc_jmp_abs(void *insn, void *op);
extern void enc_jmp_ea(void *insn, void *op);
extern void enc_jcc_abs(void *insn, void *op);
extern void enc_jcc_ea(void *insn, void *op);
extern void enc_tcc(void *insn, void *src, void *dst);
extern void enc_tcc_r(void *insn, void *s1, void *d1, void *s2, void *d2);
extern void enc_bit_ea(void *insn, void *bitno, void *op);
extern void enc_bit_reg(void *insn, void *bitno, void *op);
extern void enc_bit_abs(void *insn, void *bitno, void *op);
extern void enc_bit_pp(void *insn, void *bitno, void *op);
extern void enc_jbit_ea(void *insn, void *bitno, void *op, void *target);
extern void enc_jbit_reg(void *insn, void *bitno, void *op, void *target);
extern void enc_jbit_abs(void *insn, void *bitno, void *op, void *target);
extern void enc_jbit_pp(void *insn, void *bitno, void *op, void *target);
extern void enc_movep_reg(void *insn, void *pp, void *reg);
extern void enc_movep_mem(void *insn, void *pp, void *mem);
extern void enc_movep_reg_w(void *insn, void *reg, void *pp);
extern void enc_movep_mem_w(void *insn, void *mem, void *pp);
extern void enc_movec_ea(void *insn, void *creg, void *mem);
extern void enc_movec_ea_w(void *insn, void *mem, void *creg);
extern void enc_movec_imm(void *insn, void *imm, void *creg);
extern void enc_movec_reg(void *insn, void *creg, void *reg);
extern void enc_movec_reg_w(void *insn, void *reg, void *creg);
extern void enc_movec_abs(void *insn, void *creg, void *abs);
extern void enc_movec_abs_w(void *insn, void *abs, void *creg);
extern void enc_movec_ea2(void *insn, void *creg, void *mem);
extern void enc_movec_ea2_w(void *insn, void *mem, void *creg);
extern void enc_pm_xy(void *insn, void *xreg, void *xmem,
                      void *yreg, void *ymem);
extern void enc_pm_xy_wx(void *insn, void *xmem, void *xreg,
                         void *yreg, void *ymem);
extern void enc_pm_xy_wy(void *insn, void *xreg, void *xmem,
                         void *ymem, void *yreg);
extern void enc_pm_xy_wxy(void *insn, void *xmem, void *xreg,
                          void *ymem, void *yreg);
extern void enc_pm_xr2(void *insn, void *acc, void *mem);
extern void enc_pm_x_ea(void *insn, void *reg, void *mem);
extern void enc_pm_x_ea_w(void *insn, void *mem, void *reg);
extern void enc_pm_y_ea(void *insn, void *reg, void *mem);
extern void enc_pm_y_ea_w(void *insn, void *mem, void *reg);
extern void enc_pm_x_abs(void *insn, void *reg, void *abs);
extern void enc_pm_x_abs_w(void *insn, void *abs, void *reg);
extern void enc_pm_y_abs(void *insn, void *reg, void *abs);
extern void enc_pm_y_abs_w(void *insn, void *abs, void *reg);
extern void enc_pm_ry_w(void *insn, void *s1, void *d1,
                        void *ymem, void *yreg);
extern void enc_pm_xr(void *insn, void *xreg, void *xmem,
                      void *s2, void *d2);
extern void enc_pm_xr_w(void *insn, void *xmem, void *xreg,
                        void *s2, void *d2);
extern void enc_pm_l_abs(void *insn, void *reg, void *abs);
extern void enc_pm_l_abs_w(void *insn, void *abs, void *reg);
extern void enc_pm_l_ea(void *insn, void *reg, void *mem);
extern void enc_pm_l_ea_w(void *insn, void *mem, void *reg);
extern void enc_pm_imm(void *insn, void *imm, void *dst);
extern void enc_pm_reg(void *insn, void *src, void *dst);
extern void enc_pm_update(void *insn, void *op);
extern void enc_movem_ea(void *insn, void *reg, void *mem);
extern void enc_movem_ea_w(void *insn, void *mem, void *reg);
extern void enc_movem_abs(void *insn, void *reg, void *abs);
extern void enc_movem_abs_w(void *insn, void *abs, void *reg);
extern void enc_lua(void *insn, void *mem, void *dst);
extern void enc_mul_imm(void *insn, void *s1, void *imm, void *dst);

extern double mth_atan(double x);
extern double mth_abs(double x);
extern double mth_acos(double x);
extern double mth_asin(double x);
extern double mth_ceil(double x);
extern double mth_cosh(double x);
extern double mth_cos(double x);
extern double mth_floor(double x);
extern double mth_log10(double x);
extern double mth_log(double x);
extern double mth_sin(double x);
extern double mth_sinh(double x);
extern double mth_sqrt(double x);
extern double mth_tan(double x);
extern double mth_tanh(double x);
extern double mth_exp(double x);
extern double mth_pow(double x, double y);
extern double mth_atan2(double y, double x);

/* Recovered source-input globals used by the low-level input slice. */
extern FILE *CurSrcFp;
extern char *CurFileName;
extern void *MacroStateStack;
extern void *InputModeStack;
extern char RawLineBuf[ASM56000_INPUT_LINE_CAP];
extern unsigned long TabWidth;
extern unsigned long LineNo;
extern unsigned long LineNoBase;
extern unsigned long OpenFileCount;
extern unsigned long CurrentAddress;
extern unsigned long Pass;
extern char OptT;
extern char OptIC;
extern char OptXR;
extern char OptUR;
extern char OptSi;
extern char OptCm;
extern char OptMd;
extern char OptMex;
extern int ListingReportCrossRef;
extern int ListingReportMemory;
extern int ListingReportLocals;
extern int ListingReportSymbols;
extern int SectionGlobalCounters;
extern int ListingSeparateComments;
extern int SourceCexDirective;
extern int SourceOptCex;
extern unsigned long AsmEquCount;
extern unsigned long ForceMode;
extern int AbsoluteMode;
extern char OptWarn;
extern void *CurrentSection;
extern char NoMoreInput;
extern char PendingLine;
extern char *LabelField;
extern char *MnemField;
extern char *Op1Field;
extern char *Op2Field;
extern char *Op3Field;
extern char *Op4Field;

extern unsigned long input_getc(void);
extern unsigned long read_line(void);
extern unsigned long get_line(void);
extern int input_push_file(char *path);
extern void input_push_lines(char **lines, int count);
extern void input_skip_macro_lines(void);
extern void input_clear_macro_lines(void);
extern unsigned long input_pop(void);
extern unsigned long chk_line_end(void);
extern unsigned long parse_line(void);
extern void process_file(void);
extern unsigned long proc_line1(void);
extern unsigned long proc_line2(int pass2, int emit);
extern int pseudo_dispatch(char *name);
extern void macro_init(void);
extern void macro_begin(char *name, char *params);
extern int macro_definition_rejected(void);
extern int macro_parameter_error(void);
extern int macro_is_defined(char *name);
extern void macro_add_line(char *line);
extern void macro_end(void);
extern int macro_expand(char *name, char *args);
extern unsigned long macro_eval_builtin(char *text, int *handled);
extern void macro_purge(char *text);
extern unsigned long macro_report_count(void);
extern int macro_report_info(unsigned long index, char *name,
                             unsigned long size, unsigned long *line);
extern void macro_set_path(char *path);
extern unsigned long *subst_symbol(unsigned long *tok, unsigned long *dst,
                                   int context);
extern void mstate_push(unsigned long value);
extern unsigned long mstate_pop(void);
extern char *scan_token(char *p);

/* Shared symbol/static-table helpers recovered from util.c and symtab.c. */
extern char *str_dupcat(char *s, ...);
extern void *tab_search(void *key, void *base, int count, int size,
                        int (*cmp)(void *, void *));
extern void *tab_search_pos(void *key, void *base, int count, int size,
                            int (*cmp)(void *, void *));
extern unsigned long hash_name(char *s);
extern char *base_name(char *path);
extern char *str_lower_copy(char *s);
extern char *str_upper(char *s);
extern char *str_lower(char *s);
extern char *str_upper_copy(char *s);

/* Symbol-table and external-reference entry points. */
extern void symtab_init(void);
extern int sym_define(char *name, void *value);
extern int sym_undef(char *name);
extern int sym_set_value(void *sym, void *value);
extern void *sym_lookup(char *name, int reftype);
extern void sym_note_unresolved(char *name);
extern int sym_is_sectioned_name(char *name);
extern int sym_duplicate_name(char *name);
extern unsigned long sym_definition_line(char *name);
extern void *sym_lookup_local(char *name, int reftype);
extern void *sym_search(char *name, int reftype, int is_local);
extern void sym_add_ref(void *sym, int reftype);
extern void sym_new_local_block(void *sym);
extern int ext_add(char *name, int force);
extern void *ext_lookup(char *name);
extern void *strtab_lookup(char *name);
extern void sym_free_all(void);
extern void sym_free_local_blocks(void);
extern void ext_free_all(void);
extern void sec_init(void);
extern void asm_section_state_reset(void);
extern int asm_section_enter(char *name, char *mod1, char *mod2);
extern int asm_section_leave(void);
extern int sec_section(char *name, char *mod1, char *mod2);
extern int sec_endsec(void);
extern int sec_is_static_section(void *section);
extern void *sec_global_section(void);
extern unsigned long sec_number(void *section);
extern unsigned long sec_defined_count(void);
extern int sec_has_xdef(void *section, char *name);
extern int sym_object_xdef(unsigned long index);
extern unsigned long sec_counter_number(void *section);
extern unsigned long sec_depth(void);
extern void *sec_new(char *name);
extern int sec_push(void *section);
extern void sec_set_current(void *section, int is_new);
extern void sec_save_counters(void);
extern void sec_free_all(void);
extern int sec_local(void);
extern int sec_global(void);
extern int sec_xref(void);
extern int sec_xdef(void);
extern int sec_is_local(char *name);
extern int sec_is_global(char *name);
extern int sec_is_xref(char *name);
extern int sec_is_xdef(char *name);
extern unsigned long sec_xref_count(char *name);
extern int sec_xref_info(char *name, unsigned long index, char *out,
                         unsigned long size);
extern int sec_current_is_global(void);
extern int sec_current_section_global(void);
extern char *sec_current_name(void);
extern int sec_check_local(char *name);
extern int sec_check_global(char *name);
extern int sec_check_xref(char *name);
extern int sec_check_xdef(char *name);
extern void sec_free_names(void);
extern void sec_debug_sym(void *section, int begin);
extern void listing_prepare_diagnostic(void);
extern void listing_library_line(char *text, unsigned long line_no, int marked);
extern unsigned long sym_value(void *sym);
extern unsigned long sym_flags(void *sym);
extern char *sym_name(void *sym);
extern unsigned long sym_count(void);
extern unsigned long sym_public_count(void);
extern void sym_hide_name(char *name);
extern int sym_public_info(unsigned long index, char *name, unsigned long size,
                           unsigned long *value, unsigned long *space,
                           unsigned long *coff_scn);
extern unsigned long sym_object_count(void);
extern int sym_object_info(unsigned long index, char *name, unsigned long size,
                           unsigned long *value, unsigned long *space,
                           unsigned long *coff_scn, unsigned long *flags,
                           unsigned long *word0, unsigned long *word1,
                           unsigned long *word2, int *sectioned, int *global);
extern void sym_object_set(unsigned long old_seq, unsigned long scn,
                           unsigned long new_seq);
extern int sym_object_order(unsigned long index, unsigned long *seq,
                            unsigned long *scn);
extern int sym_object_definition_line(unsigned long index,
                                      unsigned long *line);
extern int sym_object_references(unsigned long index, unsigned long *lines,
                                 int *definitions,
                                 unsigned long max_lines,
                                 unsigned long *count);
extern int sym_public_details(unsigned long index, char *name,
                              unsigned long size, unsigned long *value,
                              unsigned long *space, unsigned long *coff_scn,
                              unsigned long *flags, unsigned long *word0,
                              unsigned long *word1, unsigned long *word2,
                              int *sectioned, int *global);
extern void sym_first_info(char *name, unsigned long size,
                           unsigned long *value);
extern void sym_copy_value(void *sym, void *value);

extern void *find_mnemonic(char *name, int chk_macro);
extern void *find_directive(char *name, int chk_macro);
extern void *find_option(char *name);
extern void *find_revision(char *name);
extern void *find_processor(char *name);
extern void *find_scs_directive(char *name);
extern void *find_debug_directive(char *name);
extern void *find_condition(char *name);
extern int mnemonic_cmp(char *key, void *entry);
extern int directive_cmp(char *key, void *entry);
extern int option_cmp(char *key, void *entry);
extern int revision_cmp(char *key, void *entry);
extern int processor_cmp(char *key, void *entry);
extern int condition_cmp(char *key, void *entry);
extern unsigned long table_entry_id(void *entry);

/* Portable expression entry points used by the recovered pass code. */
extern void *new_expr_value(void);
extern void free_expr(void *value);
extern void *eval_expr_text(char *text);
extern unsigned long expr_as_int32(void *value);
extern double expr_as_double(void *value);
extern int expr_is_unresolved(void *value);
extern char *expr_unresolved_name(char *text);
extern int expr_last_error(void);
extern int expr_is_reloc(void *value);
extern char *eval_reloc_text(void);
extern char *eval_last_text(void);
/* Location-counter state seen by the expression evaluator ("*"). */
extern int EvalCounterReloc;
extern unsigned long EvalCounterSpace;
extern unsigned long EvalCounterMap;
extern unsigned long EvalCounterIndex;
extern unsigned long EvalSection;
extern unsigned long EvalCounterSection;
/* Object-file event sequence (dspasm.c) */
extern unsigned long ObjSeq;
extern unsigned long ObjCurrentScn;
extern void obj_note_extern(char *name);
extern void obj_symbol_defined(unsigned long seq, unsigned long flags,
                               unsigned long space, int global);
extern int match_register_name(char **p);
extern unsigned long check_field_size(unsigned long value, int width_code);
extern int asm56000_parse_operand_text(char *text, unsigned long flags,
                                       void *op, int regclass, int eaclass,
                                       int absclass, int immclass);
extern int parse_operand(unsigned long flags, void *op, int regclass,
                         int eaclass, int absclass, int immclass);
extern int get_amode(unsigned long flags, void *op, int regclass,
                     int eaclass, int absclass, int immclass);
extern int amode_register(int regclass, void *op);
extern int amode_indirect(int eaclass, void *op);
extern int amode_immediate(int immclass, void *op);
extern int amode_absolute(int absclass, void *op);
extern void *get_imm_expr(int immclass);
extern int parse_addr_reg(void);
extern int parse_offset_reg(int areg);
extern void set_opt_rp(int on);
extern int get_opt_rp(void);
extern long get_date_time(char *date, char *time);
extern int set_file_type(char *fname, char *type, char *creator);
extern void free_str_list(void *list);

/* amode.c helpers shared with procop.c / procxy.c */
extern unsigned long get_force(unsigned long allowed);
extern unsigned long merge_mem_space(unsigned long a, unsigned long b);
extern int get_mem_space(void *op, int allowed);
extern int check_extra_operand(void);
extern void skip_symbol(void);
extern int parse_xfield_src(void *op);
extern char *register_name(int id);
extern void check_areg_stall(int reg, int mode);
extern int CModeFlag;
extern int OptMsw;
extern int OptPsb;
extern int InsertingNop;
extern unsigned long RtAddrMask;
extern unsigned long HazardCur;
extern unsigned long HazardPrev;
extern unsigned long DestRegMask;
extern unsigned long AregWritten;
extern unsigned long AregWrittenPrev;
extern long LastSrcReg;
extern unsigned long AregWritePc;
extern int CtrlRegAccessed;
extern long PrevInstrWords;
extern void (*RegNoteHook)(void);
extern int (*VectorCheckHook)(void);
extern unsigned long CpuVariant;
extern int CurrentSpace;
extern int ErrMultiple;
extern char EmptyFieldText[];
extern int do_xy(void *insn, unsigned long pm, void *xs, void *xd,
                 void *ys, void *yd);
extern int pseudo_check_move_class(int reg);
extern int pseudo_check_move_mask(unsigned long pm, unsigned long mask,
                                  void *insn);
extern int do_check_end_range_err(int n);

/* Instruction-pass interface.  The emitter is optional; without one the
 * most recent encoded words remain available through the accessors. */
extern int proc_instr(void *ientry);
extern int proc_instr_name(char *name);
extern char *asm56000_emit_reloc(void);
extern void asm56000_set_emit_callback(void (*callback)(unsigned long word,
                                                        int index));
extern unsigned long asm56000_last_word(int index);
extern int asm56000_last_count(void);
extern void asm56000_set_last_word(int index, unsigned long word);

#endif
