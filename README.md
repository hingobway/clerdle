# clerdle

A command-line port of the game [nerdle](https://nerdlegame.com). Final project for university c++ course.

A few things to note about my version:

- negative numbers are not allowed in guesses.
- guesses may not contain operators to the right of the `=`.
- a number of formatting liberties were taken on the command line.
- player names have been made case-insensitive.

## building

open a terminal in the project directory and run

```sh
# regular compile
make prod

# compile and remove code files
make prod cleaninstall
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

# show these instructions
./clerdle -h
```
