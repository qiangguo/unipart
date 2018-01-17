To run the program, you will need to install OpenGL library first. If you are running under Ubuntu, open a terminal and run
       sudo apt-cache search opengl
       sudo apt-get install freeglut3
       sudo apt-get install mesa-utils
       sudo apt-get install freeglut3-dev       
After install OpenGL library, you can run make to generate executable file.
The demonstrative panel allows you to set points by click mouse. Once points are set, the program automatically finds the
smallest close circle by calling Welzl algorithm.
