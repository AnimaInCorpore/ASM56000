/* Initial shared state for the reconstructed ASM56000 modules. */
#include <stdio.h>

#include "asm56000.h"

char *CurFileName = (char *)"<input>";
FILE *ErrFilePtr;
char *ObjFileName;
FILE *LstFilePtr;
char LineBuf[512];
char *CurInstrFieldMsg;
void *DoStack;

char *FieldNames[] = {
    (char *)"", (char *)"Label", (char *)"Opcode", (char *)"Operand",
    (char *)"X data move", (char *)"Y data move", (char *)"operand 4",
    (char *)"instruction"
};

unsigned long LineTotal;
unsigned long LineNo;
unsigned long ErrorCount;
unsigned long WarningCount;
unsigned long ErrOnThisLine;
int ErrMultiple;
unsigned long SuppressedErrors;
unsigned long Pass;

char NoErrors;
char InLineReplay;
char AbsModeShadow;
char ListingOpen;
char OptWarn = 1;
char OptT;
void *CurrentSection;
char OptIC;
char OptXR;
char OptUR;
char OptSi;
char OptCm;
char OptMd = 1;
char OptMex;
unsigned long AsmEquCount;
unsigned long ForceMode;

FILE *CurSrcFp;
char *CurFileNameShadow;
void *MacroStateStack;
void *InputModeStack;
char RawLineBuf[ASM56000_INPUT_LINE_CAP];
unsigned long TabWidth = 8UL;
char *LabelField;
char *MnemField;
char *Op1Field;
char *Op2Field;
char *Op3Field;
char *Op4Field;
unsigned long LineNoBase;
unsigned long OpenFileCount;
unsigned long CurrentAddress;
char NoMoreInput;
char PendingLine;

int EvalCounterReloc;
unsigned long EvalCounterSpace = 4UL;
unsigned long EvalCounterMap = 4UL;
unsigned long EvalCounterIndex;
unsigned long EvalSection;
unsigned long EvalCounterSection;
unsigned long ObjSeq;
unsigned long ObjCurrentScn;
