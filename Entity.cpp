#include<iostream>
#include<vector>
#include<cmath>
#include<sstream>
#include<fstream>
#include<stdexcept>
#include<chrono>
#include<cstdlib>

using namespace std;
class Entity
{
    private:
     char symbol;
     tuple<int, int> coordinates;
     tuple<int, int> velocity;
     tuple<int, int> acceleration;
     tuple<int, int> dimensions;
    
    public:
     bool stationary()
     {
         return(velocity==make_tuple(0,0));
     }
     
     tuple<int,int> getLocation()
     {
         return coordinates;
     }

     tuple<int,int> getVelocity()
     {
         return velocity;
     }
    
     tuple<int,int> getAcceleration()
     {
         return acceleration;
     }
     tuple<int,int> getDimensions()
     {
         return dimensions;
     }

     Entity(int length, int breadth, int Vx , int Vy, int x, int y, int Ax, int Ay, char sym)
     {
         coordinates = make_tuple(x,y);
         velocity = make_tuple(Vx,Vy);
         dimensions = make_tuple(length, breadth);
         symbol = sym;
     }

     void moveByStep(int t)
     {
         int x , y, Vx, Vy, Ax, Ay; 
         tie(x,y) = coordinates;
         tie(Vx,Vy) = velocity;
         tie(Ax,Ay) = acceleration;
         coordinates = make_tuple(x+Vx*t+Ax*t*t/2,y+Vy*t+Ay*t*t/2);
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


}

class Screen
{
    private:
    tuple<int, int> size;
    char[][] screen;
    
    Screen(int length, int breadth)
    {
        size = make_tuple(length, breadth);
        screen = new int[length][breadth];
    }
};
int main()
{
    exit(0);
}
