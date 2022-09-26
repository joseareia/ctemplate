# Directories
DIR_GENGETOPT=./gengetopt
DIR_LIBS=./libs

# Libraries to include (if any)
LIBS=#-lm -pthread

# Compiler flags
CFLAGS=-Wall -Wextra -ggdb -std=c11 -pedantic -D_POSIX_C_SOURCE=200809L #-pg

# Linker flags
LDFLAGS=#-pg

# Indentation flags
# IFLAGS=-br -brs -brf -npsl -ce -cli4 -bli4 -nut
IFLAGS=-linux -brs -brf -br

OUTPUT=prog
PROG=main
PROG_OPT_NODIR=prog_opt
PROG_OPT=$(DIR_GENGETOPT)/$(PROG_OPT_NODIR)
PROG_OBJS=$(PROG).o $(DIR_LIBS)/debug.o $(DIR_LIBS)/memory.o $(PROG_OPT).o
PROG_HEADERS=$(PROG).c $(DIR_LIBS)/debug.h $(DIR_LIBS)/memory.h $(PROG_OPT).h

# ! DEPENDENCIES GO TO - # Dependencies vendor

# Specifies which targets are not files
.PHONY: clean all docs indent debugon args optimize

all: args $(PROG)

# activate DEBUG, defining the SHOW_DEBUG macro
debugon: CFLAGS += -D SHOW_DEBUG -g
debugon: $(PROG)

# activate optimization (-O...)
OPTIMIZE_FLAGS=-O2 # possible values (for gcc): -O2 -O3 -Os -Ofast
optimize: CFLAGS += $(OPTIMIZE_FLAGS)
optimize: LDFLAGS += $(OPTIMIZE_FLAGS)
optimize: $(PROG)

$(PROG): $(PROG_OBJS)
	$(CC) -o $(OUTPUT) $(PROG_OBJS) $(LIBS)

# Dependencies
$(PROG).o: $(PROG_HEADERS)
$(PROG_OPT).o: $(PROG_OPT).c $(PROG_OPT).h

# Dependencies vendor
$(DIR_LIBS)/debug.o: $(DIR_LIBS)/debug.c $(DIR_LIBS)/debug.h
$(DIR_LIBS)/memory.o: $(DIR_LIBS)/memory.c $(DIR_LIBS)/memory.h

# disable warnings from gengetopt generated files
$(PROG_OPT).o: $(PROG_OPT).c $(PROG_OPT).h
	$(CC) -ggdb -std=c11 -pedantic -c -o $@ $<

#how to create an object file (.o) from C file (.c)
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# Generates command line arguments code from gengetopt configuration file
$(PROG_OPT).c $(PROG_OPT).h: $(PROG_OPT).ggo
	gengetopt < $(PROG_OPT).ggo --file-name=$(PROG_OPT_NODIR)  --set-package=$(PROG) --output-dir=$(DIR_GENGETOPT)

clean:
	rm -f *.o core.* *~ .*~ $(PROG) $(OUTPUT) *.bak $(PROG_OPT).h $(PROG_OPT).c $(DIR_GENGETOPT)/*.o $(DIR_LIBS)/*.o

docs: Doxyfile
	doxygen Doxyfile

# entry to create the list of dependencies
depend:
	$(CC) -MM *.c

# entry 'indent' requires the application indent (sudo apt-get install indent)
indent:
	indent $(IFLAGS) *.c *.h

# entry to run the pmccabe utility (computes the "complexity" of the code)
# Requires the application pmccabe (sudo apt-get install pmccabe)
pmccabe:
	pmccabe -v *.c

# entry to run the cppcheck tool
cppcheck:
	cppcheck --enable=all --verbose *.c *.h

args:
	gengetopt < $(PROG_OPT).ggo --file-name=$(PROG_OPT_NODIR)  --set-package=$(PROG) --output-dir=$(DIR_GENGETOPT)
