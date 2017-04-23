CMP = g++
CFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -Wall -std=c++11 -g
OBJ1 = texture
OBJ2 = sdlTools
OBJ3 = sprite
OBJ4 = player
OBJ5 = enemy
OBJ6 = collisions
OBJ7 = laser
OBJ8 = background
CLASS1 = note


FINAL = test

all:     	$(CLASS1)	\
			$(OBJ1)		\
			$(OBJ2)		\
			$(OBJ3)		\
			$(OBJ4)		\
			$(OBJ5)		\
			$(OBJ6)		\
			$(OBJ7)		\
			$(OBJ8)		\
			$(FINAL)

$(CLASS1): $(CLASS1).cpp $(CLASS1).h
		@echo Compiling $(CLASS1)...
		@$(CMP) -c $(CLASS1).cpp -o $(CLASS1).o

$(OBJ1):     $(OBJ1).cpp
	@echo Compiling $(OBJ1)...
	@$(CMP) $(OBJ1).cpp $(CFLAGS) -c -o $(OBJ1).o

$(OBJ2):     $(OBJ2).cpp
	@echo Compiling $(OBJ2)...
	@$(CMP) $(OBJ2).cpp $(CFLAGS) -c -o $(OBJ2).o

$(OBJ3):    $(OBJ3).cpp
	@echo Compiling $(OBJ3)...
	@$(CMP) $(OBJ3).cpp $(CFLAGS) -c -o $(OBJ3).o

$(OBJ4):	$(OBJ4).cpp
	@echo Compiling $(OBJ4)...
	@$(CMP) $(OBJ4).cpp $(CFLAGS) -c -o $(OBJ4).o

$(OBJ5):	$(OBJ5).cpp
	@echo Compiling $(OBJ5)...
	@$(CMP) $(OBJ5).cpp $(CFLAGS) -c -o $(OBJ5).o

$(OBJ6):	$(OBJ6).cpp
	@echo Compiling $(OBJ6)...
	@$(CMP) $(OBJ6).cpp $(CFLAGS) -c -o $(OBJ6).o

$(OBJ7):	$(OBJ7).cpp
	@echo Compiling $(OBJ7)...
	@$(CMP) $(OBJ7).cpp $(CFLAGS) -c -o $(OBJ7).o

$(OBJ8):	$(OBJ8).cpp
	@echo Compiling $(OBJ8)...
	@$(CMP) $(OBJ8).cpp $(CFLAGS) -c -o $(OBJ8).o

$(FINAL):    $(OBJ1).o $(OBJ2).o $(OBJ3).o $(OBJ4).o $(OBJ5).o $(FINAL).cpp $(CLASS1).h
	@echo Compiling $(FINAL)...
	@$(CMP) $(FINAL).cpp $(CLASS1).o $(OBJ1).o $(OBJ2).o $(OBJ3).o $(OBJ4).o $(OBJ5).o $(OBJ6).o $(OBJ7).o $(OBJ8).o $(CFLAGS) -o $(FINAL)

clean:
	@echo Cleaning up...
	@rm ./*.o $(FINAL)
