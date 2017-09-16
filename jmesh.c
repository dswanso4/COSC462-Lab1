#include "jmesh.h"
#include "offreader.h"

// Allocate memory for a mesh and then load the mesh. Return the mesh if valid.

jmesh * new_jmesh(FILE * fp) {
   jmesh * jm;

   jm = malloc(sizeof(jmesh));
	
   load_off_mesh(fp, jm);

   return jm;
}

// Clear the mesh information

void free_jmesh(jmesh * jm) {
  int d = 3;
  int i;
  for (i = 0; i < jm->nvert; i++) {
    jm->vertices[i*d+0] = 0.0;
	jm->vertices[i*d+1] = 0.0;
	jm->vertices[i*d+2] = 0.0;
  }
  for (i = 0; i < jm->ntri; i++) {
	jm->triangles[i*d+0] = 0;
	jm->triangles[i*d+1] = 0;
	jm->triangles[i*d+1] = 0;
  }
  for (i = 0; i < 3; i++) {
    jm->centroid[i] = 0.0;
  }
  jm->nvert = 0;
  jm->ntri = 0;

}
