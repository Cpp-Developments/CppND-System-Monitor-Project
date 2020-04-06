#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()
{
    vector<std::string> ProcessCPU;
    ProcessCPU = LinuxParser::CpuUtilization(pid_);

    long utime = std::stol(ProcessCPU[13]);
    long stime = std::stol(ProcessCPU[14]);
    long cutime = std::stol(ProcessCPU[15]);
    long cstime = std::stol(ProcessCPU[16]);
    long starttime = std::stol(ProcessCPU[21]);
    long hz = sysconf(_SC_CLK_TCK);
    long int uptime = UpTime();
    long totaltime;
    long int seconds;

    totaltime = utime + stime + cutime + cstime;
    seconds = uptime - (starttime / hz);

    return (totaltime / hz) / (seconds * 1.0);
}

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { return string(); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const &a [[maybe_unused]]) const { return true; }