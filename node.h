#ifndef __NODE_H__	//guard against cyclic dependancy
#define __NODE_H__

//Node Class.
//should act as a template class for other sub-types of
//Nodes
#include "Vector3D.h"
#include <vector>
using namespace std;

extern int getID();

//if you add more derived classes
//add the types here
enum NodeType{
  root,
  group,
  transformation,
  model
};

class Node{
  public:
    Node();	//constructor
    ~Node();	//constructor

    NodeType nodeType;
    bool isDrawable;
    int ID;
    vector<Node*> *children;
    Node* parent;
    int currentChild;
    bool isSelected;

    void draw();
    virtual void drawSelf();
    virtual void drawWireFrame();
    virtual void nodeSpecificCodeDown();
    virtual void nodeSpecificCodeUp();
    virtual void rayIntersection(vector<Node*> *listOfnodes, vector<double> *listOfDistances,int mx,int my);
};

#endif
