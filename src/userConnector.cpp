#include "../include/connectorMysql.h"

#include "../include/userConnector.h"


#include "../include/filmConnector.h"




  FilmConnector::FilmConnector(const string &host, const string &usr, const string &psw,
                const string &db, const int port) {
    ConnectorMySql *buffer = new ConnectorMySql(host, usr, psw, db, port);
    conn = buffer;
  };

  FilmConnector::~FilmConnector() { delete conn; };

  int FilmConnector::AddFilm(string &filmname, int year, string &country, string format,
              string &director, float rate, string description,
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
    cout << "BEFORE\n";
    string table = "film";
    if (conn->Add(table, data)) {
      cout << "Film adding fail!\n";
      return -1;
    };

    string condition = "filmname = \"" + data["filmname"] + "\"";
    vecstr userid = {"idfilm"};
    vector<mapstr> res = conn->Get(table, userid, condition);
    string id = res[0]["idfilm"];
    cout << id << endl;
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

  int FilmConnector::EditFilm(int id, mapstr data) {
    string table = "film";
    string condition = "idfilm = " + to_string(id);
    if (conn->Edit(table, data, condition)) {
      cout << "Film editing fail!\n";
      return -1;
    };
    return 0;
  };

  mapstr FilmConnector::GetFilmInfo(int id, vecstr cols) {
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

  void FilmConnector::AddFilmDetail(string filmid, string table, vecstr data) {
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

  int FilmConnector::FindDetail(string &table, string &name) {
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

  int FilmConnector::DeleteDetail(string &table, string filmid, string detail) {
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

  string FilmConnector::GetDetailId(string &table, string &name) {
    string condition = table + "name = \"" + name + "\"";
    vecstr cols = {"id" + table};
    vector<mapstr> answer = conn->Get(table, cols, condition);
    string result = "-1";
    if (answer.size())
      result = answer[0][cols[0]];
    return result;
  }

  vecstr FilmConnector::GetDetail(string filmid, string &table) {
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



  UserConnector::UserConnector(const string &host, const string &usr, const string &psw,
                const string &db, const int port) {
    ConnectorMySql *buffer = new ConnectorMySql(host, usr, psw, db, port);
    conn = buffer;
  }

  UserConnector::~UserConnector() { delete conn; };

  int UserConnector::AddUser(string &email, string &username, string &password,
              string gender, int age, vecstr format,
              vecstr genre, vecstr director, int iduser ) {

    mapstr data;
    if (iduser > 0)
      data["iduser"] = to_string(iduser);
    data["email"] = email;
    data["username"] = username;
    data["password"] = password;
    if (gender != "")
      data["gender"] = gender;
    if (age > 0)
      data["age"] = to_string(age);
    cout << "BEFORE\n";
    string table = "user";
    if (conn->Add(table, data)) {
      cout << "User adding fail!\n";
      return -1;
    };
    string condition = "username = \"" + data["username"] + "\"";
    vecstr userid = {"iduser"};
    vector<mapstr> res = conn->Get(table, userid, condition);
    string id = res[0]["iduser"];
    cout << id << endl;
    if (genre.size()) {
      AddUserPreference(id, "genre", genre);
    }
    if (director.size()) {
      AddUserPreference(id, "director", director);
    }
    if (format.size()) {
      AddUserPreference(id, "format", format);
    }
    return 0;
  };

  int UserConnector::DeleteUser(int id) {
    string table = "user";
    string condition = "iduser = " + to_string(id);
    if (conn->Delete(table, condition)) {
      cout << "User deleting fail!\n";
      return -1;
    };
    return 0;
  };

  string UserConnector::GetUserId(string &username) {
    string table = "user";
    string condition = "username = \"" + username + "\"";
    vecstr userid = {"iduser"};
    vector<mapstr> res = conn->Get(table, userid, condition);
    string id = res[0]["iduser"];
    return id;
  }

  int UserConnector::EditUser(int id, mapstr data) {
    string table = "user";
    string condition = "iduser = " + to_string(id);
    if (conn->Edit(table, data, condition)) {
      cout << "User editing fail!\n";
      return -1;
    };
    return 0;
  };

  mapstr UserConnector::GetUserInfo(int id, vecstr cols) {
    string table = "user";
    string condition = " iduser = " + to_string(id);
    vector<mapstr> answer = conn->Get(table, cols, condition);
    mapstr userinfo{};
    if (!answer.size())
      return userinfo;
    userinfo = answer[0];
    return userinfo;
  };

  int UserConnector::EstimateFilm(int userid, int film, int estimate) {
    string table = "estimation";
    mapstr data;
    data["user_iduser"] = to_string(userid);
    data["film_idfilm"] = to_string(film);
    data["estimate"] = to_string(estimate);
    if (conn->Add(table, data)) {
      cout << "User estimating film fail!\n";
      return -1;
    }
    return 0;
  };

  int UserConnector::CommentFilm(int userid, int filmid, string text) {
    string table = "comment";
    mapstr data;
    data["user_iduser"] = to_string(userid);
    data["film_idfilm"] = to_string(filmid);
    data["commenttext"] = text;

    if (conn->Add(table, data)) {
      cout << "User commenting film fail!\n";
      return -1;
    }
    return 0;
  };

  vecstr UserConnector::GetCommentsFilm(int userid, int filmid) {
    string table = "comment";
    string condition = " user_iduser = " + to_string(userid) +
                       " and film_idfilm = " + to_string(filmid);
    vecstr cols = {"commenttext"};
    vector<mapstr> commentmap = conn->Get(table, cols, condition);
    vecstr commentlist(0);

    for (auto &it : commentmap) {
      commentlist.push_back(it["commenttext"]);
    }
    return commentlist;
  };

  int UserConnector::DeleteComment(int commentid) {
    string table = "comment";
    string condition = "idcomment = " + to_string(commentid);
    if (conn->Delete(table, condition)) {
      cout << "User deleting comment fail!\n";
      return -1;
    }
    return 0;
  };

  vector<mapstr> UserConnector::GetUserEstimate(int id) {
    string table = "estimation";
    vecstr cols = {"film_idfilm", "estimate"};
    string condition = "user_iduser = " + to_string(id);
    vector<mapstr> est = conn->Get(table, cols, condition);
    return est;
  };

  vecstr UserConnector::GetUsersId(string condition) {
    string table = "user";
    vecstr cols = {"iduser"};
    vector<mapstr> ids = conn->Get(table, cols, condition);
    vecstr idlist(0);
    if (!ids.size())
      return idlist;
    for (auto &it : ids) {
      idlist.push_back(it["iduser"]);
    }
    return idlist;
  };

  vector<multimap<string, string>> UserConnector::GetDataFrame() {
    string table = "user";
    vecstr basecols = {"iduser", "age", "gender"};
    vector<multimap<string, string>> df;
    // get base info about all users
    vector<mapstr> userbase = conn->Get(table, basecols);
    for (auto &row : userbase) {
      // add base fileds
      multimap<string, string> temp;
      pair<string, string> temp_pair = make_pair("iduser", row["iduser"]);
      temp.insert(temp_pair);
      temp_pair = make_pair("age", row["age"]);
      temp.insert(temp_pair);
      temp_pair = make_pair("gender", row["gender"]);
      temp.insert(temp_pair);

      // add preferences
      vector<mapstr> pref = GetUserPreference(stoi(row["iduser"]));

      for (auto &pr : pref) {
        for (auto &couple : pr) {
          temp.insert(couple);
        }
      }

      // add estimations
      vector<mapstr> est = GetUserEstimate(stoi(row["iduser"]));

      for (auto &es : est) {
        for (auto &couple : es) {
          temp.insert(couple);
        }
      }
      df.push_back(temp);
    }
    return df;
  };

  int UserConnector::AddUserPreference(string userid, string tab, vecstr data) {
    string table = "preference_" + tab;
    for (auto &it : data) {
      mapstr temp;
      temp[tab] = it;
      temp["user_iduser"] = userid;
      if (conn->Add(table, temp)) {
        cout << "Adding user preference fail!\n";
        return -1;
      }
    }
    return 0;
  };

  int UserConnector::DeleteUserPreference(int id, multimap<string, string> data) {
    for (auto &pair : data) {
      string table = "preference_" + pair.first;
      string condition = " user_iduser = " + to_string(id) + " and " +
                         pair.first + " = \"" + pair.second + "\"";

      if (conn->Delete(table, condition)) {
        cout << "Deleting user preference fail!\n";
        return -1;
      }
    }
    return 0;
  };

  vector<mapstr> UserConnector::GetUserPreference(int id) {
    string condition = "user_iduser = " + to_string(id);
    vecstr cols;
    string tab_genre = "preference_genre";
    cols = {"genre"};
    vector<mapstr> genre = conn->Get(tab_genre, cols, condition);
    string tab_format = "preference_format";
    cols = {"format"};
    vector<mapstr> format = conn->Get(tab_format, cols, condition);
    string tab_director = "preference_director";
    cols = {"director"};
    vector<mapstr> director = conn->Get(tab_director, cols, condition);
    vector<mapstr> preference;
    preference.insert(preference.end(), genre.begin(), genre.end());
    preference.insert(preference.end(), format.begin(), format.end());
    preference.insert(preference.end(), director.begin(), director.end());
    return preference;
  };

  int UserConnector::FindUserEstimation(int userid, int filmid) {
    string table = "estimation";
    string condition = " user_iduser = " + to_string(userid) +
                       " and film_idfilm = " + to_string(filmid);
    vecstr cols = {"estimate"};
    int estim = stoi(conn->Get(table, cols, condition)[0]["estimate"]);
    return estim;
  };
