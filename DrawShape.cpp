#include <stdio.h>
#include <stdlib.h>

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

#include "DrawShape.h"
#include "Vector3D.h"

using namespace std;

//Constructors
DrawShape::DrawShape(char *modelType, int red, int green, int blue){
    nodeType = model;
    this->modelType = modelType;
    isDrawable = true;
    this->red = (float)red/255;
    this->green = (float)green/255;
    this->blue = (float)blue/255;
}

//Deconstructor
DrawShape::~DrawShape(){
}

//Public function

void DrawShape::drawAxis(){
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);

    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,100,0);

    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,100);
    glEnd();
}

void DrawShape::nodeSpecificCodeDown(){
    glColor3f(this->red,this->green,this->blue);
    material();
    if(modelType == "Cube"){
        drawCube();
    }
    if(modelType == "Sphere"){
        drawSphere();
    }
    if(modelType == "Cone"){
        drawCone();
    }
    if(modelType == "Torus"){
        drawTorus();
    }
    if(modelType == "Teapot"){
        drawTeapot();
    }else if(modelType == "Plane"){
        glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,1,0);
        glVertex3f(0,1,0);
        glEnd();
    }
}
//code where we add what the node will do when moving up the tree
void DrawShape::nodeSpecificCodeUp(){}

void DrawShape::drawWireFrame(){
    /* printf("drawing the wire frame\n"); */
    glColor3f(0.0f,1.0f,0.0f);
    /* printf("going to draw the wireframe of the cube\n"); */
    double minX=-1,minY=-1,minZ=-1;
    double maxX=1,maxY=1,maxZ=1;
    if(modelType=="Cube"){
        minX=-0.5;minY=-0.5;minZ=-0.5;
        maxX=0.5;maxY=0.5;maxZ=0.5;
    }if(modelType == "Teapot"){
        minX=-1.5;minY=-1;minZ=-1;
        maxX=1.5;maxY=1;maxZ=1;
    }else if(modelType == "Cone"){
        minX=-0.5;minY=-0.5;minZ=-0;
        maxX=0.5;maxY=0.5;maxZ=1;
    }else if(modelType == "Torus"){
        minX=-1.2,minY=-1.2,minZ=-0.5;
        maxX=1.2,maxY=1.2,maxZ=0.5;
    }
    // get min value
    Vector3D v1 = Vector3D(maxX,maxY,maxZ);
    Vector3D v2 = Vector3D(maxX,minY,maxZ);
    Vector3D v3 = Vector3D(minX,minY,maxZ);
    Vector3D v4 = Vector3D(minX,maxY,maxZ);
    Vector3D v5 = Vector3D(maxX,maxY,minZ);
    Vector3D v6 = Vector3D(maxX,minY,minZ);
    Vector3D v7 = Vector3D(minX,minY,minZ);
    Vector3D v8 = Vector3D(minX,maxY,minZ);

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glBegin(GL_POLYGON); // begin drawing
    glVertex3f(v1.x,v1.y,v1.z);
    glVertex3f(v2.x,v2.y,v2.z);
    glVertex3f(v3.x,v3.y,v3.z);
    glVertex3f(v4.x,v4.y,v4.z);
    glEnd();

    glBegin(GL_POLYGON); // begin drawing
    glVertex3f(v5.x,v5.y,v5.z);
    glVertex3f(v6.x,v6.y,v6.z);
    glVertex3f(v7.x,v7.y,v7.z);
    glVertex3f(v8.x,v8.y,v8.z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(v1.x,v1.y,v1.z);
    glVertex3f(v5.x,v5.y,v5.z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(v2.x,v2.y,v2.z);
    glVertex3f(v6.x,v6.y,v6.z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(v3.x,v3.y,v3.z);
    glVertex3f(v7.x,v7.y,v7.z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(v4.x,v4.y,v4.z);
    glVertex3f(v8.x,v8.y,v8.z);
    glEnd();

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}
void DrawShape::setLight(int lightX, int lightZ){
    this->lightX = lightX;
    this->lightZ = lightZ;
}
/*DrawShape lighting();*/
void DrawShape::lighting(){
    float amb[4] = {1, 1, 1, 1};
    float diff[4] = {1, 1, 1, 1};
    float spec[4] = {1, 1, 1, 1};
    float light_pos[] = {this->lightX+0,150,this->lightZ+0,1.0};
    float light_pos2[] = {this->lightX+100,150,this->lightZ+100,1.0};


    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glLightf(GL_LIGHT0, GL_SHININESS, 100);

    glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
    glLightf(GL_LIGHT1, GL_SHININESS, 100);
}
void DrawShape::setMaterialValue(int materialValue){
    this->materialValue = materialValue;
}
/*DrawShape material();*/
void DrawShape::material(){
    float mat_ambient[4], mat_diffuse[4], mat_specular[4], shine;

    if(materialValue == 0){
        mat_ambient[0] = this->red+0.0215f;
        mat_ambient[1] = this->green+0.1745f;
        mat_ambient[2] = this->blue+0.0215f;
        mat_ambient[3] = 1.0f;
        mat_diffuse[0] = this->red+0.07568f;
        mat_diffuse[1] = this->green+0.61424f;
        mat_diffuse[2] = this->blue+0.07568f;
        mat_diffuse[3] = 1.0f;
        mat_specular[0] = this->red+0.633f;
        mat_specular[1] = this->green+0.727811f;
        mat_specular[2] = this->blue+0.633f;
        mat_specular[3] = 1.0f;
        shine = 0.6f;
    }else if(materialValue == 9){
        mat_ambient[0] = this->red+0.05375f;
        mat_ambient[1] = this->green+0.05f;
        mat_ambient[2] = this->blue+0.06625f;
        mat_ambient[3] = 1.0f;
        mat_diffuse[0] = this->red+0.18275f;
        mat_diffuse[1] = this->green+0.17f;
        mat_diffuse[2] = this->blue+0.22525f;
        mat_diffuse[3] = 1.0f;
        mat_specular[0] = this->red+0.332741f;
        mat_specular[1] = this->green+0.328634f;
        mat_specular[2] = this->blue+0.346435f;
        mat_specular[3] = 1.0f;
        shine =  0.3f;
    }else if(materialValue == 8){
        mat_ambient[0] = this->red+0.0f;
        mat_ambient[1] = this->green+0.0f;
        mat_ambient[2] = this->blue+0.0f;
        mat_ambient[3] = 1.0f;
        mat_diffuse[0] = this->red+0.5f;
        mat_diffuse[1] = this->green+0.0f;
        mat_diffuse[2] = this->blue+0.0f;
        mat_diffuse[3] = 1.0f;
        mat_specular[0] = this->red+0.7f;
        mat_specular[1] = this->green+0.6f;
        mat_specular[2] = this->blue+0.6f;
        mat_specular[3] = 1.0f;
        shine =  0.25f;
    }else if(materialValue == 7){
        mat_ambient[0] = this->red+0.19225f;
        mat_ambient[1] = this->green+0.19225f;
        mat_ambient[2] = this->blue+0.19225f;
        mat_ambient[3] = 1.0f;
        mat_diffuse[0] = this->red+0.50754f;
        mat_diffuse[1] = this->green+0.50754f;
        mat_diffuse[2] = this->blue+0.50754f;
        mat_diffuse[3] = 1.0f;
        mat_specular[0] = this->red+0.508273f;
        mat_specular[1] = this->green+0.508273f;
        mat_specular[2] = this->blue+0.508273f;
        mat_specular[3] = 1.0f;
        shine =  0.4f;
    }else if(materialValue == 6){
        mat_ambient[0] = this->red+0.05f;
        mat_ambient[1] = this->green+0.05f;
        mat_ambient[2] = this->blue+0.0f;
        mat_ambient[3] = 1.0f;
        mat_diffuse[0] = this->red+0.05f;
        mat_diffuse[1] = this->green+0.05f;
        mat_diffuse[2] = this->blue+0.04f;
        mat_diffuse[3] = 1.0f;
        mat_specular[0] = this->red+0.07f;
        mat_specular[1] = this->green+0.07f;
        mat_specular[2] = this->blue+0.04f;
        mat_specular[3] = 1.0f;
        shine =  0.078125f;
    }




    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}
//Private

/*DrawShape drawCube();*/
void DrawShape::drawCube(){
    glutSolidCube(1);
}
/*DrawShape drawSphere();*/
void DrawShape::drawSphere(){
    glutSolidSphere(1, 10, 10);
}
/*DrawShape drawCone();*/
void DrawShape::drawCone(){
    glutSolidCone(0.5, 1, 20, 1);
}
/*DrawShape drawTorus();*/
void DrawShape::drawTorus(){
    glutSolidTorus(0.25, 1, 40, 40);
}
/*DrawShape drawTeapot();*/
void DrawShape::drawTeapot(){
    glutSolidTeapot(1);
}



//---------------------------------mouse ray intersection stuff--------------------------------------

//function which preforms intersection test
bool sphereIntersection(vector<double> *listOfDoubles, Vector3D rayStart, Vector3D rayEnd){
    /* printf("  2. rayStart:(%f,%f,%f)  rayEnd:(%f,%f,%f)\n",rayStart.x,rayStart.y, rayStart.z,rayEnd.x, rayEnd.y, rayEnd.z); */
    //just to check if it this method works
    double A, B, C;
    double R0x, R0y, R0z;
    double Rdx, Rdy, Rdz;
    R0x = rayStart.x;
    R0y = rayStart.y;
    R0z = rayStart.z;


    Rdx = rayEnd.x - rayStart.x;
    Rdy = rayEnd.y - rayStart.y;
    Rdz = rayEnd.z - rayStart.z;
    /* printf("  2. rdx:%f rdy:%f rdz:%f\n",Rdx,Rdy,Rdz); */

    //magnitude!
    double M = sqrt(Rdx*Rdx + Rdy*Rdy + Rdz* Rdz);

    //unit vector!
    Rdx /= M;
    Rdy /= M;
    Rdz /= M;
    /* printf("  2. unit vector rdx:%f rdy:%f rdz:%f\n",Rdx,Rdy,Rdz); */


    //A = Rd dot Rd
    A = Rdx*Rdx + Rdy*Rdy + Rdz*Rdz;
    /* printf("  2. a) A: %f\n", A); */
    double Btempx, Btempy, Btempz;
    Btempx = R0x;
    Btempy = R0y;
    Btempz = R0z;
    /* printf("  2. b) btempx:%f btempy:%f btempz:%f\n",Btempx, Btempy, Btempz); */
    B = Btempx * Rdx + Btempy * Rdy + Btempz *Rdz;
    B *= 2.0;
    C = R0x*R0x + R0y*R0y + R0z* R0z - 1;
    /* printf("  2. c) B:%f C:%f\n",B,C); */

    double sq = B*B  - 4*A*C;
    double t0 = 0, t1 = 0;
    /* printf("sq: %f\n",sq); */
    if(sq < 0) printf("no Intersection!!!\n");
    else{
        t0 = ((-1) * B + sqrt(sq))/(2*A);
        t1 = ((-1) * B - sqrt(sq))/(2*A);
        listOfDoubles->push_back((t0<t1)? t0:t1);

        printf("Intersection at: t = %f, and t = %f\n", t0, t1);
    }
    // else returns false
    return (sq>=0);
}
bool isPointInsideBoxInPlane(Vector3D point, Vector3D p0, Vector3D p1, Vector3D p2, Vector3D p3){
    /* printf("p0:(%f,%f,%f) p1:(%f,%f,%f) p2:(%f,%f,%f) p3:(%f,%f,%f) point:(%f,%f,%f)\n",p0.x,p0.y,p0.z,  p1.x,p1.y,p1.z,  p2.x,p2.y,p2.z,  p3.x,p3.y,p3.z, point.x,point.y,point.z); */
    Vector3D v0 = p0 - p3;
    Vector3D v1 = p1 - p0;
    Vector3D v2 = p2 - p1;
    Vector3D v3 = p3 - p2;

    //line 1
    /* printf("first, "); */
    Vector3D pToP2 = point -p2;
    double result = v2.dotVector3D(pToP2);
    if(result > 0) return false;

    //line 2
    /* printf("second, "); */
    Vector3D pToP1 = point - p1;
    result = v1.dotVector3D(pToP1);
    if(result > 0) return false;

    //line 3
    /* printf("third, "); */
    Vector3D pToP3 = point - p3;
    result = v3.dotVector3D(pToP3);
    if(result > 0) return false;

    //line 4
    /* printf("fourth, "); */
    Vector3D pToP0 = point - p0;
    result = v0.dotVector3D(pToP0);
    if(result > 0) return false;

    /* printf("done everything, returning true\n"); */
    return true;
}
//function which preforms intersection test
/* bool planeIntersection(vector<double> *listOfDistances, Vector3D rd, Vector3D r0, Vector3D planeNormal, Vector3D *rayStart, Vector3D *rayEnd){ */
bool DrawShape::planeIntersection(vector<Node*> *listOfnodes, vector<double> *listOfDistances, Vector3D p0, Vector3D p1, Vector3D p2, Vector3D p3, Vector3D rayStart, Vector3D rayEnd){
    /* printf(">>>>> testing purposes\n"); */
    /* Vector3D t0 = Vector3D(0,0,0); */
    /* Vector3D t1 = Vector3D(1,0,0); */
    /* Vector3D t2 = Vector3D(1,-1,0); */
    /* Vector3D t3 = Vector3D(0,-1,0); */
    /* Vector3D point= Vector3D(1,1,1); */
    /* printf("checking if the point is inside the box result is %i should be %i \n", isPointInsideBoxInPlane(point, t0,t1,t2,t3), 0); */
    /* printf("checking if the point is inside the box result is %i should be %i \n", isPointInsideBoxInPlane(Vector3D(1,-2,0), t0,t1,t2,t3), 0); */
    /* printf("checking if the point is inside the box result is %i should be %i \n", isPointInsideBoxInPlane(Vector3D(0,0,0), t0,t1,t2,t3), 1); */
    /* printf("checking if the point is inside the box result is %i should be %i \n", isPointInsideBoxInPlane(Vector3D(0.5,-0.5,0), t0,t1,t2,t3), 1); */
    /* printf(">>>>> done testing purposes\n"); */


    // calculate these values
    Vector3D planeNormal = (p1-p0).crossVector3D(p2-p1);
    Vector3D tempVec = (p1-p0).dotVector3D(p2-p1);
    /* printf("p0:(%f,%f,%f), p1:(%f,%f,%f) p2:(%f,%f,%f) p3:(%f,%f,%f)\n", p0.x,p0.y,p0.z, p1.x,p1.y,p1.z, p2.x,p2.y,p2.z, p3.x,p3.y,p3.z ); */
    /* printf("printing the plane normal: (%f,%f,%f)  are (p1-p0).(p2-p1):(%f,%f,%f) \n",planeNormal.x,planeNormal.y,planeNormal.z, tempVec.x,tempVec.y,tempVec.z); */
    Vector3D r0 = rayStart;
    Vector3D rd = rayEnd-rayStart;
    // D = -A*x - B * y - C * z, where (A,B,C) is the normal of the plane
    double D = -1 * p0.x * planeNormal.x - planeNormal.y * p0.y - planeNormal.z * p0.z;
    double denom = planeNormal.dotVector3D(rd); // get the denomenator of the equation
    // may have some double == 0 errors
    if(denom == 0 || fabs(denom) < 0.001){// because the plane is at 90 degrees so there is no intersection
        /* printf("the plane is at 90 degrees with the ray there is not intersection the rd:(%f,%f,%f) normal:(%f,%f,%f) denom is %f \n", rd.x,rd.y,rd.z,  planeNormal.x,planeNormal.y,planeNormal.z  , denom); */
        return false;
    }

    // t = -(N . R0 + D) / (N . Rd);
    double t = (((planeNormal.dotVector3D(r0)) + D) * -1) / (denom);
    Vector3D intersectingPoint = r0 + (rd * t);
    /* printf("checking if the intersection point is on the plane: normal:(%f,%f,%f), intersectingPoint:(%f,%f,%f),  pointOnPlane:(%f,%f,%f), result:%f\n", planeNormal.x,planeNormal.y,planeNormal.z, intersectingPoint.x,intersectingPoint.y,intersectingPoint.z, p1.x,p1.y,p1.z, (planeNormal.dotVector3D(p1-intersectingPoint))); */
    /* printf("the point intersects the plane at (%f,%f,%f), going to the isPointInsideBoxInPlane function\n", intersectingPoint.x, intersectingPoint.y, intersectingPoint.z); */
    if(!isPointInsideBoxInPlane(intersectingPoint, p0,p1,p2,p3)) return false;
    /* printf("going to put t inside the vector %f\n",t); */
    listOfDistances->push_back(t);
    listOfnodes->push_back(this);
    /* printf("done putting t inside vector"); */
    return true; // the plane intersects the ray
}

void DrawShape::rayIntersection(vector<Node*> *listOfnodes, vector<double> *listOfDistances, Vector3D rayStart, Vector3D rayEnd){
    /* printf("calling the stupid plane intersection\n"); */
    /* planeIntersection(listOfDistances, Vector3D(),Vector3D(),Vector3D(),Vector3D(), Vector3D(), Vector3D()); */
    /* printf("done testing the plane intersection \n"); */

    if(modelType =="Plane"){
        Vector3D p0 = Vector3D(0,1,0);
        Vector3D p1 = Vector3D(1,1,0);
        Vector3D p2 = Vector3D(1,0,0);
        Vector3D p3 = Vector3D(0,0,0);
        planeIntersection(listOfnodes, listOfDistances, p0,p1,p2,p3, rayStart, rayEnd);
        return;
    }

    Vector3D rayVector = rayEnd;
    if(modelType=="Sphere"){
        if(sphereIntersection(listOfDistances, rayStart, rayEnd)){
            listOfnodes->push_back(this);;
        }
        return;
    }
    double minX=-1,minY=-1,minZ=-1;
    double maxX=1,maxY=1,maxZ=1;
    if(modelType=="Cube"){
        minX=-0.5;minY=-0.5;minZ=-0.5;
        maxX=0.5;maxY=0.5;maxZ=0.5;
    }else if(modelType == "Teapot"){
        minX=-1.5;minY=-1;minZ=-1;
        maxX=1.5;maxY=1;maxZ=1;
    }else if(modelType == "Cone"){
        minX=-0.5;minY=-0.5;minZ=-0;
        maxX=0.5;maxY=0.5;maxZ=1;
    }else if(modelType == "Torus"){
        minX=-1.2,minY=-1.2,minZ=-0.5;
        maxX=1.2,maxY=1.2,maxZ=0.5;
    }
    // get the vertex values
    Vector3D p0 = Vector3D(maxX,maxY,maxZ);
    Vector3D p1 = Vector3D(maxX,minY,maxZ);
    Vector3D p2 = Vector3D(minX,minY,maxZ);
    Vector3D p3 = Vector3D(minX,maxY,maxZ);
    Vector3D p4 = Vector3D(maxX,maxY,minZ);
    Vector3D p5 = Vector3D(maxX,minY,minZ);
    Vector3D p6 = Vector3D(minX,minY,minZ);
    Vector3D p7 = Vector3D(minX,maxY,minZ);

    /* printf("going to call the plane intersections \n"); */
    /* if(planeIntersection(listOfnodes, listOfDistances, p0,p1,p2,p3, rayStart, rayEnd)) printf("got an intersection front\n"); // front */
    /* if(planeIntersection(listOfnodes, listOfDistances, p4,p5,p6,p7, rayStart, rayEnd)) printf("got an intersection back\n"); // back */
    /* if(planeIntersection(listOfnodes, listOfDistances, p1,p2,p6,p5, rayStart, rayEnd)) printf("got an intersection bottom\n"); // bottom */
    /* if(planeIntersection(listOfnodes, listOfDistances, p0,p3,p7,p4, rayStart, rayEnd)) printf("got an intersection top\n"); // top */
    /* if(planeIntersection(listOfnodes, listOfDistances, p3,p2,p6,p7, rayStart, rayEnd)) printf("got an intersection left\n"); // left */
    /* if(planeIntersection(listOfnodes, listOfDistances, p0,p1,p5,p4, rayStart, rayEnd)) printf("got an intersection right\n"); // right */

    planeIntersection(listOfnodes, listOfDistances, p0,p1,p2,p3, rayStart, rayEnd); // front
    planeIntersection(listOfnodes, listOfDistances, p4,p5,p6,p7, rayStart, rayEnd); // back
    planeIntersection(listOfnodes, listOfDistances, p1,p2,p6,p5, rayStart, rayEnd); // bottom
    planeIntersection(listOfnodes, listOfDistances, p0,p3,p7,p4, rayStart, rayEnd); // top
    planeIntersection(listOfnodes, listOfDistances, p3,p2,p6,p7, rayStart, rayEnd); // left
    planeIntersection(listOfnodes, listOfDistances, p0,p1,p5,p4, rayStart, rayEnd); // right

    /* printf("done calling the plane intersection intersection\n"); */
}

//---------------------------------mouse ray intersection stuff--------------------------------------
