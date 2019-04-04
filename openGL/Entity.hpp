//=================================
// include guard
#ifndef __ENTITY_HPP_INCLUDED__
#define __ENTITY_HPP_INCLUDED__
//=================================
// included dependencies
#include<cstdlib>
#include<tuple>
//=================================
// the actual class
using namespace std;
class Entity
{
    public:
     char symbol;
     tuple<double, double> coordinates;
     tuple<double, double> dimensions;

     Entity(double length, double breadth, double x, double y, char sym);
     tuple<double,double> getLocation();     
     tuple<double,double> getDimensions();
     void setLocation(tuple<double,double> location);
     void setDimensions(tuple<double,double> size);
};
#endif // __ENTITY_HPP_INCLUDED__ 