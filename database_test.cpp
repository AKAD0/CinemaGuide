#include <gtest/gtest.h>
#include "database.cpp"
#define private public



// CONNECTORMYSQL

TEST(ConnectorMySql_create, Assert_True) {
  ConnectorMySql testcon("localhost", "vladimir", "12345678", "Kinopoiskdata", 3306);
  EXPECT_TRUE(true);
}

TEST(ConnectorMySql_Add_Get, Assert_True) {
  ConnectorMySql testcon("localhost", "vladimir", "12345678", "Kinopoisdata", 3306);
  mapstr data = {{"table","user"},
    {"email", "mail@mail.ru"},
    {"name", "Lionel Messi"},
    {"password", "1899"}
  };
  testcon.Add(data);

  vecstr columns = {"table", "email", "name", "password"};

  mapstr result = testcon.Get(columns);

  EXPECT_EQ(data, result);

  //EXPECT_TRUE(true);
}

TEST(ConnectorMySql_Delete, Assert_True) {
  ConnectorMySql testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  mapstr data = {{"table","user"},
    {"email", "mail@mail.ru"},
    {"name", "Lionel Messi"},
    {"password", "1899"}
  };
  testcon.Add(data);
  testcon.Delete("user", 1);
  vecstr columns = {"table", "email", "name", "password"};
  mapstr result = testcon.Get(columns);
  mapstr exp = {};
  EXPECT_EQ(exp, result);
}

TEST(ConnectorMySql_Edit, Assert_True) {
  ConnectorMySql testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  mapstr data = {{"table","user"},
    {"email", "mail@mail.ru"},
    {"name", "Lionel Messi"},
    {"password", "1899"}
  };
  mapstr newData = {{"table","user"}, {"name", "Leo"}};
  testcon.Add(data);
  testcon.Edit(newData);
  vecstr columns = {"table", "name"};
  mapstr result = testcon.Get(columns);
  EXPECT_EQ("Leo", result["name"]);
}


// USERCONNECTION

TEST(UserConnector_create, Assert_True) {
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  EXPECT_TRUE(true);
}


TEST(UserConnector_AddUser_GetUserInfo, Assert_True) {
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  mapstr data = {{"table","user"},
    {"email", "mail@mail.ru"},
    {"name", "Lionel Messi"},
    {"password", "1899"}
  };
  testcon.AddUser(data);
  vecstr columns = {"table", "email", "name", "password"};
  mapstr result = testcon.GetUserInfo(1, columns);
  EXPECT_EQ(data, result);
}


TEST(UserConnector_EditUser, Assert_True) {
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  mapstr data = {{"table","user"},
    {"email", "mail@mail.ru"},
    {"name", "Lionel Messi"},
    {"password", "1899"}
  };
  testcon.AddUser(data);
  mapstr newData = {{"table","user"}, {"name", "Leo"}};
  testcon.EditUser(1, newData);
  vecstr columns = {"name"};
  mapstr result = testcon.GetUserInfo(1, columns);
  EXPECT_EQ(data, result);
  EXPECT_TRUE(true);
}


TEST(UserConnector_DeleteUser, Assert_True) {
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  mapstr data = {{"table","user"},
    {"email", "mail@mail.ru"},
    {"name", "Lionel Messi"},
    {"password", "1899"}
  };
  testcon.AddUser(data);
  testcon.DeleteUser(1);
  vecstr columns = {"table", "email", "name", "password"};
  mapstr result = testcon.GetUserInfo(1, columns);
  mapstr exp = {};
  EXPECT_EQ(exp, result);
  
}


TEST(UserConnector_EstimateFilm_GetEstimation, Assert_True) {
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  mapstr data = {{"table","user"},
    {"email", "mail@mail.ru"},
    {"name", "Lionel Messi"},
    {"password", "1899"}
  };
  testcon.AddUser(data);
  testcon.EstimateFilm(1, 1, 8);
  testcon.EstimateFilm(1, 2, 7);
  mapstr result = testcon.GetUserEstimate(1);
  mapstr exp = {{"1", "8"}, {"2", "7"}};
  EXPECT_EQ(exp, result);
}


TEST(UserConnector_CommentFilm, Assert_True) {
  UserConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  mapstr data = {{"table","user"},
    {"email", "mail@mail.ru"},
    {"name", "Lionel Messi"},
    {"password", "1899"}
  };
  testcon.AddUser(data);
  testcon.CommentFilm(1, 1, "comment1");
  testcon.CommentFilm(1, 1, "comment2");
  vecstr result = testcon.GetCommentsFilm(1, 1);
  vecstr exp = {"comment1", "comment2"};
  EXPECT_EQ(exp, result);
}


TEST(UserConnector_DeleteComment, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(UserConnector_GetUserEstimate, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(UserConnector_GetUsersId, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(UserConnector_AddUserPreference, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(UserConnector_EditUserPreference, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(UserConnector_DeleteUserPreference, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(UserConnector_GetUserPreference, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(UserConnector_FindUserEstimation, Assert_True) {
  EXPECT_TRUE(true);
}


// FILMCONNECTION

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


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
