#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int rx1, ry1, rx2, ry2;
//int cx, cy, r;
int sx1, sy1;

float green[3] = {0,1,0};
float red[3]   = {1,0,0};
float white[3] = {1,1,1};

void drawPixel(int x,int y,float r,float g,float b)
{
    glColor3f(r,g,b);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    
}

void getPixelColor(int x,int y,float color[3])
{
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
}

void boundaryFill8(int x,int y,float fillColor[3],float boundaryColor[3])
{
    float current[3];
    getPixelColor(x,y,current);

    if((current[0]!=boundaryColor[0] || current[1]!=boundaryColor[1] || current[2]!=boundaryColor[2]) &&
       (current[0]!=fillColor[0] || current[1]!=fillColor[1] || current[2]!=fillColor[2]))
    {
        drawPixel(x,y,fillColor[0],fillColor[1],fillColor[2]);

        boundaryFill8(x+1,y,fillColor,boundaryColor);
        boundaryFill8(x-1,y,fillColor,boundaryColor);
        boundaryFill8(x,y+1,fillColor,boundaryColor);
        boundaryFill8(x,y-1,fillColor,boundaryColor);
        boundaryFill8(x+1,y+1,fillColor,boundaryColor);
        boundaryFill8(x-1,y-1,fillColor,boundaryColor);
        boundaryFill8(x+1,y-1,fillColor,boundaryColor);
        boundaryFill8(x-1,y+1,fillColor,boundaryColor);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0);
    // Rectangle
    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
        glVertex2i(rx1,ry1);
        glVertex2i(rx2,ry1);
        glVertex2i(rx2,ry2);
        glVertex2i(rx1,ry2);
    glEnd();

    // Circle
    // glBegin(GL_LINE_LOOP);
    // for(int i=0;i<360;i++)
    // {
    //     float angle=i*3.1416/180;
    //     int x=cx+r*cos(angle);
    //     int y=cy+r*sin(angle);
    //     glVertex2i(x,y);
    // }
    // glEnd();

    glFlush();

    boundaryFill8(sx1,sy1,green,white);
    //boundaryFill8(sx2,sy2,red,white);
}

void init()
{
    glClearColor(0,0,0,1);
     gluOrtho2D(0,500,0,500);
}

int main(int argc,char** argv)
{
    cout<<"Enter rectangle coordinates (x1 y1 x2 y2): ";
    cin>>rx1>>ry1>>rx2>>ry2;

    // cout<<"Enter circle center and radius (cx cy r): ";
    // cin>>cx>>cy>>r;

    cout<<"Enter seed point for rectangle fill: ";
    cin>>sx1>>sy1;

    // cout<<"Enter seed point for circle fill: ";
    // cin>>sx2>>sy2;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowSize(500,500);
    glutCreateWindow("Boundary Fill 8 Connected");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
}