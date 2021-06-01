#-------------------------------------------------------------------------------
# Makefile for Ising Model
#-------------------------------------------------------------------------------

# compiler flags
DEBUG    = -ggdb
OPTIMISE = -O3 # O0 -> compilation time | O3 -> execution time
WARNINGS = -Wall -Wextra -Wno-variadic-macros -Wno-overlength-strings -pedantic
LIBS     = -lglut -lGLU -lGL -lm
CFLAGS   = $(DEBUG) $(OPTIMISE) $(WARNINGS) -fPIC
DFLAGS   = #-DDEBUG_CIRCLES

# commands
CC       = gcc
RM       = rm -f
COMPILE  = $(CC) $(CFLAGS) $(DFLAGS)
INSTALL  = install

# files
EXES     = circles

# directories
BINDIR   = ../bin
TEXDIR   = ../tex
LOCALBIN = ~/.local/bin

#-- PHONY TARGETS --------------------------------------------------------------

.PHONY: all clean install uninstall

all: circles

tex: $(TEXDIR)/writeup.tex
	$(TEXCOMP) $^ && $(TEXCOMP) $^

clean:
	$(RM) $(foreach EXEFILE, $(EXES), $(BINDIR)/$(EXEFILE))
	$(RM) *.o
	$(RM) $(BINDIR)/*.so
	$(RM) -rf $(BINDIR)/*.dSYM
	$(RM) $(TEXDIR)/*.out

install: # Put binaries in local bin
	mkdir -p $(LOCALBIN)
	$(INSTALL) $(foreach EXEFILE, $(EXES), $(wildcard $(BINDIR)/$(EXEFILE))) \
		$(LOCALBIN)

uninstall: # Remove binaries from local bin
	$(RM) $(foreach EXEFILE, $(EXES), $(LOCALBIN)/$(EXEFILE))

#-- RULES ----------------------------------------------------------------------

# executables & shared objects

circles: circles.c circles.h random.o | $(BINDIR)
	$(COMPILE) -o $(BINDIR)/$@ $^ $(LIBS)

# units

random.o: random.c random.h
	$(COMPILE) -c $<

# bin directory

$(BINDIR):
	mkdir $(BINDIR)
