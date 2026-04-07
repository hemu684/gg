#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int a, b;   // ellipse radii

void init()
{
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500,500,-500,500);
}

void plotPoint(int x,int y)
{
    cout<<"("<<x<<","<<y<<")"<<endl;

    glBegin(GL_POINTS);
        glVertex2i(x,y);
        glVertex2i(-x,y);
        glVertex2i(x,-y);
        glVertex2i(-x,-y);
    glEnd();
}

void ellipse(int a,int b)
{
    int x=0;
    int y=b;

    float p1;

    plotPoint(x,y);

    p1 = b*b - a*a*b + (a*a)/4;

    while(2*b*b*x <= 2*a*a*y)
    {
        if(p1 < 0)
        {
            x++;
            plotPoint(x,y);
            p1 = p1 + 2*b*b*x + b*b;
        }
        else
        {
            x++;
            y--;
            plotPoint(x,y);
            p1 = p1 + 2*b*b*x - 2*a*a*y + b*b;
        }
    }

    float p2 = b*b*(x+0.5)*(x+0.5) + a*a*(y-1)*(y-1) - a*a*b*b;

    while(y > 0)
    {
        if(p2 < 0)
        {
            x++;
            y--;
            plotPoint(x,y);
            p2 = p2 + 2*b*b*x - 2*a*a*y + a*a;
        }
        else
        {
            y--;
            plotPoint(x,y);
            p2 = p2 - 2*a*a*y + a*a;
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.4,0.8,0.4);
    glPointSize(2.0);

    ellipse(a,b);

    glFlush();
}

int main(int argc,char** argv)
{
    cout<<"Enter semi-major axis (a): ";
    cin>>a;

    cout<<"Enter semi-minor axis (b): ";
    cin>>b;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("Midpoint Ellipse");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}