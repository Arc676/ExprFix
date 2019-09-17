CC=gcc
FLAGS=-std=c11

LIBOUT=libexprfix.a
EXECOUT=exprfix

ifdef DEBUG
FLAGS+=-g -O0
endif

ifdef THREADSAFE
FLAGS+=-D THREADSAFE
endif

ifdef RELEASE
FLAGS+=-O2
endif

INCLUDE=-I src -L .
CFLAGS=$(FLAGS) $(INCLUDE)
LIB=-l exprfix

ODIR=obj
SDIR=src
FDIR=frontend

OBJS=exprfix.o structures.o
_OBJS=$(patsubst %, $(ODIR)/%, $(OBJS))

exprfix: lib
	$(CC) $(CFLAGS) $(FDIR)/exprfix.c $(LIB) -o $(FDIR)/$(EXECOUT)

lib: makeodir $(_OBJS)
	ar rcs $(LIBOUT) $(_OBJS)

makeodir:
	mkdir -p $(ODIR)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c $(FLAGS) -o $@ $<

clean:
	rm -f $(LIBOUT) $(FDIR)/$(EXECOUT) $(ODIR)/*.o
