#include <iostream>
#include <string>
#include <vector>
#include <ctime>        //for getting current month/day
#include <stdlib.h>     //for atoi function
#include <iomanip>      //for setprecision
#include <limits>       //for numeric_limits in ValidInput()

#include "userT.h"
#include "userListT.h"
#include "EventT.h"

using namespace std;

int numEvents = 0;
vector<EventT> userEvents;

void LoginUser();
bool Search(string name);
void OutputChoices();
int GetUserSelection();
int ValidInput();
void TrainingMenu();
void SwimData();
void RunData();
void BikeData();
void DataAnalysis();
void GetMean();
void GetMax();
void GetOverall();
int GetLocalMonthOrDay(int control);
void SetMonthDays(vector<int>&days, int mon);
bool DayIsValid(vector<int>& days, string day);
bool Find(vector<int> vec, int key);
bool ContainsOnlyNumbers(const string& str);
bool IsAFloat(string& str);
bool IsValidHR(string resp);

int main() {

    LoginUser();
    OutputChoices();
    GetUserSelection();

    return 0;
}


void LoginUser() {
    ofstream outFile;
    string username;
    int newID;

    UserListT list = UserListT();

    newID = list.UserListT::GetSize() + 1;
    list.UserListT::PrintUsers();

    UserListT();

    cout << "Please enter your username: ";
    cin >> username;

    if (!Search(username)) {
        UserT user(username, newID);
        outFile.open(USER_FILE, std::ios::app);
        outFile << username << "," << newID << endl;
        outFile.close();

        newID++;
    }
}

bool Search(string name){

    ifstream file;
    std::string line;
    int i;
    bool found = false;

    file.open(USER_FILE, std::ios::app);

    while(getline(file, line)) {
        i++;
        if (line.find(name) != std::string::npos) {
            std::cout << "Error: " << name << " already exists!" << std::endl;
            found = true;
        }
    }
    file.close();
    return found;
};

void OutputChoices() {
    cout << R"(                                                               
                                              ████                  ████      
                                              ████                  ████      
              ████                        ▓▓▓▓                ▓▓  ▓▓          
      ██████  ████                      ▓▓▓▓▓▓▓▓            ██  ▓▓▓▓▓▓██      
    ██      ████  ████████          ██▓▓▓▓    ▓▓██        ██    ▓▓▓▓    ████  
        ▓▓██▓▓██▓▓                ████          ████          ▓▓▓▓▓▓▓▓        
  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓    ██    ██      ██    ██      ██▓▓    ▓▓████    
                                ██    ██      ██    ██    ████          ██    
                                  ████          ████      ██            ████  
        )" << '\n';
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<"   Welcome to your Triathlon Training Log! " << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<"Enter 1 for Training Log" << endl;
    cout << endl;
 
    cout << '\t'<< '\t'<< '\t'<< "Enter 2 for Data Analysis" << endl;
    cout << endl;

    cout << '\t'<< '\t'<< '\t'<< "Enter 3 to Exit" << endl;
    cout << endl;

    cout << "-----------------------------------------------------------------------------" << endl;

}

int GetUserSelection() {
    int userChoice;

    cout << endl;
    cout << '\t'<<'\t'<< "     What would you like to select?";
    cout << '\t' ;
    userChoice = ValidInput();
    cout << endl;

    if (userChoice == 1) {
        TrainingMenu();
    } else if (userChoice == 2) {
        DataAnalysis();
    } else if (userChoice == 3) {
        exit(-1);
    } 
    
    while (userChoice <= 0 || userChoice > 3) {
        cout << '\t'<< '\t'<< "   Invalid selection. Please try again." << endl;
        cout << endl;

        cout << '\t'<<'\t'<< "     What would you like to select?";
        cout << '\t' ;
        cin >> userChoice;
        cout << endl;

        if (userChoice == 1) {
            TrainingMenu();
        } else if (userChoice == 2) {
            DataAnalysis();
        } else if (userChoice == 3) {
            exit(-1);
        } 
    }

    return userChoice;
}

int ValidInput()
{
    int x;
    cin >> x;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << endl;
        cout <<  '\t'<<'\t'<< "    Invalid selection. Please try again.";
        cout << endl << endl;
        cout << '\t'<<'\t'<< "     What would you like to select?";
        cout << '\t' ;
        cin >> x;
    }
    return x;
}

