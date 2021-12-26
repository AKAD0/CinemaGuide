#include <gtest/gtest.h>
#include "../include/connectorMysql.h"
//#include <libconfig.h++>

// CONNECTORMYSQL
TEST(ConnectorMySql_Add_Get, Assert_True) {
  ConnectorMySql testcon("localhost", "vladimir", "12345678", "Kinopoisdata",
                         3306);
  string table = "user";
  mapstr data = {{"email", "mail@mail.ru"},
                 {"username", "Lionel Messi"},
                 {"password", "1899"}};
  testcon.Add(table, data);
  vecstr columns = {"email", "username", "password"};
  string condition = "username = \"Lionel Messi\"";
  mapstr result = testcon.Get(table, columns, condition)[0];
  EXPECT_EQ(data, result);
  testcon.Delete(table, condition);
}

TEST(ConnectorMySql_Delete, Assert_True) {
  ConnectorMySql testcon("localhost", "vladimir", "12345678", "Kinopoisdata",
                         3306);
  string table = "user";
  mapstr data = {{"email", "mail@mail.ru"},
                 {"username", "Lionel Messi"},
                 {"password", "1899"}};
  testcon.Add(table, data);
  vecstr columns = {"email", "username", "password"};
  string condition = "username = \"Lionel Messi\"";
  testcon.Delete(table, condition);
  vector<mapstr> result = testcon.Get(table, columns, condition);
  EXPECT_FALSE(result.size());
}

TEST(ConnectorMySql_Edit, Assert_True) {
  ConnectorMySql testcon("localhost", "vladimir", "12345678", "Kinopoisdata",
                         3306);
  string table = "user";
  mapstr data = {{"email", "mail@mail.ru"},
                 {"username", "Lionel Messi"},
                 {"password", "1899"}};
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



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}