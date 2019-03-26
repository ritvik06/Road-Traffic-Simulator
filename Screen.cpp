#include<iostream>
#include<vector>
#include<cmath>
#include<sstream>
#include<fstream>
#include<stdexcept>
#include<chrono>
#include<cstdlib>
#include<tuple>
#include "Vehicle.cpp"
#include "TrafficSignal.cpp"

using namespace std;
class Screen
{
    private:
    tuple<int, int> size;
    vector<vector<char>> screen;
    vector<Vehicle> vehicles_on_screen;
    int time;
    int TotalTime;
    TrafficSignal signal;
    
    public:
    Screen(int length, int breadth, int timelimit)
    {
        signal = TrafficSignal(length/2);
        size = make_tuple(length, breadth);
        screen = vector<vector<char>> (breadth,vector<char>(length,' '));
        time = 0;
        TotalTime = timelimit;
    }

    void Print()
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
        cout <<"Time Elapsed :- " << time << "s      " << "SIGNAL: " << signal.getSignal()<< "     Time Left :- "<<  TotalTime-time << "s " <<endl; 
    }

    void addVehicle(Vehicle vehicle)
    {
        vehicles_on_screen.push_back(vehicle);
    }
    void cleanScreen()
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
    void refresh()
    {
        cleanScreen();
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
        moveTime(1);
    }
    void moveTime(int t)
    {
        time += t;
        if (time%5==0) signal.toggle();
    }
    void RunSimulation()
    {
        for(int i=0; i<TotalTime; i++)
        {
            Print();
        }
    }
};
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
    screen.RunSimulation();
    exit(0);
}