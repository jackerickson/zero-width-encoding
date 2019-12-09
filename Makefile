# MeowMeow - A stream encoder/decoder

ZWE= zwe

TARGETS= $(ZWE)

SRC= main.c encode.c decode.c
OBJ= $(SRC:.c=.o)
HDR= $(SRC:.c=.h) pad.h

MANIFEST= $(SRC) $(HDR) Makefile
SDIST_ROOT= hacks
SDIST_TARFILE= $(SDIST_ROOT).tar.gz

CC= gcc
CP= cp
DIFF= diff
MKDIR= mkdir
RM= rm
TAR= tar

CFLAGS= -g
LDFLAGS=

.PHONY: sdist

all: $(TARGETS)

$(ZWE): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LDFLAGS)

.c.o: $(HDR)
	$(CC) -c $< $(CFLAGS)

sdist: clobber
	$(MKDIR) -p $(SDIST_ROOT)
	$(CP) $(MANIFEST) $(SDIST_ROOT)
	$(TAR) zcf $(SDIST_TARFILE) $(SDIST_ROOT)

clean:
	@$(RM) -f $(OBJ)

clobber: clean
	@$(RM) -f $(TARGETS) $(SDIST_TARFILE)
	@$(RM) -rf $(SDIST_ROOT)