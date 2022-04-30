# this script automatically compiles the app when a file is changed.
# it makes use of nodemon - see https://nodemon.io/.

make clean
nodemon -L -e cpp,h --exec "make"
