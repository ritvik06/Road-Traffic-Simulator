//=================================
// include guard
#ifndef __VEHICLE_HPP_INCLUDED__
#define __VEHICLE_HPP_INCLUDED__
//=================================
// included dependencies
#include <tuple>
#include <string>
#include "Entity.hpp"
//=================================
// the actual class
using namespace std;
class Vehicle : public Entity
{
    private:
    string vehicle = "";
    string color = "";
    tuple<double, double> velocity;
    tuple<double, double> acceleration;

    public:
    Vehicle(string vehicle_type,double length, double breadth, double Vx, double Vy, double Ax, double Ay, double x, double y);
    void Init(string vehicle_type,double length, double breadth, double Vx, double Vy, double Ax, double Ay, double x, double y);
    tuple<double,double> getVelocity();
     tuple<double,double> getAcceleration();
     void setColor(string Color);
     void setCoordinates(int X,int Y);
     void moveByStep(double t);
     void move(double framelength, double time);
};
#endif // __VEHICLE_HPP_INCLUDED__ 