void TrainingMenu() {
    int trainingChoice;

    cout << "-----------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<'\t'<< "Training Log" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<"Enter 1 to log a swim training" << endl;
    cout << endl;

    cout << '\t'<<'\t'<<'\t'<< "Enter 2 to log a run training" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<"Enter 3 to log a bike training" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<"Enter 4 to go back to the Main Menu" << endl;
    cout << endl;
    cout << '\t'<< '\t'<<'\t';

    cout << "Selection: ";
    cout << '\t' ;

    trainingChoice = ValidInput();
    cout << endl << endl;
    cout << "-----------------------------------------------------------------------------";
    cout << endl;

    if (trainingChoice == 1) {
        SwimData();
    } else if (trainingChoice == 2) {
        RunData();
    } else if (trainingChoice == 3) {
        BikeData();
    } else if (trainingChoice ==4){
        OutputChoices();
        GetUserSelection();
    }

    while (trainingChoice <= 0 || trainingChoice > 3) {
        cout << '\t'<< '\t'<< "   Invalid selection. Please try again." << endl;
        cout << endl;

        cout << '\t'<<'\t'<< '\t'<< "Selection: ";
        cout << '\t' ;
        cin >> trainingChoice;
        cout << endl;

         if (trainingChoice == 1) {
            SwimData();
        } else if (trainingChoice == 2) {
            RunData();
        } else if (trainingChoice == 3) {
            BikeData();
        } else if (trainingChoice ==4){
            OutputChoices();
            GetUserSelection();
        }

    }
}

void SwimData() {
    EventT swimEvent(S, numEvents);
    string useCurrentDate;
    string userHeartRate;
    string userDistance;
    string notes;
    string userMonth;
    string userDay;
    string userTrainingWeek;
    string userDuration;
    int day;
    int month;
    int trainingWeek;
    int duration;
    float distance;
    int heartRate;
    vector<int> validDays;
    
    //for testing purposes, will remove when user repositories are implemented
    //ofstream outFile;
    //outFile.open("dummyRepo.txt");


    cout << R"(
                                      _                                  
                                     (_)                         
                         _____      ___ _ __ ___  
                        / __\ \ /\ / / | '_ ` _ \
                        \__ \\ V  V /| | | | | | |
                        |___/ \_/\_/ |_|_| |_| |_|
                                  
        )" << '\n';

    cout << "-----------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Enter swim training data: " << endl;
    cout << endl;

    /********** Date **********/
    cout << '\t' << '\t'<<'\t'<< "Use Current Date (Y/N): ";
    cin >> useCurrentDate;
    while(useCurrentDate != "Y" and useCurrentDate != "y" and useCurrentDate != "N" and useCurrentDate != "n"){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid selection. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<< "Use Current Date (Y/N): ";
        cin >> useCurrentDate;
    }
    
    if(useCurrentDate == "Y" or useCurrentDate == "y"){
        month = GetLocalMonthOrDay(1);
        day = GetLocalMonthOrDay(2);
        cout << endl;
    }else{
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Month of Workout (1-12): ";
        cin >> userMonth;

        //Validate userMonth
        while(userMonth != "1" and userMonth != "2" and userMonth != "3" and userMonth != "4" and userMonth != "5" and userMonth != "6" and
        userMonth != "7" and userMonth != "8" and userMonth != "9" and userMonth != "10" and userMonth != "11" and userMonth != "12"){
            cout << endl;
            cout << '\t'<< '\t' << "   Invalid month. Please try again." << endl;
            cout << endl;
            cout << '\t' << '\t'<<'\t'<<"Month of Workout (1-12): ";
            cin>> userMonth;
        }
        cout << endl;
        month = atoi(userMonth.c_str());

        //Set the days of the entered month for validating userDay
        SetMonthDays(validDays, month);

        cout << '\t' << '\t'<<'\t'<<"Day of Workout: ";
        cin >> userDay;

        //Validate userDay
        while(!DayIsValid(validDays, userDay)){
            cout << endl;
            cout << '\t'<< '\t' << "   Invalid day. Please try again." << endl;
            cout << endl;
            cout << '\t' << '\t'<<'\t'<<"Day of Workout: ";
            cin>> userDay;
        }
        cout << endl;
        day = atoi(userDay.c_str());
    }

    /********** Training Week Number **********/
    cout << '\t' << '\t'<<'\t'<<"Training Week Number:  ";
    cin >> userTrainingWeek;
    while(!ContainsOnlyNumbers(userTrainingWeek) or userTrainingWeek == "0" or userTrainingWeek.length() == 0){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid training week number. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Training Week Number:  ";
        cin >> userTrainingWeek;
    }
    cout << endl;
    trainingWeek = atoi(userTrainingWeek.c_str());

    /********** Duration **********/
    cout << '\t' << '\t'<<'\t'<<"Workout Duration (minutes):  ";
    cin >> userDuration;
    while(!ContainsOnlyNumbers(userDuration) or userDuration.length() == 0 or (atoi(userDuration.c_str())) == 0){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid duration. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Workout Duration (minutes):  ";
        cin >> userDuration;
    }
    cout << endl;
    duration = atoi(userDuration.c_str());

    /********** Distance **********/
    cout << '\t' << '\t'<<'\t'<<"Total Distance (miles): ";
    cin >> userDistance;
    while(userDistance.length() == 0 or !IsAFloat(userDistance)){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid distance. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Total Distance (miles)):  ";
        cin >> userDistance;
    }
    cout << endl;
    distance = stof(userDistance);

    /********** Heart Rate **********/
    cout << '\t' << '\t'<<'\t'<<"Heart Rate: ";
    cin >> userHeartRate;
    while(!IsValidHR(userHeartRate)){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid heart rate. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Heart Rate:  ";
        cin >> userHeartRate;
    }
    cout << endl;
    heartRate = atoi(userHeartRate.c_str());

    /********** Notes ***********/
    cout << '\t' << '\t'<<'\t'<<"Notes: "; 
    cin.ignore(100, '\n');
    getline(cin, notes);
    cout << endl;

    //set the swim EventT attributes and eventually write event to userREPO file.
    swimEvent.SetDistance(distance);
    swimEvent.SetHeartRate(heartRate);
    swimEvent.SetNotes(notes);
    swimEvent.SetMonth(month);
    swimEvent.SetDay(day);
    swimEvent.SetTrainingWeek(trainingWeek);
    swimEvent.SetTime(duration);
    swimEvent.CalculateSpeed();

    userEvents.push_back(swimEvent);

    //For testing purposes, output created event to dummyRepo file.
    /*
        outFile<< swimEvent.GetType() << " ; ";
        outFile<< swimEvent.GetMonth() << " ; ";
        outFile<< swimEvent.GetDay() << " ; ";
        outFile<< swimEvent.GetTrainingWeek() << " ; ";
        outFile<< swimEvent.GetTime() << " ; ";
        outFile<< swimEvent.GetDistance() << " ; ";
        outFile<< fixed;
        outFile<< setprecision(2) << swimEvent.GetSpeed() << " ; ";
        outFile<< swimEvent.GetHeartRate() << " ; ";
        outFile<< swimEvent.GetNotes() << " ; \n";
        
        outFile.close();
    */

    TrainingMenu();

}

