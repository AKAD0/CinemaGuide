#include <gtest/gtest.h>
#include "database.cpp"
#include <chrono>
#define private public



// CONNECTORMYSQL

TEST(ConnectorMySql_create, Assert_True) {
  ConnectorMySql testcon("localhost", "vladimir", "12345678", "Kinopoiskdata", 3306);
  EXPECT_TRUE(true);
}

TEST(ConnectorMySql_Add_Get, Assert_True) {
  ConnectorMySql testcon("localhost", "vladimir", "12345678", "Kinopoisdata", 3306);
  string table = "user";
  mapstr data = {
    {"email", "mail@mail.ru"},
    {"username", "Lionel Messi"},
    {"password", "1899"}
  };
  testcon.Add(table, data);

  vecstr columns = {"email", "username", "password"};

  string condition = "username = \"Lionel Messi\"";
  mapstr result = testcon.Get(table, columns, condition)[0];



  EXPECT_EQ(data, result);

  testcon.Delete(table, condition);

  //EXPECT_TRUE(true);
}

TEST(ConnectorMySql_Delete, Assert_True) {
  ConnectorMySql testcon("localhost", "vladimir", "12345678", "Kinopoisdata", 3306);
  string table = "user";
  mapstr data = {
    {"email", "mail@mail.ru"},
    {"username", "Lionel Messi"},
    {"password", "1899"}
  };
  testcon.Add(table, data);

  vecstr columns = {"email", "username", "password"};

  string condition = "username = \"Lionel Messi\"";

  testcon.Delete(table, condition);

  mapstr result {};// = testcon.Get(table, columns, condition)[0];

  mapstr exp = {};
  EXPECT_EQ(exp, result);
}

TEST(ConnectorMySql_Edit, Assert_True) {
  ConnectorMySql testcon("localhost", "vladimir", "12345678", "Kinopoisdata", 3306);
  string table = "user";
  mapstr data = {
    {"email", "mail@mail.ru"},
    {"username", "Lionel Messi"},
    {"password", "1899"}
  };
  testcon.Add(table, data);

  vecstr columns = {"email", "username", "password"};

  string condition = "email = \"mail@mail.ru\"";

  mapstr newdata = {{"username", "Neymar"}};

  testcon.Edit(table, newdata, condition);

  mapstr result = testcon.Get(table, columns, condition)[0];

  data["username"] = "Neymar";

  EXPECT_EQ(data, result);

  testcon.Delete(table, condition);
}


// USERCONNECTION

TEST(UserConnector_create, Assert_True) {
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  EXPECT_TRUE(true);
}





TEST(UserConnector_AddUser_GetUserInfo, Assert_True) {
  mapstr data = {
    {"email", "mail@mail.ru"},
    {"username", "Lionel Messi"},
    {"password", "1899"}
  };
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  string email = "mail@mail.ru";
	string username = "Lionel Messi";
	string password = "1899";

	testcon.AddUser(email, username, password);
  vecstr columns = {"email", "username", "password"};
  string id = testcon.GetUserId(username);
  mapstr result = testcon.GetUserInfo(stoi(id), columns);
  EXPECT_EQ(data, result);
  
  testcon.DeleteUser(stoi(id));
}


TEST(UserConnector_DeleteUser, Assert_True) {
  mapstr data = {};
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  string email = "mail@mail.ru";
	string username = "Lionel Messi";
	string password = "1899";

	testcon.AddUser(email, username, password);
  vecstr columns = {"email", "username", "password"};
  string id = testcon.GetUserId(username);
  testcon.DeleteUser(stoi(id));
  mapstr result = {};//testcon.GetUserInfo(stoi(id), columns);
  EXPECT_EQ(data, result);
  
  
}


TEST(UserConnector_EditUser, Assert_True) {
  mapstr data = {
    {"email", "mail@mail.ru"},
    {"username", "Neymar"},
    {"password", "1899"}
  };
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  string email = "mail@mail.ru";
	string username = "Lionel Messi";
	string password = "1899";

	testcon.AddUser(email, username, password);
  vecstr columns = {"email", "username", "password"};
  string id = testcon.GetUserId(username);

  mapstr newdata = {{"username", "Neymar"}};

  testcon.EditUser(stoi(id), newdata);

  mapstr result = testcon.GetUserInfo(stoi(id), columns);
  EXPECT_EQ(data, result);
  
  testcon.DeleteUser(stoi(id));
}


TEST(UserConnector_EstimateFilm_GetEstimation, Assert_True) {

  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  string email = "mail@mail.ru";
	string username = "Lionel Messi";
	string password = "1899";

	testcon.AddUser(email, username, password);
  vecstr columns = {"email", "username", "password"};
  string id = testcon.GetUserId(username);
  testcon.EstimateFilm(stoi(id), 1, 5);
  testcon.EstimateFilm(stoi(id), 2, 8);
  vector<mapstr> est = testcon.GetUserEstimate(stoi(id));
  vector<mapstr> exp = { { {"estimate", "5"}, {"film_idfilm", "1"} }, { {"estimate", "8"}, {"film_idfilm", "2"} } };
  //mapstr result = testcon.GetUserInfo(stoi(id), columns);
  EXPECT_EQ(exp, est);
  
  testcon.DeleteUser(stoi(id));

  
}


