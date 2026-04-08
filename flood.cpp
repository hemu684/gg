#include <GL/glut.h>
#include <iostream>

int screenWidth = 500, screenHeight = 500;


void getPixelColor(int x, int y, float color[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}


void setPixelColor(int x, int y, float color[3]) {
    glColor3fv(color);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}


void floodFill(int x, int y, float oldColor[3], float newColor[3]) {
    float color[3];
    getPixelColor(x, y, color);

    
    if (color[0] == oldColor[0] && color[1] == oldColor[1] && color[2] == oldColor[2]) {
        setPixelColor(x, y, newColor);

        floodFill(x + 1, y, oldColor, newColor);
        floodFill(x - 1, y, oldColor, newColor);
        floodFill(x, y + 1, oldColor, newColor);
        floodFill(x, y - 1, oldColor, newColor);
    }
}


void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      
        int oglY = screenHeight - y;

        float oldColor[3];
        getPixelColor(x, oglY, oldColor);

        float newColor[3] = {1.0, 0.0, 0.0}; 

        floodFill(x, oglY, oldColor, newColor);
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    
    glColor3f(0.0, 1.0, 0.0); 
    glBegin(GL_POLYGON);
        glVertex2i(100, 100);
        glVertex2i(400, 100);
        glVertex2i(400, 400);
        glVertex2i(100, 400);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Flood Fill Algorithm");

    glClearColor(1.0, 1.0, 1.0, 1.0); 
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, screenWidth, 0, screenHeight);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}