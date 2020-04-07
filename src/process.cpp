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

// Class constructor
Process::Process(int p) : pid_(p), cpu_(CpuUtilization()){};

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()
{
    vector<std::string> ProcessCPU;
    ProcessCPU = LinuxParser::CpuUtilization(pid_);

    long int utime = std::stol(ProcessCPU[13]);
    long int stime = std::stol(ProcessCPU[14]);
    long int cutime = std::stol(ProcessCPU[15]);
    long int cstime = std::stol(ProcessCPU[16]);
    long int starttime = std::stol(ProcessCPU[21]);
    long int hz = sysconf(_SC_CLK_TCK);
    long uptime = LinuxParser::UpTime();
    long int totaltime;
    long int seconds;

    totaltime = utime + stime + cutime + cstime;
    seconds = uptime - (starttime / hz);

    return (totaltime / hz) / (seconds * 1.0);
}

// TODO: Return the command that generated this process
string Process::Command()
{
    return LinuxParser::Command(pid_);
}

// TODO: Return this process's memory utilization
string Process::Ram()
{
    return LinuxParser::Ram(pid_);
}

// TODO: Return the user (name) that generated this process
string Process::User()
{
    return LinuxParser::User(pid_);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime()
{
    return LinuxParser::UpTime(pid_);
}

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const &a) const
{
    return a.cpu_ <= this->cpu_;
}