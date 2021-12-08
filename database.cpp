#include <iostream>
#include <map>
#include <vector>
//#include <mysql/mysql.h>
#include <mysql_connection.h> // include path /mysql-cppcon-8
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;


typedef map<string, string> mapstr;
typedef vector<string> vecstr;

class ConnectorDb {
public:
	ConnectorDb() = default;
	ConnectorDb(const ConnectorDb&) = delete;
	ConnectorDb & operator= (const ConnectorDb&) = default;
	virtual ~ConnectorDb() = default;
	virtual int Add(string& table, mapstr& data) = 0;
	virtual int Delete(const string& table, string condition) = 0;
	virtual int Edit(string& table, mapstr& newData, string condition) = 0;
	virtual vector<mapstr> Get(string& table, vecstr& cols, string condition = "") = 0;

};

bool clear(string str, bool quotes=true) {
    vector<string> stops = { "insert", "delete", "update", "drop", "alter", "select", ";"};
	if (quotes) {
		stops.push_back("\"");
		stops.push_back("'");
	}
	if (quotes) {

	}
    for (auto& key : stops) {
        if (str.find(key) < str.size()) {
			cout << str << ": " << "INJECTION\n" << "position: " << str.find(key);;
			return true;
		}
    }
    return false;

}

class ConnectorMySql:public ConnectorDb {
public:
	ConnectorMySql(const string& host, const string& usr, const string& psw, const string& db, const int port) { 
		// Create a connection 
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", usr, psw);
		// Connect to the MySQL test database 
		con->setSchema("Kinopoiskdata");
		stmt = con->createStatement();
		//prstmt = con->prepareStatement("SHOW DATABASES");
		
		
		cout << "Created mysql\n";
	};

	//ConnectorMySql() = default;
	
	~ConnectorMySql() {
		
		cout << "NOT Closed\n";
		if (res != nullptr) delete res;
		delete stmt;
		if (prstmt != nullptr) delete prstmt;
		delete con;
		cout << "Closed mysql\n";

	};
	int Add(string& table, map<string, string>& data) override {
		cout <<"INSIDE add\n";

		if (clear(table)) return -1;
		string sqlquery = "insert into " + table + " (";
		mapstr :: iterator it;


		
		for (auto& it : data) { 
			if (clear(it.first)) return -1;
			sqlquery += it.first + ", ";
		}
		sqlquery.pop_back();
		sqlquery.pop_back();
		sqlquery += ") values (";

		for (auto& it : data) { 
			if (clear(it.second)) return -1;
			sqlquery += "\"" + it.second + "\", ";
		}
		sqlquery.pop_back();
		sqlquery.pop_back();
		
		sqlquery += ");";

		cout <<"QUERY:: " << sqlquery << endl;

		prstmt = con->prepareStatement(sqlquery);
		prstmt->execute();

		//stmt->execute(sqlquery);

		return 0;

	};

	int Delete(const string& table, string condition) override {
		if (clear(table)) return -1;
		if (clear(condition, false)) return -1;
		string sqlquery = "delete from " + table + " where " + condition + ";";
		cout <<"QUERY:: " << sqlquery << endl;
		//stmt->execute(sqlquery);
		prstmt = con->prepareStatement(sqlquery);
		prstmt->execute();
		return 0;
		
	};

