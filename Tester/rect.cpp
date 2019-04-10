#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
float aspectRatio=10;
int frame=0;

void rectangle(float x,float y,float w,float h,char colour){
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
              glVertex3f(x,y,-10);
              glVertex3f(x+w,y,-10);
              glVertex3f(x+w,y-h,-10);
              glVertex3f(x,y-h,-10);

  glEnd();	
}

void road(void){
	glColor3f(0.1,0.1,0.1);
	glBegin(GL_QUADS);
	glVertex3f(10,3,-10);
	glVertex3f(-10,3,-10);
	glVertex3f(-10,-3,-10);
	glVertex3f(10,-3,-10);
	glEnd();

}

/* GLUT callback Handlers */
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}  

static void display(void)
{
  fstream file;
  string word;
  float aspectRatio;
  string Display1 = "DisplayInfo.txt";
  file.open(Display1.c_str());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

  float Y_coordinate = 0, X_coordinate = 0, vehicle_length = 0,vehicle_width = 0;   
  char colour = 'W'; 

  file >> word;
  file >> word;
   file >> word;
  // cout << word << endl;

   aspectRatio = (stoi(word))/10;
   // cout << aspectRatio << endl;
  while(file >> word){
      // cout << word << " " << endl;
     if(word=="Time"){
      file >> word;
      // cout << word << endl;
      // cout << word << endl;
      if(stof(word)==frame){
          file >> word;
          if(word=="SIGNAL"){
            file >> word;
            cout << word << endl;
            //add feature for red or green light;
            while(word!="Time"){             
              file >> word;
              if(word=="Vehicle"){
                file >> word;
                file >> word;
                file >> word;
                colour = word.at(0);
                cout << colour << endl;
                file >> word; 
                vehicle_length = stod(word);
                file >> word;
                vehicle_width = stod(word);
                file >> word;
                X_coordinate = stod(word);
                file >> word; 
                Y_coordinate = stod(word);
                // cout << "Print Rectangle" << endl;
                rectangle(X_coordinate ,Y_coordinate ,vehicle_width,vehicle_length,colour);
              }
            }            
          }
      
      }
     }

  }

  road();

  file.close();
  rectangle(-10,0,1,0.1,'W');
  rectangle(-7,0,1,0.1,'W');
  rectangle(-4,0,1,0.1,'W');
  rectangle(-1,0,1,0.1,'W');
  rectangle(2,0,1,0.1,'W');
  rectangle(5,0,1,0.1,'W'); 
  rectangle(8,0,1,0.1,'W');
  rectangle(0,3,0.1,6,'W');
  frame+=1;

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
    // cout << "aspectRatio- " << aspectRatio << endl; 

    glutIdleFunc(idle);

    glClearColor(0,0,0,0);

    glutMainLoop();
    return EXIT_SUCCESS;
}
