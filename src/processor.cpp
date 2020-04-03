#include <string>
#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{    
    float dTotal;
    float dIdle;
    float utilization;
    // Read and update the CPU values
    mapCpu();
    CpuUtilizationValues();
    // Calculate delta utilization values
    dTotal = CPUUtilizationValues_[CPUValues::Total_] - pTotal_;
    dIdle = CPUUtilizationValues_[CPUValues::Idle_] - pIdle_;
    utilization = (dTotal - dIdle) / dTotal;
    // Update the previous values with new values
    pTotal_ = CPUUtilizationValues_[CPUValues::Total_];
    pIdle_ = CPUUtilizationValues_[CPUValues::Idle_];
    return utilization;
}

// Update CPU Utilization values
void Processor::CpuUtilizationValues()
{
    CPUUtilizationValues_[CPUValues::Idle_] = CpuMap_[LinuxParser::CPUStates::kIdle_] + CpuMap_[LinuxParser::CPUStates::kIOwait_];
    CPUUtilizationValues_[CPUValues::NonIdle_] = CpuMap_[LinuxParser::CPUStates::kUser_] + CpuMap_[LinuxParser::CPUStates::kNice_] + CpuMap_[LinuxParser::CPUStates::kSystem_] + CpuMap_[LinuxParser::CPUStates::kSteal_] + CpuMap_[LinuxParser::CPUStates::kIRQ_] + CpuMap_[LinuxParser::CPUStates::kSoftIRQ_];
    CPUUtilizationValues_[CPUValues::Total_] = CPUUtilizationValues_[CPUValues::Idle_] + CPUUtilizationValues_[CPUValues::NonIdle_];
}

// Create an unordered map from parsed data based on cpu states
void Processor::mapCpu()
{
    std::vector<std::string> cpuUtilization;
    cpuUtilization = LinuxParser::CpuUtilization();
    for (size_t i = 0; i < cpuUtilization.size(); ++i)
    {
        CpuMap_[static_cast<LinuxParser::CPUStates>(i)] = std::stof(cpuUtilization[i]);
    }
}