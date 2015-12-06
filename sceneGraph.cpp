#include "sceneGraph.h"
#include "node.h"
#include <stdio.h>

SceneGraph::SceneGraph(){
	rootNode = new Node();
	currentNode = rootNode;
    selectedNode = NULL;
}

//Scene Graph Navigation
//resets the current node to the root of the graph
void SceneGraph::goToRoot(){
	currentNode = rootNode;
}

//moves to a child node i
void SceneGraph::goToChild(int i){
	if (i < currentNode->children->size() && i >= 0)
		currentNode = currentNode->children->at(i);
	else
		printf("child out of range\n");
}

void SceneGraph::goToParent(){
	if (currentNode->parent != 0)
		currentNode = currentNode->parent;
}

//inserts a child node into the current node
void SceneGraph::insertChildNodeHere(Node *node){
	currentNode->children->push_back(node);
}

//deletes the current node, relinking the children as necessary
void SceneGraph::deleteThisNode(){
	//TODO
}

void SceneGraph::selectnodeAtPos(int x, int y){
  // TODO

  // go to the root node


  // go to all the children checking if they had got the collision


  // this is just a temp fix
  printf("going to select the first node \n");
  this->goToRoot();
  this->goToChild(0);
  this->selectCurrentNode();
  printf("done selecting the first node\n");
}

void SceneGraph::selectCurrentNode(){
   selectedNode = currentNode;
}

//draw the scenegraph
void SceneGraph::draw(){
	rootNode->draw();
    /* printf("is selected node null: %i\n",(selectedNode!=NULL)); */
    if(selectedNode != NULL) selectedNode->drawWireFrame();
}
