#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <string>
#include <sqlite3.h>

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) {
    
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

class HelloApplication : public Wt::WApplication
{
public:
  HelloApplication(const Wt::WEnvironment& env);
  int InitDB(const char *DataBase);

private:
  Wt::WLineEdit *nameEdit_;
  Wt::WText     *greeting_;
  Wt::WText     *listUsers_;
  sqlite3* DB;
  void greet();
  int id;
};

int HelloApplication::InitDB(const char *DataBase) {
  int exit = 0;
	exit = sqlite3_open(DataBase, &DB);
  return exit;
}
HelloApplication::HelloApplication(const Wt::WEnvironment& env)
  : WApplication(env)
{
  char DataBase[11] = "example.db";
  InitDB(DataBase);
  root()->addWidget(std::make_unique<Wt::WText>("Your name, please ? "));
  nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
  nameEdit_->setFocus();
  auto button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
  button->setMargin(5, Wt::Side::Left);
  root()->addWidget(std::make_unique<Wt::WBreak>());
  greeting_ = root()->addWidget(std::make_unique<Wt::WText>()); 
  button->clicked().connect(this, &HelloApplication::greet);
  nameEdit_->enterPressed().connect(std::bind(&HelloApplication::greet, this));
  button->clicked().connect([=]() {
    std::cerr << "Hello there, " << nameEdit_->text() << std::endl;
  });
  root()->addWidget(std::make_unique<Wt::WBreak>());
  root()->addWidget(std::make_unique<Wt::WText>("List Users:"));
}

void HelloApplication::greet()
{
  char* messaggeError;
  string sql("INSERT INTO PERSON(NAME) VALUES('");
  wstring w = nameEdit_->text();
  for(char x : w) sql += x;
  sql += "');";
  int exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messaggeError);
  greeting_->setText("Hello there, " + nameEdit_->text());
  sqlite3_stmt *stmt;
  sql = "SELECT * FROM PERSON WHERE ID=(SELECT max(ID) FROM PERSON);";
  int i = 0;
  int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL) ;
  rc = sqlite3_step(stmt);
  int ID = sqlite3_column_int (stmt, 0);
  string tmp_str(reinterpret_cast< char const* >(sqlite3_column_text(stmt, 1)));
  string NAME = tmp_str;
  root()->addWidget(std::make_unique<Wt::WBreak>());
  root()->addWidget(std::make_unique<Wt::WText>(NAME));
  ++i;
}

int main(int argc, char **argv)
{
  return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
    return std::make_unique<HelloApplication>(env);
  });
}