void RunData() {
    EventT runEvent(R, numEvents);
    string useCurrentDate;
    string userHeartRate;
    string userDistance;
    string notes;
    string userMonth;
    string userDay;
    string userTrainingWeek;
    string userDuration;
    int day;
    int month;
    int trainingWeek;
    int duration;
    float distance;
    int heartRate;
    vector<int> validDays;

    //for testing purposes, will remove when user repositories are implemented
    //ofstream outFile;
    //outFile.open("dummyRepo.txt");

    cout << R"(

                             _ __ _   _ _ __  
                            | '__| | | | '_ \
                            | |  | |_| | | | |
                            |_|   \__,_|_| |_|
                                  
        )" << '\n';

    cout << "-----------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Enter run training data: " << endl;
    cout << endl;

    /********** Date **********/
    cout << '\t' << '\t'<<'\t'<< "Use Current Date (Y/N): ";
    cin >> useCurrentDate;
    while(useCurrentDate != "Y" and useCurrentDate != "y" and useCurrentDate != "N" and useCurrentDate != "n"){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid selection. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<< "Use Current Date (Y/N): ";
        cin >> useCurrentDate;
    }

    if(useCurrentDate == "Y" or useCurrentDate == "y"){
        month = GetLocalMonthOrDay(1);
        day = GetLocalMonthOrDay(2);
        cout << endl;
    }else{
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Month of Workout (1-12): ";
        cin >> userMonth;

        //Validate userMonth
        while(userMonth != "1" and userMonth != "2" and userMonth != "3" and userMonth != "4" and userMonth != "5" and userMonth != "6" and
        userMonth != "7" and userMonth != "8" and userMonth != "9" and userMonth != "10" and userMonth != "11" and userMonth != "12"){
            cout << endl;
            cout << '\t'<< '\t' << "   Invalid month. Please try again." << endl;
            cout << endl;
            cout << '\t' << '\t'<<'\t'<<"Month of Workout (1-12): ";
            cin>> userMonth;
        }
        cout << endl;
        month = atoi(userMonth.c_str());

        //Set the days of the entered month for validating userDay
        SetMonthDays(validDays, month);

        cout << '\t' << '\t'<<'\t'<<"Day of Workout: ";
        cin >> userDay;

        //Validate userDay
        while(!DayIsValid(validDays, userDay)){
            cout << endl;
            cout << '\t'<< '\t' << "   Invalid day. Please try again." << endl;
            cout << endl;
            cout << '\t' << '\t'<<'\t'<<"Day of Workout: ";
            cin>> userDay;
        }
        cout << endl;
        day = atoi(userDay.c_str());
    }

    /********** Training Week Number **********/
    cout << '\t' << '\t'<<'\t'<<"Training Week Number:  ";
    cin >> userTrainingWeek;
    while(!ContainsOnlyNumbers(userTrainingWeek) or userTrainingWeek == "0" or userTrainingWeek.length() == 0){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid training week number. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Training Week Number:  ";
        cin >> userTrainingWeek;
    }
    cout << endl;
    trainingWeek = atoi(userTrainingWeek.c_str());

    /********** Duration **********/
    cout << '\t' << '\t'<<'\t'<<"Workout Duration (minutes):  ";
    cin >> userDuration;
    while(!ContainsOnlyNumbers(userDuration) or userDuration.length() == 0 or (atoi(userDuration.c_str())) == 0){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid duration. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Workout Duration (minutes):  ";
        cin >> userDuration;
    }
    cout << endl;
    duration = atoi(userDuration.c_str());

    /********** Distance **********/
    cout << '\t' << '\t'<<'\t'<<"Total Distance (miles): ";
    cin >> userDistance;
    while(userDistance.length() == 0 or !IsAFloat(userDistance)){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid distance. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Total Distance (miles)):  ";
        cin >> userDistance;
    }
    cout << endl;
    distance = stof(userDistance);

    /********** Heart Rate **********/
    cout << '\t' << '\t'<<'\t'<<"Heart Rate: ";
    cin >> userHeartRate;
    while(!IsValidHR(userHeartRate)){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid heart rate. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Heart Rate:  ";
        cin >> userHeartRate;
    }
    cout << endl;
    heartRate = atoi(userHeartRate.c_str());

    /********** Notes ***********/
    cout << '\t' << '\t'<<'\t'<<"Notes: "; 
    cin.ignore(100, '\n');
    getline(cin, notes);
    cout << endl;

    //set the run EventT attributes and eventually write event to userREPO file.
    runEvent.SetDistance(distance);
    runEvent.SetHeartRate(heartRate);
    runEvent.SetNotes(notes);
    runEvent.SetMonth(month);
    runEvent.SetDay(day);
    runEvent.SetTrainingWeek(trainingWeek);
    runEvent.SetTime(duration);
    runEvent.CalculateSpeed();

    userEvents.push_back(runEvent);

    //For testing purposes, output created event to dummyRepo file.
    /*
        outFile<< runEvent.GetType() << " ; ";
        outFile<< runEvent.GetMonth() << " ; ";
        outFile<< runEvent.GetDay() << " ; ";
        outFile<< runEvent.GetTrainingWeek() << " ; ";
        outFile<< runEvent.GetTime() << " ; ";
        outFile<< runEvent.GetDistance() << " ; ";
        outFile<< fixed;
        outFile<< setprecision(2) << runEvent.GetSpeed() << " ; ";
        outFile<< runEvent.GetHeartRate() << " ; ";
        outFile<< runEvent.GetNotes() << " ; \n";
        
        outFile.close();
    */

    TrainingMenu();


}

