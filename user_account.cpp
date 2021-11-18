#include <iostream>
#include <string.h>
#include <assert.h>
#include <sstream>
#include <fstream>
#include <stdio.h> 

class UserAccaunt {
private:
    int id;
    std::string Login;
    std::string Name;
    std::string Surname;
    std::string Email;
    std::string Password;
public:
    UserAccaunt() = default;
	UserAccaunt( const UserAccaunt& ) = delete;
	~UserAccaunt() {};
    void SetLogin(std::string newLogin);
    void SetName(std::string newName);
    void SetSurname(std::string newSurname);
    void SetEmail(std::string newEmail);
    std::string GetLogin();
    std::string GetName();
    std::string GetSurname();
    std::string GetEmail();
    void OutputInformation();
};

std::string UserAccaunt::GetLogin() {
    std::string GivenLogin;
    int i=-1;
    do {
        ++i;
        GivenLogin += Login[i];
    } while (Login[i] != '\0');
    return GivenLogin;
}
std::string UserAccaunt::GetName() {
    std::string GivenName;
    int i=-1;
    do {
        ++i;
        GivenName += Name[i];
    } while (Name[i] != '\0');
    return GivenName;
}
std::string UserAccaunt::GetSurname() {
    std::string GivenSurname;
    int i=-1;
    do {
        ++i;
        GivenSurname += Surname[i];
    } while (Surname[i] != '\0');
    return GivenSurname;
}
std::string UserAccaunt::GetEmail() {
    std::string GivenEmail;
    int i=-1;
    do {
        ++i;
        GivenEmail += Email[i];
    } while (Email[i] != '\0');
    GivenEmail[i] = Email[i];
    return GivenEmail;
}

void UserAccaunt::SetLogin(std::string newLogin) {
    int i=-1;
    do {
        ++i;
        Login += newLogin[i];
    }while (newLogin[i] != '\0');
}
void UserAccaunt::SetName(std::string newName) {
    int i=-1;
    do {
        ++i;
        Name += newName[i];
    } while (newName[i] != '\0');
}
void UserAccaunt::SetSurname(std::string newSurname) {
    int i=-1;
    do {
        ++i;
        Surname += newSurname[i];
    } while (newSurname[i] != '\0');
}
void UserAccaunt::SetEmail(std::string newEmail) {
    int i=-1;
    do {
        ++i;
        Email += newEmail[i];
    } while (newEmail[i] != '\0');
}

void UserAccaunt::OutputInformation() {
    std::cout <<"id: " <<id << "\n";
    std::cout <<"Login: " << Login << "\n";
    std::cout <<"Name: " <<Name << "\n";
    std::cout <<"Surname: " <<Surname << "\n";
    std::cout <<"Email: " <<Email << "\n";
}

class UserPage : public UserAccaunt{
private:
    std::string AboutMe;
    std::string Status;
    std::string Avatar;
    std::string FavoriteMovie;
    std::string FavoriteActor;
public:
    void SetAboutMe(std::string newAboutMe);
    void SetStatus(std::string newStatus);
    void SetAvatar(std::string newAvatar);
    void SetFavoriteMovie(std::string newFavoriteMovie);
    void SetFavoriteActor(std::string newFavoriteActor);
    std::string GetAboutMe();
    std::string GetStatus();
    std::string GetAvatar();
    std::string GetFavoriteMovie();
    std::string GetFavoriteActor();
};

void UserPage::SetAboutMe(std::string newAboutMe) {
    int i=-1;
    do {
        ++i;
        AboutMe += newAboutMe[i];
    } while (newAboutMe[i] != '\0');
}
void UserPage::SetStatus(std::string newStatus) {
    int i=-1;
    do {
        ++i;
        Status += newStatus[i];
    } while (newStatus[i] != '\0');
}
void UserPage::SetAvatar(std::string newAvatar) {
    int i=-1;
    do {
        ++i;
        Avatar += newAvatar[i];
    } while (newAvatar[i] != '\0');
}
void UserPage::SetFavoriteMovie(std::string newFavoriteMovie) {
    int i=-1;
    do {
        ++i;
        FavoriteMovie += newFavoriteMovie[i];
    } while (newFavoriteMovie[i] != '\0');
}
void UserPage::SetFavoriteActor(std::string newFavoriteActor) {
    int i=-1;
    do {
        ++i;
        FavoriteMovie += newFavoriteActor[i];
    } while (newFavoriteActor[i] != '\0');
}

std::string UserPage::GetAboutMe() {
    std::string GivenAboutMe;
    int i=-1;
    do {
        ++i;
        GivenAboutMe += AboutMe[i];
    } while (AboutMe[i] != '\0');
    return GivenAboutMe;
}

UserAccaunt* RegistrationAccount(std::string Login, std::string Name, std::string Surname, std::string Email) {
    UserAccaunt* newUser = new UserAccaunt;
    int i=0;
    newUser->SetLogin(Login);
    newUser->SetName(Name);
    newUser->SetSurname(Surname);
    newUser->SetEmail(Email);
    return newUser;
}
bool AuthenticationString(std::string str) {
    for (int i=0;i<str.length();++i) {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))) {
            return false;
        }
    }
    return true;
}
bool AuthenticationEmail(std::string str) {
    bool at = false, dot = false; 
    for (int i=0;i<str.length();++i) {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') 
        || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '@') || (str[i] == '.'))) {
            return false;
        }
        if (str[i] == '@') {
            at = true;
        }
        if (str[i] == '.') {
            dot = true;
        }
    }
    if (dot == true && at == true) {
        return true;
    } else {
        return false;
    }
}

int run( std::istream& input, std::ostream& output ) {
    UserAccaunt User;
    std::string TmprEmail;
    std::string TmprName;
    std::string TmprSurname;
    input >> TmprEmail;
    if (!AuthenticationEmail(TmprEmail)) {
        output << "Error related to the authentication of input data.";    
        return -1;
    }
    input >> TmprName;
    if (!AuthenticationString(TmprName)) {
        output << "Error related to the authentication of input data.";    
        return -1;
    }
    input >> TmprSurname;
    if (!AuthenticationString(TmprSurname)) {
        output << "Error related to the authentication of input data.";    
        return -1;
    }
    User.SetEmail(TmprEmail); 
    User.SetName(TmprName);
    User.SetSurname(TmprSurname);
    output << User.GetEmail() << User.GetName() << User.GetSurname();
    return 0;
}
