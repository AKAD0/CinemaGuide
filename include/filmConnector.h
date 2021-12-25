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

  ~FilmConnector();

  int AddFilm(string &filmname, int year, string &country, string format,
              string &director, float rate = 0, string description = "",
              vecstr genre = {}, vecstr actor = {}, int idfilm = -1);

  int DeleteFilm(int id);

  int EditFilm(int id, mapstr data);

  mapstr GetFilmInfo(int id, vecstr cols);

  int RecountRate();

  vecstr GetFilmId(string condition = "");

  void AddFilmDetail(string filmid, string table, vecstr data);

  int RecountRateFilm(int id);

  int FindDetail(string &table, string &name);

  int DeleteDetail(string &table, string filmid, string detail);

  string GetDetailId(string &table, string &name);

  vecstr GetDetail(string filmid, string &table);
};
