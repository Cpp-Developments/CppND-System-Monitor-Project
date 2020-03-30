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
    std::string hh_s;
    std::string mm_s;
    std::string ss_s;

    hh = seconds / 3600;
    mm = (seconds % 3600) / 60;
    ss = (seconds % 3600) % 60;

    // If less than 10 add "0" before the digit
    hh < 10? hh_s = "0" + std::to_string(hh) : hh_s = std::to_string(hh);
    mm < 10? mm_s = "0" + std::to_string(mm) : mm_s = std::to_string(mm);
    ss < 10? ss_s = "0" + std::to_string(ss) : ss_s = std::to_string(ss);   

    return hh_s + ":" + mm_s + ":" + ss_s;
}

//Unit Testing 
/* The output for 12500 seconds should be 3:28:20
int main()
{
    std::cout << Format::ElapsedTime(12500) << "\n";
}
*/