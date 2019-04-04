#include<cstdlib>
#include<tuple>
#include <string>
#include "Entity.hpp"
#include "Vehicle.hpp"

using namespace std;
     
    Vehicle::Vehicle(string vehicle_type,double length, double breadth, double Vx, double Vy, double Ax, double Ay, double x, double y)
        :Entity(length, breadth,x,y,vehicle_type[0])
    {   
        vehicle = vehicle_type;
        velocity = make_tuple(Vx,Vy);
        acceleration = make_tuple(Ax,Ay);
    }

    void Vehicle::Init(string vehicle_type,double length, double breadth, double Vx, double Vy, double Ax, double Ay, double x, double y)
    {   
        Entity::dimensions = make_tuple(length,breadth);
        vehicle = vehicle_type;
        velocity = make_tuple(Vx,Vy);
        acceleration = make_tuple(Ax,Ay);
        Entity::setLocation(make_tuple(x,y));
        Entity::symbol = vehicle_type[0];
    }
    
    tuple<double,double> Vehicle::getVelocity()
     {
         return velocity;
     }
    
     tuple<double,double> Vehicle::getAcceleration()
     {
         return acceleration;
     }

     void Vehicle::setColor(string Color)
     {
       color = Color;
     }

     void Vehicle::setCoordinates(int X,int Y)
     {
       Entity::setLocation(make_tuple(X,Y));
     }

     void Vehicle::moveByStep(double t)
     {
         double x , y, Vx, Vy, Ax, Ay; 
         tie(x,y) = Entity::getLocation();
         tie(Vx,Vy) = velocity;
         tie(Ax,Ay) = acceleration;
         Entity::setLocation(make_tuple(x+Vx*t+Ax*t*t/2,y+Vy*t+Ay*t*t/2));
         velocity = make_tuple(Vx+Ax*t, Vy+Ay*t);
     }

     void Vehicle::move(double framelength, double time)
     {
         double N = time/framelength;
         while(N>0)
         {
             Vehicle::moveByStep(framelength);
             N--;
         }
     }