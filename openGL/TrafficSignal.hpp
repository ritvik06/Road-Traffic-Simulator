//=================================
// include guard
#ifndef __TRAFFICSIGNAL_HPP_INCLUDED__
#define __TRAFFICSIGNAL_HPP_INCLUDED__
//=================================
// included dependencies
//=================================
// the actual class
using namespace std;
class TrafficSignal
{
    private:
    string SIGNAL = "RED";
    double position;
    public:
     TrafficSignal(double pos);
     TrafficSignal();
     string getSignal();
     void setSignal(string Sig);
     double getLocation();
     char symbol();
};
#endif //__TRAFFICSIGNAL_HPP_INCLUDED__ 