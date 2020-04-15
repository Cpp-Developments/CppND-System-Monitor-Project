#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <linux_parser.h>
#include <algorithm>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor &System::Cpu()
{
    cpu_ = Processor();
    return cpu_;
}

// TODO: Return a container of cpu info
std::vector<Processor> &System::Cpus()
{
    GetNumCPU();
    std::vector<Processor> pcpus = cpus_;
    cpus_ = {};
    for (int i = 0; i < cpuNum_; ++i)
    {
        cpus_.push_back(Processor(std::to_string(i)));
        cpus_[i].pTotal_ = pcpus[i].pTotal_;
        cpus_[i].pNonIdle_ = pcpus[i].pNonIdle_;
    }
    return cpus_;
}

int System::GetNumCPU()
{
    cpuNum_ = LinuxParser::GetNumberofCPUs();
    return cpuNum_;
}

// TODO: Return a container composed of the system's processes
vector<Process> &System::Processes()
{
    UpdateProcesses_();
    return processes_;
}

// TODO: Update processes
void System::UpdateProcesses_()
{
    processes_.clear();
    vector<int> pids = LinuxParser::Pids();
    for (int p : pids)
    {
        processes_.push_back(Process(p));
    }
    std::sort(processes_.begin(), processes_.end());
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel()
{
    return LinuxParser::Kernel();
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization()
{
    return LinuxParser::MemoryUtilization();
}

// TODO: Return the operating system name
std::string System::OperatingSystem()
{
    return LinuxParser::OperatingSystem();
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses()
{
    return LinuxParser::RunningProcesses();
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses()
{
    return LinuxParser::TotalProcesses();
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime()
{
    return LinuxParser::UpTime();
}