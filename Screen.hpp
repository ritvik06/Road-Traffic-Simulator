//=================================
// include guard
#ifndef __SCREEN_HPP_INCLUDED__
#define __SCREEN_HPP_INCLUDED__
//=================================
// included dependencies
#include<iostream>
#include<vector>
#include<tuple>
#include<fstream>
#include "Vehicle.hpp"
#include "TrafficSignal.hpp"
//=================================
// the actual class
class Screen
{
    private:
    tuple<int, int> size;
    vector<vector<char>> screen;
    vector<Vehicle> vehicles_on_screen;
    TrafficSignal signal;
    float CurrentTime;
    int LaneWidth;
    
    public:
    bool InitialPrint = false;
    Screen(int length, int breadth,int signal_loc, int lane_width);
    //Screen(Screen &oldScreen);
    tuple<int,int,int,int,string,float> ScreenInfo();
    vector<Vehicle> Vehicles();
    void Print();
    void PrintDisplayInfo();
    void RunDisplay(float FutureTime,float framelength);
    void RunDisplayFor(int delta_time);
    void addVehicle(Vehicle vehicle);
    void cleanScreen();
    bool isEmpty();
    void refresh(double framelength);
    void setSignal(string COLOR);
    void RedLight(Vehicle& curr);
    void Ahead(Vehicle& curr);
    void Left(Vehicle& curr);
    void Right(Vehicle& curr);
    void LaneLeftEnd(Vehicle& curr);
    void LaneRightEnd(Vehicle& curr);
    void RoadLeftEnd(Vehicle& curr);
    void RoadRightEnd(Vehicle& curr);
    void RunSimulation(int FutureTime);
    void RunFor(int delta_time);
};
#endif // __SCREEN_HPP_INCLUDED__ 