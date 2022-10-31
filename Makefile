.SUFFIXES:.c .o
CXX = g++
#CFLAGS = -O2 -g -D_REENTERANT
#LDLIBS = -lpthread
OBJ1 = main.o User.o Customer_Manager.o board.o
OBJ2 = main_c.o

SRCS = $(OBJS1:.o=.c) $(OBJS2:.o=.c)

all : server client

server: $(OBJ1)
	$(CXX) -o server $(OBJ1) -lpthread

client: $(OBJ2)
	$(CXX) -o client $(OBJ2) -lpthread

clean :
	rm -rf $(OBJ1) $(OBJ2) server client core final reference reference_server

main.o : main.cpp
User.o : User.h User.cpp
Customer_Manager.o : Customer_Manager.h Customer_Manager.cpp
main_c.o : main_c.cpp
board.o : board.cpp