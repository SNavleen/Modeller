#ifndef __SCENEGRAPH_H__	//guard against cyclic dependancy
#define __SCENEGRAPH_H__

#include "node.h"
#include "nodeTransform.h"
#include <iostream>
#include <fstream>


class SceneGraph{
  public:
    SceneGraph();	//constructor

    //Scene Graph Navigation
    void goToRoot();
    void goToChild(int i);
    void goToMaxChild();
    void goToParent();
    void insertChildNodeHere(Node *node);
    void deleteThisNode();
    void resetScene();
    void saveFile(ofstream *sceneFile);
    void loadFile(ifstream *sceneFile);

    //get the selected node
    void selectnodeAtPos(int x,int y);
    //Scene Graph Draw
    void draw();

    void drawRay();

    void selectFirstnode();
    void useCustomSettings();
    bool isSelectednodeNull();
    void printScene();
    Node* getSelectedNode();
    void addTransformationToCurrentNode(char *transformation, Node * transform);
    void insertDefaultTransformations(NodeTransform *rotate, NodeTransform *translate, NodeTransform *scale);

  private:
    Vector3D * startRayD;
    Vector3D * endRayD;
    Node *rootNode;
    Node *selectedNode;
    Node *transformNode;
    Node *currentNode;

    double oldMat[16];

    void printModelMatrix();
    void printScene(Node *curNode, int depth);
};

#endif
