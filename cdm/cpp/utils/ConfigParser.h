/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once

#ifdef REBASE_TOOL
#define CDM_DECL
#else
#include "CommonDataModel.h"
#endif

#include <string>
#include <vector>
#include <map>

class CDM_DECL ConfigSet
{
public:
    void SetKeyValues(const std::map<std::string, std::string>& keyValues);
    void AddKeyValue(const std::string& key, const std::string& value);
    const std::map<std::string, std::string>& GetKeyValues() const { return m_keyValues; }

    bool HasKey(const std::string& key) const;
    std::string GetValue(const std::string& key) const;

private:
    std::map<std::string, std::string> m_keyValues;
};

class CDM_DECL ConfigParser
{
public:
    ConfigParser(const std::string& configFilePath);

    const std::vector<ConfigSet>& GetConfigSets() const { return m_configSets; }

private:
    void ParseConfigFile(const std::string& configFile);
    std::tuple<std::string, std::string> ParseKeyValue(const std::string& line);

    std::map<std::string, std::string> m_globalKeyValues;
    std::vector<ConfigSet> m_configSets;

    bool m_parsingGlobalKeyValues = true;
};