#include "../include/connectorMysql.h"
#include "../include/filmConnector.h"
#include <memory>





  FilmConnector::FilmConnector(const string &host, const string &usr, const string &psw,
                const string &db, const int port) {
    std::unique_ptr<ConnectorMySql> buffer(new ConnectorMySql(host, usr, psw, db, port));
    conn = move(buffer);
  };

  int FilmConnector::AddFilm(const string &filmname, int year, const string &country, const string& format,
              const string &director, float rate, string description,
              vecstr genre, vecstr actor, int idfilm) {

    mapstr data;
    if (idfilm > 0)
      data["idfilm"] = to_string(idfilm);
    data["filmname"] = filmname;
    data["year"] = to_string(year);
    data["country"] = country;
    data["format"] = format;
    data["director"] = director;
    if (description != "")
      data["description"] = description;
    if (rate > 0)
      data["format"] = to_string(rate);
    string table = "film";
    if (conn->Add(table, data)) {
      cout << "Film adding fail!\n";
      return -1;
    };

    string condition = "filmname = \"" + data["filmname"] + "\"";
    vecstr userid = {"idfilm"};
    vector<mapstr> res = conn->Get(table, userid, condition);
    string id = res[0]["idfilm"];
    if (genre.size()) {
      AddFilmDetail(id, "genre", genre);
    }
    if (actor.size()) {
      AddFilmDetail(id, "actor", actor);
    }

    return 0;
  };

  int FilmConnector::DeleteFilm(int id) {
    string table = "film";
    string condition = "idfilm = " + to_string(id);
    if (conn->Delete(table, condition)) {
      cout << "Film deleting fail!\n";
      return -1;
    };
    return 0;
  };

  int FilmConnector::EditFilm(int id, const mapstr& data) {
    string table = "film";
    string condition = "idfilm = " + to_string(id);
    if (conn->Edit(table, data, condition)) {
      cout << "Film editing fail!\n";
      return -1;
    };
    return 0;
  };

  mapstr FilmConnector::GetFilmInfo(int id, const vecstr& cols) {
    string table = "film";
    string condition = " idfilm = " + to_string(id);
    vector<mapstr> filminfo = conn->Get(table, cols, condition);
    if (!filminfo.size()) {
      return mapstr{};
    }
    return filminfo[0];
  };

  int FilmConnector::RecountRate() {
    vecstr allfilms = GetFilmId();
    for (auto &filmid : allfilms) {
      if (RecountRateFilm(stoi(filmid))) {
        cout << "Rate recountig fail!\n";
        return -1;
      };
    }
    return 0;
  };

  vecstr FilmConnector::GetFilmId(string condition) {
    string table = "film";
    vecstr cols = {"idfilm"};
    vector<mapstr> ids = conn->Get(table, cols, condition);
    vecstr idlist(0);
    if (!ids.size()) {
      return idlist;
    }
    for (auto &it : ids) {
      idlist.push_back(it["idfilm"]);
    }

    return idlist;
  };

  void FilmConnector::AddFilmDetail(const string& filmid, const string& table, const vecstr& data) {
    if (data.size()) {
      for (auto &item : data) {
        if (FindDetail(table, item) == -1) {
          mapstr temp = {{table + "name", item}};
          conn->Add(table, temp);
        }
        int id = FindDetail(table, item);
        string tab = "film_has_" + table;
        mapstr connectid = {{"film_idfilm", filmid},
                            {table + "_id" + table, to_string(id)}};
        conn->Add(tab, connectid);
      }
    }
  };

  int FilmConnector::RecountRateFilm(int id) {
    string table = "estimation";
    string condition = "film_idfilm = " + to_string(id);
    vecstr cols = {"estimate"};
    vector<mapstr> estimates = conn->Get(table, cols, condition);
    float mean;
    for (auto &est : estimates) {
      mean += stoi(est["estimate"]);
    }
    mean = mean / estimates.size();
    mapstr edit = {{"rate", to_string(mean)}};
    if (EditFilm(id, edit)) {
      cout << "Film editing fail!\n";
      return -1;
    };
    return 0;
  };

  int FilmConnector::FindDetail(const string &table, const string &name) {
    vecstr cols = {"id" + table};
    vector<mapstr> answer =
        conn->Get(table, cols, " " + table + "name = \"" + name + "\"");
    if (!answer.size()) {
      return -1;
    }
    int res = stoi((conn->Get(
        table, cols, " " + table + "name = \"" + name + "\"")[0][cols[0]]));
    return res;
  }

  int FilmConnector::DeleteDetail(const string &table, const string& filmid, const string& detail) {
    string id = GetDetailId(table, detail);
    string condition = "film_idfilm = " + filmid + " and " + table + "_id" +
                       table + " = \"" + id + "\"";
    string tab = "film_has_" + table;
    if (conn->Delete(tab, condition)) {
      cout << "Detail deleting fail!\n";
      return -1;
    };
    return 0;
  };

  string FilmConnector::GetDetailId(const string &table, const string &name) {
    string condition = table + "name = \"" + name + "\"";
    vecstr cols = {"id" + table};
    vector<mapstr> answer = conn->Get(table, cols, condition);
    string result = "-1";
    if (answer.size())
      result = answer[0][cols[0]];
    return result;
  }

  vecstr FilmConnector::GetDetail(const string& filmid, const string &table) {
    vecstr result(0);
    string condition = "film_idfilm = " + filmid;
    string tab = "film_has_" + table;
    string field = table + "_id" + table;
    vecstr cols = {field};
    vecstr cols_detail = {table + "name"};
    vector<mapstr> list = conn->Get(tab, cols, condition);
    vecstr ids(0);
    for (auto &mapa : list) {
      string cond = "id" + table + " = " + mapa[field];
      vector<mapstr> answer = conn->Get(table, cols_detail, cond);
      if (answer.size()) {
        result.push_back(answer[0][cols_detail[0]]);
      }
    }
    return result;
  }
