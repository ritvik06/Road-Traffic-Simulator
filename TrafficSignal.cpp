#include<cstdlib>
#include<tuple>
#include "TrafficSignal.hpp"

using namespace std;
    TrafficSignal::TrafficSignal(double pos)
    {   
        position = pos;
    }
    TrafficSignal::TrafficSignal()
    {   
        position = 0;
    }

    string TrafficSignal::getSignal()
     {
         return SIGNAL;
     }
    
     void TrafficSignal::setSignal(string Sig)
     {
         SIGNAL = Sig;
     }

     double TrafficSignal::getLocation()
     {
         return position;
     }
     char TrafficSignal::symbol()
     {
         if(SIGNAL=="RED") return 'X';
         else return '=';
     }