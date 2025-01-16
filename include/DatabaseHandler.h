//
// Created by Terry on 1/15/2025.
//

#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <mysql_connection.h>
#include <LuaEntry.h>
#include <vector>

namespace DatabaseHandler {

    sql::Connection *connectToDatabase();

    void createTables(sql::Connection *con);

    void insertData(sql::Connection *con, const std::vector<LuaEntry> &entries, const std::string& tableName);

    const std::string GlueStringsTable = "lua_Gluestrings_12340";
    const std::string GlueStringsTableStatement = "CREATE TABLE IF NOT EXISTS " + GlueStringsTable + " ("
                                                  "id INT AUTO_INCREMENT PRIMARY KEY, "
                                                  "tag TEXT, "
                                                  "text TEXT, "
                                                  "comment TEXT)";

    const std::string GlobalStringsTable = "lua_Globalstrings_12340";
    const std::string GlobalStringsTableStatement = "CREATE TABLE IF NOT EXISTS " + GlobalStringsTable + " ("
                                                 "id INT AUTO_INCREMENT PRIMARY KEY, "
                                                 "tag TEXT, "
                                                 "text TEXT, "
                                                 "comment TEXT)";

}

#endif //DATABASEHANDLER_H
