//User Implementation File

#include "userT.h"

UserT::UserT() {
    name = "test";
    UserID = 0;
}

UserT::UserT(std::string username, int ID) {
    name = username;
    UserID = ID;

    //std::cout << "Created User with Name: " << username << " and ID " << ID << "." << std::endl;

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

void UserT::SetSwim(float num) {
    if (num > 0) {
        targetSwim = num;
    } else {
        std::cout << "Input must be greater than 0!" << std::endl;
    }
    std::cout << "                              New SWIM target is: " << targetSwim << std::endl << std::endl;
};

void UserT::SetRun(float num) {
    if (num > 0) {
        targetRun = num;
    } else {
        std::cout << "Input must be greater than 0!" << std::endl;
    }
    std::cout << "                              New RUN target is:  " << targetRun << std::endl << std::endl;
};

void UserT::SetBike(float num) {
   if (num > 0) {
        targetBike = num;
   }  else {
        std::cout << "Input must be greater than 0!" << std::endl;
    }
    std::cout << "                              New BIKE target is: " << targetBike << std::endl << std::endl ;
};

void UserT::SwimCheck(float speed) {
    if (speed > 0) {
        float swim = (speed/targetSwim) * 100;
        if (swim >= 100) {
            swim = 100;
        }
        OutputGraph(static_cast<float>(ceil(swim)));
        std::cout << "                      You are " << std::setprecision(3) << swim << "%" << " towards your swim target!" << std::endl << std::endl;
    } else {
        std::cout << "Input must be greater than 0!" << std::endl;
    }
};

void UserT::RunCheck(float speed) {
    if (speed > 0) {
        float run = (speed/targetRun) * 100;
        if (run >= 100) {
            run = 100;
        }
        OutputGraph(static_cast<float>(ceil(run)));
        std::cout << "                      You are " << std::setprecision(3) << run << "%" <<  " towards your run target!" << std::endl << std::endl;
    } else {
        std::cout << "Input must be greater than 0!" << std::endl;
    } 
};

void UserT::BikeCheck(float speed) {
    if (speed > 0) {
        float bike = (speed/targetBike) * 100;
        if (bike >= 100) {
            bike = 100;
        }
        OutputGraph(static_cast<float>(ceil(bike)));
        std::cout << "                      You are " << std::setprecision(3) << bike << "%" << " towards your bike target!" << std::endl << std::endl;
    } else {
        std::cout << "Input must be greater than 0!" << std::endl;
    }
};

void UserT::CheckTargets() {
    float num;
    std::cout << "                      Enter SWIM target (mph): ";
    std::cin >> num;
    SetSwim(num);

    std::cout << "                      Enter BIKE target (mph): ";
    std::cin >> num;
    SetBike(num);

    std::cout << "                      Enter RUN target (mph):  ";
    std::cin >> num;
    SetRun(num);

    /*
    SwimCheck();
    BikeCheck();
    RunCheck();
    */

};

void UserT::OutputGraph(float num) {
    int tracker = static_cast<int>(num);
    int blank = 100 - tracker;
    std::cout << "                               |||PROGRESS BAR|||" << std::endl;
    std::cout << "{";
    while (tracker > 0) {
        std::cout << "|";
        tracker = tracker - 1;
    }
    while (blank > 0) {
        std::cout << " ";
       blank = blank - 1;
    }
    std::cout << "}" << std::endl;

    return;
}