void BikeData() {
    EventT bikeEvent(B, numEvents);
    string useCurrentDate;
    string userHeartRate;
    string userDistance;
    string notes;
    string userMonth;
    string userDay;
    string userTrainingWeek;
    string userDuration;
    int day;
    int month;
    int trainingWeek;
    int duration;
    float distance;
    int heartRate;
    vector<int> validDays;

    //for testing purposes, will remove when user repositories are implemented
    //ofstream outFile;
    //outFile.open("dummyRepo.txt");

    cout << R"(
                             _     _ _        
                            | |   (_) |       
                            | |__  _| | _____ 
                            | '_ \| | |/ / _ \
                            | |_) | |   <  __/
                            |_.__/|_|_|\_\___|
        )" << '\n';
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Enter bike training data: " << endl;
    cout << endl;

   /********** Date **********/
    cout << '\t' << '\t'<<'\t'<< "Use Current Date (Y/N): ";
    cin >> useCurrentDate;
    while(useCurrentDate != "Y" and useCurrentDate != "y" and useCurrentDate != "N" and useCurrentDate != "n"){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid selection. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<< "Use Current Date (Y/N): ";
        cin >> useCurrentDate;
    }

    if(useCurrentDate == "Y" or useCurrentDate == "y"){
        month = GetLocalMonthOrDay(1);
        day = GetLocalMonthOrDay(2);
        cout << endl;
    }else{
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Month of Workout (1-12): ";
        cin >> userMonth;

        //Validate userMonth
        while(userMonth != "1" and userMonth != "2" and userMonth != "3" and userMonth != "4" and userMonth != "5" and userMonth != "6" and
        userMonth != "7" and userMonth != "8" and userMonth != "9" and userMonth != "10" and userMonth != "11" and userMonth != "12"){
            cout << endl;
            cout << '\t'<< '\t' << "   Invalid month. Please try again." << endl;
            cout << endl;
            cout << '\t' << '\t'<<'\t'<<"Month of Workout (1-12): ";
            cin>> userMonth;
        }
        cout << endl;
        month = atoi(userMonth.c_str());

        //Set the days of the entered month for validating userDay
        SetMonthDays(validDays, month);

        cout << '\t' << '\t'<<'\t'<<"Day of Workout: ";
        cin >> userDay;

        //Validate userDay
        while(!DayIsValid(validDays, userDay)){
            cout << endl;
            cout << '\t'<< '\t' << "   Invalid day. Please try again." << endl;
            cout << endl;
            cout << '\t' << '\t'<<'\t'<<"Day of Workout: ";
            cin>> userDay;
        }
        cout << endl;
        day = atoi(userDay.c_str());
    }

    /********** Training Week Number **********/
    cout << '\t' << '\t'<<'\t'<<"Training Week Number:  ";
    cin >> userTrainingWeek;
    while(!ContainsOnlyNumbers(userTrainingWeek) or userTrainingWeek == "0" or userTrainingWeek.length() == 0){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid training week number. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Training Week Number:  ";
        cin >> userTrainingWeek;
    }
    cout << endl;
    trainingWeek = atoi(userTrainingWeek.c_str());

    /********** Duration **********/
    cout << '\t' << '\t'<<'\t'<<"Workout Duration (minutes):  ";
    cin >> userDuration;
    while(!ContainsOnlyNumbers(userDuration) or userDuration.length() == 0 or (atoi(userDuration.c_str())) == 0){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid duration. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Workout Duration (minutes):  ";
        cin >> userDuration;
    }
    cout << endl;
    duration = atoi(userDuration.c_str());

    /********** Distance **********/
    cout << '\t' << '\t'<<'\t'<<"Total Distance (miles): ";
    cin >> userDistance;
    while(userDistance.length() == 0 or !IsAFloat(userDistance)){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid distance. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Total Distance (miles)):  ";
        cin >> userDistance;
    }
    cout << endl;
    distance = stof(userDistance);
    
    /********** Heart Rate **********/
    cout << '\t' << '\t'<<'\t'<<"Heart Rate: ";
    cin >> userHeartRate;
    while(!IsValidHR(userHeartRate)){
        cout << endl;
        cout << '\t'<< '\t'<< "   Invalid heart rate. Please try again." << endl;
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"Heart Rate:  ";
        cin >> userHeartRate;
    }
    cout << endl;
    heartRate = atoi(userHeartRate.c_str());

    /********** Notes ***********/
    cout << '\t' << '\t'<<'\t'<<"Notes: "; 
    cin.ignore(100, '\n');
    getline(cin, notes);
    cout << endl;

    //set the run EventT attributes and eventually write event to userREPO file.
    bikeEvent.SetDistance(distance);
    bikeEvent.SetHeartRate(heartRate);
    bikeEvent.SetNotes(notes);
    bikeEvent.SetMonth(month);
    bikeEvent.SetDay(day);
    bikeEvent.SetTrainingWeek(trainingWeek);
    bikeEvent.SetTime(duration);
    bikeEvent.CalculateSpeed();

    userEvents.push_back(bikeEvent);

    //For testing purposes, output created event to dummyRepo file.
    /*
        outFile<< bikeEvent.GetType() << " ; ";
        outFile<< bikeEvent.GetMonth() << " ; ";
        outFile<< bikeEvent.GetDay() << " ; ";
        outFile<< bikeEvent.GetTrainingWeek() << " ; ";
        outFile<< bikeEvent.GetTime() << " ; ";
        outFile<< bikeEvent.GetDistance() << " ; ";
        outFile<< fixed;
        outFile<< setprecision(2) << bikeEvent.GetSpeed() << " ; ";
        outFile<< bikeEvent.GetHeartRate() << " ; ";
        outFile<< bikeEvent.GetNotes() << " ; \n";
        
        outFile.close();
    */
    TrainingMenu();

}

