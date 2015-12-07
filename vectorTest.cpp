#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "Vector3D.h"


int main(){
  Vector3D origin = Vector3D(0,0,0);
  Vector3D a = Vector3D(1,1,1);
  Vector3D b = Vector3D(2,2,2);

  Vector3D result = a - b;
  printf("a:(%f,%f,%f) b:(%f,%f,%f) (a-b):(%f,%f,%f)\n", a.x,a.y,a.z,  b.x,b.y,b.z,  result.x,result.y,result.z);

  result = origin;
  Vector3D * pa = new Vector3D(1,1,1);
  Vector3D * pb = new Vector3D(2,2,2);
  result = pa - pb;
  printf("a:(%f,%f,%f) b:(%f,%f,%f) (a-b):(%f,%f,%f)\n", pa->x,pa->y,pa->z,  pb->x,pb->y,pb->z,  result.x,result.y,result.z);

  return 0;
}