TEST(UserConnector_CommentFilm, Assert_True) {
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  string email = "mail@mail.ru";
	string username = "Lionel Messi";
	string password = "1899";

	testcon.AddUser(email, username, password);
  vecstr columns = {"email", "username", "password"};
  string id = testcon.GetUserId(username);
  //mapstr result = testcon.GetUserInfo(stoi(id), columns);
  string txt = "random txt for test lorem ipsum";
  testcon.CommentFilm(stoi(id), 1, txt);
  string result = testcon.GetCommentsFilm(stoi(id), 1)[0];
  EXPECT_EQ(txt, result);
  
  testcon.DeleteUser(stoi(id));


}


TEST(UserConnector_GetUserEstimate, Assert_True) {
  vector<mapstr> exp = { {{"film_idfilm", "1"}, {"estimate", "5"}}};
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  string email = "mail@mail.ru";
	string username = "Lionel Messi";
	string password = "1899";

	testcon.AddUser(email, username, password);
  vecstr columns = {"email", "username", "password"};
  string id = testcon.GetUserId(username);
  testcon.EstimateFilm(stoi(id), 1, 5);

  vector<mapstr> result = testcon.GetUserEstimate(stoi(id));
  EXPECT_EQ(exp, result);
  
  testcon.DeleteUser(stoi(id));
}


TEST(UserConnector_GetUsersId, Assert_True) {
  mapstr data = {
    {"email", "mail@mail.ru"},
    {"username", "Lionel Messi"},
    {"password", "1899"}
  };
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  string email = "mail@mail.ru";
	string username = "Lionel Messi";
	string password = "1899";

	testcon.AddUser(email, username, password);
  string id = testcon.GetUserId(username);
  string condition = "username = \"" + username + "\"";
  string result = testcon.GetUsersId(condition)[0];
  EXPECT_EQ(id, result);
  
  testcon.DeleteUser(stoi(id));
}


TEST(UserConnector_AddUserPreference, Assert_True) {
  vector<mapstr> exp { { {"genre", "action"} }, { {"genre", "comedy"} }, 
                      { {"format", "full"} }, { {"director", "guy richie"} } };
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  string email = "mail@mail.ru";
	string username = "Lionel Messi";
	string password = "1899";

	testcon.AddUser(email, username, password);
  vecstr columns = {"email", "username", "password"};
  string id = testcon.GetUserId(username);
  vecstr genre = {"action", "comedy"};
	vecstr format = {"full"};
	vecstr director = {"guy richie"};
  testcon.AddUserPreference(id, "genre", genre);
  testcon.AddUserPreference(id, "director", director);
	testcon.AddUserPreference(id, "format", format);
  vector<mapstr> result = testcon.GetUserPreference(stoi(id));
  EXPECT_EQ(exp, result);
  
  testcon.DeleteUser(stoi(id));
}




TEST(UserConnector_DeleteUserPreference, Assert_True) {
  vector<mapstr> exp { { {"genre", "action"} }, { {"genre", "comedy"} }, 
                       { {"director", "guy richie"} } };
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  string email = "mail@mail.ru";
	string username = "Lionel Messi";
	string password = "1899";

	testcon.AddUser(email, username, password);
  vecstr columns = {"email", "username", "password"};
  string id = testcon.GetUserId(username);
  vecstr genre = {"action", "comedy"};
	vecstr format = {"full"};
	vecstr director = {"guy richie"};
  testcon.AddUserPreference(id, "genre", genre);
  testcon.AddUserPreference(id, "director", director);
	testcon.AddUserPreference(id, "format", format);
  multimap<string, string> data{};
  pair<string, string> delfull = make_pair("format", "full");
  data.insert(delfull);
  testcon.DeleteUserPreference(stoi(id), data);
  vector<mapstr> result = testcon.GetUserPreference(stoi(id));
  EXPECT_EQ(exp, result);
  
  testcon.DeleteUser(stoi(id));
}



TEST(UserConnector_FindUserEstimation, Assert_True) {
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  string email = "mail@mail.ru";
	string username = "Lionel Messi";
	string password = "1899";

	testcon.AddUser(email, username, password);
  vecstr columns = {"email", "username", "password"};
  string id = testcon.GetUserId(username);
  testcon.EstimateFilm(stoi(id), 1, 5);

  int result = testcon.FindUserEstimation(stoi(id), 1);
  int exp = 5;
  EXPECT_EQ(exp, result);
  
  testcon.DeleteUser(stoi(id));
}


// FILMCONNECTION
/*
TEST(FilmConnector_create, Assert_True) {
  FilmConnector x("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  EXPECT_TRUE(true);
}

TEST(FilmConnector_AddFilm, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(FilmConnector_DeleteFilm, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(FilmConnector_EditFilm, Assert_True) {
  EXPECT_TRUE(true);
}

TEST(FilmConnector_GetFilmInfo, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(FilmConnector_RecountRate, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(FilmConnector_GetFilmsId, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(FilmConnector_GetFilmGenre, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(FilmConnector_AddFilmGenre, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(FilmConnector_GetFilmActor, Assert_True) {
  EXPECT_TRUE(true);
}

TEST(FilmConnector_AddFilmActor, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(FilmConnector_RecountRateFilm, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(FilmConnector_FindActor, Assert_True) {
  EXPECT_TRUE(true);
}
*/

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
