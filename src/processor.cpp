
#include <linux_parser.h>
#include <string>

#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
    long dIdle;
    long dTotal;

    // Read and copy the first CPU values
    mapCpu();
    CpuUtilizationValues();
    dTotal = CPUUtilizationValues_[CPUValues::Total_];
    dIdle = CPUUtilizationValues_[CPUValues::Idle_];
    //Update the CPU values
    mapCpu();
    CpuUtilizationValues();
    dTotal -= CPUUtilizationValues_[CPUValues::Total_];
    dIdle -= CPUUtilizationValues_[CPUValues::Idle_];
    //Calculate CPU utilization with differential values
    return (dTotal - dIdle) / dTotal;
}

// Update CPU Utilization values
void Processor::CpuUtilizationValues()
{
    CPUUtilizationValues_[CPUValues::Idle_] = CpuMap_[LinuxParser::CPUStates::kIdle_] + CpuMap_[LinuxParser::CPUStates::kIOwait_];
    CPUUtilizationValues_[CPUValues::NonIdle_] = CpuMap_[LinuxParser::CPUStates::kUser_] + CpuMap_[LinuxParser::CPUStates::kNice_] + CpuMap_[LinuxParser::CPUStates::kSystem_] + CpuMap_[LinuxParser::CPUStates::kSteal_] + CpuMap_[LinuxParser::CPUStates::kIRQ_] + CpuMap_[LinuxParser::CPUStates::kSoftIRQ_];
    CPUUtilizationValues_[CPUValues::Total_] = CPUUtilizationValues_[CPUValues::Idle_] + CPUUtilizationValues_[CPUValues::NonIdle_];
}

// Create an unordered map from pared data based on cpu states
void Processor::mapCpu()
{
    std::vector<std::string> cpuUtilization;
    cpuUtilization = LinuxParser::CpuUtilization();
    for (size_t i = 0; i < cpuUtilization.size(); ++i)
    {
        CpuMap_[LinuxParser::CPUStates(i)] = std::stol(cpuUtilization[i]);
    }
}