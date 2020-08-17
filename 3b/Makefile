CPPFLAGS=-Wall -g -std=c++11
LIBS=-g -lglut -lGLU -lGL
OBJECTS=Viewer.o Camera.o Env3D.o Terrarium.o TerrEntity.o TerrWall.o Animal.o Bug.o Penguin.o
TARGET=3dViewer
%.o: %.cpp
	g++ -c $(CPPFLAGS) -o $@ $< 
all: $(TARGET)
$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LIBS)
Viewer.o: Viewer.cpp
Camera.o: Camera.cpp Camera.h
Env3D.o: Env3D.cpp Env3D.h
Terrarium.o: Terrarium.cpp Terrarium.h
TerrEntity.o: TerrEntity.cpp TerrEntity.h
TerrWall.o: TerrWall.cpp TerrWall.h
Animal.o: Animal.cpp Animal.h
Bug.o: Bug.cpp Bug.h
Penguin.o: Penguin.cpp Penguin.h

clean:
	rm *.o $(TARGET)
