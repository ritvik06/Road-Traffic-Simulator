#include<tuple>
#include<cstdlib>
#include "Entity.hpp"

using namespace std;

     Entity::Entity(double length, double breadth, double x, double y, char sym)
     {
         coordinates = make_tuple(x,y);
         dimensions = make_tuple(length, breadth);
         symbol = sym;
     }

     tuple<double,double> Entity::getLocation()
     {
         return coordinates;
     }

     
     tuple<double,double> Entity::getDimensions()
     {
         return dimensions;
     }

     void Entity::setLocation(tuple<double,double> location)
     {
         coordinates = location;
     }

     
     void Entity::setDimensions(tuple<double,double> size)
     {
         dimensions = size;
     }
