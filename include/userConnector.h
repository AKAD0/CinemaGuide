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

  ~UserConnector();

  int AddUser(string &email, string &username, string &password,
              string gender = "", int age = -1, vecstr format = {},
              vecstr genre = {}, vecstr director = {}, int iduser = -1);

  int DeleteUser(int id);

  string GetUserId(string &username);

  int EditUser(int id, mapstr data);

  mapstr GetUserInfo(int id, vecstr cols);

  int EstimateFilm(int userid, int film, int estimate);

  int CommentFilm(int userid, int filmid, string text);

  vecstr GetCommentsFilm(int userid, int filmid);

  int DeleteComment(int commentid);

  vector<mapstr> GetUserEstimate(int id);

  vecstr GetUsersId(string condition = "");

  vector<multimap<string, string>> GetDataFrame();

  int AddUserPreference(string userid, string tab, vecstr data);

  int DeleteUserPreference(int id, multimap<string, string> data);

  vector<mapstr> GetUserPreference(int id);

  int FindUserEstimation(int userid, int filmid);
};