#include<iostream>
#include<vector>
#include<cmath>
#include<sstream>
#include<fstream>
#include<stdexcept>
#include<chrono>
#include<cstdlib>
#include<tuple>
#include "Entity.cpp"

using namespace std;
class Vehicle : public Entity
{
    
    private:
    tuple<double, double> velocity;
    tuple<double, double> acceleration;
     
    public:
    Vehicle(string vehicle_type,double length, double breadth, double Vx, double Vy, double Ax, double Ay, double x, double y)
        :Entity(length, breadth,x,y,vehicle_type[0])
    {   
        velocity = make_tuple(Vx,Vy);
        acceleration = make_tuple(Ax,Ay);
    }

    tuple<double,double> getVelocity()
     {
         return velocity;
     }
    
     tuple<double,double> getAcceleration()
     {
         return acceleration;
     }

     void moveByStep(double t)
     {
         double x , y, Vx, Vy, Ax, Ay; 
         tie(x,y) = getLocation();
         tie(Vx,Vy) = velocity;
         tie(Ax,Ay) = acceleration;
         setLocation(make_tuple(x+Vx*t+Ax*t*t/2,y+Vy*t+Ay*t*t/2));
         velocity = make_tuple(Vx+Ax*t, Vy+Ay*t);
     }

     void move(double framelength, double time)
     {
         double N = time/framelength;
         while(N>0)
         {
             moveByStep(framelength);
             N--;
         }
     }
};