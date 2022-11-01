INC = ../include
CXX = g++
CFLAGS = -fPIC -c  -g
LDFLAGS = -L../libsrc -lmenu -lhash -lpthread -ldl
#LDFLAGS = -L../../lib -lmenu -lprofile -lhash -lio  -lpthread
OBJS = add.o sub.o
#TARGET = libadd.so libsub.so

all: server libadd.so libsub.so

server: server.o
	$(CXX) -o $@ $@.o $(LDFLAGS)
#	cp $@ ../../bin/

server.o: server.cpp
	$(CXX) -c -I$(INC) -g $<

libadd.so: add.o 
	$(CXX) -shared -fPIC -o $@ $<
#	cp lib$@.so ../../bin/

libsub.so: sub.o 
	$(CXX) -shared -fPIC -o $@ $<
#	cp lib$@.so ../../bin/

clean:
	rm *.o lib*.so server 
