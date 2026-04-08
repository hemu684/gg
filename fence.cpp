#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
}

void drawLineDDA(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++)
    {
        glVertex2i(round(x), round(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
}

void plotCirclePoints(int cx, int cy, int x, int y)
{
    glVertex2i(cx + x, cy + y);
    glVertex2i(cx - x, cy + y);
    glVertex2i(cx + x, cy - y);
    glVertex2i(cx - x, cy - y);
    glVertex2i(cx + y, cy + x);
    glVertex2i(cx - y, cy + x);
    glVertex2i(cx + y, cy - x);
    glVertex2i(cx - y, cy - x);
}

void drawSun(int cx, int cy, int r)
{
    int x = 0;
    int y = r;
    int p = 1 - r;

    glBegin(GL_POINTS);

    while (x <= y)
    {
        plotCirclePoints(cx, cy, x, y);

        x++;

        if (p < 0)
        {
            p = p + 2 * x + 1;
        }
        else
        {
            y--;
            p = p + 2 * (x - y) + 1;
        }
    }

    glEnd();

    drawLineDDA(cx + r, cy, cx + r + 30, cy);
    drawLineDDA(cx - r, cy, cx - r - 30, cy);
    drawLineDDA(cx, cy + r, cx, cy + r + 30);
    drawLineDDA(cx, cy - r, cx, cy - r - 30);
}

void drawHouse(int xBase)
{
    int ground = -50;
    int height = 120;
    int width = 120;

    // House body
    drawLineDDA(xBase, ground, xBase + width, ground);
    drawLineDDA(xBase + width, ground, xBase + width, ground + height);
    drawLineDDA(xBase + width, ground + height, xBase, ground + height);
    drawLineDDA(xBase, ground + height, xBase, ground);

    // Roof
    drawLineDDA(xBase - 20, ground + height,
                xBase + width / 2, ground + height + 60);

    drawLineDDA(xBase + width / 2, ground + height + 60,
                xBase + width + 20, ground + height);
}

void drawFence()
{
    int bottom = -100;
    int top = -50;

    for (int i = -380; i <= 380; i += 40)
    {
        drawLineDDA(i, bottom, i, top);
    }

    drawLineDDA(-380, bottom, 380, bottom);
    drawLineDDA(-380, top, 380, top);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.2, 0.4, 0.4);
    glPointSize(2.0);

    drawSun(300, 200, 50);

    drawLineDDA(-400, -50, 400, -50);

    drawHouse(-320);
    drawHouse(-60);
    drawHouse(200);

    drawFence();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);

    glutCreateWindow("DDA Line Example");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}