void DataAnalysis() {
    int dataAnalysisChoice = 0;

    cout << "-----------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<"   What kind of data analysis are you looking for?" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<"Enter 1 to for show mean" << endl;
    cout << endl;

    cout << '\t'<<'\t'<<'\t'<< "Enter 2 to for show max" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<"Enter 3 to for show overall performance" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<"Enter 4 to go back to the Main Menu" << endl;
    cout << endl;

    cout << '\t' ;
    cout << '\t'<<'\t'<<"Selection: ";
   

    dataAnalysisChoice = ValidInput();
    cout << endl;

    if (dataAnalysisChoice == 1) {
        GetMean();
    } else if (dataAnalysisChoice == 2) {
        GetMax();
    } else if (dataAnalysisChoice == 3) {
        GetOverall();
    } else if (dataAnalysisChoice == 4){
        OutputChoices();
        GetUserSelection();
    }

    while (dataAnalysisChoice <= 0 || dataAnalysisChoice > 3) {
        cout << '\t'<< '\t'<< "   Invalid selection. Please try again." << endl;
        cout << endl;

        cout << '\t'<<'\t'<< '\t'<< "Selection: ";
        cout << '\t' ;
        dataAnalysisChoice = ValidInput();
        cout << endl;
        
        if (dataAnalysisChoice == 1) {
            GetMean();
        } else if (dataAnalysisChoice == 2) {
            GetMax();
        } else if (dataAnalysisChoice == 3) {
            GetOverall();
        } else if (dataAnalysisChoice == 4){
            OutputChoices();
            GetUserSelection();
        }
    }

}

