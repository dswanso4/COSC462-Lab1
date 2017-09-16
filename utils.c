/* utils.c */

#include "utils.h"

// Global GLubyte used to output ppm file, angle and speed arrays are used in
// rotation the objects.
static graphics_state * current_gs;
static GLubyte *pixels = NULL;
GLfloat angle[10] = {0.0};
GLfloat speed[10] = {0.0, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1};


// Function that prints instructions.
void print_howto(void){
  printf("Keyboard Commands:\n");
  printf("q or Q		Quits program\n");
  printf("s or S		Takes screenshot\n");
}

// Sets the graphics state.
void 
set_gs(graphics_state * gs){
  current_gs = gs;
}


// Initialization function, sets background to orange and resizes the graphic
void 
init(graphics_state * gs){
  current_gs = gs;
  glClearColor(1.0f, 0.6f, 0.0f, 1.0f);
  reshape(current_gs->width, current_gs->height);
}

// Function that changes the display
void 
display(void){
  GLfloat v[9];
  int i, j, k;
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);

  // Each of the 10 cubes (1 sun and 9 planets) are loops through. The are 
  // translated and rotated according to their global constants.
  for (k = 0; k < 10; k++) {
	glPushMatrix();
	glRotatef(angle[k], 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, k*2.0);
	glTranslatef(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
	for (i = 0; i < current_gs->mesh->ntri; i++) {
	  j = current_gs->mesh->triangles[i*3+0];
	  v[0] = current_gs->mesh->vertices[j*3+0]; 
	  v[1] = current_gs->mesh->vertices[j*3+1];
	  v[2] = current_gs->mesh->vertices[j*3+2];
	  j = current_gs->mesh->triangles[i*3+1];
	  v[3] = current_gs->mesh->vertices[j*3+0];
	  v[4] = current_gs->mesh->vertices[j*3+1];
	  v[5] = current_gs->mesh->vertices[j*3+2];
	  j = current_gs->mesh->triangles[i*3+2];
	  v[6] = current_gs->mesh->vertices[j*3+0];
	  v[7] = current_gs->mesh->vertices[j*3+1];
      v[8] = current_gs->mesh->vertices[j*3+2];
	  glVertex3f(v[0], v[1], v[2]);
	  glVertex3f(v[3], v[4], v[5]);
	  glVertex3f(v[6], v[7], v[8]);
    }
	glEnd();
	glPopMatrix();
  }
  glutSwapBuffers();

}


// Function that sets the camera, perspective, and makes the images wireframe
void 
reshape(int w, int h){
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat) w/h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 20.0, -30, current_gs->mesh->centroid[0], 
		  current_gs->mesh->centroid[1], current_gs->mesh->centroid[2], 
		  0.0, 0.0, 1.0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void 
mouse_handler(int button, int button_state, int x, int y){
  
}

void 
trackMotion(int x, int y) {

}

void idle (void) {

}


// Function that reacts when a key is pressed.
void 
keys(unsigned char c, int x, int y) {
  switch (c) {
	  case 'q': 
	    printf("Quitting Program...\n");
	    exit(0);
	    break;
	  case 'Q':
		printf("Quitting Program...\n");
	    exit(0);
	    break;
	  case 's':
	    screenshot("lab1.ppm", current_gs->width, current_gs->height, &pixels);
	    break;
	  case 'S':
	    screenshot("lab1.ppm", current_gs->width, current_gs->height, &pixels);
	    break;
  }
}

// Function that updates the image. The new angle of roatation is calculated 
// based on the speed of the object. 
void update(int value) {
  int i;
  for (i = 0; i < 10; i++) {
    angle[i] += speed[i];
	if (angle[i] > 360) {
	  angle[i] -= 360;
	}
  }

  glutPostRedisplay();
  glutTimerFunc(10, update, 0);

}

// Function that captures the screenshot. It reads the pixel data from the top 
// left corner of the screen to the bottom right corner and then stores the 
// RGB data into a PPM file.
void screenshot(char * file, int w, int h, GLubyte **pixels) {
  size_t i, j, current;
  const size_t format_nchannels = 3;
  FILE *fp = fopen(file, "w");
  printf("Making PPM File...\n");
  fprintf(fp, "P3\n%d %d\n%d\n", w, h, 255);
  *pixels = realloc(*pixels, format_nchannels*sizeof(GLubyte)*w*h);
  glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, *pixels);
  for (i = 0; i < h; i++) {
	for (j = 0; j < w; j++) {
	  current = format_nchannels * ((h - i - 1)*w + j);
	  fprintf(fp, "%3d %3d %3d ", (*pixels)[current], (*pixels)[current+1],
			  (*pixels)[current+2]);
	}
	fprintf(fp, "\n");
  }
  fclose(fp);
  printf("Done Making PPM File!\n");
}
