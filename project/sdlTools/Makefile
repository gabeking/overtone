CMP = g++
CFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -Wall
OBJ1 = texture
OBJ2 = sdlTools
OBJ3 = sprite

FINAL = test

all:            $(OBJ1) $(OBJ2) $(OBJ3) $(FINAL)

$(OBJ1):     $(OBJ1).cpp
	$(CMP) $(OBJ1).cpp $(CFLAGS) -c -o $(OBJ1).o

$(OBJ2):     $(OBJ2).cpp
	$(CMP) $(OBJ2).cpp $(CFLAGS) -c -o $(OBJ2).o

$(OBJ3):    $(OBJ3).cpp
	$(CMP) $(OBJ3).cpp $(CFLAGS) -c -o $(OBJ3).o

$(FINAL):    $(OBJ1).o $(OBJ2).o $(OBJ3).o $(FINAL).cpp
	$(CMP) $(FINAL).cpp $(OBJ1).o $(OBJ2).o $(OBJ3).o $(CFLAGS) -o $(FINAL)

clean:
	rm ./*.o $(FINAL)
