#ifndef __SCENEGRAPH_H__	//guard against cyclic dependancy
#define __SCENEGRAPH_H__

#include "node.h"

class SceneGraph{
  public:
    SceneGraph();	//constructor

    //Scene Graph Navigation
    void goToRoot();
    void goToChild(int i);
    void goToParent();
    void insertChildNodeHere(Node *node);
    void deleteThisNode();

    //get the selected node
    void selectnodeAtPos(int x,int y);
    //Scene Graph Draw
    void draw();

    void drawRay();

    void selectFirstnode();
    void useCustomSettings();
    Node* getSelectedNode();


  private:
    Vector3D * startRayD;
    Vector3D * endRayD;
    Node *rootNode;
    Node *selectedNode;
    Node *currentNode;
};

#endif
