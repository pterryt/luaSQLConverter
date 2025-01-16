//
// Created by Terry on 1/15/2025.
//

#include "FileHandler.h"

#include <iostream>
#include <fstream>
#include <regex>
#include <stdexcept>
#include <filesystem>

namespace FileHandler {
    std::string trim(const std::string &str) {
        size_t start = str.find_first_not_of(" \t\n\r\f\v");

        if (start == std::string::npos) {
            return "";
        }

        size_t end = str.find_last_not_of(" \t\n\r\f\v");

        return str.substr(start, end - start + 1);
    }


    LuaEntry parseLine(const std::string &line) {
        LuaEntry entry;

        size_t equalPos = line.find(" = \"");
        if (equalPos == std::string::npos) {
            return entry;
        }

        size_t semiColonPos = line.rfind("\";");
        if (semiColonPos == std::string::npos) {
            return entry;
        }

        entry.tag = trim(line.substr(0, equalPos));
        entry.text = line.substr(equalPos + 4, semiColonPos - (equalPos + 4));

        size_t commentPos = line.find("--", semiColonPos + 2);
        if (commentPos != std::string::npos) {
            entry.comment = trim(line.substr(commentPos + 2));
        }

        return entry;
    }

    std::vector<LuaEntry> parseFile(const std::string &filePath) {
        std::filesystem::path cwd = std::filesystem::current_path();
        std::cout << cwd << std::endl;
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Error opening lua file: " + filePath);
        }
        std::vector<LuaEntry> entries;
        std::string line;

        while (std::getline(file, line)) {
            LuaEntry entry = parseLine(line);
            if (!entry.tag.empty()) {
                entries.push_back(entry);
            }
        }

        file.close();
        return entries;
    }

    void createFile(const std::vector<LuaEntry> &entries) {
        std::ofstream outputFile("../output/output.lua");
        if (!outputFile.is_open()) {
            throw std::runtime_error("Error creating output file.");
        }

        for (const auto &entry: entries) {
            outputFile << entry.tag << " = \"" << entry.text << "\";";
            if (!entry.comment.empty()) {
                outputFile << " -- " << entry.comment;
            }
            outputFile << "\n";
        }
        std::cout << "Created lua file from database at output.lua" << "\n";
    }

    void printLast5Entries(const std::vector<LuaEntry> &entries) {
        size_t start = entries.size() > 5 ? entries.size() - 5 : 0;
        for (size_t i = start; i < entries.size(); ++i) {
            const LuaEntry &entry = entries[i];
            std::cout << "TAG: " << entry.tag << "\n";
            std::cout << "TEXT: " << entry.text << "\n";
            std::cout << "COMMENT: " << entry.comment << "\n";
            std::cout << "-------------------------\n";
        }
    }

    void printDetails(const std::vector<LuaEntry> &entries) {
        size_t totalEntries = entries.size();
        size_t entriesWithText = 0;
        size_t entriesWithComments = 0;

        for (const auto &entry: entries) {
            if (!entry.text.empty()) {
                ++entriesWithText;
            }
            if (!entry.comment.empty()) {
                ++entriesWithComments;
            }
        }

        std::cout << "Total entries: " << totalEntries << "\n";
        std::cout << "Entries with text: " << entriesWithText << "\n";
        std::cout << "Entries with comments: " << entriesWithComments << "\n";
    }
}
