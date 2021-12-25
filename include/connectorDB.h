#pragma once

#include <map>
#include <vector>

using namespace std;

typedef map<string, string> mapstr;
typedef vector<string> vecstr;


class ConnectorDb {
public:
  ConnectorDb() = default;
  ConnectorDb(const ConnectorDb &) = delete;
  ConnectorDb &operator=(const ConnectorDb &) = default;
  virtual ~ConnectorDb() = default;
  virtual int Add(string &table, mapstr &data) = 0;
  virtual int Delete(const string &table, string condition) = 0;
  virtual int Edit(string &table, mapstr &newData, string condition) = 0;
  virtual vector<mapstr> Get(string &table, vecstr &cols,
                             string condition = "") = 0;
};