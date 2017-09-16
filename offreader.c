
#include "offreader.h"


typedef struct {
  int * size;
  int tris;
  int ** verts;
 
} polygon;

int load_off_mesh(FILE * fp, jmesh * jm) {
  size_t buf_size = 100;
  int d = 3;
  int tri_count = 0;
  float tmp[3] = {0.0};
  float min[3] = {0.0};
  float max[3] = {0.0};
  int num_edges, num_verts, num_faces;
  int i, j;
  char * buffer;
  char * extra;
  char * swap;
  polygon * p;


  // Allocate memmory for buffers and reader in first few info lines of the file

  buffer = (char *) malloc (buf_size + 1);
  extra = (char *) malloc (buf_size + 1);
  swap = (char *) malloc (buf_size + 1);
  getline(&buffer, &buf_size, fp);
  getline(&buffer, &buf_size, fp);
  sscanf(buffer, "%d %d %d\n",&num_verts, &num_faces, &num_edges);
  p = malloc(sizeof(polygon));
  p->size = malloc (num_faces*sizeof(int));
  jm->vertices = malloc(num_verts*d*sizeof(float));
  jm->centroid = malloc(3*sizeof(float));
  p->tris = 0;
  // Read in the lines of the file that relate to the vertices. Compare values as
  // they are read in to find the min and max

  for (i = 0; i < num_verts; i++) {
	getline(&buffer, &buf_size, fp);
	sscanf(buffer, "%f %f %f\n", &tmp[0], &tmp[1], &tmp[2]);
	jm->vertices[i*d+0] = tmp[0];
	if (tmp[0] > max[0])
      max[0] = tmp[0];
	if (tmp[0] < min[0])
	  min[0] = tmp[0];
	jm->vertices[i*d+1] = tmp[1];
	if (tmp[1] > max[1])
	  max[1] = tmp[1];
	if (tmp[1] < min[1])
	  min[1] = tmp[1];
	jm->vertices[i*d+2] = tmp[2];
	if (tmp[2] > max[2])
	  max[2] = tmp[2];
	if (tmp[2] < min[2])
	  min[2] = tmp[2];
  }

  // Read in lines of the file that relate to the faces. For now, the code handles
  // everything as a quad. Keep a count of how many triangles can be formed.

  p->verts = malloc(num_faces*20*sizeof(int));
  for (i = 0; i < num_faces; i++) {
    getline(&buffer, &buf_size, fp);
	sscanf(buffer, "%d %100c", &(p->size[i]), extra);
	p->verts[i] = malloc((p->size[i])*sizeof(int));
	for (j = 0; j < (p->size[i]); j++) {
	  sscanf(extra, "%100c", swap);
	  sscanf(swap, "%d %100c", &(p->verts[i][j]), extra); 
	}
	p->tris += p->size[i] - 2;
  }

  // Set mesh variables accordingly, reset the count, allocate memory

  jm->nvert = num_verts;
  jm->ntri = p->tris;
  jm->triangles = malloc(jm->ntri*3*sizeof(int));

  // Loop through the quads, if the quad is found to have only 3 vertices, then
  // just make a triangle. Otherwise, split the quad into 2 triangles.

  for (i = 0; i < num_faces; i++) {
    for(j = 2; j < p->size[i]; j++) {
	  jm->triangles[tri_count*3+0] = p->verts[i][0];
	  jm->triangles[tri_count*3+1] = p->verts[i][j-1];
	  jm->triangles[tri_count*3+2] = p->verts[i][j];
	  tri_count++;
	}
  }

  // Centroid of the object is calculated

  for (i = 0; i < 3; i++) {
    jm->centroid[i] = (max[i] + min[i])/2;
  }

  // Print useful information

  printf("\nNumber of Vertices: %d\nNumber of Triangles: %d\n", num_verts, 
		  jm->ntri);
  printf("Bounding Box:\n");
  printf("Min (x,y,z): %f, %f, %f \n", min[0], min[1], min[2]);
  printf("Max (x,y,z): %f, %f, %f \n", max[0], max[1], max[2]);
  printf("Centroid: (%f, %f, %f) \n\n", jm->centroid[0], jm->centroid[1], 
		  jm->centroid[2]);

  // Return the number of vertices

  return num_verts;
}