void GetMean() {
    int trainingWeekChoice = 0;
    string userEventType;
    string logEventType = "X";
    string matchingEventType;
    vector<EventT> matchingTWEvents;
    vector<EventT> matchingTWAndTypeEvents;
    bool noEvents = false;
    float avgHR = 0.0;
    float avgTime = 0.0;
    float avgDist = 0.0;
    float avgSpeed = 0.0;
    float totalDist = 0.0;
    int totalHR = 0;
    int totalTime = 0;
    float totalSpeed = 0.0;
    float amtEvents = 0.0;


    cout << "-----------------------------------------------------------------------------" << endl;

    /*
        What to do here:
            - Ask the user for what training week they would like to evaluate
            - Walk through vector of events and put events with matching training week number (TWN) into new vector
            - If no events have the trianing week number inputted by the user
                Then output "Sorry, no events have that training week number. please try again" or something
            - otherwise
                > calculate mean HR, time, distance, speed for each event
                    (step through new vector, grab those things and add them together, and divide by the number of events)
                > Output mean and return to DataAnalysis menu

        Future enhancements to this function:
            - Ask user what event they'd like the average of (S/B/R/All)
                > If S, only get Swim events. If B, only bike events. If R, only run events. If A/all/All, use all events
            - Allow user to enter multiple weeks for the average
                > Ask user for first TWN
                > Then ask if they want to enter another TWN for calculation (a Y/N)
                > If Y, loop the following steps until N received:
                    - Ask user for TWN
                    - Ask if they want to enter another TWN (Y/N)
            - Put in some bar graphs?        
    */

    //Check if there are any events for the user. If not, return to Data Analytics menu
    if(userEvents.size() == 0){
        cout << '\t' << '\t' << "Sorry, no events have been logged yet." << endl;
        cout << '\t' << '\t' << "Please log an event before trying to calculate the mean." << endl;
    }else{
        do{
            if(noEvents){
                cout << '\t' << '\t' << "     Sorry, no logged events have that training week number." << endl;
                cout << '\t' << '\t' << "     Please try again." << endl;
            }
        
            cout << '\t'<< '\t'<<"   Please enter the training week number for evaluation." << endl;
            cout << endl;
            cout << '\t' << '\t' << '\t' << "Selection: ";
            trainingWeekChoice = ValidInput();

            //Get the events from the user's list of logged events that match the given training week number
            for(size_t i = 0; i < userEvents.size(); i++){
                if(userEvents[i].GetTrainingWeek() == trainingWeekChoice){
                    matchingTWEvents.push_back(userEvents[i]);
                }
            }

            if(matchingTWEvents.size() == 0){
                noEvents = true;
            }
        }while(matchingTWEvents.size() == 0);

        //Ask what kind of events the user would like to analyze
        cout << '\t' << '\t' << "    Please enter the type of event for evaluation (S/B/R/All)." << endl << endl;
        cout << '\t' << '\t' << '\t' << "Selection: ";
        cin.ignore(100, '\n');
        getline(cin, userEventType);
        cout << endl;

        if(isalpha(userEventType[0])){
            logEventType = char(toupper(userEventType[0]));
        }

        while(logEventType != "S" and logEventType != "B" and logEventType != "R" and logEventType != "A"){
            cout << '\t'<< '\t'<< "   Invalid selection. Please try again." << endl;
            cout << endl;
            cout << '\t'<<'\t'<< '\t'<< "Selection: ";
            cout << '\t' ;
            cin.ignore(100, '\n');
            getline(cin, userEventType);
            cout << endl;

            if(isalpha(userEventType[0])){
                logEventType = char(toupper(userEventType[0]));
            }
        }
        
        if(logEventType == "S"){
            matchingEventType = "Swim";
        }else if(logEventType == "B"){
            matchingEventType = "Bike";
        }else if(logEventType == "R"){
            matchingEventType = "Run";
        }else if(logEventType == "A"){
            matchingEventType = "All";
        }

        if(matchingEventType != "All"){
            for(size_t i = 0; i < matchingTWEvents.size(); i++){
                if(matchingTWEvents[i].GetType() == matchingEventType){
                    matchingTWAndTypeEvents.push_back(matchingTWEvents[i]);
                }
            }
        }else{
            for(size_t j = 0; j < matchingTWEvents.size(); j++){
                matchingTWAndTypeEvents.push_back(matchingTWEvents[j]);
            }
        }

        for(size_t k = 0; k < matchingTWAndTypeEvents.size(); k++){
            totalHR += matchingTWAndTypeEvents[k].GetHeartRate();
            totalDist += matchingTWAndTypeEvents[k].GetDistance();
            totalSpeed += matchingTWAndTypeEvents[k].GetSpeed();
            totalTime += matchingTWAndTypeEvents[k].GetTime();
        }   

        amtEvents = float(matchingTWAndTypeEvents.size());
        avgHR = float(totalHR)/amtEvents;
        avgDist = totalDist/amtEvents;
        avgSpeed = totalSpeed/amtEvents;
        avgTime = float(totalTime)/amtEvents;

        cout << fixed;
        cout << setprecision(2) << endl;
        cout << '\t' << '\t' << "For Training Week " << trainingWeekChoice << ": " << endl;
        cout << '\t' << '\t' << '\t' << "Average Heart Rate: " << avgHR << "bpm" << endl;
        cout << '\t' << '\t' << '\t' << "Average Distance: " << avgDist << " miles" <<endl;
        cout << '\t' << '\t'<< '\t' << "Average Time: " << avgTime << " minutes" << endl;
        cout << '\t' << '\t'<< '\t' << "Average Speed: " << avgSpeed << "mph" << endl;
        cout << endl;

    }
    DataAnalysis();
}


