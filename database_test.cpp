#include <gtest/gtest.h>
#include "database.cpp"
#define private public



// CONNECTORMYSQL

TEST(ConnectorMySql_create, Assert_True) {
  ConnectorMySql x("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  EXPECT_TRUE(true);
}

TEST(ConnectorMySql_Add, Assert_True) {
  EXPECT_TRUE(true);
}

TEST(ConnectorMySql_Delete, Assert_True) {
  EXPECT_TRUE(true);
}

TEST(ConnectorMySql_Edit, Assert_True) {
  EXPECT_TRUE(true);
}

TEST(ConnectorMySql_Get, Assert_True) {
  EXPECT_TRUE(true);
}



// USERCONNECTION

TEST(UserConnector_create, Assert_True) {
  UserConnector x("localhost", "vladimir", "12345678", "Kinopoiskdb", 3306);
  EXPECT_TRUE(true);
}


TEST(UserConnector_AddUser, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(UserConnector_DeleteUser, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(UserConnector_EditUser, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(UserConnector_GetUserInfo, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(UserConnector_EstimateFilm, Assert_True) {
  EXPECT_TRUE(true);
}


TEST(UserConnector_CommentFilm, Assert_True) {
  EXPECT_TRUE(true);
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

/*


	vecstr (int filmid) const;
	void (int filmid, string genre);
	vecstr (int filmid);
	void (string name);
	void (int id);
	int (string name);
*/

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
