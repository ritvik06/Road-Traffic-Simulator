#include<iostream>
#include<iterator>
#include<vector>
#include<sstream>
#include<fstream>
#include<stdexcept>
#include<cstdlib>
#include<tuple>
#include "Vehicle.hpp"
#include "Screen.hpp"


using namespace std;
int main()
{   
    Vehicle car("car",0,0,0,0,0,0,0,0);
    Vehicle bike("bike",0,0,0,0,0,0,0,0);
    Vehicle truck("truck",0,0,0,0,0,0,0,0);
    Vehicle bus("BUS",0,0,0,0,0,0,0,0);
    Vehicle autorickshaw("autorickshaw",0,0,0,0,0,0,0,0);
    
    fstream road_file,vehicle_file,simulation_file;
    string Road = "RoadInfo.txt";
    string Vehicle = "VehicleInfo.txt";
    string Simulation = "SimulationInfo.txt";

    string word="";

    road_file.open(Road.c_str());
    vehicle_file.open(Vehicle.c_str());
    simulation_file.open(Simulation.c_str());

    int length = 0,width = 0,signal_loc = 0;
    int SimulationID = 0;
    int max_vel = 0,max_acc = 0; 
    string vehicle_name = "";
    int Y_coordinate = 0, vehicle_length = 0,vehicle_width = 0,vehicle_vel = 0,vehicle_acc = 0;
    
    // while(vehicle_file >> word){
    //     if(word=="MaxValues"){
    //         vehicle_file >> word;
    //         max_vel = stoi(word);
    //         vehicle_file >> word;
    //         max_acc = stoi(word);
    //     }
    // }
    Screen screen(0,0,0);
    string line = "";
  
    while(road_file >> word){
        if(word=="Road_Length"){
            road_file >> word;
            length = stoi(word);
        }

        if(word=="Road_Width"){
            road_file >> word;
            width = stoi(word);
        }
        
        if(word=="Road_Signal"){
            road_file >> word;
            signal_loc = stoi(word);
        }
    }
  
    while(getline (vehicle_file,line)){

        stringstream ss(line);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> result (begin, end);
        
        if(result[0]=="MaxValues"){
            vehicle_vel = stoi(result[1]);  
            vehicle_acc = stoi(result[2]); 
        }
        else {
            vehicle_name = result[0];
            vehicle_length = stoi(result[2]);
            vehicle_width = stoi(result[4]);
            vehicle_vel = stoi(result[6]);
            vehicle_acc = stoi(result[8]);
        
            if(vehicle_name=="car"){
                Y_coordinate = rand() % width;
                car.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,0,Y_coordinate);
                }
            else if(vehicle_name=="bike"){
                Y_coordinate = rand() % width;
                bike.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,0,Y_coordinate);
                }
            else if(vehicle_name=="truck"){
                Y_coordinate = rand() % width;
                truck.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,0,Y_coordinate);
                }
            else if(vehicle_name=="bus"){
                Y_coordinate = rand() % width;
                bus.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,0,Y_coordinate);
                }
            else if(vehicle_name=="auto"){
                Y_coordinate = rand() % width;
                autorickshaw.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,0,Y_coordinate);
                }
        }
    }        
    
    while(getline (simulation_file,line)){
        
        stringstream ss(line);
        istream_iterator<std::string> begin(ss);
        istream_iterator<std::string> end;
        vector<string> result (begin, end);
        
        string color = "";
        int time = -1;
        if(result[0]=="ID"){
            SimulationID = stoi(result[1]);
        }

        else if(result[0]=="START") {
            cout <<"Starting Simulation #"<< SimulationID <<endl; 
                screen = Screen(length,width,signal_loc);              
        
        }
        else if(result[0]=="Signal") {
           color = result[1]; 
           time = stoi(result[2]);
           screen.setSignal(color);
           cout <<"Signal changed to  "<< color <<endl; 
           screen.RunSimulation(time);
                  
        }
        else if(result[0]=="CAR") {
           color = result[1]; 
           time = stoi(result[2]);
           car.setColor(color);
           car.setCoordinates(0,rand() % width);
           screen.addVehicle(car);
           cout <<"A " << color <<" car is added."<<endl; 
           screen.RunSimulation(time);
        }
        else if(result[0]=="BIKE") {
           color = result[1]; 
           time = stoi(result[2]);
           bike.setColor(color);
           bike.setCoordinates(0,rand() % width);
           screen.addVehicle(bike);
           cout <<"A " << color <<" bike is added."<<endl; 
           screen.RunSimulation(time);
        }
        else if(result[0]=="BUS") {
           color = result[1]; 
           time = stoi(result[2]);
           bus.setColor(color);
           bus.setCoordinates(0,rand() % width);
           screen.addVehicle(bus);
           cout <<"A " << color <<" bus is added."<<endl; 
           screen.RunSimulation(time);
        }
        else if(result[0]=="TRUCK") {
           color = result[1]; 
           time = stoi(result[2]);
           truck.setColor(color);
           truck.setCoordinates(0,rand() % width);
           screen.addVehicle(truck);
           cout <<"A " << color <<" truck is added."<<endl;
           screen.RunSimulation(time);
        }
        else if(result[0]=="AUTO") {
           color = result[1]; 
           time = stoi(result[2]);
           autorickshaw.setColor(color);
           autorickshaw.setCoordinates(0,rand() % width);
           screen.addVehicle(autorickshaw);
           cout <<"A " << color <<" auto-rickshaw is added."<<endl; 
           screen.RunSimulation(time);
        }
        else if(result[0]=="PASS") {
            time = stoi(result[1]);
            screen.RunSimulation(time);                       
        }
        else if(result[0]=="END") {
            while(!screen.isEmpty())
            {
                screen.RunFor(1);
            }
            cout <<"Simulation #"<< SimulationID << " has ended." << endl;                       
        }
    }
    exit(0);
}

