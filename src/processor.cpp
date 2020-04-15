#include <string>
#include "processor.h"

// Class constructor
Processor::Processor() : cpuID_("") {};
Processor::Processor(std::string num) : cpuID_(num) {};

// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
    long dTotal;
    long dNonIdle;
    // Read and update the CPU values
    mapCpu();
    CpuUtilizationValues();
    // Calculate delta utilization values
    dTotal = CPUUtilizationValues_[CPUValues::Total_] - pTotal_;
    dNonIdle = CPUUtilizationValues_[CPUValues::NonIdle_] - pNonIdle_;
    // Update the previous values with new values
    pTotal_ = CPUUtilizationValues_[CPUValues::Total_];
    pNonIdle_ = CPUUtilizationValues_[CPUValues::NonIdle_];
    return dNonIdle / (dTotal * 1.0);
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
    cpuUtilization = LinuxParser::CpuUtilization(cpuID_);
    for (size_t i = 0; i < cpuUtilization.size(); ++i)
    {
        CpuMap_[static_cast<LinuxParser::CPUStates>(i)] = std::stol(cpuUtilization[i]);
    }
}