//User Header File
#pragma once

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>

/*
To Do:
Function to create a user repo and add an event to it. (Date,Type,Distance,Time)

*/

const std::string USER_FILE {"users.txt"};

class UserT {

public:
UserT();
UserT(std::string username, int ID);
~UserT();

std::string GetUser();
int GetID();
void Print();
void SetSwim(float num);
void SetRun(float num);
void SetBike(float num);
void SwimCheck(float speed);
void RunCheck(float speed);
void BikeCheck(float speed);
void CheckTargets();
void OutputGraph(float num);

private:
std::string name;
int UserID;
float targetSwim;
float targetRun;
float targetBike;
};