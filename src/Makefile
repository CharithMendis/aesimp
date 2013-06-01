
IDIR =../include
ODIR=../obj
LDIR =../lib
EDIR = ../exec

CC=gcc
CFLAGS= -m32 -DBUILD_32 -I $(IDIR)

#-Wall

LIBS=-lm

_DEPS = aeskeyex.h aescipher.h aesdecipher.h aessub.h aeshelper.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = aeskeyex.o aescipher.o aesdecipher.o aessub.o aeshelper.o main.o 
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