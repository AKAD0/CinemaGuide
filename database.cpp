#include <iostream>
#include <map>
#include <vector>
using namespace std;


typedef map<string, string> mapstr;
typedef vector<string> vecstr;

class ConnectorDb {
public:
	ConnectorDb() = default;
	ConnectorDb(const ConnectorDb&) = delete;
	ConnectorDb & operator= (const ConnectorDb&) = default;
	virtual ~ConnectorDb() = default;
	virtual void Add(const mapstr& data) = 0;
	virtual void Delete(const string& table, int id) = 0;
	virtual void Edit(const mapstr& newData) = 0;
	virtual mapstr Get(const vecstr& cols) = 0;

};

class ConnectorMySql:public ConnectorDb {
public:
	ConnectorMySql(const string& host, const string& usr, const string& psw, const string& db, const int port) { };
	~ConnectorMySql() {};
	void Add(const mapstr& data) override {};
	void Delete(const string& table, int id) override {};
	void Edit(const mapstr& newData) override {};
	mapstr Get(const vecstr& cols) override {
		mapstr m;
		return m;
	};
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

