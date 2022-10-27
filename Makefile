OBJECTS = main.o
SRCS = main.cpp

CXX = g++

TARGET = final

$(TARGET) : $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)

clean :
	rm -rf $(OBJECTS) $(TARGET) core

main.o : main.cpp


