#include <GL/glut.h>
#include <iostream>
using namespace std;

int x1, y_1, x2, y2;

void bresenham()
{
    int dx = x2 - x1;
    int dy = y2 - y_1;

    int d = 2 * dy - dx;

    int x = x1;
    int y = y_1;

    glBegin(GL_POINTS);

    while (x <= x2)
    {
        glVertex2i(x, y);
        cout << "(" << x << "," << y << ")" << endl;

        if (d < 0)
        {
            d = d + 2 * dy;
        }
        else
        {
            y = y + 1;
            d = d + 2 * (dy - dx);
        }

        x = x + 1;
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    bresenham();

    glFlush();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv)
{
    cout << "Enter starting point (x y): ";
    cin >> x1 >> y_1;

    cout << "Enter ending point (x y): ";
    cin >> x2 >> y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line Drawing Algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}