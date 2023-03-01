//User Implementation File

#include "userT.h"

UserT::UserT() {
    name = "test";
    UserID = 0;
}

UserT::UserT(std::string username, int ID) {
    name = username;
    UserID = ID;

    std::cout << "Created User with Name: " << username << " and ID " << ID << "." << std::endl;

};

UserT::~UserT(){

};

std::string UserT::GetUser() {
    return name;
};

int UserT::GetID() {
    return UserID;
};

void UserT::Print() {
    std::cout << "Username: " << name << ", ID: " << UserID << std::endl;
};
