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

using namespace std;
class Screen
{
    private:
    tuple<int, int> size;
    vector<vector<char>> screen;
    vector<Vehicle> vehicles_on_screen;
    
    public:
    Screen(int length, int breadth)
    {
        size = make_tuple(length, breadth);
        screen = vector<vector<char>> (breadth,vector<char>(length,' '));
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
        for (int i = 0; i != vehicles_on_screen.size(); i++)
        {
            int x,y,l,b;
            Vehicle curr = vehicles_on_screen[i];
            tie(x,y) = curr.getLocation();
            tie(l,b) = curr.getDimensions();
            for(int k = x; k< x+l;k++)
            {
                for(int j = y; j< y+b;j++)
                {
                    if(screen.at(j).at(k) == ' ')
                    screen.at(j).at(k) = curr.symbol;
                    else
                    screen.at(j).at(k) = '!';
                }
            }
            curr.moveByStep(2);
            tie(x,y) = curr.getLocation();
            vehicles_on_screen[i] = curr;
        } 
    }
};
int main()
{
    Screen screen(20,10);
    Vehicle car("car",2,2,1,1,1,0,0,0);
    Vehicle bike("bike",2,1,1,0,1,0,0,5);
    screen.addVehicle(car);
    screen.addVehicle(bike);
    screen.Print();
    screen.Print();
    screen.Print();
    
    exit(0);
}