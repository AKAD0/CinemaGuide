#include "../include/connectorMysql.h"


bool clear(const string& str, bool quotes) {
  vector<string> stops = {"insert", "delete", "update", "drop",
                          "alter",  "select", ";"};
  if (quotes) {
    stops.push_back("\"");
    stops.push_back("'");
  }
  for (auto &key : stops) {
    if (str.find(key) < str.size()) {
      cout << str << ": "
           << "INJECTION\n"
           << "position: " << str.find(key);
      ;
      return true;
    }
  }
  return false;
}

ConnectorMySql::ConnectorMySql(const string &host, const string &usr, const string &psw,
                               const string &db, const int port) {
    // Create a connection
    driver = get_driver_instance();
    con = unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3306", usr, psw));
    // Connect to the MySQL test database
    con->setSchema("Kinopoiskdata");
    stmt = unique_ptr<sql::Statement>(con->createStatement());
  };


  int ConnectorMySql::Add(const string &table, const map<string, string> &data) {
    try {
      if (clear(table))
        return -1;
      string sqlquery = "insert into " + table + " (";
      for (auto &it : data) {
        if (clear(it.first))
          return -1;
        sqlquery += it.first + ", ";
      }
      sqlquery.pop_back();
      sqlquery.pop_back();
      sqlquery += ") values (";

      for (auto &it : data) {
        if (clear(it.second))
          return -1;
        sqlquery += "\"" + it.second + "\", ";
      }
      sqlquery.pop_back();
      sqlquery.pop_back();
      sqlquery += ");";
      prstmt = unique_ptr<sql::PreparedStatement>(con->prepareStatement(sqlquery));
      prstmt->execute();

    } catch (sql::SQLException &e) {
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
      return -1;
    }
    return 0;
  };

  int ConnectorMySql::Delete(const string &table, const string& condition) {
    if (clear(table))
      return -1;
    if (clear(condition, false))
      return -1;
    string sqlquery = "delete from " + table + " where " + condition + ";";
    prstmt = unique_ptr<sql::PreparedStatement>(con->prepareStatement(sqlquery));
    prstmt->execute();
    return 0;
  };

  int ConnectorMySql::Edit(const string &table, const mapstr &newData, const string& condition) {
    if (clear(table))
      return -1;
    string sqlquery = "update " + table + " set ";

    for (auto &it : newData) {
      if (clear(it.first) || clear(it.second))
        return -1;
      sqlquery += it.first + " = \"" + it.second + "\", ";
    }
    sqlquery.pop_back();
    sqlquery.pop_back();
    sqlquery += " where ";
    if (clear(condition, false))
      return -1;
    sqlquery += condition + ";";
    prstmt = unique_ptr<sql::PreparedStatement>(con->prepareStatement(sqlquery));
    prstmt->execute();
    return 0;
  };

  vector<mapstr> ConnectorMySql::Get(const string &table, const vecstr &cols, string condition) {
    vector<mapstr> answer(0);

    string sqlquery = "select ";

    for (auto &it : cols) {
      sqlquery += it + ", ";
    }
    sqlquery.pop_back();
    sqlquery.pop_back();

    sqlquery += " from " + table;
    if (condition != "")
      sqlquery += " where " + condition;
    sqlquery += +" order by " + *cols.begin();
    string existquery = "select count(*) from (" + sqlquery + ") as tab;";
    sqlquery += ";";

    prstmt = unique_ptr<sql::PreparedStatement>(con->prepareStatement(existquery));
    res = unique_ptr<sql::ResultSet>(prstmt->executeQuery());
    res->next();
    int exist = res->getInt("count(*)");
    if (!exist) {
      cout << "NOT FOUND!\n";
      return vector<mapstr>(0);
    }

    prstmt = unique_ptr<sql::PreparedStatement>(con->prepareStatement(sqlquery));
    res = unique_ptr<sql::ResultSet>(prstmt->executeQuery());
    res->beforeFirst();
    while (res->next()) {
      mapstr buffer = mapstr();
      for (auto &it : cols) {
        string temp = res->getString(it);
        buffer[it] = temp;
      }
      answer.push_back(buffer);
    }
    return answer;
  };

