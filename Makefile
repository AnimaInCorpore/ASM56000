# Motorola DSP56000 CLAS56 tools, reconstructed C sources.
#
# Plain make + any ANSI C89 compiler.  Examples:
#   make                                   (host cc)
#   make CC=gcc CFLAGS="-O2 -std=c89 -pedantic -Wall" EXE=.exe
#   make CC=m68k-atari-mintelf-gcc EXE=.ttp

CC      = cc
CFLAGS  = -O
LDFLAGS =
LIBS    = -lm
EXE     =
B       = build

TOOLS   = $(B)/cldinfo$(EXE) $(B)/cldlod$(EXE) $(B)/cofdmp$(EXE) $(B)/dsplib$(EXE) $(B)/dsplnk$(EXE) $(B)/srec$(EXE) $(B)/strip$(EXE) $(B)/tiohist$(EXE)

all: $(B) $(TOOLS)

$(B):
	mkdir -p $(B)

$(B)/cldinfo$(EXE): src/cldinfo/cldinfo.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/cldinfo/cldinfo.c

$(B)/cldlod$(EXE): src/cldlod/cldlod.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/cldlod/cldlod.c $(LIBS)

$(B)/cofdmp$(EXE): src/cofdmp/cofdmp.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/cofdmp/cofdmp.c $(LIBS)

$(B)/dsplib$(EXE): src/dsplib/dsplib.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/dsplib/dsplib.c

$(B)/srec$(EXE): src/srec/srec.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/srec/srec.c

$(B)/strip$(EXE): src/strip/strip.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/strip/strip.c

$(B)/tiohist$(EXE): src/tiohist/tiohist.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/tiohist/tiohist.c

# DSPLNK (linker): many modules sharing src/dsplnk/dsplnk.h.  Not part of
# "all"; also buildable alone with "make dsplnk".
DSPLNK_SRC = src/dsplnk/dsplnk.c src/dsplnk/arith.c src/dsplnk/error.c             src/dsplnk/eval.c src/dsplnk/fixup.c src/dsplnk/func.c             src/dsplnk/input.c src/dsplnk/lib.c src/dsplnk/lnkglb.c             src/dsplnk/map.c src/dsplnk/memctl.c src/dsplnk/object.c             src/dsplnk/sdi.c src/dsplnk/symtab.c src/dsplnk/util.c src/dsplnk/abistub.c
DSPLNK_HDR = src/dsplnk/dsplnk.h

dsplnk: $(B) $(B)/dsplnk$(EXE)