	int Edit(string& table, mapstr& newData, string condition) override {
		if (clear(table)) return -1;
		string sqlquery = "update " + table + " set ";
		//mapstr :: iterator it;
		for (auto& it : newData) { 
			if (clear(it.first) || clear(it.second)) return -1;
			sqlquery += it.first +" = \"" + it.second + "\", ";
		}
		sqlquery.pop_back();
		sqlquery.pop_back();

		sqlquery += " where ";
		if (clear(condition, false)) return -1;
		sqlquery += condition + ";";

		cout <<"QUERY:: " << sqlquery << endl;
		
		//stmt->execute(sqlquery);
		prstmt = con->prepareStatement(sqlquery);
		prstmt->execute();
		return 0;

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
			//select count(*) from (select * from user where iduser = 10) as tab;
		//res = stmt->executeQuery(sqlquery);
		prstmt = con->prepareStatement(sqlquery);
		res = prstmt->executeQuery();
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
	sql::PreparedStatement *prstmt = nullptr;
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
	int AddUser(string& email, string& username, string& password, 
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
		if (conn->Add(table, data)){
			cout << "User adding fail!\n";
			return -1;
		};

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
		return 0;
	};

	int DeleteUser(int id) {
		string table = "user";
		string condition = "iduser = " + to_string(id);
		if (conn->Delete(table, condition)) {
			cout << "User deleting fail!\n";
			return -1;
		};
		return 0;
	};

	string GetUserId(string& username) {
		string table = "user";
		string condition = "username = \"" + username + "\"";
		vecstr userid = {"iduser"};

		vector<mapstr> res = conn->Get(table, userid, condition);
		string id = res[0]["iduser"];
		return id;
	}

	int EditUser(int id, mapstr data) {
		string table = "user";
		string condition = "iduser = " + to_string(id);
		if (conn->Edit(table, data, condition)) {
			cout << "User editing fail!\n";
			return -1;
		};
		return 0;

	};

	mapstr GetUserInfo(int id, vecstr cols) {
		string table = "user";
		string condition = " iduser = " + to_string(id);
		mapstr userinfo = conn->Get(table, cols, condition)[0];
		//mapstr m;
		return userinfo;
	};

	int EstimateFilm(int userid, int film, int estimate) {
		string table = "estimation";
		mapstr data;
		data["user_iduser"] = to_string(userid);
		data["film_idfilm"] = to_string(film);
		data["estimate"] = to_string(estimate);
		if (conn->Add(table, data)) {
			cout << "User estimating film fail!\n";
			return -1;
		}
		return 0;
	};

	int CommentFilm(int userid, int filmid, string text) {
		string table = "comment";
		mapstr data;
		data["user_iduser"] = to_string(userid);
		data["film_idfilm"] = to_string(filmid);
		data["commenttext"] = text;
		
		if (conn->Add(table, data)) {
			cout << "User commenting film fail!\n";
			return -1;
		}
		return 0;
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

	int DeleteComment(int commentid) {
		string table = "comment";
		string condition = "idcomment = " + to_string(commentid);
		if (conn->Delete(table, condition)) {
			cout << "User deleting comment fail!\n";
			return -1;
		}
		return 0;
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
	int AddUserPreference(string userid, string tab, vecstr data) {
		string table = "preference_" + tab;
		for (auto& it : data) {
				mapstr temp;
				temp[tab] = it;
				temp["user_iduser"] = userid;
				if (conn->Add(table, temp)) {
					cout << "Adding user preference fail!\n";
					return -1;
				}
				
			}
		return 0;
	};

	int DeleteUserPreference(int id, multimap<string, string> data) {
		for (auto& pair : data) {
			string table = "preference_" + pair.first;
			string condition = " user_iduser = " + to_string(id) + " and " + pair.first + 
								" = \"" + pair.second + "\""; 
			
			if (conn->Delete(table, condition)) {
				cout << "Deleting user preference fail!\n";
				return -1;
			}
		}
		return 0;
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
        ConnectorMySql* buffer = new ConnectorMySql(host, usr, psw, db, port);
		conn = buffer;
		//*conn = ConnectorMySql(host, usr, psw, db, port);
		cout << "FILM CREATED\n";
	};
	~FilmConnector() {
		delete conn;
		cout << "FILM DESTRUCTOR\n";
	};
	int AddFilm(string& filmname, int year, string& country, 
				string format, string & director, float rate = 0, string description = "",
				vecstr genre = { }, vecstr actor = { }, int idfilm = -1) {
		
		mapstr data; 
		if (idfilm > 0) data["idfilm"] = to_string(idfilm);
		data["filmname"] = filmname;
		data["year"] = to_string(year);
		data["country"] = country;
		data["format"] = format;
		data["director"] = director;
		if (description != "") data["description"] = description;
		if (rate > 0) data["format"] = to_string(rate);
		cout <<"BEFORE\n";
		string table = "film";
		if (conn->Add(table, data)){
			cout << "Film adding fail!\n";
			return -1;
		};

		string condition = "filmname = \"" + data["filmname"] + "\"";
		vecstr userid = {"idfilm"};

		vector<mapstr> res = conn->Get(table, userid, condition);
		string id = res[0]["idfilm"];

		cout << id << endl;

		/*if (genre.size()) {
			AddFilmDetail(id, "genre", genre);
		}

		if (actor.size()) {
			AddFilmDetail(id, "actor", actor);
			
		}*/

		return 0;
	};
	void DeleteFilm(int id);
	void EditFilm(int id, mapstr data);
	mapstr GetFilmInfo(int id, vecstr cols);
	void RecountRate();
	vecstr GetFilmsId(mapstr condition);
private:

	vecstr GetFilmGenre(int filmid);
	void AddFilmDetail(string filmid, string table, vecstr data);
	vecstr GetFilmActor(int filmid);
	//void AddFilmActor(int filmid, string name);
	void RecountRateFilm(int id);
	int FindActor(string name);
};

