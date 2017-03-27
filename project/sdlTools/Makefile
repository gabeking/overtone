CMP = g++
CFLAGS = -lSDL2 -lSDL2_image -Wall
OBJ1 = texture
OBJ2 = sdlTools
OBJ3 = test

all:            $(OBJ1) $(OBJ2) $(OBJ3)

$(OBJ1):     $(OBJ1).cpp
	$(CMP) $(OBJ1).cpp $(CFLAGS) -c -o $(OBJ1).o

$(OBJ2):     $(OBJ2).cpp
	$(CMP) $(OBJ2).cpp $(CFLAGS) -c -o $(OBJ2).o

$(OBJ3):    $(OBJ1).o $(OBJ2).o $(OBJ3).cpp
	$(CMP) $(OBJ3).cpp $(OBJ1).o $(OBJ2).o $(CFLAGS) -o $(OBJ3)

clean:
	rm ./*.o $(OBJ3)
