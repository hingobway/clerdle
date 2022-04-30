CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror

out_file = clerdle
objs = AppMode.o clerdle.o color.o Game.o Guess.o Player.o Puzzle.o StatsCollection.o UX.o
headers = AppMode.h color.h Game.h Guess.h Player.h Puzzle.h StatsCollection.h UX.h

$(out_file): $(objs)
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(objs): %.o: %.cpp $(headers)

prod: $(out_file) cleanProd

.PHONY: clean cleanProd
clean:
	rm -f *.o $(out_file)
cleanProd:
	rm -f *.o
cleaninstall:
	rm -f *.cpp *.h
