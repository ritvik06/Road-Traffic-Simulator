//=================================
// include guard
#ifndef __VEHICLE_HPP_INCLUDED__
#define __VEHICLE_HPP_INCLUDED__
//=================================
// included dependencies
#include <cstdlib>
#include <tuple>
#include <string>
#include <cmath>
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
    tuple<double, double> maxVelocity;
    tuple<double, double> acceleration;
    bool ClearAhead = true;
    bool ClearLeft = true;
    bool ClearRight = true;
    bool RedLight = false;
    bool RoadLeftEnd = false;
    bool RoadRightEnd = false;
    
    public:
    int RedLightDistance = -1;
    int RoadLeftEndDistance = -1;
    int RoadRightEndDistance = -1;
    Vehicle(string vehicle_type,double length, double breadth, double Vx, double Vy, double Ax, double Ay, double x, double y);
     void Init(string vehicle_type,double length, double breadth, double Vx, double Vy, double Ax, double Ay, double x, double y);
     tuple<double,double> getVelocity();
     tuple<double,double> getAcceleration();
     void setRedLight(bool redLight);
     void setRoadLeftEnd(bool roadLeftEnd);
     void setRoadRightEnd(bool roadRightEnd);
     void setClearAhead(bool clearAhead);
     void setClearLeft(bool clearLeft);
     void setClearRight(bool clearRight);
     void setColor(string Color);
     bool getRedLight();
     bool getRoadLeftEnd();
     bool getRoadRightEnd();
     bool getClearAhead();
     bool getClearLeft();
     bool getClearRight();
     double FutureX(double t);
     double FutureY(double t);
     void setCoordinates(int X,int Y);
     int turn();
     bool isTurningLeft();
     bool isTurningRight();
     void moveByStep(double t);
     void move(double framelength, double time);
};
#endif // __VEHICLE_HPP_INCLUDED__ 