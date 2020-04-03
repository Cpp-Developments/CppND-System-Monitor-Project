#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <unordered_map>
#include "linux_parser.h"

class Processor
{
public:
    float Utilization(); // TODO: See src/processor.cpp

    // TODO: Declare any necessary private members
private:

    enum CPUValues {
        Idle_,
        NonIdle_,
        Total_
    };

    float pIdle_{0.0};
    float pTotal_{0.0};
    float pNonIdle_{0.0};

    std::unordered_map<CPUValues, float, std::hash<std::underlying_type<CPUValues>::type>> CPUUtilizationValues_;
    std::unordered_map<LinuxParser::CPUStates, float, std::hash<std::underlying_type<LinuxParser::CPUStates>::type>> CpuMap_;
    
    void CpuUtilizationValues();
    void mapCpu();
};

#endif