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

bool clear(string str, bool quotes = true);



class ConnectorMySql : public ConnectorDb {
public:
  ConnectorMySql(const string &host, const string &usr, const string &psw,
                 const string &db, const int port);

  ~ConnectorMySql();

  int Add(string &table, map<string, string> &data) override;

  int Delete(const string &table, string condition) override;

  int Edit(string &table, mapstr &newData, string condition) override;

  vector<mapstr> Get(string &table, vecstr &cols,
                     string condition = "") override;
private:
  sql::Driver *driver;
  sql::Connection *con;
  sql::ResultSet *res = nullptr;
  sql::Statement *stmt;
  sql::PreparedStatement *prstmt = nullptr;
};
