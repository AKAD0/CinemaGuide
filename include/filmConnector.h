#pragma once

#include <map>

#include <vector>

#include "connector.h"
#include "connectorMysql.h"
using namespace std;


typedef map<string, string> mapstr;
typedef vector<string> vecstr;


class FilmConnector : public Connector {
public:
  FilmConnector(const string &host, const string &usr, const string &psw,
                const string &db, const int port);

  ~FilmConnector() = default;

  int AddFilm(const string &filmname, int year, const string &country, const string& format,
              const string &director, float rate = 0, string description = "",
              vecstr genre = {}, vecstr actor = {}, int idfilm = -1);

  int DeleteFilm(int id);

  int EditFilm(int id, const mapstr& data);

  mapstr GetFilmInfo(int id, const vecstr& cols);

  int RecountRate();

  vecstr GetFilmId(string condition = "");

  void AddFilmDetail(const string& filmid, const string& table, const vecstr& data);

  int RecountRateFilm(int id);

  int FindDetail(const string &table, const string &name);

  int DeleteDetail(const string &table, const string& filmid, const string& detail);

  string GetDetailId(const string &table, const string &name);

  vecstr GetDetail(const string& filmid, const string &table);
};
