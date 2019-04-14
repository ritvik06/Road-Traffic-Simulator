#include <cstdlib>
#include <tuple>
#include <string>
#include <cmath>
#include "Entity.hpp"
#include "Vehicle.hpp"

using namespace std;
     
    Vehicle::Vehicle(string vehicle_type,double length, double breadth, double VX, double VY, double Ax, double Ay, double x, double y)
        :Entity(length, breadth,x,y,vehicle_type[0])
    {   
        vehicle = vehicle_type;
        velocity = make_tuple(0,0);
        maxVelocity = make_tuple(VX,VY);
        acceleration = make_tuple(Ax,Ay);
    }

    void Vehicle::Init(string vehicle_type,double length, double breadth, double VX, double VY, double Ax, double Ay, double x, double y, bool jump)
    {   
        Entity::dimensions = make_tuple(length,breadth);
        vehicle = vehicle_type;
        velocity = make_tuple(0,0);
        maxVelocity = make_tuple(VX,VY);
        acceleration = make_tuple(Ax,Ay);
        Entity::setLocation(make_tuple(x,y));
        Entity::symbol = vehicle_type[0];
        LaneJumper = jump;
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

     void Vehicle::setRedLight(bool redLight)
     {
        RedLight = redLight;            
     }

     void Vehicle::setRoadLeftEnd(bool roadLeftEnd)
     {
        RoadLeftEnd = roadLeftEnd;
        if(RoadLeftEnd)
            NoSpaceLeft++;
     }
     
     void Vehicle::setRoadRightEnd(bool roadRightEnd)
     {
        RoadRightEnd = roadRightEnd;
        if(RoadRightEnd)
            NoSpaceRight++;
     }

     void Vehicle::setLaneLeftEnd(bool laneLeftEnd)
     {
        if(!LaneJumper)
            LaneLeftEnd = laneLeftEnd;
        if(LaneLeftEnd)
            NoSpaceLeft++;
     }
     
     void Vehicle::setLaneRightEnd(bool laneRightEnd)
     {
        if(!LaneJumper)
            LaneRightEnd = laneRightEnd;
        if(LaneRightEnd)
            NoSpaceRight++;
     }
     
     void Vehicle::setClearAhead(bool clearAhead)
     {
        ClearAhead = clearAhead;
        /*if(ClearAhead)
        {
            NoSpaceLeft = 0;
            NoSpaceRight = 0;
        } */           
     }

     void Vehicle::setClearLeft(bool clearLeft)
     {
        ClearLeft = clearLeft;    
        if(!clearLeft)
            NoSpaceLeft++;        
     }
     
     void Vehicle::setClearRight(bool clearRight)
     {
        ClearRight = clearRight;  
        if(!clearRight)
            NoSpaceRight++;          
     }
     
      string Vehicle::getName()
     {
        return vehicle;            
     }

      string Vehicle::getColor()
     {
        return color;            
     }

      bool Vehicle::getRedLight()
     {
        return RedLight;            
     }

     bool Vehicle::getLaneLeftEnd()
     {
         return LaneLeftEnd;
     }

     bool Vehicle::getLaneRightEnd()
     {
         return LaneRightEnd;
     }

     bool Vehicle::getRoadLeftEnd()
     {
         return RoadLeftEnd;
     }

     bool Vehicle::getRoadRightEnd()
     {
         return RoadRightEnd;
     }

     bool Vehicle::getClearAhead()
     {
        return ClearAhead;            
     }

     bool Vehicle::getClearLeft()
     {
        return ClearLeft;            
     }

     bool Vehicle::getClearRight()
     {
        return ClearRight;            
     }

     int Vehicle::turn()
     {
        double Vx, Vy;
        tie(Vx,Vy) = velocity;
        if(Vy>0)
            return 1;
        else if(Vy<0)
            return -1;
        else
            return 0;
     }

     bool Vehicle::isTurningLeft()
     {
         return (Vehicle::turn()<0);
     }

     bool Vehicle::isTurningRight()
     {
         return (Vehicle::turn()>0);
     }
     

     void Vehicle::moveByStep(double t)
     {
         double x , y, Vx, Vy, Ax, Ay,VX,VY; 
         double new_Vx, new_Vy;
         tie(x,y) = Entity::getLocation();
         tie(VX,VY) = maxVelocity;
         tie(Vx,Vy) = velocity;
         tie(Ax,Ay) = acceleration;
         new_Vx = (VX>Vx+Ax*t) ? (Vx + Ax*t) : VX;
         //new_Vy = (abs(VY)>abs(Vy+Ay*t)) ? (Vy + Ay*t) : direction*abs(VY);
         new_Vx = (ClearAhead) ? new_Vx : 0;
         new_Vx = (RedLight) ? 0 : new_Vx;
         if(!ClearAhead)
         {
            if(NoSpaceLeft >0 && NoSpaceRight >0)
            {
                new_Vy = 0;
            }
            else if(Vehicle::isTurningRight())
            {
                if(ClearRight&&!RoadRightEnd &&!LaneRightEnd)
                    new_Vy = 1;
                else 
                {
                    new_Vy = 0;
                    //NoSpace++;
                }
            }

            else if(Vehicle::isTurningLeft())
            {
                if(ClearLeft&&!RoadLeftEnd &&!LaneLeftEnd)
                    new_Vy = -1;
                else 
                {
                    new_Vy = 0;
                    //NoSpace++;
                }
            }
            else
            {
                if(ClearRight&&!RoadRightEnd && !LaneRightEnd)
                    new_Vy = 1;
                else if(ClearLeft&&!RoadLeftEnd && !LaneLeftEnd)
                    new_Vy = -1;
                else
                {
                    new_Vy = 0;
                    //NoSpace++;
                }
            }               
         }
         else
         {
            new_Vy = 0;
            NoSpaceLeft = 0;
            NoSpaceRight = 0;
         }
         Entity::setLocation(make_tuple(x+new_Vx*t,y+new_Vy*t));
         velocity = make_tuple(new_Vx, new_Vy);
     }

     double Vehicle::FutureX(double t)
     {
         double x , y, Vx, Vy; 
         tie(x,y) = Entity::getLocation();
         tie(Vx,Vy) = velocity;
         return (x+Vx*t);
     }

     double Vehicle::FutureY(double t)
     {
         double x , y, Vx, Vy; 
         tie(x,y) = Entity::getLocation();
         tie(Vx,Vy) = velocity;
         return (y+Vy*t);  
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

     void Vehicle::setLaneJumper(bool jump)
     {
         LaneJumper = jump;
     }

     bool Vehicle::getLaneJumper()
     {
         return LaneJumper;
     }