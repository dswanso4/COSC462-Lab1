# COSC462-Lab1
Simulate a solar system using C and OpenGL

# jmesh.c / jmesh.h:
These files are in charge of initializing the mesh strucuture that will be used throughout the program.
A mesh contains an array containing the vertices, an array containing the triangles, and an array containing 
centeroid information. The vertices are a set of 3 floating point coordinates (x,y,z). The triangles are are 
a set of 3 integars specifying which vertices are contained in the triangle.

# offreader.c / offreader.h :
These file is in charge of loading an object in the form of a .OFF file, and then converting it to a mesh.
A mesh is a structure of vertices and triangles that form an object. 

# utils.c / utils.h :
These files contain functions that are used to assist the rendering process. The listener functions, 
keyboard commands, and the display function are declared here.

# hello.c :
This file is the main file that holds everything together. The OpenGL environment is declared here with some
initial settings. User imput is taken and then a timer is set up to establish the animation.

# Using the Application:
First compile the application on the command line using the given makefile. An executeable called "hello" will 
be created. Call this file with the desired .OFF file in the following way:

./hello filename.off

The render will open in a new window and statistics will be printed to the command line. You can quit the
application using 'q' or 'Q' and take a screenshot using 's' or 'S'.
