
#include <linux_parser.h>
#include <string>

#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
    long dIdle;
    long dTotal;

    mapCpu();
    CpuUtilizationValues();

    dTotal = CPUUtilizationValues_[CPUValues::Total_];
    dIdle = CPUUtilizationValues_[CPUValues::Idle_];

    mapCpu();
    CpuUtilizationValues();

    dTotal -= CPUUtilizationValues_[CPUValues::Total_];
    dIdle -= CPUUtilizationValues_[CPUValues::Idle_];
    return (dTotal - dIdle)/dTotal;
}

void Processor::CpuUtilizationValues()
{
    CPUUtilizationValues_[CPUValues::Idle_] = CpuMap_[LinuxParser::CPUStates::kIdle_] + CpuMap_[LinuxParser::CPUStates::kIOwait_];
    CPUUtilizationValues_[CPUValues::NonIdle_] = CpuMap_[LinuxParser::CPUStates::kUser_] + CpuMap_[LinuxParser::CPUStates::kNice_] + CpuMap_[LinuxParser::CPUStates::kSystem_] + CpuMap_[LinuxParser::CPUStates::kSteal_] + CpuMap_[LinuxParser::CPUStates::kIRQ_] + CpuMap_[LinuxParser::CPUStates::kSoftIRQ_];
    CPUUtilizationValues_[CPUValues::Total_] = CPUUtilizationValues_[CPUValues::Idle_] + CPUUtilizationValues_[CPUValues::NonIdle_]; 
}

void Processor::mapCpu()
{
    std::vector<std::string> cpuUtilization;
    cpuUtilization = LinuxParser::CpuUtilization();
    for ( i = 0; i < cpuUtilization.size(); ++i)
    {
        CpuMap_[LinuxParser::CPUStates(i)] = std::stol(cpuUtilization[i]);
    }
}