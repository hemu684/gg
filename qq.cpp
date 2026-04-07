#include <GL/glut.h>
#include <iostream>
using namespace std;

float hx1, hy1, hx2, hy2;
float dx1, dy1, dx2, dy2;
float tx, ty;

void drawHouse(float x1,float y1,float x2,float y2)
{
    // house
    glBegin(GL_LINE_LOOP);
        glVertex2f(x1,y1);
        glVertex2f(x2,y1);
        glVertex2f(x2,y2);
        glVertex2f(x1,y2);
    glEnd();

    // roof
    float midx = (x1+x2)/2;

    glBegin(GL_LINE_LOOP);
        glVertex2f(x1,y2);
        glVertex2f(x2,y2);
        glVertex2f(midx,y2+3);
    glEnd();
}

void drawDoor(float x1,float y1,float x2,float y2)
{
    glBegin(GL_LINE_LOOP);
        glVertex2f(x1,y1);
        glVertex2f(x2,y1);
        glVertex2f(x2,y2);
        glVertex2f(x1,y2);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // -------- ORIGINAL --------
    glColor3f(1,1,1);

    drawHouse(hx1,hy1,hx2,hy2);
    drawDoor(dx1,dy1,dx2,dy2);

    // -------- TRANSFORMED --------
    glColor3f(0,1,0);

    float newhx1 = hx1 + tx;
    float newhx2 = hx2 + tx;

    float newhy1 = hy1 + ty;
    float newhy2 = hy2 + ty;

    drawHouse(newhx1,newhy1,newhx2,newhy2);

    // ---- CENTER DOOR ----
    float houseWidth = hx2 - hx1;
    float doorWidth = dx2 - dx1;
    float doorHeight = dy2 - dy1;

    float centerX = newhx1 + (houseWidth - doorWidth)/2;
    float doorY = newhy1;

    drawDoor(centerX,doorY,centerX+doorWidth,doorY+doorHeight);

    glFlush();
}

void init()
{
    glClearColor(0,0,0,1);
    gluOrtho2D(-10,25,-10,20);
}

int main(int argc,char** argv)
{
    cout<<"Enter house bottom-left (x y): ";
    cin>>hx1>>hy1;

    cout<<"Enter house top-right (x y): ";
    cin>>hx2>>hy2;

    cout<<"Enter door bottom-left (x y): ";
    cin>>dx1>>dy1;

    cout<<"Enter door top-right (x y): ";
    cin>>dx2>>dy2;

    cout<<"Enter translation (tx ty): ";
    cin>>tx>>ty;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(700,600);
    glutCreateWindow("House Transformation");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}