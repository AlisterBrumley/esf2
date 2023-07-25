IDIR =../include
CC=clang


SRCDIR		= src
INCLDIR		= include
OUTFILE		= esf2

SOURCES		:= $(wildcard $(SRCDIR)/*.c)
INCLUDES	:= $(wildcard $(INCLDIR)/*.h)


UNAME_S		:= $(shell uname -s)
UNAME_M		:= $(shell uname -m)

$(OUTFILE): $(SOURCES) $(INCLUDES)
		mkdir $(UNAME_S)_$(UNAME_M)
		$(CC) -I $(INCLDIR) -o $(UNAME_S)_$(UNAME_M)/$(OUTFILE) $(SOURCES)