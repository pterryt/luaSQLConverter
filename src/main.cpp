#include <FileHandler.h>
#include <ConfigurationManager.h>
#include <DatabaseHandler.h>
#include <iostream>
#include <filesystem>

int main() {

    auto& config = ConfigurationManager::getInstance();
    bool loaded = config.loadConfig();
    std::cout << "Load result: " + std::string(loaded ? "true" : "false") << std::endl;


    const std::string outputDir = config.getString("Path", "OutputDirectory", "../output");
    const std::string inputDir = config.getString("Path", "InputDirectory", "../input");
    const std::string globalsPath =  inputDir + "/GlobalStrings.lua";
    const std::string gluesPath = inputDir + "/GlueStrings.lua";
    const std::vector<LuaEntry> globEntries = FileHandler::parseFile(globalsPath);
    const std::vector<LuaEntry> glueEntries = FileHandler::parseFile(gluesPath);
    sql::Connection *con = DatabaseHandler::connectToDatabase();


//    FileHandler::createFile(e);

    return 0;
}