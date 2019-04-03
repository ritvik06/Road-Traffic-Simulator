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
    double max_vel = 0,max_acc = 0; 
    string vehicle_name = "";
    double Y_coordinate = 0, X_coordinate = 0, vehicle_length = 0,vehicle_width = 0,vehicle_vel = 0,vehicle_acc = 0;
    
    // while(vehicle_file >> word){
    //     if(word=="MaxValues"){
    //         vehicle_file >> word;
    //         max_vel = stod(word);
    //         vehicle_file >> word;
    //         max_acc = stod(word);
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
            vehicle_vel = stod(result[1]);  
            vehicle_acc = stod(result[2]); 
        }
        else {
            vehicle_name = result[0];
            vehicle_length = stod(result[2]);
            vehicle_width = stod(result[4]);
            vehicle_vel = stod(result[6]);
            vehicle_acc = stod(result[8]);
        
            if(vehicle_name=="Car"){
                X_coordinate = -1*vehicle_length;
                Y_coordinate = rand() % (int)(width-vehicle_width+1);
                car.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,X_coordinate,Y_coordinate);
                }
            else if(vehicle_name=="bike"){
                X_coordinate = -1*vehicle_length;
                Y_coordinate = rand() % (int)(width-vehicle_width+1);
                bike.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,X_coordinate,Y_coordinate);
                }
            else if(vehicle_name=="Truck"){
                X_coordinate = -1*vehicle_length;
                Y_coordinate = rand() % (int)(width-vehicle_width+1);
                truck.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,X_coordinate,Y_coordinate);
                }
            else if(vehicle_name=="Bus"){
                X_coordinate = -1*vehicle_length;
                Y_coordinate = rand() % (int)(width-vehicle_width+1);
                bus.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,X_coordinate,Y_coordinate);
                }
            else if(vehicle_name=="Auto"){
                X_coordinate = -1*vehicle_length;
                Y_coordinate = rand() % (int)(width-vehicle_width+1);
                autorickshaw.Init(vehicle_name,vehicle_length,vehicle_width,vehicle_vel,0,vehicle_acc,0,X_coordinate,Y_coordinate);
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
           time = stod(result[2]);
           screen.setSignal(color);
           cout <<"Signal changed to  "<< color <<endl; 
           screen.RunSimulation(time);
                  
        }
        else if(result[0]=="CAR") {
           color = result[1]; 
           time = stod(result[2]);
           car.setColor(color);
           double l=0,b=0;
           tie(l,b) = car.dimensions;
           car.setCoordinates(-1*l,rand() % (int)(width-b+1));
           screen.addVehicle(car);
           cout <<"A " << color <<" car is added."<<endl; 
           screen.RunSimulation(time);
        }
        else if(result[0]=="BIKE") {
           color = result[1]; 
           time = stod(result[2]);
           bike.setColor(color);
           double l=0,b=0;
           tie(l,b) = bike.dimensions;
           bike.setCoordinates(-1*l,rand() % (int)(width-b+1));
           screen.addVehicle(bike);
           cout <<"A " << color <<" bike is added."<<endl; 
           screen.RunSimulation(time);
        }
        else if(result[0]=="BUS") {
           color = result[1]; 
           time = stod(result[2]);
           bus.setColor(color);
           double l=0,b=0;
           tie(l,b) = bus.dimensions;
           bus.setCoordinates(-1*l,rand() % (int)(width-b+1));
           screen.addVehicle(bus);
           cout <<"A " << color <<" bus is added."<<endl; 
           screen.RunSimulation(time);
        }
        else if(result[0]=="TRUCK") {
           color = result[1]; 
           time = stod(result[2]);
           truck.setColor(color);
           double l=0,b=0;
           tie(l,b) = truck.dimensions;
           truck.setCoordinates(-1*l,rand() % (int)(width-b+1));
           screen.addVehicle(truck);
           cout <<"A " << color <<" truck is added."<<endl;
           screen.RunSimulation(time);
        }
        else if(result[0]=="AUTO") {
           color = result[1]; 
           time = stod(result[2]);
           autorickshaw.setColor(color);
           double l=0,b=0;
           tie(l,b) = autorickshaw.dimensions;
           autorickshaw.setCoordinates(-1*l,rand() % (int)(width-b+1));
           screen.addVehicle(autorickshaw);
           cout <<"A " << color <<" auto-rickshaw is added."<<endl; 
           screen.RunSimulation(time);
        }
        else if(result[0]=="PASS") {
            time = stod(result[1]);
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
    road_file.close();
    vehicle_file.close();
    simulation_file.close();

    exit(0);
}