$(B)/dsplnk$(EXE): $(DSPLNK_SRC) $(DSPLNK_HDR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(DSPLNK_SRC) $(LIBS)

# ASM56000 reconstruction.  The portable assembler driver is linked from the
# recovered modules below; the module target also keeps each translation unit
# independently checkable on both host and m68k toolchains.
ASM56000_MODULES = src/asm56000/error.c src/asm56000/util.c \
                   src/asm56000/encode.c src/asm56000/input.c \
                   src/asm56000/asmglb.c src/asm56000/globals.c \
                   src/asm56000/symtab.c src/asm56000/eval.c \
                   src/asm56000/tables.c src/asm56000/arith.c \
                   src/asm56000/section.c src/asm56000/pseudo.c \
                   src/asm56000/macro.c \
                   src/asm56000/amode.c src/asm56000/procop.c src/asm56000/procxy.c \
                   src/asm56000/listing.c

ASM56000_DRIVER = src/asm56000/dspasm.c

asm56000: $(B) $(B)/asm56000$(EXE)

$(B)/asm56000$(EXE): $(ASM56000_MODULES) $(ASM56000_DRIVER) \
                     src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -Wextra -Isrc/asm56000 \
	    -o $@ $(ASM56000_MODULES) $(ASM56000_DRIVER) $(LIBS)

asm56000-modules: $(B) $(B)/asm56000-error.o $(B)/asm56000-util.o \
                  $(B)/asm56000-encode.o $(B)/asm56000-input.o \
                  $(B)/asm56000-asmglb.o $(B)/asm56000-globals.o \
                  $(B)/asm56000-symtab.o $(B)/asm56000-eval.o \
                  $(B)/asm56000-tables.o $(B)/asm56000-arith.o \
                  $(B)/asm56000-section.o $(B)/asm56000-pseudo.o \
                  $(B)/asm56000-macro.o \
                  $(B)/asm56000-amode.o $(B)/asm56000-procop.o \
                  $(B)/asm56000-listing.o

$(B)/asm56000-error.o: src/asm56000/error.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-util.o: src/asm56000/util.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-encode.o: src/asm56000/encode.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-input.o: src/asm56000/input.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-asmglb.o: src/asm56000/asmglb.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-globals.o: src/asm56000/globals.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-symtab.o: src/asm56000/symtab.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-eval.o: src/asm56000/eval.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-tables.o: src/asm56000/tables.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-arith.o: src/asm56000/arith.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-section.o: src/asm56000/section.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-pseudo.o: src/asm56000/pseudo.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-macro.o: src/asm56000/macro.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-amode.o: src/asm56000/amode.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-procop.o: src/asm56000/procop.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

$(B)/asm56000-listing.o: src/asm56000/listing.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

asm56000-tests: $(B) $(B)/test-asm56000-primitives$(EXE) \
                $(B)/test-asm56000-expr$(EXE) \
                $(B)/test-asm56000-instr$(EXE)

$(B)/test-asm56000-primitives$(EXE): tests/asm56000/test_primitives.c \
                                      src/asm56000/util.c \
                                      src/asm56000/encode.c src/asm56000/input.c \
                                      src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -Isrc/asm56000 -o $@ \
	    tests/asm56000/test_primitives.c src/asm56000/util.c \
    src/asm56000/encode.c src/asm56000/input.c

$(B)/test-asm56000-expr$(EXE): tests/asm56000/test_expr.c \
                                src/asm56000/eval.c src/asm56000/symtab.c \
                                src/asm56000/util.c src/asm56000/globals.c \
                                src/asm56000/tables.c \
                                src/asm56000/arith.c \
                                src/asm56000/asmglb.c \
                                src/asm56000/section.c \
                                src/asm56000/pseudo.c \
                                src/asm56000/amode.c \
                                src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -Isrc/asm56000 -o $@ \
	    tests/asm56000/test_expr.c src/asm56000/eval.c \
    src/asm56000/symtab.c src/asm56000/util.c src/asm56000/globals.c \
    src/asm56000/tables.c src/asm56000/arith.c src/asm56000/asmglb.c \
    src/asm56000/section.c src/asm56000/pseudo.c src/asm56000/amode.c

$(B)/test-asm56000-instr$(EXE): tests/asm56000/test_instr.c \
                                src/asm56000/error.c src/asm56000/util.c \
                                src/asm56000/encode.c \
                                src/asm56000/input.c src/asm56000/asmglb.c \
                                src/asm56000/globals.c src/asm56000/symtab.c \
                                src/asm56000/eval.c src/asm56000/tables.c \
                                src/asm56000/arith.c src/asm56000/section.c \
                                src/asm56000/pseudo.c src/asm56000/amode.c \
                                src/asm56000/procop.c src/asm56000/asm56000.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -Wextra -Isrc/asm56000 -o $@ \
	    tests/asm56000/test_instr.c src/asm56000/error.c src/asm56000/util.c \
	    src/asm56000/encode.c \
	    src/asm56000/input.c src/asm56000/asmglb.c src/asm56000/globals.c \
	    src/asm56000/symtab.c src/asm56000/eval.c src/asm56000/tables.c \
	    src/asm56000/arith.c src/asm56000/section.c src/asm56000/pseudo.c \
	    src/asm56000/amode.c src/asm56000/procop.c src/asm56000/procxy.c $(LIBS)

DSPLNK_MODULES = $(DSPLNK_SRC)

dsplnk-modules: $(B) $(DSPLNK_MODULES:src/dsplnk/%.c=$(B)/dsplnk-%.o)

$(B)/dsplnk-%.o: src/dsplnk/%.c $(DSPLNK_HDR)
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -c -o $@ $<

clean:
	rm -f $(TOOLS) $(B)/dsplnk$(EXE) $(B)/asm56000$(EXE) \
	      $(B)/asm56000-error.o \
	      $(B)/asm56000-util.o $(B)/asm56000-encode.o \
	      $(B)/asm56000-input.o \
	      $(B)/asm56000-asmglb.o $(B)/asm56000-globals.o \
             $(B)/asm56000-symtab.o \
             $(B)/asm56000-eval.o \
             $(B)/asm56000-tables.o \
             $(B)/asm56000-arith.o \
             $(B)/asm56000-section.o \
             $(B)/asm56000-pseudo.o \
	      $(B)/asm56000-macro.o \
             $(B)/asm56000-amode.o \
	      $(B)/asm56000-procop.o $(B)/asm56000-listing.o \
	      $(B)/test-asm56000-primitives$(EXE) \
	      $(B)/test-asm56000-expr$(EXE) \
	      $(B)/test-asm56000-instr$(EXE) \
	      $(B)/dsplnk-*.o $(B)/test-sim56000-avl$(EXE) \
	      $(B)/test-sim56000-mem$(EXE) $(B)/sim56000-*.o

# SIM56000 foundation primitives (the full simulator is not linked yet).
sim56000-tests: $(B) $(B)/test-sim56000-avl$(EXE)
	$(B)/test-sim56000-avl$(EXE)

$(B)/test-sim56000-avl$(EXE): tests/sim56000/test_avl.c tests/sim56000/avlmock.c \
                            src/sim56000/avltree.c src/sim56000/sim56000.h \
                            src/sim56000/simdata.h src/sim56000/simproto.h
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -Wextra -Isrc/sim56000 \
	    -o $@ tests/sim56000/test_avl.c tests/sim56000/avlmock.c src/sim56000/avltree.c

SIM56000_MEM_SRC = src/sim56000/console.c src/sim56000/profdata.c \
                   src/sim56000/miscx.c src/sim56000/avltree.c
SIM56000_HEADERS = src/sim56000/sim56000.h src/sim56000/simdata.h \
                   src/sim56000/simproto.h

sim56000-memory-tests: $(B) $(B)/test-sim56000-mem$(EXE)
	$(B)/test-sim56000-mem$(EXE)

# Override libc allocation only in the radix object to inject deterministic
# failures. The test harness and all other modules use ordinary libc.
$(B)/sim56000-memtest.o: src/sim56000/radix.c $(SIM56000_HEADERS)
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -Wextra \
	    -Dmalloc=sim_test_malloc -Drealloc=sim_test_realloc -Dfree=sim_test_free \
	    -c -o $@ src/sim56000/radix.c

$(B)/test-sim56000-mem$(EXE): tests/sim56000/test_mem.c $(SIM56000_MEM_SRC) \
                             $(B)/sim56000-memtest.o $(SIM56000_HEADERS)
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -Wextra -Isrc/sim56000 \
	    -o $@ tests/sim56000/test_mem.c $(SIM56000_MEM_SRC) \
	    $(B)/sim56000-memtest.o

sim56000-tests: sim56000-memory-tests

SIM56000_FOUNDATION_SRC = $(SIM56000_MEM_SRC) src/sim56000/radix.c

sim56000-modules: $(B) $(SIM56000_FOUNDATION_SRC:src/sim56000/%.c=$(B)/sim56000-%.o)

$(B)/sim56000-%.o: src/sim56000/%.c $(SIM56000_HEADERS)
	$(CC) $(CFLAGS) -std=c89 -pedantic -Wall -Wextra -c -o $@ $<
