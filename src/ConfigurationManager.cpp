//
// Created by Terry on 1/15/2025.
//

#include "ConfigurationManager.h"
#include <iostream>
#include <filesystem>
#include <stdexcept>

ConfigurationManager& ConfigurationManager::getInstance() {
    static ConfigurationManager instance;
    return instance;
}

bool ConfigurationManager::loadConfig() {
    ini.SetUnicode();

    if(!std::filesystem::exists(ConfigPath)) {
        saveDefaultConfig();
        throw std::runtime_error("Please configure your config.ini file before continuing.");
    }

    SI_Error rc = ini.LoadFile(ConfigPath.c_str());
    return rc == SI_OK;
}

void ConfigurationManager::saveDefaultConfig() {

    ini.SetValue("Database", "Host", "127.0.0.1");
    ini.SetValue("Database", "Port", "3306");
    ini.SetValue("Database", "User", "");
    ini.SetValue("Database", "Password", "");
    ini.SetValue("Database", "DatabaseName", "wow_dev_central_data");
    ini.SetValue("Path", "InputDirectory", "../input");
    ini.SetValue("Path", "OuputDirectory", "../output");

    SI_Error rc = ini.SaveFile(ConfigPath.c_str());
    if (rc != SI_OK) {
        std::cerr << "Failed to save default configuration to: " << ConfigPath << std::endl;
    }
}

std::string ConfigurationManager::getString(const std::string &section, const std::string &key,
                                            const std::string &defaultValue) const {
    return ini.GetValue(section.c_str(), key.c_str(), defaultValue.c_str());
}

int ConfigurationManager::getInt(const std::string &section, const std::string &key, const int defaultValue) const {
    const char* value = ini.GetValue(section.c_str(), key.c_str(), nullptr);
    return value ? std::stoi(value) : defaultValue;
}


bool ConfigurationManager::getBool(const std::string &section, const std::string &key, const bool defaultValue) const {
    const char* value = ini.GetValue(section.c_str(), key.c_str(), nullptr);
    if (!value) {
        return defaultValue;
    }
    std::string lowerValue = value;
    std::transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(), ::tolower);
    return lowerValue == "true" || lowerValue == "1";
}
