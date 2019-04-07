#include <GL/glut.h>
#include <stdlib.h>

float location1 = 10;
float location2 = 10;

void rectangle(int x,int y,float w,float h,char colour){
	switch(colour){
              case 'G': glColor3f(0.0,1.0,0.0);
	      break;
	      case 'R': glColor3f(1.0,0.0,0.0);
	      break;
	      case 'B': glColor3f(0.0,0.0,1.0);
	      break;
	      default: glColor3f(1.0,1.0,1.0);
	}

          glBegin(GL_QUADS);
              glVertex3f(x,y+h,-10);
              glVertex3f(x+w,y+h,-10);
              glVertex3f(x+w,y,-10);
              glVertex3f(x,y,-10);

  glEnd();	
}

void road(void){
	glColor3f(0.1,0.1,0.1);
	glBegin(GL_QUADS);
	glVertex3f(0,6,-10);
	glVertex3f(20,6,-10);
	glVertex3f(20,0,-10);
	glVertex3f(0,0,-10);
	glEnd();

}

/* GLUT callback Handlers */
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, 0.0, height, -50.0, 50.0);
    glFrustum(0, 2*ar, 0.0, 2.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    road();
    rectangle(location1,2,4,1,'G');
    location1 = location1+0.08;
    rectangle(location2,4,8,1,'R');  
    location2 = location2+0.05;
   //rectangle(-10,0,1,0.1,'W');
  //rectangle(-7,0,1,0.1,'W');
//rectangle(-4,0,1,0.1,'W');
//rectangle(-1,0,1,0.1,'W');
//rectangle(2,0,1,0.1,'W');
//rectangle(5,0,1,0.1,'W'); 
//rectangle(8,0,1,0.1,'W');
//rectangle(0,3,0.1,6,'W');
 
   glutSwapBuffers();
}



static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT quadPoly");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glClearColor(0,0,0,0);

    glutMainLoop();

    return EXIT_SUCCESS;
}
