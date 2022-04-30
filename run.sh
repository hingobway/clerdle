# this is a click-to-run start script for the project.
# it will build and run the app, and then prevent it from closing 
# instantly at the end.

make prod
./clerdle
read -p "Press ENTER to close."
