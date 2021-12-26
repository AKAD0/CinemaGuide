#pragma once

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>

#include <map>

#include <vector>

#include "connectorDB.h"
using namespace std;

typedef map<string, string> mapstr;
typedef vector<string> vecstr;

bool clear(const string& str, bool quotes = true);



class ConnectorMySql : public ConnectorDb {
public:
  ConnectorMySql(const string &host, const string &usr, const string &psw,
                 const string &db, const int port);

  ~ConnectorMySql() = default;

  int Add(const string &table, const map<string, string> &data) override;

  int Delete(const string &table, const string& condition) override;

  int Edit(const string &table, const mapstr &newData, const string& condition) override;

  vector<mapstr> Get(const  string &table, const  vecstr &cols, string condition = "") override;
private:
  sql::Driver *driver; //incompatible with smart pointers: https://stackoverflow.com/questions/17176122/how-to-combine-sqldriver-with-smart-pointers
  unique_ptr<sql::Connection> con;
  unique_ptr<sql::ResultSet> res;
  unique_ptr<sql::Statement> stmt;
  unique_ptr<sql::PreparedStatement> prstmt;
};
