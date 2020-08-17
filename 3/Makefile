CPPFLAGS=-Wall -g
LIBS=-g -lglut -lGLU -lGL
OBJECTS=TerrariumViewer.o Terrarium.o TerrEntity.o TerrWall.o Animal.o Bug.o Penguin.o
TARGET=terrRunner
%.o: %.cpp
	g++ -c $(CPPFLAGS) -o $@ $< 
all: $(TARGET)
$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LIBS)
TerrariumViewer.o: TerrariumViewer.cpp Terrarium.h
Terrarium.o: Terrarium.cpp Terrarium.h
TerrEntity.o: TerrEntity.cpp TerrEntity.h
TerrWall.o: TerrWall.cpp TerrWall.h
Animal.o: Animal.cpp Animal.h
Bug.o: Bug.cpp Bug.h
Penguin.o: Penguin.cpp Penguin.h

clean:
	rm *.o $(TARGET)
