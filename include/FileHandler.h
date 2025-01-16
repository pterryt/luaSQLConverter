//
// Created by Terry on 1/15/2025.
//

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <LuaEntry.h>
#include <vector>

namespace FileHandler {
    std::string trim(const std::string &str);

    LuaEntry parseLine(const std::string &line);

    std::vector<LuaEntry> parseFile(const std::string &filePath);

    void createFile(const std::vector<LuaEntry> &entries);

    void printLast5Entries(const std::vector<LuaEntry> &entries);

    void printDetails(const std::vector<LuaEntry> &entries);
}

#endif //FILEHANDLER_H
