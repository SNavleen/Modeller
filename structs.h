#ifndef __STRUCTS_H__	//guard against cyclic dependancy
#define __STRUCTS_H__

typedef struct{
  double x, y, z;
  void addProduct(Vector3D other){ x+= other.x; y+=other.y; z+=other.z;}
  int dotProduct(Vector3D other){ return x*other.x + y * other.y + z * other.z; }
  void multiplyScaler(double scalerValue){ x = scalerValue * x; y = scalerValue * y; z = scalerValue * z; }
  void divideScaler(double scalerValue){ x/= scalerValue; y/=scalerValue; z/=scalerValue;}
  void addScaler(double scalerValue){ x+= scalerValue; y+=scalerValue; z+=scalerValue;}
  void addScaler(double scalerValue){ x-= scalerValue; y-=scalerValue; z-=scalerValue;}
}Vector3D;


typedef struct{
  float x, y, z, w;
}Vector4D;
#endif
