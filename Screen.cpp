#include<iostream>
#include<vector>
#include<cstdlib>
#include<tuple>
#include<cmath>
#include<fstream>
#include<string>
#include<cstddef>
#include "Vehicle.hpp"
#include "TrafficSignal.hpp"
#include "Screen.hpp"

using namespace std;
    /*Screen::Screen(Screen &oldScreen) 
    {
        int length;
        int breadth;
        int signal_loc;
        float t;
        string Signal = "";
        tie(length,breadth,signal_loc,Signal,t)= oldScreen.ScreenInfo();
        signal = TrafficSignal(signal_loc);
        signal.setSignal(Signal);
        size = make_tuple(length, breadth);
        vector<Vehicle> Vehicles = oldScreen.Vehicles();
        CurrentTime = t;
        for (int i = 0; i < Vehicles.size(); i++)
            {
                Vehicle curr = Vehicles[i];
                vehicles_on_screen.push_back(curr);
            }
        screen = vector<vector<char>> (breadth,vector<char>(length,' '));
    }*/

    Screen::Screen(int length, int breadth,int signal_loc, int lane_width)
    {
        signal = TrafficSignal(signal_loc);
        size = make_tuple(length, breadth);
        screen = vector<vector<char>> (breadth,vector<char>(length,' '));
        CurrentTime = -1;
        LaneWidth = lane_width;
    }

    tuple<int,int,int,int,string,float> Screen::ScreenInfo()
    {
        int height, width;
        tie(height,width) = size;
        int position = (int)round(signal.getLocation());
        string Signal = signal.getSignal();
        return make_tuple(height,width,LaneWidth,position,Signal,CurrentTime);
    }

    vector<Vehicle> Screen::Vehicles()
    {
        return vehicles_on_screen;
    }
    
    
    void Screen::Print()
    {
        int length, breadth;
        double framelength = 0.25;
        tie(length,breadth) = size;
        for(double i=0; i < 1; i+=framelength)
        {
            refresh(framelength);
        }
        for(int j=0;j<length;j++)
        {
            cout<<"##";
        }
        cout<<endl;
        for(int i=0; i<breadth;i++)
        {
            for(int j=0;j<length;j++)
            {
                cout<<' '<<screen.at(i).at(j);
            }
            cout<<endl;
            if(i%LaneWidth == (LaneWidth-1) && i!= (breadth-1))
            {
                for(int j=0;j<length;j++)
                {
                    cout<<"--";
                }
                cout<<endl;
            }
        }
        for(int j=0;j<length;j++)
        {
            cout<<"##";
        }
        cout<<endl;
        cout <<"Time Elapsed :- " << CurrentTime << "s      " << "SIGNAL: " << signal.getSignal()<< endl; 
    }
    
    void Screen::PrintDisplayInfo()
    {
        fstream display_file;
        string Display = "DisplayInfo.txt";
        if(!InitialPrint)
        {
            
            int height, width;
            tie(height,width) = size;
            int position = (int)round(signal.getLocation());
            display_file.open(Display.c_str(),ios::app);
            display_file <<"Road " << height << " " << width << " TrafficLight " << position << endl;
            display_file.close();
            InitialPrint = true;
        }
        display_file.open(Display.c_str(), ios::app);
        display_file <<"Time " << CurrentTime << "      " << "SIGNAL " << signal.getSignal()<< endl;
        for (int i = 0; i < vehicles_on_screen.size(); i++)
        {
            double x,y,l,b,new_x,new_y;
            Vehicle curr = vehicles_on_screen[i];
            tie(l,b) = curr.getDimensions();
            tie(new_x,new_y) = curr.getLocation();
            display_file << "Vehicle " << i << " " <<curr.getName() << " " << curr.getColor() << " " << l << " " << b << " " << new_x << " " << new_y << endl;  
        } 
        display_file.close();
        
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
    void Screen::Left(Vehicle& curr)
    {
        int height, width;
        tie(height,width) = size;
        int position = (int)round(signal.getLocation());
        double x,y,l,b;
        tie(x,y) = curr.getLocation();
        tie(l,b) = curr.getDimensions();
        curr.setClearLeft(true);                            
        {
            int j = (int)(y-1);
            if(j>=width|| j<0) return;
            for(int k = (int)round(x); k< round(x+l);k++)
            {
                if(k>=height || k<0) continue;
                if(screen.at(j).at(k) == ' ' || screen.at(j).at(k) == '=' || screen.at(j).at(k) == 'X' )
                {
                    //cout<<"There-Here"<<endl;
                    continue;
                }
                else 
                {
                    //cout<<"Here"<<endl;
                    curr.setClearLeft(false);
                    break;
                }
            }
        }
    }
    void Screen::Right(Vehicle& curr)
    {
        int height, width;
        tie(height,width) = size;
        int position = (int)round(signal.getLocation());
        double x,y,l,b;
        tie(x,y) = curr.getLocation();
        tie(l,b) = curr.getDimensions();
        curr.setClearRight(true);                            
        int j = (int)(y+b);
        if(j>=width|| j<0) return;
        for(int k = (int)round(x); k< round(x+l);k++)
        {
            if(k>=height || k<0) continue;
            if(screen.at(j).at(k) == ' ' || screen.at(j).at(k) == '=' || screen.at(j).at(k) == 'X' )
            {
                //cout<<"There-Here"<<endl;
                continue;
            }
            else 
            {
                //cout<<"Here"<<endl;
                curr.setClearRight(false);
                break;
            }
        }
    }
    void Screen::Ahead(Vehicle& curr)
    {
        int height, width;
        tie(height,width) = size;
        double x,y,l,b;
        tie(x,y) = curr.getLocation();
        tie(l,b) = curr.getDimensions();
        curr.setClearAhead(true);                            
        for(int j = (int)round(y); j< round(y+b);j++)
        {
            if(j>=width|| j<0) continue;
            int k = (int) round(x+l);
            if(k>=height || k<0) continue;
            if(screen.at(j).at(k) == ' ' || screen.at(j).at(k) == '=' || screen.at(j).at(k) == 'X' )
            {
                //cout<<"There-Here"<<endl;
                continue;
            }
            else
            {
                //cout<<"Here"<<endl;
                //if(curr.symbol[0] == 'C') cout <<"CarShouldStop"<<endl;
                curr.setClearAhead(false);
                break;
            }
        }
    }

    void Screen::RedLight(Vehicle& curr)
    {
        int height, width;
        tie(height,width) = size;
        int position = (int)round(signal.getLocation());
        double x,y,l,b;
        tie(x,y) = curr.getLocation();
        tie(l,b) = curr.getDimensions();
        curr.setRedLight(false);                            
        for(int j = (int)round(y); j< round(y+b);j++)
        {
            int k = (int)round(x+l);
            if(k==position && signal.getSignal()=="RED")
            {
                //cout<<"There-Here"<<endl;
                curr.setRedLight(true);
                break;
            }
            else
            {
                //cout<<"Here"<<endl;
                continue;
            }
        }
    }
   
    void Screen::LaneLeftEnd(Vehicle& curr)
    {
        int height, width;
        tie(height,width) = size;
        double x,y,l,b;
        tie(x,y) = curr.getLocation();
        tie(l,b) = curr.getDimensions();
        curr.setLaneLeftEnd(false);                            
        int j = (int)round(y);
        if(j%LaneWidth==0 && !curr.getLaneJumper()) 
        {
            //cout << curr.getName() << "JumpLeft"<<endl;
            curr.setLaneLeftEnd(true);                           
        }
    }

    void Screen::LaneRightEnd(Vehicle& curr)
    {
        int height, width;
        tie(height,width) = size;
        double x,y,l,b;
        tie(x,y) = curr.getLocation();
        tie(l,b) = curr.getDimensions();
        curr.setLaneRightEnd(false);                            
        int j = (int)(y+b);
        if(j%LaneWidth==LaneWidth-1 && !curr.getLaneJumper()) 
        {
            //cout << curr.getName() << "JumpRight"<<endl;
            curr.setLaneRightEnd(true);                            
        }
    }
    void Screen::RoadLeftEnd(Vehicle& curr)
    {
        int height, width;
        tie(height,width) = size;
        double x,y,l,b;
        tie(x,y) = curr.getLocation();
        tie(l,b) = curr.getDimensions();
        curr.setRoadLeftEnd(false);                            
        int j = (int)round(y);
        if(j<=0) 
        {
            //cout <<"Left Touch"<<endl;
            curr.setRoadLeftEnd(true);
            /*if(b==1 && j==0) 
            {
                curr.setRoadLeftEnd(false);
            } */                           
        }
    }

    void Screen::RoadRightEnd(Vehicle& curr)
    {
        int height, width;
        tie(height,width) = size;
        double x,y,l,b;
        tie(x,y) = curr.getLocation();
        tie(l,b) = curr.getDimensions();
        curr.setRoadRightEnd(false);                            
        int j = (int)(y+b);
        if(j>=width) 
        {
            //cout <<"Right Touch"<<endl;
            curr.setRoadRightEnd(true);                            
        }
    }

    void Screen::refresh(double framelength)
    {
        //Screen::cleanScreen();
        int height, width;
        tie(height,width) = size;
        int position = (int)round(signal.getLocation());
        for(int i =0; i < width;i++)
        {
            screen.at(i).at(position) = signal.symbol();
        }
        for (int i = 0; i < vehicles_on_screen.size(); i++)
        {
            double x,y,l,b,new_x,new_y;
            Vehicle curr = vehicles_on_screen[i];
            tie(l,b) = curr.getDimensions();
            tie(x,y) = curr.getLocation();
            for(int k = (int)round(x); k< round(x+l);k++)
            {
                if(k>=height || k<0) continue;
                for(int j = (int)round(y); j< round(y+b);j++)
                {
                    if(j>=width|| j<0) continue;
                    screen.at(j).at(k) = (screen.at(j).at(k) == curr.symbol || screen.at(j).at(k) == '!' ) ? ' ' : screen.at(j).at(k) ;
                }
            }
            Screen::RedLight(curr);
            Screen::Ahead(curr);
            Screen::Left(curr);
            Screen::RoadLeftEnd(curr);
            Screen::LaneLeftEnd(curr);
            Screen::Right(curr);
            Screen::RoadRightEnd(curr);    
            Screen::LaneRightEnd(curr);    
            curr.moveByStep(framelength);
            tie(new_x,new_y) = curr.getLocation();
            
            for(int k = (int)round(new_x); k< round(new_x+l);k++)
            {
                if(k>=height || k<0) continue;
                for(int j = (int)round(new_y); j< round(new_y+b);j++)
                {
                    if(j>=width|| j<0) continue;
                    if(screen.at(j).at(k) == ' ' || screen.at(j).at(k) == '=')
                        screen.at(j).at(k) = curr.symbol;                    
                    else
                    {
                        screen.at(j).at(k) = '!';
                    } 
                    //if(k+l>=position && k<=position) stop = true;
                }
            }
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
            //Screen::PrintDisplayInfo();
        }
    }

    void Screen::RunDisplay(float FutureTime,float framelength)
    {
        while(FutureTime>CurrentTime)
        {
            CurrentTime+=framelength;
            Screen::refresh(framelength);
        }
    }

    void Screen::RunFor(int delta_time)
    {
        //TimeJump is the time in future till which we want the Simulation to run.
        Screen::RunSimulation(CurrentTime+delta_time);
    }

    void Screen::RunDisplayFor(int delta_time)
    {
        //TimeJump is the time in future till which we want the Simulation to run.
        Screen::RunDisplay(CurrentTime+delta_time,0.25);
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
