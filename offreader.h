#ifndef OFFREADER_H
#define OFFREADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h" 
#include "jmesh.h"


/* return value: number of vertices upon success, -1 upon failure*/
int load_off_mesh(FILE *, jmesh *);

#endif
