/**
*class MyMesh header file
*@author LigangChen
*@version 0.1 2007/02/04
*/

#include "global.h"

MyMesh       mesh;
UserDensity  user_density;

int smooth_time = 0;

EPropHandleT<EdgeType>         edge_type;
VPropHandleT<NodeTypeInfo>     node_type; // have used traits as static configuration

