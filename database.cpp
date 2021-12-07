#include <iostream>
#include <map>
#include <vector>
//#include <mysql/mysql.h>
#include <mysql_connection.h> // include path /mysql-cppcon-8
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;


typedef map<string, string> mapstr;
typedef vector<string> vecstr;

class ConnectorDb {
public:
	ConnectorDb() = default;
	ConnectorDb(const ConnectorDb&) = delete;
	ConnectorDb & operator= (const ConnectorDb&) = default;
	virtual ~ConnectorDb() = default;
	virtual void Add(string& table, mapstr& data) = 0;
	virtual void Delete(const string& table, string condition) = 0;
	virtual void Edit(string& table, mapstr& newData, string condition) = 0;
	virtual vector<mapstr> Get(string& table, vecstr& cols, string condition = "") = 0;

};

class ConnectorMySql:public ConnectorDb {
public:
	ConnectorMySql(const string& host, const string& usr, const string& psw, const string& db, const int port) { 
		// Create a connection 
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", usr, psw);
		// Connect to the MySQL test database 
		con->setSchema("Kinopoiskdata");
		stmt = con->createStatement();
		
		
		cout << "Created mysql\n";
	};

	//ConnectorMySql() = default;
	
	~ConnectorMySql() {
		
		cout << "NOT Closed\n";
		if (res != nullptr) delete res;
		delete stmt;
		delete con;
		cout << "Closed mysql\n";

	};
	void Add(string& table, map<string, string>& data) override {
		cout <<"INSIDE add\n";
		string sqlquery = "insert into " + table + " (";
		mapstr :: iterator it;
		
		for (auto& it : data) { 
			sqlquery += it.first + ", ";
		}
		sqlquery.pop_back();
		sqlquery.pop_back();
		sqlquery += ") values (";

		for (auto& it : data) { 
			sqlquery += "\"" + it.second + "\", ";
		}
		sqlquery.pop_back();
		sqlquery.pop_back();
		
		sqlquery += ");";

		cout <<"QUERY:: " << sqlquery << endl;

		stmt->execute(sqlquery);

	};

	void Delete(const string& table, string condition) override {
		string sqlquery = "delete from " + table + " where " + condition + ";";
		cout <<"QUERY:: " << sqlquery << endl;
		stmt->execute(sqlquery);
		
	};

	void Edit(string& table, mapstr& newData, string condition) override {
		string sqlquery = "update " + table + " set ";
		//mapstr :: iterator it;
		for (auto& it : newData) { 
			sqlquery += it.first +" = \"" + it.second + "\", ";
		}
		sqlquery.pop_back();
		sqlquery.pop_back();

		sqlquery += " where ";

		sqlquery += condition + ";";

		cout <<"QUERY:: " << sqlquery << endl;

		stmt->execute(sqlquery);

	};
	
