CC = gcc -ggdb
AR = ar
RL = runlib
LIBDIR = lib
INCDIR = inc

OBJFILES = \
	$(LIBDIR)/simpleComputer.o \
	$(LIBDIR)/term.o \
	$(LIBDIR)/bigChars.o \
	$(LIBDIR)/readKey.o

STLIBFILES = \
	$(LIBDIR)/simpleComputer.a \
	$(LIBDIR)/term.a \
	$(LIBDIR)/bigChars.a \
	$(LIBDIR)/readKey.a

all: kernel

clean:
	rm $(LIBDIR)/*.o
	rm $(LIBDIR)/*.a
	rm kernel 

rebuild:
	make clean
	make

.c.o:
	$(CC) -I$(INCDIR) -o $@ -c $<

.o.a:
	$(AR) rcs $@ $<
	ranlib $@

kernel: $(STLIBFILES) $(OBJFILES)	
	mv $(LIBDIR)/simpleComputer.a $(LIBDIR)/libsimpleComputer.a
	mv $(LIBDIR)/term.a $(LIBDIR)/libterm.a
	mv $(LIBDIR)/bigChars.a $(LIBDIR)/libbigChars.a
	mv $(LIBDIR)/readKey.a $(LIBDIR)/libreadKey.a
	gcc -I$(INCDIR) -static kernel.c -L$(LIBDIR) -lsimpleComputer -lterm -lbigChars -lreadKey -o kernel
