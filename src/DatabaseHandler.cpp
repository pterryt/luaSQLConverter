//
// Created by Terry on 1/15/2025.
//
#include <DatabaseHandler.h>
#include <ConfigurationManager.h>
#include <mysql_driver.h>
#include <cppconn/prepared_statement.h>


auto &config = ConfigurationManager::getInstance();

sql::Connection *DatabaseHandler::connectToDatabase() {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

    std::string Host = config.getString("Database", "Host", "127.0.0.1");
    std::string Port = config.getString("Database", "Port", "3306");
    std::string User = config.getString("Database", "User", "");
    std::string Password = config.getString("Database", "Password", "");
    std::string DatabaseName = config.getString("Database", "DatabaseName", "wow-dev-central-data");

    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://" + Host + ":" + Port, User, Password);
        sql::Statement *stmt = con->createStatement();
        stmt->execute("CREATE DATABASE IF NOT EXISTS " + DatabaseName);
        delete stmt;

        con->setSchema(DatabaseName);
    } catch (sql::SQLException &e) {
        std::cerr << "Error connecting to or creating the database: " << e.what() << std::endl;
        throw;
    }
    return con;
}

void DatabaseHandler::createTables(sql::Connection *con) {
    try {
        sql::Statement *stmt = con->createStatement();
        stmt->execute(GlobalStringsTableStatement);
        stmt->execute(GlueStringsTableStatement);
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error creating tables: " << e.what() << std::endl;
    }
}

void DatabaseHandler::insertData(sql::Connection *con, const std::vector<LuaEntry> &entries,
                                 const std::string &tableName) {
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement(
                "INSERT INTO "
                + tableName +
                " (tag, text, comment"
                " VALUES (?, ?, ?)");

        for (const auto &entry: entries) {
            pstmt->setString(1, entry.tag);
            pstmt->setString(2, entry.text);
            pstmt->setString(3, entry.comment);
            pstmt->executeUpdate();
        }

        delete pstmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error inserting data: " << e.what() << std::endl;
    }
}