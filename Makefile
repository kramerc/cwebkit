BDIR=./bin
IDIR=./include
ODIR=./obj
SDIR=./src
CCFLAGS=`pkg-config --cflags --libs gtk+-3.0 webkitgtk-3.0` -I$(IDIR) -shared -fPIC

all: cwebkit

cwebkit: compile
	gcc $(ODIR)/cwebkit/*.o $(ODIR)/cwebkit/js/*.o -o $(BDIR)/libcwebkit.so $(CCFLAGS)

compile:
	mkdir -p $(BDIR) $(ODIR)/cwebkit $(ODIR)/cwebkit/js
	gcc -c $(SDIR)/cwebkit/cwebkit.c -o $(ODIR)/cwebkit/cwebkit.o $(CCFLAGS)
	gcc -c $(SDIR)/cwebkit/gtk.c -o $(ODIR)/cwebkit/gtk.o $(CCFLAGS)
	gcc -c $(SDIR)/cwebkit/js.c -o $(ODIR)/cwebkit/js.o $(CCFLAGS)
	gcc -c $(SDIR)/cwebkit/js/list.c -o $(ODIR)/cwebkit/js/list.o $(CCFLAGS)
	gcc -c $(SDIR)/cwebkit/js/utils.c -o $(ODIR)/cwebkit/js/utils.o $(CCFLAGS)
	
clean:
	rm -rf $(BDIR) $(ODIR)