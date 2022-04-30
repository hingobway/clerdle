CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror

out_file = clerdle
objs = AppMode.o Guess.o Puzzle.o UX.o color.o Game.o Player.o StatsCollection.o clerdle.o
headers = AppMode.h Game.h Guess.h Player.h Puzzle.h StatsCollection.h UX.h color.h

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
