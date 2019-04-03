//=================================
// include guard
#ifndef __SCREEN_HPP_INCLUDED__
#define __SCREEN_HPP_INCLUDED__
//=================================
// included dependencies
#include<iostream>
#include<vector>
#include<tuple>
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
    int CurrentTime;
    
    public:
    Screen(int length, int breadth,int signal_loc);
    void Print();
    void addVehicle(Vehicle vehicle);
    void cleanScreen();
    bool isEmpty();
    void refresh(double framelength);
    void setSignal(string COLOR);
    void RedLight(Vehicle& curr);
    void Ahead(Vehicle& curr);
    void Left(Vehicle& curr);
    void Right(Vehicle& curr);
    void RoadLeftEnd(Vehicle& curr);
    void RoadRightEnd(Vehicle& curr);
    void RunSimulation(int FutureTime);
    void RunFor(int delta_time);
};
#endif // __SCREEN_HPP_INCLUDED__ 