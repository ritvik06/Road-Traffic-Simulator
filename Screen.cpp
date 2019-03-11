#include<iostream>
#include<vector>
#include<cmath>
#include<sstream>
#include<fstream>
#include<stdexcept>
#include<chrono>
#include<cstdlib>
#include<tuple>

using namespace std;
class Screen
{
    private:
    tuple<int, int> size;
    vector<vector<char>> screen;
    
    Screen(int length, int breadth)
    {
        size = make_tuple(length, breadth);
        screen = vector<vector<char>> (length,vector<char>(breadth,'0'));
    }
};
int main()
{
    exit(0);
}