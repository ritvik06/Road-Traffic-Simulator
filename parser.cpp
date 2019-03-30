#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
using namespace std;
int main() 
{    
    fstream file; 
    ofstream road_file,vehicle_file;
    string word,filename,filename1,filename2; 
    
    filename = "config.ini.txt"; 
    filename1 = "road.txt";
    filename2 = "vehicle.txt";
  
    file.open(filename.c_str()); 
    road_file.open(filename1.c_str());
    vehicle_file.open(filename2.c_str());

    while (file >> word) 
    { 
        // cout << word << endl; 

        if(word=="Road_Id"){
        // cout << "Entered road_id" << endl;
          file >> word;
          file >> word;
          road_file << "Road_Id " << word << "\n";
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
        if(word=="Signal"){
        file >> word;
        vehicle_file << '\n' << word << '\n'; 
        }    
        if(word=="CAR"){
          file >> word;
          vehicle_file << "CAR" << " ";
          vehicle_file << word << '\n';
        }
        if(word=="BIKE"){
          file >> word;
          vehicle_file << "BIKE" << " ";
          vehicle_file << word << '\n';
        }              
        if(word=="TRUCK"){
          file >> word;
          vehicle_file << "TRUCK" << " ";
          vehicle_file << word << '\n';
        }  
        if(word=="BUS"){
          file >> word;
          vehicle_file << "BUS" << " ";
          vehicle_file << word << '\n';
        }            

        if(word=="Pass"){
        file >> word;
        vehicle_file << "Pass " << word << '\n';
        }         

    }

    file.close(); 
    road_file.close();
    vehicle_file.close();

    return 0; 
}