void GetMax() {
    cout << "-----------------------------------------------------------------------------" << endl;

    /*
        What to do here:
            - Ask the user for what training week they would like to evaluate
            - Walk through vector of events and put events with matching training week # into new vector
            - If no events have the trianing week number inputted by the user
                Then output "Sorry, no events have that training week number. please try again" or something
            - otherwise
                > Walk through new vector and find the max HR, time, distance, and speed for that week
                > Output these and return to data analysis menu
    */    

    cout << '\t' << "Max:" << endl;
    

    DataAnalysis();
}

void GetOverall() {
    cout << "-----------------------------------------------------------------------------" << endl;

    /*
        What to do here:
            Maybe somehow do a graph of some sort? 
    */    

    cout << '\t' << "Overall performance:" << endl;


    DataAnalysis();
}

int GetLocalMonthOrDay(int control){
    time_t rawTime;
    struct tm *info;
    int rv;

    time(&rawTime);
    info = localtime(&rawTime);

    if(control == 1){
        rv = info->tm_mon;
        rv++;
    }else{
        rv = info->tm_mday;
    }

    return rv;
}

void SetMonthDays(vector<int>&days, int mon){
    int stepDay = 1;
    int numDaysInMonth = 0;

    if(mon == 1 or mon == 3 or mon == 5 or mon == 7 or mon == 8 or mon == 10 or mon == 12){
        numDaysInMonth = 31;
    }else if(mon == 4 or mon == 6 or mon == 9 or mon == 11){
        numDaysInMonth = 30;
    }else if(mon == 2){
        numDaysInMonth = 28;
    }

    for(int i = 0; i < numDaysInMonth; i++){
        days.push_back(stepDay);
        stepDay++;
    }

    return;
}

