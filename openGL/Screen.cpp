#include<iostream>
#include<vector>
#include<cstdlib>
#include<tuple>
#include<cmath>
#include<string>
#include<cstddef>
#include "Vehicle.hpp"
#include "TrafficSignal.hpp"
#include "Screen.hpp"

using namespace std;
    Screen::Screen(int length, int breadth,int signal_loc)
    {
        signal = TrafficSignal(signal_loc);
        size = make_tuple(length, breadth);
        screen = vector<vector<char>> (breadth,vector<char>(length,' '));
        CurrentTime = -1;
    }

    void Screen::Print()
    {
        int length, breadth;
        tie(length,breadth) = size;
        refresh();
        for(int j=0;j<length;j++)
        {
            cout<<"--";
        }
        cout<<endl;
        for(int i=0; i<breadth;i++)
        {
            for(int j=0;j<length;j++)
            {
                cout<<' '<<screen.at(i).at(j);
            }
            cout<<endl;
        }
        for(int j=0;j<length;j++)
        {
            cout<<"--";
        }
        cout<<endl;
        cout <<"Time Elapsed :- " << CurrentTime << "s      " << "SIGNAL: " << signal.getSignal()<< endl; 
    }

    void Screen::addVehicle(Vehicle vehicle)
    {
        vehicles_on_screen.push_back(vehicle);
    }
    void Screen::cleanScreen()
    {
        int length, breadth;
        tie(length,breadth) = size;
        for(int i=0; i<breadth;i++)
        {
            for(int j=0;j<length;j++)
            {  
                screen.at(i).at(j) = ' ';
            }    
        }
    }
    bool Screen::isEmpty()
    {
        int length, breadth;
        tie(length,breadth) = size;
        for(int i=0; i<breadth;i++)
        {
            for(int j=0;j<length;j++)
            {
                if(screen.at(i).at(j) == ' ' || screen.at(i).at(j) == 'X' || screen.at(i).at(j) == '=')
                {
                    continue;
                }
                else
                {
                    return false;
                }   
            }
        }
        return true;
    }
    void Screen::refresh()
    {
        Screen::cleanScreen();
        int height, width;
        tie(height,width) = size;
        int position = (int)round(signal.getLocation());
        for(int i =0; i < width;i++)
        {
            screen.at(i).at(position) = signal.symbol();
        }
        for (int i = 0; i != vehicles_on_screen.size(); i++)
        {
            double x,y,l,b;
            bool stop = false;
            Vehicle curr = vehicles_on_screen[i];
            tie(x,y) = curr.getLocation();
            tie(l,b) = curr.getDimensions();
            for(int k = (int)round(x); k< x+l;k++)
            {
                if(k>=height || k<0) break;
                for(int j = (int)round(y); j< y+b;j++)
                {
                    if(j>=width|| j<0) break;
                    if(screen.at(j).at(k) == ' ' || screen.at(j).at(k) == 'X' || screen.at(j).at(k) == '=')
                    screen.at(j).at(k) = curr.symbol;                    
                    else
                    screen.at(j).at(k) = '!';
                    //if(k+l>=position && k<=position) stop = true;
                }
            }
            curr.moveByStep(1);
            vehicles_on_screen[i] = curr;
        } 
    }
    void Screen::setSignal(string COLOR)
    {
        signal.setSignal(COLOR);
    }
    void Screen::RunSimulation(int FutureTime)
    {
        //TimeJump is the time in future till which we want the Simulation to run.
        while(FutureTime>CurrentTime)
        {
            CurrentTime++;
            Screen::Print();
        }
    }

    void Screen::RunFor(int delta_time)
    {
        //TimeJump is the time in future till which we want the Simulation to run.
        Screen::RunSimulation(CurrentTime+delta_time);
    }
/*
int main()
{
    Screen screen(30,15,15);
    Vehicle car("car",2,2,1,0,1,0,5,0);
    Vehicle bike("bike",2,1,1,0,1,0,0,5);
    Vehicle truck("truck",4,2,1,0,1,0,-10,10);
    Vehicle Bus("BUS",3,2,1,0,1,0,0,13);
    screen.addVehicle(truck);
    screen.addVehicle(car);
    screen.addVehicle(bike);
    screen.addVehicle(Bus);
    screen.RunSimulation(20);
    exit(0);
}*/
