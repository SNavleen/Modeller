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
    void resetScene();

    //get the selected node
    void selectnodeAtPos(int x,int y);
    //Scene Graph Draw
    void draw();

    void drawRay();

    void selectFirstnode();
    void useCustomSettings();
    Node* getSelectedNode();
    void addTransformationToCurrentNode(Node * transform);

  private:
    Vector3D * startRayD;
    Vector3D * endRayD;
    Node *rootNode;
    Node *selectedNode;
    Node *transformNode;
    Node *currentNode;
};

#endif
