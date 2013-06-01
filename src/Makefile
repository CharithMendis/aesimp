
IDIR =../include
ODIR=../obj
LDIR =../lib
EDIR = ../exec

CC=gcc
CFLAGS=-Wall -m32 -DBUILD_32 -I $(IDIR)

LIBS=-lm

_DEPS = aeskeyex.h aessbox.h aessub.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = aeskeyex.o aescipher.o aesdecipher.o aessub.o main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

PRODUCT = $(EDIR)/aes

all : $(PRODUCT)

$(PRODUCT) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 