CPPFLAGS=-Wall -g -std=c++11
LIBS=-g -lglut -lGLU -lGL
OBJECTS=Viewer.o Camera.o Env3D.o Terrarium.o TerrEntity.o AnimalLeg.o Animal.o Bug.o
TARGET=3dViewer
%.o: %.cpp
	g++ -c $(CPPFLAGS) -o $@ $< 
all: $(TARGET)
$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LIBS)
Viewer.o: Viewer.cpp common.h
Camera.o: Camera.cpp Camera.h
Env3D.o: Env3D.cpp Env3D.h
Terrarium.o: Terrarium.cpp Terrarium.h
TerrEntity.o: TerrEntity.cpp TerrEntity.h
AnimalLeg.o: AnimalLeg.cpp AnimalLeg.h
Animal.o: Animal.cpp Animal.h
Bug.o: Bug.cpp Bug.h

clean:
	rm *.o $(TARGET)
