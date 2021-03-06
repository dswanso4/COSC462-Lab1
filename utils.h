/* utils.h */

#ifndef UTILS_H
#define UTILS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "jmesh.h"


#ifndef _GRAPHICS_UTILS_
#define _GRAPHICS_UTILS_

typedef struct {
  int width;        /* width of rendering target */
  int height;       /* height of rendering target */
  double cubesize;  /* size of cube - for playing with */
  jmesh * mesh;
} graphics_state;   /* global graphics state */

#ifdef __cplusplus
extern "C" {
#endif
  
  void print_howto(void);

  void init(graphics_state *);
  void set_gs(graphics_state *);

  void display(void); 
  void reshape(int w, int h);
  void idle(void);
  void screenshot (char* , int , int , GLubyte **);
  void mouse_handler(int button, int button_state, int x, int y);
  void trackMotion(int x, int y);
  void keys(unsigned char c,int x, int y);
  void update(int);
  /* GLSL specific functions */
  char*textFileRead(char *fn);
  int  load_shader(GLuint shader, GLchar * source);
  int  init_GLSL(char * vert_source, char * frag_source);

#ifdef __cplusplus
}
#endif
    
#endif

#endif
