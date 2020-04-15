#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem()
{
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value)
      {
        if (key == "PRETTY_NAME")
        {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel()
{
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids()
{
  vector<int> pids;
  DIR *directory = opendir(kProcDirectory.c_str());
  struct dirent *file;
  while ((file = readdir(directory)) != nullptr)
  {
    // Is this a directory?
    if (file->d_type == DT_DIR)
    {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit))
      {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization()
{
  string Line;
  string KeyWord;
  float MemTotal;
  float MemFree;
  std::ifstream ifs(kProcDirectory + kMeminfoFilename);
  if (ifs.is_open())
  {
    std::getline(ifs, Line);
    std::istringstream LineStream1(Line);
    LineStream1 >> KeyWord >> MemTotal;
    std::getline(ifs, Line);
    std::istringstream LineStream2(Line);
    LineStream2 >> KeyWord >> MemFree;
    //std::cout << std::to_string((MemTotal - MemFree) / MemTotal) << "\n";
    return (MemTotal - MemFree) / MemTotal;
  };
  return 0.0;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime()
{
  std::string file;
  std::string line;
  long total;
  std::ifstream ifs(kProcDirectory + kUptimeFilename);
  if (ifs.is_open())
  {
    std::getline(ifs, line);
    std::istringstream LineStream(line);
    LineStream >> total;
    //std::cout << std::to_string(total);
    return total;
  };
  return 0;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies()
{
  return ActiveJiffies() + IdleJiffies();
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid)
{
  std::vector<std::string> cpuValues = CpuUtilization(pid);
  std::vector<int> totalIndeces{13, 14, 15, 16};
  long ActiveJiffies = 0;
  for (int i : totalIndeces)
  {
    ActiveJiffies += std::stol(cpuValues[i]);
  }
  return ActiveJiffies;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies()
{
  std::vector<std::string> cpuValues = CpuUtilization();
  std::vector<int> totalIndeces{0, 1, 2, 5, 6, 7};
  long ActiveJiffies = 0;
  for (int i : totalIndeces)
  {
    ActiveJiffies += std::stol(cpuValues[i]);
  }
  return ActiveJiffies;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies()
{
  std::vector<std::string> cpuValues = CpuUtilization();
  std::vector<int> totalIndeces{3, 4};
  long IdleJiffies = 0;
  for (int i : totalIndeces)
  {
    IdleJiffies += std::stol(cpuValues[i]);
  }
  return IdleJiffies;
}

// Return the number of available processors
int LinuxParser::GetNumberofCPUs()
{
  int num = 0;
  string line;
  string key;
  std::ifstream ifs(kProcDirectory + kCpuinfoFilename);
  if (ifs.is_open())
  {
    while (std::getline(ifs, line))
    {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "processor")
      {
        num++;
      }
    }
  }
  return num;
}

// TODO: Read and return CPU utilization specific to each cpu
vector<string> LinuxParser::CpuUtilization(std::string num)
{
  vector<string> cpu;
  string line;
  string word;
  string cpuID = ("cpu" + num);
  std::ifstream ifs(kProcDirectory + kStatFilename);
  if (ifs.is_open())
  {
    while (std::getline(ifs, line))
    {
      std::istringstream linestream(line);
      linestream >> word;
      if (word == cpuID)
      {
        while (linestream >> word)
        {
          cpu.push_back(word);
        }
        return cpu;
      }
    }
  }
  return {};
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization()
{
  vector<string> cpu;
  string line;
  string word;
  std::ifstream ifs(kProcDirectory + kStatFilename);
  if (ifs.is_open())
  {
    std::getline(ifs, line);
    std::istringstream linestream(line);
    linestream >> word;
    if (word == "cpu")
    {
      while (linestream >> word)
      {
        cpu.push_back(word);
      }
      return cpu;
    }
  }
  return {};
}

// TODO: Read and return Process CPU utilization
vector<string> LinuxParser::CpuUtilization(int pid)
{
  vector<string> cpu;
  string line;
  string word;
  std::ifstream ifs(kProcDirectory + "/" + to_string(pid) + kStatFilename);
  if (ifs.is_open())
  {
    std::getline(ifs, line);
    std::istringstream linestream(line);
    while (linestream >> word)
    {
      cpu.push_back(word);
    }
    return cpu;
  }
  return {};
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses()
{
  int value;
  string key;
  string Line;
  std::ifstream ifs(kProcDirectory + kStatFilename);
  if (ifs.is_open())
  {
    while (std::getline(ifs, Line))
    {
      std::istringstream Linestream(Line);
      Linestream >> key >> value;
      if (key == "processes")
      {
        return value;
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{
  int value;
  string key;
  string Line;
  std::ifstream ifs(kProcDirectory + kStatFilename);
  if (ifs.is_open())
  {
    while (std::getline(ifs, Line))
    {
      std::istringstream Linestream(Line);
      Linestream >> key >> value;
      if (key == "procs_running")
      {
        return value;
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid)
{
  string line;
  std::ifstream ifs(kProcDirectory + "/" + to_string(pid) + kCmdlineFilename);
  if (ifs.is_open())
  {
    std::getline(ifs, line);
    return line;
  }
  return string();
}

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid)
{
  string line;
  string key;
  string value;
  std::ifstream ifs(kProcDirectory + "/" + to_string(pid) + kStatusFilename);
  if (ifs.is_open())
  {
    while (std::getline(ifs, line))
    {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "VmSize:")
      {
        linestream >> value;
        int ram = std::stof(value) / (1024);
        return to_string(ram);
      }
    }
  }
  return string();
}

// TODO: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid)
{
  string key;
  string value;
  string line;
  std::ifstream ifs(kProcDirectory + "/" + to_string(pid) + kStatusFilename);
  if (ifs.is_open())
  {
    while (std::getline(ifs, line))
    {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid:")
      {
        return value;
      }
    }
  }
  return "NA";
}

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid)
{
  string line;
  string username;
  string pass;
  string uid;
  std::ifstream ifs(kPasswordPath);
  if (ifs.is_open())
  {
    while (std::getline(ifs, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> username >> pass >> uid;
      if (uid == Uid(pid))
      {
        return username;
      }
    }
  }
  return string();
}

// TODO: Read and return the uptime of a process
long LinuxParser::UpTime(int pid)
{
  vector<string> cpu = CpuUtilization(pid);
  long int hz = sysconf(_SC_CLK_TCK);
  long int uptime = LinuxParser::UpTime();
  long int starttime = std::stol(cpu[21]);
  return uptime - (starttime / hz);
}