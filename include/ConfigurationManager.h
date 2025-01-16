//
// Created by Terry on 1/15/2025.
//

#ifndef LEARN_CONFIGURATIONMANAGER_H
#define LEARN_CONFIGURATIONMANAGER_H

#include <SimpleIni.h>
#include <string>

class ConfigurationManager {

public:
    static ConfigurationManager &getInstance();

    bool loadConfig();

    std::string getString(
            const std::string &section,
            const std::string &key,
            const std::string &defaultValue = "") const;

    int getInt(
            const std::string &section,
            const std::string &key,
            const int defaultValue = 0) const;

    bool getBool(
            const std::string &section,
            const std::string &key,
            const bool defaultValue = false) const;

    void saveDefaultConfig();

private:
    ConfigurationManager() = default;

    ~ConfigurationManager() = default;

    ConfigurationManager(const ConfigurationManager &) = delete;

    ConfigurationManager &operator=(const ConfigurationManager &) = delete;

    CSimpleIniA ini;

    std::string ConfigPath = "../config.ini";
};

#endif //LEARN_CONFIGURATIONMANAGER_H
