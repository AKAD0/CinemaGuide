#include <iostream>
#include <string.h>
#include <assert.h>
#include <sstream>

using namespace std;

class movie
{
private:
	int id;
	float rate;
	string name;
	string genre;
	string description;
public:
	movie();
	~movie();
	int get_id() { return id; }
	float get_rate() { return rate; }
	string get_name() { return name; }
	string get_genre() { return genre; }
	string get_description() { return description; }
	void set_movie(int movie_id, float movie_rate, string movie_name, string movie_genre, string movie_description) {
		id = movie_id;
		rate = movie_rate;
		name = movie_name;
		genre = movie_genre;
		description = movie_description;
	}
};

class comment
{
private:
	int us_id;
	int mov_id;
    string comment_text;
public:
	comment();
	~comment();
	int get_user_id() { return us_id; }
	int get_movie_id() { return us_id; }
	string get_comment_text() { return comment_text; }
	void set_comment(int user_id, int movie_id, string text) {
		us_id = user_id;
		mov_id = movie_id;
		comment_text = text;
	}
	bool is_bad_comment(string text) {
		text = comment_text;
		if(/*Комментарий имеет нецензурную лексику*/) {
			return TRUE;
		} else {
			return FALSE;
		}
	}
};

void selection(int top, string genre) {
	//КАКОЙ-ТО КОД
}

int main() {
    return 0;
}