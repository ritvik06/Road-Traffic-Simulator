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
class TrafficSignal
{
    
    private:
    string SIGNAL = "RED";
    int position;
    public:
    TrafficSignal(int pos)
    {   
        position = pos;
    }
    TrafficSignal()
    {   
        position = 0;
    }

    string getSignal()
     {
         return SIGNAL;
     }
    
     void setSignal(string Sig)
     {
         SIGNAL = Sig;
     }

     void toggle()
     {
         if(SIGNAL == "RED") SIGNAL = "GREEN";
         else SIGNAL = "RED";
     }

     int getLocation()
     {
         return position;
     }
     char symbol()
     {
         if(SIGNAL=="RED") return 'X';
         else return '=';
     }
};