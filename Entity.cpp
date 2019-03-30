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
     tuple<double, double> coordinates;
     tuple<double, double> dimensions;
    
    public:
     char symbol;
     
     Entity(double length, double breadth, double x, double y, char sym)
     {
         coordinates = make_tuple(x,y);
         dimensions = make_tuple(length, breadth);
         symbol = sym;
     }

     tuple<double,double> getLocation()
     {
         return coordinates;
     }

     
     tuple<double,double> getDimensions()
     {
         return dimensions;
     }

     void setLocation(tuple<double,double> location)
     {
         coordinates = location;
     }

     
     void setDimensions(tuple<double,double> size)
     {
         dimensions = size;
     }

};
