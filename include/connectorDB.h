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


  virtual int Add(const string &table, const map<string, string> &data) = 0;
  virtual int Delete(const string &table, const string& condition) = 0;
  virtual int Edit(const string &table, const mapstr &newData, const string& condition) = 0;
  virtual vector<mapstr> Get(const  string &table, const  vecstr &cols, string condition = "") = 0;


};