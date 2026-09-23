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

TOOLS   = $(B)/cldinfo$(EXE) $(B)/cldlod$(EXE) $(B)/dsplib$(EXE) $(B)/strip$(EXE) $(B)/tiohist$(EXE)

all: $(B) $(TOOLS)

$(B):
	mkdir -p $(B)

$(B)/cldinfo$(EXE): src/cldinfo/cldinfo.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/cldinfo/cldinfo.c

$(B)/cldlod$(EXE): src/cldlod/cldlod.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/cldlod/cldlod.c $(LIBS)

$(B)/dsplib$(EXE): src/dsplib/dsplib.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/dsplib/dsplib.c

$(B)/strip$(EXE): src/strip/strip.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/strip/strip.c

$(B)/tiohist$(EXE): src/tiohist/tiohist.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/tiohist/tiohist.c

clean:
	rm -f $(TOOLS)
