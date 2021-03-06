#ifndef __DRAWSHAPE_H__
#define __DRAWSHAPE_H__

#include "node.h"

#ifdef __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/freeglut.h>
#   include <windows.h>
#endif

class DrawShape:public Node{
    public:
        //Constructors
        DrawShape(char *modelType, int red, int green, int blue);

        //Deconstructor
        ~DrawShape();

        //Public variables
        float red, green, blue;
        //Public function
        virtual void nodeSpecificCodeDown();
        void drawAxis();  // draws the axis
        void drawWireFrame(); // this draws the wireframe of the object
        virtual void nodeSpecificCodeUp();
        void drawSelf();
        void lighting();
        void material();
        void setMaterialValue(int materialValue);
        void rayIntersection(vector<Node*> *listOfnodes, vector<double> *listOfDistances, int mx, int my);
        void setLight(int lightX, int lightZ);
        char *modelType;

    private:

        int lightX, lightZ, materialValue;

        void drawCube();
        void drawSphere();
        void drawCone();
        void drawTorus();
        void drawTeapot();
        bool planeIntersection(vector<Node*> *listOfnodes, vector<double> *listOfDistances, Vector3D p0, Vector3D p1, Vector3D p2, Vector3D p3, Vector3D rayStart, Vector3D rayEnd);

};
#endif
