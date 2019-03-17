#include<iostream>
#include<vector>
#include<cmath>
#include<sstream>
#include<fstream>
#include<stdexcept>
#include<chrono>
#include<cstdlib>
#include<tuple>

using namespace std;
class Entity
{
    private:
     tuple<int, int> coordinates;
     tuple<int, int> dimensions;
    
    public:
     char symbol;
     
     Entity(int length, int breadth, int x, int y, char sym)
     {
         coordinates = make_tuple(x,y);
         dimensions = make_tuple(length, breadth);
         symbol = sym;
     }

     tuple<int,int> getLocation()
     {
         return coordinates;
     }

     
     tuple<int,int> getDimensions()
     {
         return dimensions;
     }

     void setLocation(tuple<int,int> location)
     {
         coordinates = location;
     }

     
     void setDimensions(tuple<int,int> size)
     {
         dimensions = size;
     }

};