#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <unordered_map>

class Processor
{
public:
    float Utilization(); // TODO: See src/processor.cpp

    // TODO: Declare any necessary private members
private:

    enum CPUValues
    {
        Idle_,
        NonIdle_,
        Total_
    };

    std::unordered_map<CPUValues, long> CPUUtilizationValues_;
    std::unordered_map<LinuxParser::CPUStates, long> CpuMap_;
    
    void CpuUtilizationValues();
    void mapCpu();
};

#endif