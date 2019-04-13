#include<iostream>
#include<iterator>
#include<vector>
#include<sstream>
#include<fstream>
#include<stdexcept>
#include<cstdlib>
#include<tuple>
//#include<chrono>
//#include<thread>
#include <unistd.h>
#include <GL/glut.h>
#include <stdlib.h>
#include "Vehicle.hpp"
#include "Screen.hpp"

//using namespace std;
//new coordinates have to be such that pixels work
// X pixels by Y pixels. I am representing the array such that each array box is a square. My sample screen is 30 by 15 .
// X pixels are -1 to 1. Meaning X/20 pixels per 0.1 
// Y pixels are -1 to 1. Meaning Y/20 pixels per 0.1 
// Let us make one square of a size of S pixels. 
// That means length is L X S = SL pixels and breadth of road is B X S = SB pixels.
// Screen_X = SL pixels.
// Screen_Y = SB + Y_Buffer;
float Square_Size = 50; //S
float Screen_X = 0;
float Screen_Y = 0;
float Y_Buffer = 200; // Buffer Pixels for Displaying extra stuff like grass stats or whatever.    
// Length Scaler is 2/L and Breadth Scaler is 2/(B + Y_Buffer/S)
float Length_Scaler = 0, Breadth_Scaler = 0;
float X_Scaler = 0, Y_Scaler = 0;
vector<Screen> ScreenFrame;
int Frame = 0;

