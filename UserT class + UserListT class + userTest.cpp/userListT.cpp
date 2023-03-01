//implementation of user list class

#include "userListT.h"

UserListT::UserListT() {
    std::fstream file;

    std::string line;
    std::string user;
    std::string ID;
    size_t index = 1;
    
    file.open(USER_FILE);
    while(getline(file, line)) {
        //std::cout << line << std::endl;
        user = {};
        for (size_t i = 0; line[i] != ','; i++) {
            user = user + line[i];
            index = i+2;
        }
        ID = {};
        for (size_t j = index; j < line.size(); j++) {
            ID = ID + line[j];
            //std::cout << "."<< ID << "." << std::endl;
        }
        //std::cout << user << " " << ID << std::endl;
        list.push_back(UserT(user, stoi(ID)));
    }
    file.close();
};

UserListT::~UserListT() {
};

int UserListT::GetSize() {
    return static_cast<int>(list.size());
};


void UserListT::PrintUsers() {
    for (size_t i = 0; i < list.size(); i++) {
       list[i].Print();
    }
};