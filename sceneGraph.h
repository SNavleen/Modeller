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

    //here temporarily
    Node *selectedNode;
	Node *currentNode;

private:
	Node *rootNode;
};

#endif
