INC = ../include
CFLAGS = -fPIC -c  -g
OBJS = menu.o profile.o input.o
TARGET = libmenu.so libhash.so libarray.so 

all: libmenu.so libhash.so libarray.so

libmenu.so: $(OBJS)
	$(LD) -shared -o $@ $(OBJS)
#	cp lib$@.so ../../bin/

libhash.so: hash.o 
	$(LD) -shared -o $@ $<
#	cp lib$@.so ../../bin/

libarray.so: array.o
	$(LD) -shared -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -I$(INC) $< 

clean:
	rm *.o lib*.so
