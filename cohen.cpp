#include <GL/glut.h>
#include <iostream>
using namespace std;

float xmin=100, ymin=100, xmax=300, ymax=300;
float x1,y_1,x2,y2;

const int INSIDE = 0;
const int LEFT   = 1;
const int RIGHT  = 2;
const int BOTTOM = 4;
const int TOP    = 8;

int computeCode(float x, float y)
{
    int code = INSIDE;

    if(x < xmin) code |= LEFT;
    else if(x > xmax) code |= RIGHT;

    if(y < ymin) code |= BOTTOM;
    else if(y > ymax) code |= TOP;

    return code;
}

void cohenSutherlandClip()
{
    float x,y;

    int code1 = computeCode(x1,y_1);
    int code2 = computeCode(x2,y2);

    bool accept = false;

    while(true)
    {
        if((code1 | code2) == 0)
        {
            accept = true;
            break;
        }
        else if(code1 & code2)
        {
            break;
        }
        else
        {
            int code_out = code1 ? code1 : code2;

            if(code_out & TOP)
            {
                x = x1 + (x2-x1)*(ymax-y_1)/(y2-y_1);
                y = ymax;
            }
            else if(code_out & BOTTOM)
            {
                x = x1 + (x2-x1)*(ymin-y_1)/(y2-y_1);
                y = ymin;
            }
            else if(code_out & RIGHT)
            {
                y = y_1 + (y2-y_1)*(xmax-x1)/(x2-x1);
                x = xmax;
            }
            else if(code_out & LEFT)
            {
                y = y_1 + (y2-y_1)*(xmin-x1)/(x2-x1);
                x = xmin;
            }

            if(code_out == code1)
            {
                x1 = x;
                y_1 = y;
                code1 = computeCode(x1,y_1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2,y2);
            }
        }
    }

    if(accept)
    {
        glColor3f(1,0,0);
        glBegin(GL_LINES);
            glVertex2f(x1,y_1);
            glVertex2f(x2,y2);
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Clipping window
    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymax);
        glVertex2f(xmin,ymax);
    glEnd();

    // Original line
    glColor3f(0,1,0);
    glBegin(GL_LINES);
        glVertex2f(x1,y_1);
        glVertex2f(x2,y2);
    glEnd();

    // Clipped line
    cohenSutherlandClip();

    glFlush();
}

void init()
{
    glClearColor(0,0,0,1);
    gluOrtho2D(0,400,0,400);
}

int main(int argc,char** argv)
{
    cout<<"Enter line coordinates (x1 y1 x2 y2): ";
    cin>>x1>>y_1>>x2>>y2;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(500,500);
    glutCreateWindow("Cohen-Sutherland Line Clipping");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}