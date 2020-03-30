#include <string>
//#include <iostream>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds)
{
    int hh;
    int mm;
    int ss;
    std::string time;

    hh = seconds / 3600;
    mm = (seconds % 3600) / 60;
    ss = (seconds % 3600) % 60;

    time = std::to_string(hh) + ":" + std::to_string(mm) + ":" + std::to_string(ss);

    return time;
}

//Unit Testing 
/* The output for 12500 seconds should be 3:28:20
int main()
{
    std::cout << Format::ElapsedTime(12500) << "\n";
}
*/