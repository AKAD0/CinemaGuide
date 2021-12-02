#include <iostream>
#include <map>
#include <vector>
#include <mysql/mysql.h>
using namespace std;


typedef map<string, string> mapstr;
typedef vector<string> vecstr;

class ConnectorDb {
public:
	ConnectorDb() = default;
	ConnectorDb(const ConnectorDb&) = delete;
	ConnectorDb & operator= (const ConnectorDb&) = default;
	virtual ~ConnectorDb() = default;
	virtual void Add(mapstr& data) = 0;
	virtual void Delete(const string& table, int id) = 0;
	virtual void Edit(mapstr& newData) = 0;
	virtual mapstr Get(vecstr& cols) = 0;

};

class ConnectorMySql:public ConnectorDb {
public:
	ConnectorMySql(const string& host, const string& usr, const string& psw, const string& db, const int port) { 
		mysqlconn = mysql_init(NULL);

		// Connect to database 
		if (!mysql_real_connect(mysqlconn, host.c_str(), usr.c_str(), psw.c_str(), db.c_str(), port, NULL, 0)) {
			fprintf(stderr, "%s\n", mysql_error(mysqlconn));
			exit(1);
		}	
	};
	~ConnectorMySql() {
		mysql_free_result(res);
      	mysql_close(mysqlconn);

	};
	void Add(map<string, string>& data) override {
		string sqlquery = "insert into " + data["table"] + " (";
		mapstr :: iterator it;
		
		for (it = data.begin(); it != data.end(); it++) { 

			sqlquery += it->first + ", ";
		}
		sqlquery += ") values (";

		for (it = data.begin(); it != data.end(); it++) { 
			sqlquery += it->first + ", ";
		}
		sqlquery += "):";

		if (mysql_query(mysqlconn, sqlquery.c_str())) {
          fprintf(stderr, "%s\n", mysql_error(mysqlconn));
          exit(1);
      }
	};
	void Delete(const string& table, int id) override {
		string sqlquery = "delete " + table + " where id = " + std::to_string(id) + ";";
		map<string, string> :: iterator it;
		
		if (mysql_query(mysqlconn, sqlquery.c_str())) {
          fprintf(stderr, "%s\n", mysql_error(mysqlconn));
          exit(1);
      	}
	};

	void Edit(mapstr& newData) override {
		string sqlquery = "update " + newData["tablename"] + " set ";
		mapstr :: iterator it;
		for (it = newData.begin(); it != newData.end(); it++) { 
			sqlquery += it->first +" = " + it->second + ", ";
		}
		sqlquery += ";";

		if (mysql_query(mysqlconn, sqlquery.c_str())) {
          fprintf(stderr, "%s\n", mysql_error(mysqlconn));
          exit(1);
      	}

	};
	mapstr Get(vecstr& cols) override {
		mapstr answer;
		string sqlquery = "select ";// + " from " + cols[1] + " set ";
		vecstr::iterator it;
		for (it = cols.begin(); it != cols.end(); it++) { 
			sqlquery += *it + ", ";
		}
		return answer;
	};

private:
	MYSQL *mysqlconn;
    MYSQL_RES *res;
    MYSQL_ROW row;
};


class Connector {
public:
	Connector() = default;
	Connector(const Connector&) = delete;
	Connector & operator= (const Connector&) = delete;
	~Connector() = default;
protected:
	ConnectorDb *conn;
};


class UserConnector:public Connector {
public:
	UserConnector(const string& host, const string& usr, const string& psw, const string& db, const int port) { 
		*conn = ConnectorMySql(host, usr, psw, db, port);
	}
	~UserConnector() {};
	void AddUser(mapstr data) {};
	void DeleteUser(int id) {};
	void EditUser(int id, mapstr data) {};
	mapstr GetUserInfo(int id, vecstr cols) {
		mapstr m;
		return m;
	};
	void EstimateFilm(int userid, int film, int estimate) {};
	void CommentFilm(int userid, int filmid, string text) {};
	vecstr GetCommentsFilm(int userid, int filmid) {
		vecstr v;
		return v;
	};
	void DeleteComment(int userid, int filmid) {};
	mapstr GetUserEstimate(int id) {
		mapstr m;
		return m;
	};
	vecstr GetUsersId(string condition) {
		vecstr v;
		return v;
	};

	map<string, vector<string>> GetDataFrame() { };
private:
	void AddUserPreference(mapstr data);
	void EditUserPreference(mapstr data);
	void DeleteUserPreference(mapstr data);
	mapstr GetUserPreference(int id);
	int FindUserEstimation(int userid, int filmid);

};

class FilmConnector :public Connector {
public:
	FilmConnector(const string& host, const string& usr, const string& psw, const string& db, const int port) {
        *conn = ConnectorMySql(host, usr, psw, db, port);
	};
	~FilmConnector() {};
	void AddFilm(mapstr data);
	void DeleteFilm(int id);
	void EditFilm(int id, mapstr data);
	mapstr GetFilmInfo(int id, vecstr cols);
	void RecountRate();
	vecstr GetFilmsId(mapstr condition);
private:

	vecstr GetFilmGenre(int filmid);
	void AddFilmGenre(int filmid, string genre);
	vecstr GetFilmActor(int filmid);
	void AddFilmActor(string name);
	void RecountRateFilm(int id);
	int FindActor(string name);
};