	vector<mapstr> Get(string& table, vecstr& cols, string condition = "") override {
		vector<mapstr> answer(0);

		string sqlquery = "select ";
		
		for (auto& it : cols) {
			sqlquery += it + ", ";
		}
		sqlquery.pop_back();
		sqlquery.pop_back();

		sqlquery += " from " + table;// +";";
		if (condition != "") sqlquery += " where " + condition;
		sqlquery += + " order by " + *cols.begin() + ";";

		cout <<"QUERY:: " << sqlquery << endl;
		bool exist = false;
		//try {
			res = stmt->executeQuery(sqlquery);
			exist = res->next();
			cout <<"EXIST: " << exist <<endl;
			if (!exist) {
				cout <<"NOT EXIST\n";
				
			}
			else {
				cout <<"EXIST\n";
				res->beforeFirst();
			//cout << res->isNull(1) <<endl;
				while (res->next()) {
					cout <<"IN\n";
					mapstr buffer = mapstr();
					for (auto& it : cols) {
						string temp = res->getString(it);

						cout <<"RES: " << res->wasNull() <<endl;
						buffer[it] = temp;
						//cout << it << endl;
						//answer[it].push_back(temp);
						//cout << " " << temp;
						
					}
					answer.push_back(buffer);
					//cout << endl;
						}
					//}
					//else {
					//	cout<<"EMPTY";
					//	return {};
						
					//}
				
				cout << endl;
				
			}
			cout <<"END\n";
		return answer;	
	};

private:
	sql::Driver *driver;
	sql::Connection *con;
	sql::ResultSet *res = nullptr;
	sql::Statement *stmt;
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
		ConnectorMySql* buffer = new ConnectorMySql(host, usr, psw, db, port);
		conn = buffer;
		//*conn = ConnectorMySql(host, usr, psw, db, port);
		cout << "USER CREATED\n";
	}
	~UserConnector() {
		delete conn;
		cout << "USER DESTRUCTOR\n";
		
	};
	void AddUser(string& email, string& username, string& password, 
				string gender = "", int age = -1, vecstr format = { },
				vecstr genre = { }, vecstr director = { }, int iduser = -1) {
		
		mapstr data; 
		if (iduser > 0) data["iduser"] = to_string(iduser);
		data["email"] = email;
		data["username"] = username;
		data["password"] = password;
		if (gender != "") data["gender"] = gender;
		if (age > 0) data["age"] = to_string(age);
		cout <<"BEFORE\n";
		string table = "user";
		conn->Add(table, data);

		string condition = "username = \"" + data["username"] + "\"";
		vecstr userid = {"iduser"};

		vector<mapstr> res = conn->Get(table, userid, condition);
		string id = res[0]["iduser"];

		cout << id << endl;

		if (genre.size()) {
			AddUserPreference(id, "genre", genre);
		}

		if (director.size()) {
			AddUserPreference(id, "director", director);
			
		}

		if (format.size()) {
			AddUserPreference(id, "format", format);
			
		}

	};

	void DeleteUser(int id) {
		string table = "user";
		string condition = "iduser = " + to_string(id);
		conn->Delete(table, condition);
	};

	string GetUserId(string& username) {
		string table = "user";
		string condition = "username = \"" + username + "\"";
		vecstr userid = {"iduser"};

		vector<mapstr> res = conn->Get(table, userid, condition);
		string id = res[0]["iduser"];
		return id;
	}

	void EditUser(int id, mapstr data) {
		string table = "user";
		string condition = "iduser = " + to_string(id);
		conn->Edit(table, data, condition);

	};

	mapstr GetUserInfo(int id, vecstr cols) {
		string table = "user";
		string condition = " iduser = " + to_string(id);
		mapstr userinfo = conn->Get(table, cols, condition)[0];
		//mapstr m;
		return userinfo;
	};

	void EstimateFilm(int userid, int film, int estimate) {
		string table = "estimation";
		mapstr data;
		data["user_iduser"] = to_string(userid);
		data["film_idfilm"] = to_string(film);
		data["estimate"] = to_string(estimate);
		conn->Add(table, data);
	};

	void CommentFilm(int userid, int filmid, string text) {
		string table = "comment";
		mapstr data;
		data["user_iduser"] = to_string(userid);
		data["film_idfilm"] = to_string(filmid);
		data["commenttext"] = text;
		conn->Add(table, data);
	};

	vecstr GetCommentsFilm(int userid, int filmid) {
		string table = "comment";
		string condition = " user_iduser = " + to_string(userid) + " and film_idfilm = " + to_string(filmid);
		vecstr cols = {"commenttext"};
		vector<mapstr> commentmap = conn->Get(table, cols, condition);
		vecstr commentlist(0);

		for (auto& it : commentmap) {
			commentlist.push_back(it["commenttext"]);
		}
		return commentlist;
	};

	void DeleteComment(int commentid) {
		string table = "comment";
		string condition = "idcomment = " + to_string(commentid);
		conn->Delete(table, condition);
	};


	vector<mapstr> GetUserEstimate(int id) {
		string table = "estimation";
		vecstr cols = {"film_idfilm", "estimate"};
		string condition = "user_iduser = " + to_string(id);
		vector<mapstr> est = conn->Get(table, cols, condition);
		return est;
	};

	vecstr GetUsersId(string condition = "") {
		string table = "user";
		vecstr cols = {"iduser"};
		vector<mapstr> ids = conn->Get(table, cols, condition);
		vecstr idlist(0);
		for (auto& it : ids) {
			idlist.push_back(it["iduser"]);
		}
		return idlist;
	};

	map<string, vector<string>> GetDataFrame() {
		string table = "user"; 
		vecstr cols = {"iduser", "age", "gender"};
		map<string, vector<string>> df;

		vector<map<string, vecstr>> dataframe;

		vector<mapstr> userbase = conn->Get(table, cols);

		// add base fileds
		for (auto& row : userbase) {
			map<string, vecstr> temp;
			temp["iduser"] = {row["iduser"]};
			temp["age"] = {row["age"]};
			temp["age"] = {row["age"]};


			// add preferences ????????????????????//

			// add estimations
			temp["estimate"] = vecstr(0);

			vector<mapstr> estimates = GetUserEstimate(stoi(row["iduser"]));
			for (auto& pair : estimates) {
				temp["estimate"].push_back(pair["film_idfilm"] + " " + pair["estimate"]);
			}
			dataframe.push_back(temp);
		}

		
		return df;
	};

//private:
	void AddUserPreference(string userid, string tab, vecstr data) {
		string table = "preference_" + tab;
		for (auto& it : data) {
				mapstr temp;
				temp[tab] = it;
				temp["user_iduser"] = userid;
				conn->Add(table, temp);
			}
	};

	/*void EditUserPreference(int id, mapstr data) {

	};*/
	void DeleteUserPreference(int id, multimap<string, string> data) {
		for (auto& pair : data) {
			string table = "preference_" + pair.first;
			string condition = " user_iduser = " + to_string(id) + " and " + pair.first + 
								" = \"" + pair.second + "\""; 
			conn->Delete(table, condition);
		}
	};

	vector<mapstr> GetUserPreference(int id) {
		string condition = "user_iduser = " + to_string(id);
		vecstr cols;
		string tab_genre = "preference_genre";
		cols = {"genre"};
		vector<mapstr> genre = conn->Get(tab_genre, cols, condition);

		string tab_format = "preference_format";
		cols = {"format"};
		vector<mapstr> format = conn->Get(tab_format, cols, condition);

		string tab_director = "preference_director";
		cols = {"director"};
		vector<mapstr> director = conn->Get(tab_director, cols, condition);

		vector<mapstr> preference;
		preference.insert(preference.end(), genre.begin(), genre.end());
		preference.insert(preference.end(), format.begin(), format.end());
		preference.insert(preference.end(), director.begin(), director.end());

		return preference;
	};

	int FindUserEstimation(int userid, int filmid) {
		string table = "estimation";
		string condition = " user_iduser = " + to_string(userid) + " and film_idfilm = " + to_string(filmid);
		vecstr cols = {"estimate"};
		int estim = stoi(conn->Get(table, cols, condition)[0]["estimate"]);
		return estim;
	};

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

