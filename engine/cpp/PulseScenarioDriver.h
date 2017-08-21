/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once

#include <string>
#include <set>

class PulseScenarioDriver
{
public:
    PulseScenarioDriver() = default;
    ~PulseScenarioDriver() = default;

    bool Configure(int argc, char* argv[]);
    void Run();

private:
    bool HasArgument(const std::string& argument);
    std::string m_file;
    std::set<std::string> m_arguments;
};