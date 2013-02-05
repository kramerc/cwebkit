BDIR=./bin
IDIR=./include
ODIR=./obj
SDIR=./src
CCFLAGS=`pkg-config --cflags --libs gtk+-3.0 webkitgtk-3.0` -I../include -I$(IDIR) -L../bin -lcwebkit

all: tester

tester: compile
	gcc $(ODIR)/*.o -o $(BDIR)/tester $(CCFLAGS)

compile:
	mkdir -p $(BDIR) $(ODIR)
	gcc -c $(SDIR)/tester.c -o $(ODIR)/tester.o $(CCFLAGS)
	gcc -c $(SDIR)/js.c -o $(ODIR)/js.o $(CCFLAGS)
	
clean:
	rm -rf $(ODIR) $(BDIR)