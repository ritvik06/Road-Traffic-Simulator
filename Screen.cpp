#include<iostream>
#include<vector>
#include<cmath>
#include<sstream>
#include<fstream>
#include<stdexcept>
#include<chrono>
#include<cstdlib>
#include<tuple>
#include <string>
#include <cstddef>
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
    int tog_time;
    TrafficSignal signal;
    
    public:
    Screen(int length, int breadth, int timelimit,int toggle)
    {
        signal = TrafficSignal(length/2);
        size = make_tuple(length, breadth);
        screen = vector<vector<char>> (breadth,vector<char>(length,' '));
        time = 0;
        TotalTime = timelimit;
        tog_time = toggle;
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
        if (time%(tog_time)==0) signal.toggle();
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
    fstream road_file,vehicle_file;
    string Road = "Road.txt";
    string Vehicle = "Vehicle.txt";

    string word="";

    road_file.open(Road.c_str());
    vehicle_file.open(Vehicle.c_str());

    int length,width,signal_loc;
    int toggle;
    int max_vel,max_acc; 
    int car_length,car_width,car_vel,car_acc;
    int truck_length,truck_width,truck_vel,truck_acc;
    int bus_length,bus_width,bus_vel,bus_acc;
    int bike_length,bike_width,bike_vel,bike_acc;

    // while(vehicle_file >> word){
    //     if(word=="MaxValues"){
    //         vehicle_file >> word;
    //         max_vel = stoi(word);
    //         vehicle_file >> word;
    //         max_acc = stoi(word);
    //     }
    // }


    while(road_file >> word){
        if(word=="Road_Length"){
            road_file >> word;
            length = stoi(word);
        }

        else if(word=="Road_Width"){
            road_file >> word;
            width = stoi(word);
        }
        
        else if(word=="Road_Signal"){
            road_file >> word;
            signal_loc = stoi(word);
        }
    }

    while(vehicle_file >> word){

        if(word=="Car"){
            vehicle_file >> word;
            vehicle_file >> word;
            // cout << word << endl;
            car_length = stoi(word);
            vehicle_file >> word;
            vehicle_file >> word;
            car_width = stoi(word);
            vehicle_file >> word;
            vehicle_file >> word;
            // cout << word << endl;   
            car_vel = stoi(word);
            vehicle_file >> word;
            vehicle_file >> word;
            car_acc = stoi(word);            
        }
        if(word=="bike"){
            vehicle_file >> word;
            vehicle_file >> word;
            bike_length = stoi(word);
            vehicle_file >> word;
            vehicle_file >> word;
            bike_width = stoi(word);
            vehicle_file >> word;
            vehicle_file >> word;
            bike_vel = stoi(word);
            vehicle_file >> word;
            vehicle_file >> word;
            bike_acc = stoi(word);            
        }
        if(word=="Bus"){
            vehicle_file >> word;
            vehicle_file >> word;
            bus_length = stoi(word);
            vehicle_file >> word;
            vehicle_file >> word;
            bus_width = stoi(word);
            vehicle_file >> word;
            vehicle_file >> word;
            bus_vel = stoi(word);
            vehicle_file >> word;
            vehicle_file >> word;
            bus_acc = stoi(word);            
        }
        if(word=="Truck"){
            vehicle_file >> word;
            vehicle_file >> word;
            truck_length = stoi(word);
            vehicle_file >> word;
            vehicle_file >> word;
            truck_width = stoi(word);
            vehicle_file >> word;
            vehicle_file >> word;
            truck_vel = stoi(word);
            vehicle_file >> word;
            vehicle_file >> word;
            truck_acc = stoi(word);            
        }

        if(word=="Pass"){
            vehicle_file >> word;
            toggle = stoi(word);
        }


    }



     Screen screen(length,width,20,toggle);
     Vehicle car("car",car_length,car_width,car_vel,0,car_acc,0,0,1);
     Vehicle bike("bike",bike_length,bike_width,bike_vel,0,bike_acc,0,0,5);
     Vehicle truck("truck",truck_length,truck_width,truck_vel,0,truck_vel,0,0,10);
     Vehicle Bus("BUS",bus_length,bus_width,bus_vel,0,bus_acc,0,0,13);
     screen.addVehicle(truck);
     screen.addVehicle(car);
     screen.addVehicle(bike);
     screen.addVehicle(Bus);
     screen.RunSimulation();
     exit(0);
}
