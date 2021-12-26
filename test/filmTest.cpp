#include <gtest/gtest.h>
#include "../include/filmConnector.h"


// FILMCONNECTION

TEST(FilmConnector_AddFilm, Assert_True) {
  mapstr data = {{"filmname", "Testfilm"},
                 {"year", "2015"},
                 {"country", "USA"},
                 {"director", "gamer"},
                 {"format", "full"}};
  FilmConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb",
                        3306);
  string filmname = "Testfilm";
  int year = 2015;
  string country = "USA";
  string format = "full";
  string director = "gamer";
  testcon.AddFilm(filmname, year, country, format, director);

  string condition = " filmname = \"Testfilm\"";
  string id = testcon.GetFilmId(condition)[0];
  vecstr columns = {"filmname", "year", "director", "country", "format"};

  mapstr result = testcon.GetFilmInfo(stoi(id), columns);
  EXPECT_EQ(data, result);
  testcon.DeleteFilm(stoi(id));
}

TEST(FilmConnector_DeleteFilm, Assert_True) {
  FilmConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb",
                        3306);
  string filmname = "Testfilm";
  int year = 2015;
  string country = "USA";
  string format = "full";
  string director = "gamer";
  testcon.AddFilm(filmname, year, country, format, director);
  string condition = " filmname = \"Testfilm\"";
  vecstr columns = {"filmname", "year", "director", "country", "format"};
  string id = testcon.GetFilmId(condition)[0];
  testcon.DeleteFilm(stoi(id));
  mapstr result = testcon.GetFilmInfo(stoi(id), columns);
  EXPECT_FALSE(result.size());
}

TEST(FilmConnector_EditFilm, Assert_True) {
  mapstr data = {{"filmname", "Testfilm2"},
                 {"year", "2015"},
                 {"country", "USA"},
                 {"director", "gamer"},
                 {"format", "full"}};
  FilmConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb",
                        3306);
  string filmname = "Testfilm";
  int year = 2015;
  string country = "USA";
  string format = "full";
  string director = "gamer";
  testcon.AddFilm(filmname, year, country, format, director);

  string condition = " filmname = \"Testfilm\"";
  string id = testcon.GetFilmId(condition)[0];
  vecstr columns = {"filmname", "year", "director", "country", "format"};

  mapstr newdata = {{"filmname", "Testfilm2"}};
  testcon.EditFilm(stoi(id), newdata);

  mapstr result = testcon.GetFilmInfo(stoi(id), columns);
  EXPECT_EQ(data, result);
  testcon.DeleteFilm(stoi(id));
}

TEST(FilmConnector_AddFilmDetail, Assert_True) {
  FilmConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb",
                        3306);
  string filmname = "Testfilm";
  int year = 2015;
  string country = "USA";
  string format = "full";
  string director = "gamer";
  testcon.AddFilm(filmname, year, country, format, director);

  string condition = " filmname = \"Testfilm\"";
  string id = testcon.GetFilmId(condition)[0];

  string table = "genre";
  vecstr genres = {"art", "action"};
  testcon.AddFilmDetail(id, table, genres);

  vecstr filmactors = testcon.GetDetail(id, table);

  EXPECT_EQ(genres, filmactors);
  testcon.DeleteFilm(stoi(id));
}

TEST(FilmConnector_DeleteFilmDetail, Assert_True) {
  FilmConnector testcon("localhost", "vladimir", "12345678", "Kinopoiskdb",
                        3306);
  string filmname = "Testfilm";
  int year = 2015;
  string country = "USA";
  string format = "full";
  string director = "gamer";
  testcon.AddFilm(filmname, year, country, format, director);

  string table = "genre";
  vecstr genres = {"art", "action"};
  vecstr expected = {"action"};
  string condition = " filmname = \"Testfilm\"";
  string id = testcon.GetFilmId(condition)[0];

  testcon.AddFilmDetail(id, table, genres);
  testcon.DeleteDetail(table, id, genres[0]);
  vecstr filmactors = testcon.GetDetail(id, table);

  EXPECT_EQ(expected, filmactors);
  testcon.DeleteFilm(stoi(id));
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
