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
    tuple<int, int> velocity;
    tuple<int, int> acceleration;
     
    public:
    Vehicle(string vehicle_type,int length, int breadth, int Vx, int Vy, int Ax, int Ay, int x, int y)
        :Entity(length, breadth,x,y,vehicle_type[0])
    {   
        velocity = make_tuple(Vx,Vy);
        acceleration = make_tuple(Ax,Ay);
    }

    tuple<int,int> getVelocity()
     {
         return velocity;
     }
    
     tuple<int,int> getAcceleration()
     {
         return acceleration;
     }

     void moveByStep(int t)
     {
         int x , y, Vx, Vy, Ax, Ay; 
         tie(x,y) = getLocation();
         tie(Vx,Vy) = velocity;
         tie(Ax,Ay) = acceleration;
         setLocation(make_tuple(x+Vx*t+Ax*t*t/2,y+Vy*t+Ay*t*t/2));
         velocity = make_tuple(Vx+Ax*t, Vy+Ay*t);
     }

     void move(int framelength, int time)
     {
         int N = time/framelength;
         while(N>0)
         {
             moveByStep(framelength);
             N--;
         }
     }
};