void Simulation()
{   
    Vehicle car("car",0,0,0,0,0,0,0,0);
    Vehicle bike("bike",0,0,0,0,0,0,0,0);
    Vehicle truck("truck",0,0,0,0,0,0,0,0);
    Vehicle bus("BUS",0,0,0,0,0,0,0,0);
    Vehicle autorickshaw("autorickshaw",0,0,0,0,0,0,0,0);
    
    fstream road_file,vehicle_file,simulation_file;
    string Road = "RoadInfo.txt";
    string Vehicle = "VehicleInfo.txt";
    string Simulation = "SimulationInfo.txt";

    string word="";

    road_file.open(Road.c_str());
    vehicle_file.open(Vehicle.c_str());
    simulation_file.open(Simulation.c_str());

    float length = 0,width = 0,signal_loc = 0;
    int SimulationID = 0;
    double max_vel = 0,max_acc = 0; 
    string vehicle_name = "";
    double Y_coordinate = 0, X_coordinate = 0, vehicle_length = 0,vehicle_width = 0,vehicle_vel = 0,vehicle_acc = 0;
    //int TimeIndex = 0;    
    
    Screen screen(0,0,0);
    string line = "";
  
    while(road_file >> word)
    {
        if(word=="Road_Length")
        {
            road_file >> word;
            length = stod(word);
        }

        if(word=="Road_Width")
        {
            road_file >> word;
            width = stod(word);
        }
        
        if(word=="Road_Signal")
        {
            road_file >> word;
            signal_loc = stod(word);
        }
    }

    Screen_X = Square_Size * length;
    Screen_Y = Square_Size * width + Y_Buffer;
    Length_Scaler = 2*Square_Size/Screen_X;
    Breadth_Scaler = 2*Square_Size/Screen_Y;
    X_Scaler = length/2;
    Y_Scaler = width/2;

    while(getline (vehicle_file,line))
    {

        stringstream ss(line);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> result (begin, end);
        
        if(result[0]=="MaxValues")
        {
            vehicle_vel = stod(result[1]);  
            vehicle_acc = stod(result[2]); 
        }
        else 
        {
            vehicle_name = result[0];
            vehicle_length = stod(result[2]);
            vehicle_width = stod(result[4]);
            vehicle_vel = stod(result[6]);
            vehicle_acc = stod(result[8]);
        
            if(vehicle_name=="Car")
            {
                X_coordinate = -1*vehicle_length;
                Y_coordinate = rand() % (int)(width-vehicle_width+1);
                car.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,X_coordinate,Y_coordinate);
            }
            else if(vehicle_name=="bike")
            {
                X_coordinate = -1*vehicle_length;
                Y_coordinate = rand() % (int)(width-vehicle_width+1);
                bike.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,X_coordinate,Y_coordinate);
            }
            else if(vehicle_name=="Truck")
            {
                X_coordinate = -1*vehicle_length;
                Y_coordinate = rand() % (int)(width-vehicle_width+1);
                truck.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,X_coordinate,Y_coordinate);
            }
            else if(vehicle_name=="Bus")
            {
                X_coordinate = -1*vehicle_length;
                Y_coordinate = rand() % (int)(width-vehicle_width+1);
                bus.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,X_coordinate,Y_coordinate);
            }
            else if(vehicle_name=="Auto")
            {
                X_coordinate = -1*vehicle_length;
                Y_coordinate = rand() % (int)(width-vehicle_width+1);
                autorickshaw.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,X_coordinate,Y_coordinate);
            }
        }
    }        
    
    while(getline (simulation_file,line))
    {
        
        stringstream ss(line);
        istream_iterator<std::string> begin(ss);
        istream_iterator<std::string> end;
        vector<string> result (begin, end);
        
        string color = "";
        int time = -1;
        if(result[0]=="ID")
        {
            SimulationID = stoi(result[1]);
        }

        else if(result[0]=="START")
        {
            cout <<"Starting Simulation #"<< SimulationID <<endl; 
            screen = Screen(length,width,signal_loc);              
        
        }
        else if(result[0]=="Signal")
        {
           color = result[1]; 
           screen.setSignal(color);
           cout <<"Signal changed to  "<< color <<endl; 
           screen.RunFor(1);
           ScreenFrame.push_back(screen);
           //TimeIndex++;
                  
        }
        else if(result[0]=="CAR")
        {
           color = result[1]; 
           car.setColor(color);
           double l=0,b=0;
           tie(l,b) = car.dimensions;
           car.setCoordinates(-1*l,rand() % (int)(width-b+1));
           screen.addVehicle(car);
           cout <<"A " << color <<" car is added."<<endl; 
           screen.RunFor(1);
           ScreenFrame.push_back(screen);
           //ScreenFrame[TimeIndex] = screen;
           //TimeIndex++;
        }
        else if(result[0]=="BIKE")
        {
           color = result[1]; 
           bike.setColor(color);
           double l=0,b=0;
           tie(l,b) = bike.dimensions;
           bike.setCoordinates(-1*l,rand() % (int)(width-b+1));
           screen.addVehicle(bike);
           cout <<"A " << color <<" bike is added."<<endl; 
           screen.RunFor(1);
           ScreenFrame.push_back(screen);
           //ScreenFrame[TimeIndex] = screen;
           //TimeIndex++;
        }
        else if(result[0]=="BUS")
        {
           color = result[1]; 
           bus.setColor(color);
           double l=0,b=0;
           tie(l,b) = bus.dimensions;
           bus.setCoordinates(-1*l,rand() % (int)(width-b+1));
           screen.addVehicle(bus);
           cout <<"A " << color <<" bus is added."<<endl; 
           screen.RunFor(1);
           ScreenFrame.push_back(screen);
           //ScreenFrame[TimeIndex] = screen;
           //TimeIndex++;
        }
        else if(result[0]=="TRUCK")
        {
           color = result[1]; 
           truck.setColor(color);
           double l=0,b=0;
           tie(l,b) = truck.dimensions;
           truck.setCoordinates(-1*l,rand() % (int)(width-b+1));
           screen.addVehicle(truck);
           cout <<"A " << color <<" truck is added."<<endl;
           screen.RunFor(1);
           ScreenFrame.push_back(screen);
           //ScreenFrame[TimeIndex] = screen;
           //TimeIndex++;
        }
        else if(result[0]=="AUTO")
        {
           color = result[1]; 
           autorickshaw.setColor(color);
           double l=0,b=0;
           tie(l,b) = autorickshaw.dimensions;
           autorickshaw.setCoordinates(-1*l,rand() % (int)(width-b+1));
           screen.addVehicle(autorickshaw);
           cout <<"A " << color <<" auto-rickshaw is added."<<endl; 
           screen.RunFor(1);
           ScreenFrame.push_back(screen);
           //ScreenFrame[TimeIndex] = screen;
           //TimeIndex++;
        }
        else if(result[0]=="PASS")
        {
            time = stod(result[1]);
            while(time>0)
            {
                screen.RunFor(1);
                ScreenFrame.push_back(screen);
                //ScreenFrame[TimeIndex] = screen;
                //TimeIndex++;
                time--;
            }                       
        }
        else if(result[0]=="END")
        {
            while(!screen.isEmpty())
            {
                screen.RunFor(1);
                ScreenFrame.push_back(screen);
                //ScreenFrame[TimeIndex] = screen;
                //TimeIndex++;
            }
            cout <<"Simulation #"<< SimulationID << " has ended." << endl;                       
        }
    }
    road_file.close();
    vehicle_file.close();
    simulation_file.close();

    //exit(0);
}

