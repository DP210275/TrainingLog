//User Header File
#pragma once

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>

const std::string USER_FILE {"users.txt"};

class UserT {

public:
UserT();
UserT(std::string username, int ID);
~UserT();

std::string GetUser();
int GetID();
void Print();

private:
std::string name;
int UserID;

};