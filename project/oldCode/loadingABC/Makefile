CMP = g++ -Wall -std=c++11
CLASS = note
MAIN = buildSong
EXEC = runit

$(EXEC):        $(MAIN).o $(CLASS).o
	$(CMP) $(MAIN).o $(CLASS).o -o $(EXEC)

$(MAIN).o:      $(MAIN).cpp
	$(CMP) -c $(MAIN).cpp

$(CLASS).o:     $(CLASS).cpp
	$(CMP) -c $(CLASS).cpp

clean:
	rm *.o
	rm $(EXEC)
