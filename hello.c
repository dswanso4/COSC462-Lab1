/* hello.c */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include "jmesh.h"
#include "offreader.h"
#include "utils.h"

int main(int argc, char * argv[]) {

  graphics_state gs;
  jmesh * jm;
  FILE *fp;


  // Screen size
  gs.height=512;
  gs.width =512;

  // check for command line arguments 
  if(argc != 2){
    printf("Usage: executable cubesize\n");
    exit(1);
  }

  // Open file to read, report error if unsuccessful
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
	printf("Can't open input file!\n");
	exit(1);
  }

  // Create a new mesh with the information in the file. Then close file.
  jm = new_jmesh(fp);
  if (jm == NULL) {
	printf("load_off_mesh Failed!\n");
    exit(1);
  }
  fclose(fp);


  gs.mesh = jm;
  print_howto();

  { /* GLUT initialization */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(gs.width,gs.height);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(keys);
    glutMouseFunc(mouse_handler);
    glutMotionFunc(trackMotion);

  }

  // Initialize the graphics state and set up a timer for animation
  init(&gs);
  glutTimerFunc(10, update, 0);
  
  // Enter main loop, clear mesh when done.
  glutMainLoop();

  return 0;
}
