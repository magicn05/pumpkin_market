OBJECTS = main.o User.o Customer_Manager.o
SRCS = main.cpp User.cpp Customer_Manager.cpp

CXX = g++

TARGET = final

$(TARGET) : $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)

clean :
	rm -rf $(OBJECTS) $(TARGET) core

main.o : main.cpp
User.o : User.h User.cpp
Customer_Manager.o : Customer_Manager.h Customer_Manager.cpp


