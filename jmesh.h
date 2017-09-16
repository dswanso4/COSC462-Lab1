#ifndef JMESH_H
#define JMESH_H

#include <stdlib.h>
#include <stdio.h>


typedef struct {
  int nvert;
  int ntri;
  float * vertices;
  float * normals;
  int * triangles;
  float * centroid;
} jmesh;


/* return value: pointer to jmesh upon success, NULL upon failure*/
jmesh * new_jmesh(FILE *);
void free_mesh(jmesh *);

#endif
