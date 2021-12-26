#pragma once

#include <map>

#include <vector>

#include "connector.h"
#include "connectorMysql.h"
using namespace std;

typedef map<string, string> mapstr;
typedef vector<string> vecstr;

class UserConnector : public Connector {
public:
  UserConnector(const string &host, const string &usr, const string &psw,
                const string &db, const int port);

  ~UserConnector() = default;

  int AddUser(const string &email, const string &username, const string &password,
              string gender = "", int age = -1, vecstr format = {},
              vecstr genre = {}, vecstr director = {}, int iduser = -1);

  int DeleteUser(int id);

  string GetUserId(const string &username);

  int EditUser(int id, const mapstr& data);

  mapstr GetUserInfo(int id, const vecstr& cols);

  int EstimateFilm(int userid, int film, int estimate);

  int CommentFilm(int userid, int filmid, const string& text);

  vecstr GetCommentsFilm(int userid, int filmid);

  int DeleteComment(int commentid);

  vector<mapstr> GetUserEstimate(int id);

  vecstr GetUsersId(string condition = "");

  vector<multimap<string, string>> GetDataFrame();

  int AddUserPreference(const string& userid, const string& tab, const vecstr& data);

  int DeleteUserPreference(int id, const multimap<string, string>& data);

  vector<mapstr> GetUserPreference(int id);

  int FindUserEstimation(int userid, int filmid);
};