void RectangleTL(float X,float Y,float L,float B,char colour)
{
	// (X,Y) is Center Coordinate. L = Length ; B = Breadth The remaining coordinates are (X+L/2,Y), (X+L/2,Y-B/2) (X,Y-B/2)
    // Length Scaler and Breadth Scaler Automatically fixes the coordinates and scales everything correctly.
    switch(colour)
    {
        case 'G': glColor3f(0.0,1.0,0.0); //Green
        break;
        case 'R': glColor3f(1.0,0.0,0.0); //Red
        break;
        case 'B': glColor3f(0.0,0.0,1.0); //Blue
        break;
        case 'W': glColor3f(1.0,1.0,1.0); //White
        break;
        case 'Y': glColor3f(1.0,1.0,0.0); //Yellow
        break;
        case 'M': glColor3f(1.0,0.0,1.0); //Magenta
        break;
        case 'P': glColor3f(1.0,0.0,0.5); //Pink
        break;
        case 'g': glColor3f(0.15,0.15,0.15); //grey
        break;

        default: glColor3f(0.0,1.0,1.0); //Aqua
	}
    //cout << X << Y << L << B <<endl;
    
    //X = (X-X_Scaler)*Length_Scaler;
    //Y = (Y-Y_Scaler)*Breadth_Scaler;
    //L = L*Length_Scaler;
    //B = B*Breadth_Scaler;
    //cout << X << Y << L << B <<endl;
    glBegin(GL_QUADS);
    /*    glVertex2f(X-L/2,Y+B/2); // Top Left
        glVertex2f(X+L/2,Y+B/2); // Top Right 
        glVertex2f(X+L/2,Y-B/2); // Bottom Right
        glVertex2f(X-L/2,Y-B/2); // Bottom Left */
        glVertex2f(X,Y); // Top Left
        glVertex2f(X+L,Y); // Top Right 
        glVertex2f(X+L,Y-B); // Bottom Right
        glVertex2f(X,Y-B); // Bottom Left
    glEnd();	
}

/*void Scaled_Rectangle(float X,float Y,float L,float B,char colour)
{
    X = (X-X_Scaler)*Length_Scaler;
    Y = (Y-Y_Scaler)*Breadth_Scaler;
    L = L*Length_Scaler;
    B = B*Breadth_Scaler;
    //Rectangle(X,Y,L,B,colour);
}*/

void Scaled_RectangleTL(float X,float Y,float L,float B,char colour)
{
	// (X,Y) is Top Left Coordinate. L = Length ; B = Breadth The remaining coordinates are (X+L,Y), (X+L,Y-B) (X,Y-B) Center Coordinate is (X+L/2, Y-B/2).
    X = (X-X_Scaler)*Length_Scaler;
    Y = (Y-Y_Scaler)*(-1*Breadth_Scaler);
    L = L*Length_Scaler;
    B = B*Breadth_Scaler;
    RectangleTL(X,Y,L,B,colour);	
}

/* GLUT callback Handlers */
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void LoadCurrentFrame(int Frame)
{
    //using namespace std;
    Screen screen = ScreenFrame.at(Frame);
    float length, width, position,t;
    string Signal = "";
    tie(length,width,position,Signal,t) = screen.ScreenInfo();
    //cout << length << width << endl;
    /*Length_Scaler = 2/length;
    Breadth_Scaler = -1.5/width;
    X_Scaler = length/2;
    Y_Scaler = width/2;*/
    //Loading Road Configuration    
    Scaled_RectangleTL(0,0,length,width,'g'); // Load Road
    Scaled_RectangleTL(position,0,1,width,'W');    // Load Signal Line
    Scaled_RectangleTL(position,-1,1,1,Signal[0]); // Load Signal Color
    
    vector<Vehicle> Vehicles = screen.Vehicles();
    for (int i = 0; i < Vehicles.size(); i++)
        {
            double x,y,l,b;
            Vehicle curr = Vehicles[i];
            tie(l,b) = curr.getDimensions();
            tie(x,y) = curr.getLocation();
            string Color = curr.getColor();
            Scaled_RectangleTL(round(x),y,0.9*l,0.8*b,Color[0]); //Load Vehicles
        }
    //using namespace std::chrono_literals; 
    //std::this_thread::sleep_for(0.1s);
    usleep(80000);
    
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    LoadCurrentFrame(Frame);
    Frame++;
    Frame = (Frame<ScreenFrame.size()) ? Frame : 0;
    glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
    //System::Threading::Thread::Sleep(100);
}

/* Program entry point */
int main(int argc, char *argv[])
{
    Simulation();
    //float Aspect_Ratio = Screen_X/Screen_Y;
    glutInit(&argc, argv);
    glutInitWindowSize(Screen_X,Screen_Y);
    glutInitWindowPosition(0,0);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Road Traffic Simulation");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glClearColor(0,0,0,0);

    glutMainLoop();

    return EXIT_SUCCESS;
}