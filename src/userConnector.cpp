#include "../include/connectorMysql.h"

#include "../include/userConnector.h"


  UserConnector::UserConnector(const string &host, const string &usr, const string &psw,
                const string &db, const int port) {
    std::unique_ptr<ConnectorMySql> buffer(new ConnectorMySql(host, usr, psw, db, port));
    conn = move(buffer);
  }


  int UserConnector::AddUser(const string &email, const string &username, const string &password,
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
    string table = "user";
    if (conn->Add(table, data)) {
      cout << "User adding fail!\n";
      return -1;
    };
    string condition = "username = \"" + data["username"] + "\"";
    vecstr userid = {"iduser"};
    vector<mapstr> res = conn->Get(table, userid, condition);
    string id = res[0]["iduser"];
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

  string UserConnector::GetUserId(const string &username) {
    string table = "user";
    string condition = "username = \"" + username + "\"";
    vecstr userid = {"iduser"};
    vector<mapstr> res = conn->Get(table, userid, condition);
    string id = res[0]["iduser"];
    return id;
  }

  int UserConnector::EditUser(int id, const mapstr& data) {
    string table = "user";
    string condition = "iduser = " + to_string(id);
    if (conn->Edit(table, data, condition)) {
      cout << "User editing fail!\n";
      return -1;
    };
    return 0;
  };

  mapstr UserConnector::GetUserInfo(int id, const vecstr& cols) {
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

  int UserConnector::CommentFilm(int userid, int filmid, const string& text) {
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

  int UserConnector::AddUserPreference(const string& userid, const string& tab, const vecstr& data) {
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

  int UserConnector::DeleteUserPreference(int id, const multimap<string, string>& data) {
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
