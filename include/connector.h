#pragma once

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>

#include <map>

#include <vector>

#include <memory>

#include "connectorDB.h"

using namespace std;

typedef map<string, string> mapstr;
typedef vector<string> vecstr;



class Connector {
public:
  Connector() = default;
  Connector(const Connector &) = delete;
  Connector &operator=(const Connector &) = delete;
  ~Connector() = default;

protected:
  std::unique_ptr<ConnectorDb> conn;
};