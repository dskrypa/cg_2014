CPPFLAGS=-Wall -g
LIBS=-g -lglut -lGLU -lGL
OBJECTS=hw2Runner.o Clickable.o Icon.o LogicGate.o Terminal.o Wire.o
TARGET=assign2
%.o: %.cpp
	g++ -c $(CPPFLAGS) -o $@ $< 
all: $(TARGET)
$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LIBS)
hw2Runner.o: hw2Runner.cpp Clickable.h Icon.h LogicGate.h Terminal.h Wire.h
Clickable.o: Clickable.cpp Clickable.h
Icon.o: Icon.cpp Icon.h
LogicGate.o: LogicGate.cpp LogicGate.h
Terminal.o: Terminal.cpp Terminal.h
Wire.o: Wire.cpp Wire.h

clean:
	rm *.o $(TARGET)
