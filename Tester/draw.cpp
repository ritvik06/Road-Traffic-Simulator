#include <stdio.h> 
#include <math.h> 
#include <time.h> 
#include <GL/glut.h> 

#define maxWD 640 
#define maxHT 480

void delay(unsigned int mseconds) 
{ 
    clock_t goal = mseconds + clock(); 
    while (goal > clock()) 
        ; 
} 

void myInit(void) 
{ 
    glClearColor(0.0,0.0, 0.0, 0.0); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluOrtho2D(0.0, maxWD, 0.0, maxHT); 
    glClear(GL_COLOR_BUFFER_BIT); 
    glFlush(); 
} 

void drawRect(int x) 
{ 
    glColor3f(0.0f, 1.0f, 0.0f); 
    glBegin(GL_QUADS); 
    glVertex2i(x, 1);
    glVertex2i(x+3,1);
    glVertex2i(x+3, -1);
    glVertex2i(x,-1); 
    glEnd(); 
} 

void translatePoint(int px,int tx) 
{ 
    int fx = px;
  while (1) { 
    glClear(GL_COLOR_BUFFER_BIT); 
  
        update 
        px = px + tx; 
  
        drawRect(px); // drawing the point 
  
        glFlush(); 
        delay(10); 
    } 
} 

void myDisplay(void) 
{
    // translatePoint(100,1);
    drawRect(0);
}

int main(int argc, char** argv) 
{ 
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    glutInitWindowSize(maxWD, maxHT); 
    glutInitWindowPosition(100, 150); 
    glutCreateWindow("Transforming point"); 
    glutDisplayFunc(myDisplay); 
    myInit(); 
    glutMainLoop(); 

}
