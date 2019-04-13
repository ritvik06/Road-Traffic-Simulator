#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
using namespace std;
int main() 
{    
    fstream file; 
    ofstream road_file,vehicle_file,simulation_file;
    string word,config,Road,Vehicle,Simulation;
    int timestamp = 0; 
    
    config = "config.ini"; 
    Road = "RoadInfo.txt";
    Vehicle = "VehicleInfo.txt";
    Simulation = "SimulationInfo.txt";
  
    file.open(config.c_str()); 
    road_file.open(Road.c_str());
    vehicle_file.open(Vehicle.c_str());
    simulation_file.open(Simulation.c_str());

    while (file >> word) 
    { 
        // cout << word << endl; 

        if(word=="Road_Id"){
        // cout << "Entered road_id" << endl;
          file >> word;
          file >> word;
          simulation_file <<"ID " << word << "\n";
        }

        if(word=="Road_Length"){
          file >> word;
          file >> word;
          road_file << "Road_Length " << word <<"\n";
        }

        if(word=="Road_Width"){
          file >> word;
          file >> word;
          road_file << "Road_Width " << word<<"\n"; 
        }

        if(word=="Road_Signal"){
          file >> word;
          file >> word;
          road_file << "Road_Signal " << word<<"\n";
        }

        if(word=="Default_MaxSpeed"){
          file >> word;
          file >> word;  
          vehicle_file << "MaxValues ";
          vehicle_file << word << " ";
        }

        if(word=="Default_Acceleration"){
          file >> word;
          file >> word; 
          vehicle_file << word;
        }
        if(word=="Vehicle_Type"){
            vehicle_file << "\n";
          file >> word;
          file >> word;
          vehicle_file << word << " ";
        }
        if(word=="Vehicle_Length"){
        file >> word;
        file >> word;
        vehicle_file << "length" << " " << word << " ";
        }
        if(word=="Vehicle_Width"){
        file >> word;
        file >> word;
        vehicle_file << "width" << " " << word << " ";
        } 
        if(word=="Vehicle_MaxSpeed"){
        file >> word;
        file >> word;
        vehicle_file << "speed" << " " << word << " ";
        } 
        if(word=="Vehicle_Acceleration"){
        file >> word;
        file >> word;
        vehicle_file << "acc" << " " << word << " ";
        }

        if(word=="START"){
        simulation_file << word << '\n'; 
        }
        if(word=="Signal"){
        file >> word;
        simulation_file << "Signal " << word << " " << '\n'; 
        }    
        if(word=="CAR"){
          file >> word;
          simulation_file << "CAR" << " ";
          simulation_file << word << " " << '\n';
          //timestamp++;
        }
        if(word=="BIKE"){
          file >> word;
          simulation_file << "BIKE" << " ";
          simulation_file << word << " " << '\n';
          //timestamp++;
        }              
        if(word=="TRUCK"){
          file >> word;
          simulation_file << "TRUCK" << " ";
          simulation_file << word << " " << '\n';
          //timestamp++;
        }  
        if(word=="BUS"){
          file >> word;
          simulation_file << "BUS" << " ";
          simulation_file << word << " " << '\n';
          //timestamp++;
        }
        if(word=="AUTO"){
          file >> word;
          simulation_file << "AUTO" << " ";
          simulation_file << word << " " << '\n';
          //timestamp++;
        }            
        if(word=="Pass"){
        file >> word;
        simulation_file << "PASS " << word << '\n';
        //timestamp++;
        }
        if(word=="END"){
        simulation_file << word; 
        }         

    }

    file.close(); 
    road_file.close();
    vehicle_file.close();
    simulation_file.close();

    return 0; 
}