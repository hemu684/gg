#include<GL/glut.h>
#include<iostream>
#include<vector>
using namespace std;

int xc, yc, r;




void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void plotCirclePoints(int xc, int yc, int x, int y){

    cout << "(" << xc + x << ", " << yc + y << ")\n";
    cout << "(" << xc - x << ", " << yc + y << ")\n";
    cout << "(" << xc + x << ", " << yc - y << ")\n";
    cout << "(" << xc - x << ", " << yc - y << ")\n";
    cout << "(" << xc + y << ", " << yc + x << ")\n";
    cout << "(" << xc - y << ", " << yc + x << ")\n";
    cout << "(" << xc + y << ", " << yc - x << ")\n";
    cout << "(" << xc - y << ", " << yc - x << ")\n";


    drawPixel(xc + x, yc + y);
    drawPixel(xc - x, yc + y);
    drawPixel(xc + x, yc - y);
    drawPixel(xc - x, yc - y);
    drawPixel(xc + y, yc + x);
    drawPixel(xc - y, yc + x);
    drawPixel(xc + y, yc - x);
    drawPixel(xc - y, yc - x);
}

void midPointCirclr(){
     int x = 0 ;
     int y = r;
     int p = 1 - r;

     plotCirclePoints(xc, yc, x, y);

     while( x < y){
         x++;
         if(p < 0){
                p = p + 2*x + 1;
         }
         else{
             y--;
             p = p + 2*x - 2*y + 1;
         }
            plotCirclePoints(xc, yc, x, y);
     }
     
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(2.0);

    midPointCirclr();
    glutSwapBuffers();   
    glFlush();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);

    gluOrtho2D(-10, 10, -10, 10);
}
int main(int argc, char**argv){
    cout << "Enter the center of circle (xc, yc) : ";
    cin >> xc  >> yc;
    cout << "Enter the radius of circle : ";
    cin >> r;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);

    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mid Point circle drawing");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    
}