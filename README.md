# clerdle

A command-line port of the game [nerdle](https://nerdlegame.com). Final project for university c++ course.

## building

open a terminal in the project directory and run

```sh
make prod
```

the file `clerdle` is now the standalone app and can be moved anywhere. the code can be deleted.

## usage

```sh
# normal gameplay
./clerdle [playername]

# test mode (see the answer)
./clerdle -t [playername]

# show stats
./clerdle -s [playername]

# generation test
./clerdle -g <number>
```