bool DayIsValid(vector<int>& days, string day){
    bool isValid = true;
    int dayInt;
    int check;

    if(day.length() == 2 or day.length() == 1){ 
        for(size_t i = 0; i < day.length(); i++){
            //Verify that the string we have is indeed only numbers. If it there are any alphabet characters, return false
            check = isalpha(day[i]);
            if(check){
                isValid = false;
            }
        }
        if(isValid){
            dayInt = atoi(day.c_str());

            //See if the number given by the user is a valid day of the specific month input previously
            if(!Find(days, dayInt)){
                isValid = false;
            }
        }
    }else{
        isValid = false;
    }

    return isValid;
}

bool Find(vector<int> vec, int key){
    bool found = false;

    for(size_t i = 0; i < vec.size(); i++){
        if(vec[i] == key){
            found = true;
        }
    }

    return found;
}

bool ContainsOnlyNumbers(const string& str){
    bool onlyNumbers = true;
    int check;

    for(size_t i = 0; i < str.length(); i++){
        check = isalpha(str[i]);
        if(check){
            onlyNumbers = false;
        }
    }

    return onlyNumbers;
}

bool IsAFloat(string& str){
    size_t decimalPos = str.find(".");
    bool rv;
    string beforePeriod;
    string afterPeriod;
    string round;
    int compare;

    if(decimalPos == string::npos){
        if(!ContainsOnlyNumbers(str)){
            rv = false;
        }else{
            compare = atoi(str.c_str());
            if(compare == 0 or compare > 10){
                rv = false;
            }else{
                str.append(".00");
                rv = true;
            }
        }
    }else{
        beforePeriod = str.substr(0, decimalPos);
        afterPeriod = str.substr(decimalPos+1);

        if(!ContainsOnlyNumbers(beforePeriod) or !ContainsOnlyNumbers(afterPeriod)){
            rv = false;
        }else{
            compare = atoi(beforePeriod.c_str());
            if(compare <= 10 and compare != 0){                      //checking distance for reasonableness, if not return false
                if(afterPeriod.length() > 2){
                    round = afterPeriod.substr(0, 3);
                    
                    //Case for rounding up
                    if(round[2] == '5' or round[2] == '6' or round[2] == '7' or round[2] == '8' or round[2] == '9'){
                        compare = atoi(round.substr(0,2).c_str());
                        compare++;                        
                    }else{
                        compare = atoi(round.substr(0,2).c_str());
                    }
                    afterPeriod = to_string(compare);

                    //If there was a round where .99 became 1.00
                    if(afterPeriod == "100"){   
                        afterPeriod = "00";
                        compare = stoi(beforePeriod);
                        compare++;
                        beforePeriod = to_string(compare);
                    }
                    str = beforePeriod + "." + afterPeriod;
                }else if(afterPeriod.length() == 1){
                    str.append("0");
                }else if(afterPeriod.length() == 0){
                    str.append("00");
                }
                rv = true;
            }else{
                rv = false;
            }
        }   
    }
    
    return rv;
}

bool IsValidHR(string resp){
    bool isValid = false;
    int respInt;

    if(ContainsOnlyNumbers(resp)){
        respInt = atoi(resp.c_str());

        if(respInt >= 100 and respInt < 200){
            isValid = true;
        }
    }

    return isValid;
}