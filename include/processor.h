#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <unordered_map>
#include "linux_parser.h"

class Processor
{
public:
    Processor(std::string num);
    float Utilization(); // TODO: See src/processor.cpp

    // TODO: Declare any necessary private members
private:
    enum CPUValues
    {
        Idle_,
        NonIdle_,
        Total_
    };
    std::string cpuID_;
    long pTotal_{0};
    long pNonIdle_{0};

    std::unordered_map<CPUValues, long, std::hash<std::underlying_type<CPUValues>::type>> CPUUtilizationValues_;
    std::unordered_map<LinuxParser::CPUStates, long, std::hash<std::underlying_type<LinuxParser::CPUStates>::type>> CpuMap_;

    void CpuUtilizationValues();
    void mapCpu();
};

#endif