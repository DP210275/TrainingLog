#include <iostream>
#include <string>
#include <vector>
#include <ctime>                        //for getting current month/day
#include <stdlib.h>                     //for atoi function
#include <iomanip>                      //for setprecision
#include <limits>                       //for numeric_limits in ValidInput()
#include <boost/algorithm/string.hpp>   //for the trim() function in ReadEventsFromFile()
#include <algorithm>                    //for max_element

#include "userT.h"
#include "userListT.h"
#include "EventT.h"

using namespace std;

int numEvents = 0;
vector<EventT> userEvents;
string currentUserRepo;

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
bool FindDay(vector<int>& vec, int key);
bool ContainsOnlyNumbers(const string& str);
bool IsAFloat(string& str);
bool IsValidHR(string resp);
bool FindMatchingTW(int key);
void FillTrainingWeeks(vector<int>& tws);
bool CheckForExit(string input, int control);
void ReadEventsFromFile();
void WriteToFile();

int main() {

    LoginUser();
    OutputChoices();
    GetUserSelection();

    return 0;
}


void LoginUser() {
    ofstream outFile;
    string username;
    string createAccount;
    int newID;
    bool userExists = false;
    bool newAccount = false;

    UserListT list = UserListT();

    newID = list.UserListT::GetSize() + 1;
    //list.UserListT::PrintUsers();

    UserListT();

    cout << "Please enter your username: ";
    cin >> username;
    cin.ignore(100, '\n');

    userExists = Search(username);

    while(!userExists) {
        //ask the user if they would like to create an account (Y/N)
        cout << "That seems to be a new username. Would you like to create an account? (Y/N): ";
        cin >> createAccount;
        cin.ignore(100, '\n');

        while(createAccount[0] != 'Y' and createAccount[0] != 'y' and createAccount[0] != 'N' and createAccount[0] != 'n'){
            cout << endl;
            cout << '\t' << "** Invalid selection. Please try again." << endl;
            cout << endl;

            cout << "Would you like to create an account? (Y/N): ";
            cin >> createAccount;
            cin.ignore(100, '\n');
        }
       
        if(createAccount[0] == 'Y' or createAccount[0] == 'y'){
            UserT user(username, newID);
            outFile.open(USER_FILE, std::ios::app);
            outFile << username << "," << newID << endl;
            outFile.close();
            newID++;

            userExists = true;
            newAccount = true;
        }else if(createAccount[0] == 'N' or createAccount[0] == 'n'){
            cout << "Please enter your username: ";
            cin >> username;
            cin.ignore(100, '\n');

            userExists = Search(username);
        }
    }

    currentUserRepo = username + "REPO.txt";
    
    if(userExists and !newAccount){
        ReadEventsFromFile();
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
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t'<< '\t'<< '\t'<< "Welcome to your Triathlon Training Log! " << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<< '\t'<< "Enter 1 for Training Log" << endl;
    cout << endl;
 
    cout << '\t'<< '\t'<< '\t'<< '\t'<< "Enter 2 for Data Analysis" << endl;
    cout << endl;

    cout << '\t'<< '\t'<< '\t'<< '\t'<< "Enter 3 to Check Your Progress" << endl;
    cout << endl;

    cout << '\t'<< '\t'<< '\t'<< '\t'<< "Enter 4 to Exit" << endl;
    cout << endl;

    cout << "--------------------------------------------------------------------------------------" << endl;

}

int GetUserSelection() {
    int userChoice;

    cout << endl;
    cout << '\t'<<'\t'<< '\t' << '\t' << "    Selection: ";
    userChoice = ValidInput();
    cout << endl;

    if (userChoice == 1) {
        TrainingMenu();
    } else if (userChoice == 2) {
        DataAnalysis();
    } else if (userChoice == 3) {
        TrainingMenu();
        //This will be for DAVID to put the Check User Progress
    } else if (userChoice == 4){
        WriteToFile();
        exit(-1);
    } 
    
    while (userChoice <= 0 || userChoice > 4) {
        cout << endl;
        cout << endl;
        cout << '\t'<< '\t'<< '\t'<< "**Invalid selection. Please try again.**" << endl;
        cout << endl;

        cout << '\t'<<'\t'<< '\t' << '\t' << "    Selection: ";
        cin >> userChoice;
        cout << endl;

        if (userChoice == 1) {
            TrainingMenu();
        } else if (userChoice == 2) {
            DataAnalysis();
        } else if (userChoice == 3) {
            TrainingMenu();
            //This will be for DAVID to put the Check User Progress
        } else if (userChoice == 4){
            WriteToFile();
            exit(-1);
        }
    }
    return userChoice;
}

int ValidInput(){
    int x;
    cin >> x;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << endl;
        cout << '\t'<< '\t'<< '\t'<< "**Invalid selection. Please try again.**" << endl;
        cout << endl << endl;
        cout << '\t'<<'\t'<< '\t' << '\t' << "    Selection: ";
        cin >> x;
    }
    return x;
}

void TrainingMenu() {
    int trainingChoice;

    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<'\t'<< "     Training Log" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<< "    Enter 1 to log a swim training" << endl;
    cout << endl;

    cout << '\t'<<'\t'<<'\t'<< "    Enter 2 to log a run training" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<< "    Enter 3 to log a bike training" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<< "    Enter 4 to go back to the Main Menu" << endl;
    cout << endl;
    cout << '\t'<<'\t'<< '\t' << '\t' << "    Selection: ";



    trainingChoice = ValidInput();
    cout << endl << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    //cout << endl;

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
        cout << endl;
        cout << endl;
        cout << '\t'<< '\t'<< '\t'<< "**Invalid selection. Please try again.**" << endl;
        cout << endl;

        cout << '\t'<<'\t'<< '\t' << '\t' << "    Selection: ";
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
    string checkNotesForExit;
    string confirmExit;
    int day;
    int month;
    int trainingWeek;
    int duration;
    float distance;
    int heartRate;
    bool wantToExit = false;
    vector<int> validDays;


    cout << R"(
                                            _                                  
                                           (_)                         
                               _____      ___ _ __ ___  
                              / __\ \ /\ / / | '_ ` _ \
                              \__ \\ V  V /| | | | | | |
                              |___/ \_/\_/ |_|_| |_| |_|
                                  
        )" << '\n';

    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"       Enter swim training data: " << endl;
    cout << endl;

    cout << '\t' << '\t'<<"   Enter \"Exit\" at any time to exit the logging process." << endl;
    cout << endl;

    /********** Date **********/
    cout << '\t' << '\t'<<'\t'<<"       Use Current Date (Y/N): ";
    cin >> useCurrentDate;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(useCurrentDate, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(useCurrentDate[0] != 'Y' and useCurrentDate[0] != 'y' and useCurrentDate[0] != 'N' and useCurrentDate[0] != 'n'){
        cout << endl;
        cout << endl;
        if(useCurrentDate != "exit"){
            cout << '\t'<< '\t'<< '\t'<< "** Invalid selection. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<< "       Use Current Date (Y/N): ";
        cin >> useCurrentDate;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(useCurrentDate, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }
    
    if(useCurrentDate[0] == 'Y' or useCurrentDate[0] == 'y'){
        month = GetLocalMonthOrDay(1);
        day = GetLocalMonthOrDay(2);
        cout << endl;
    }else{
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"       Month of Workout (1-12): ";
        cin >> userMonth;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userMonth, 1);
        if(wantToExit){
            TrainingMenu();
        }
        //Validate userMonth
        while(userMonth != "1" and userMonth != "2" and userMonth != "3" and userMonth != "4" and userMonth != "5" and userMonth != "6" and
        userMonth != "7" and userMonth != "8" and userMonth != "9" and userMonth != "10" and userMonth != "11" and userMonth != "12"){
            cout << endl;
            cout << endl;
            if(userMonth != "exit"){
                cout << '\t'<< '\t' << '\t' << "** Invalid month. Please try again. **" << endl;
                cout << endl;
            }
            cout << '\t' << '\t'<<'\t'<<"       Month of Workout (1-12): ";
            cin>> userMonth;
            cin.ignore(100, '\n');

            wantToExit = CheckForExit(userMonth, 1);
            if(wantToExit){
                TrainingMenu();
            }
        }
        cout << endl;
        month = atoi(userMonth.c_str());

        //Set the days of the entered month for validating userDay
        SetMonthDays(validDays, month);

        cout << '\t' << '\t'<<'\t'<<"       Day of Workout: ";
        cin >> userDay;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userDay, 1);
        if(wantToExit){
            TrainingMenu();
        }

        //Validate userDay
        while(!DayIsValid(validDays, userDay)){
            cout << endl;
            cout << endl;
            if(userDay != "exit"){
                cout << '\t'<< '\t' << '\t' << "** Invalid day. Please try again. **" << endl;
                cout << endl;
            }
            cout << '\t' << '\t'<<'\t'<<"       Day of Workout: ";
            cin>> userDay;
            cin.ignore(100,'\n');

            wantToExit = CheckForExit(userDay, 1);
            if(wantToExit){
                TrainingMenu();
            }
        }
        cout << endl;
        day = atoi(userDay.c_str());
    }

    /********** Training Week Number **********/
    cout << '\t' << '\t'<<'\t'<<"       Training Week Number:  ";
    cin >> userTrainingWeek;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(userTrainingWeek, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(!ContainsOnlyNumbers(userTrainingWeek) or userTrainingWeek == "0" or userTrainingWeek.length() == 0){
        cout << endl;
        cout << endl;
        if(userTrainingWeek != "exit"){
            cout << '\t'<< '\t'<< '\t' << "** Invalid number. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<<"       Training Week Number:  ";
        cin >> userTrainingWeek;
        cin.ignore(100, '\n');
        
        wantToExit = CheckForExit(userTrainingWeek, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }
    cout << endl;
    trainingWeek = atoi(userTrainingWeek.c_str());

    /********** Duration **********/
    cout << '\t' << '\t'<<'\t'<<"       Workout Duration (minutes):  ";
    cin >> userDuration;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(userDuration, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(!ContainsOnlyNumbers(userDuration) or userDuration.length() == 0 or (atoi(userDuration.c_str())) == 0){
        cout << endl;
        cout << endl;
        if(userDuration != "exit"){
            cout << '\t'<< '\t'<< '\t' << "** Invalid duration. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<<"       Workout Duration (minutes):  ";
        cin >> userDuration;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userDuration, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }
    cout << endl;
    duration = atoi(userDuration.c_str());

    /********** Distance **********/
    cout << '\t' << '\t'<<'\t'<<"       Total Distance (miles): ";
    cin >> userDistance;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(userDistance, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(userDistance.length() == 0 or !IsAFloat(userDistance)){
        cout << endl;
        cout << endl;
        if(userDistance != "exit"){
            cout << '\t'<< '\t'<< '\t' << "** Invalid distance. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<<"       Total Distance (miles):  ";
        cin >> userDistance;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userDistance, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }
    cout << endl;
    distance = stof(userDistance);

    /********** Heart Rate **********/
    cout << '\t' << '\t'<<'\t'<<"       Heart Rate: ";
    cin >> userHeartRate;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(userHeartRate, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(!IsValidHR(userHeartRate)){
        cout << endl;
        cout << endl;
        if(userHeartRate!= "exit"){
            cout << '\t'<< '\t'<<'\t' << "** Invalid heart rate. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<<"       Heart Rate:  ";
        cin >> userHeartRate;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userHeartRate, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }
    cout << endl;
    heartRate = atoi(userHeartRate.c_str());

    /********** Notes ***********/
    cout << '\t' << '\t'<<'\t'<<"       Notes: "; 
    getline(cin, notes);

    checkNotesForExit = notes.substr(0, 4);
    wantToExit = CheckForExit(checkNotesForExit, 1);
    if(wantToExit){
        TrainingMenu();
    }
    while(checkNotesForExit == "exit"){
        cout << '\t' << '\t'<<'\t'<<"       Notes: "; 
        getline(cin, notes);

        checkNotesForExit = notes.substr(0, 4);
        wantToExit = CheckForExit(checkNotesForExit, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }
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
    string checkNotesForExit;
    int day;
    int month;
    int trainingWeek;
    int duration;
    float distance;
    int heartRate;
    bool wantToExit = false;
    vector<int> validDays;


    cout << R"(

                                  _ __ _   _ _ __  
                                 | '__| | | | '_ \
                                 | |  | |_| | | | |
                                 |_|   \__,_|_| |_|
                                  
        )" << '\n';

    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"       Enter run training data: " << endl;
    cout << endl;

    cout << '\t' << '\t'<<"   Enter \"Exit\" at any time to exit the logging process." << endl;
    cout << endl;

    /********** Date **********/
    cout << '\t' << '\t'<<'\t'<< "       Use Current Date (Y/N): ";
    cin >> useCurrentDate;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(useCurrentDate, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(useCurrentDate[0] != 'Y' and useCurrentDate[0] != 'y' and useCurrentDate[0] != 'N' and useCurrentDate[0] != 'n'){
        cout << endl;
        cout << endl;
        if(useCurrentDate != "exit"){
            cout << '\t'<< '\t'<< '\t'<< "** Invalid selection. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<< "       Use Current Date (Y/N): ";
        cin >> useCurrentDate;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(useCurrentDate, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }

    if(useCurrentDate[0] == 'Y' or useCurrentDate[0] == 'y'){
        month = GetLocalMonthOrDay(1);
        day = GetLocalMonthOrDay(2);
        cout << endl;
    }else{
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"      Month of Workout (1-12): ";
        cin >> userMonth;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userMonth, 1);
        if(wantToExit){
            TrainingMenu();
        }

        //Validate userMonth
        while(userMonth != "1" and userMonth != "2" and userMonth != "3" and userMonth != "4" and userMonth != "5" and userMonth != "6" and
        userMonth != "7" and userMonth != "8" and userMonth != "9" and userMonth != "10" and userMonth != "11" and userMonth != "12"){
            cout << endl;
            cout << endl;
            if(userMonth != "exit"){
                cout << '\t'<< '\t' << '\t' << "** Invalid month. Please try again. **" << endl;
                cout << endl;
            }
            cout << '\t' << '\t'<<'\t'<<"       Month of Workout (1-12): ";
            cin>> userMonth;
            cin.ignore(100, '\n');

            wantToExit = CheckForExit(userMonth, 1);
            if(wantToExit){
                TrainingMenu();
            }
        }
        cout << endl;
        month = atoi(userMonth.c_str());

        //Set the days of the entered month for validating userDay
        SetMonthDays(validDays, month);

        cout << '\t' << '\t'<<'\t'<<"       Day of Workout: ";
        cin >> userDay;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userDay, 1);
        if(wantToExit){
            TrainingMenu();
        }

        //Validate userDay
        while(!DayIsValid(validDays, userDay)){
            cout << endl;
            cout << endl;
            if(userDay != "exit"){
                cout << '\t'<< '\t' << '\t' << "** Invalid day. Please try again. **" << endl;
                cout << endl;
            }
            cout << '\t' << '\t'<<'\t'<<"       Day of Workout: ";
            cin>> userDay;
            cin.ignore(100,'\n');

            wantToExit = CheckForExit(userDay, 1);
            if(wantToExit){
                TrainingMenu();
            }
        }
        cout << endl;
        day = atoi(userDay.c_str());
    }

    /********** Training Week Number **********/
    cout << '\t' << '\t'<<'\t'<<"       Training Week Number:  ";
    cin >> userTrainingWeek;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(userTrainingWeek, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(!ContainsOnlyNumbers(userTrainingWeek) or userTrainingWeek == "0" or userTrainingWeek.length() == 0){
        cout << endl;
        cout << endl;
        if(userTrainingWeek != "exit"){
            cout << '\t'<< '\t'<< '\t' << "** Invalid number. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<<"       Training Week Number:  ";
        cin >> userTrainingWeek;
        cin.ignore(100, '\n');
        
        wantToExit = CheckForExit(userTrainingWeek, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }
    cout << endl;
    trainingWeek = atoi(userTrainingWeek.c_str());

    /********** Duration **********/
    cout << '\t' << '\t'<<'\t'<<"       Workout Duration (minutes):  ";
    cin >> userDuration;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(userDuration, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(!ContainsOnlyNumbers(userDuration) or userDuration.length() == 0 or (atoi(userDuration.c_str())) == 0){
        cout << endl;
        cout << endl;
        if(userDuration != "exit"){
            cout << '\t'<< '\t'<< '\t' << "** Invalid duration. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<<"       Workout Duration (minutes):  ";
        cin >> userDuration;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userDuration, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }
    cout << endl;
    duration = atoi(userDuration.c_str());

    /********** Distance **********/
    cout << '\t' << '\t'<<'\t'<<"       Total Distance (miles): ";
    cin >> userDistance;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(userDistance, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(userDistance.length() == 0 or !IsAFloat(userDistance)){
        cout << endl;
        cout << endl;
        if(userDistance != "exit"){
            cout << '\t'<< '\t'<< '\t' << "** Invalid distance. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<<"       Total Distance (miles):  ";
        cin >> userDistance;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userDistance, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }
    cout << endl;
    distance = stof(userDistance);

    /********** Heart Rate **********/
    cout << '\t' << '\t'<<'\t'<<"       Heart Rate: ";
    cin >> userHeartRate;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(userHeartRate, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(!IsValidHR(userHeartRate)){
        cout << endl;
        cout << endl;
        if(userHeartRate!= "exit"){
            cout << '\t'<< '\t'<<'\t' << "** Invalid heart rate. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<<"       Heart Rate:  ";
        cin >> userHeartRate;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userHeartRate, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }
    cout << endl;
    heartRate = atoi(userHeartRate.c_str());

    /********** Notes ***********/
    cout << '\t' << '\t'<<'\t'<<"       Notes: "; 
    getline(cin, notes);

    checkNotesForExit = notes.substr(0, 4);
    wantToExit = CheckForExit(checkNotesForExit, 1);
    if(wantToExit){
        TrainingMenu();
    }
    while(checkNotesForExit == "exit"){
        cout << '\t' << '\t'<<'\t'<<"       Notes: "; 
        getline(cin, notes);

        checkNotesForExit = notes.substr(0, 4);
        wantToExit = CheckForExit(checkNotesForExit, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }

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
    string checkNotesForExit;
    int day;
    int month;
    int trainingWeek;
    int duration;
    float distance;
    int heartRate;
    bool wantToExit;
    vector<int> validDays;


    cout << R"(
                                  _     _ _        
                                 | |   (_) |       
                                 | |__  _| | _____ 
                                 | '_ \| | |/ / _ \
                                 | |_) | |   <  __/
                                 |_.__/|_|_|\_\___|
        )" << '\n';
    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"       Enter bike training data: " << endl;
    cout << endl;

    cout << '\t' << '\t'<<"   Enter \"Exit\" at any time to exit the logging process." << endl;
    cout << endl;

   /********** Date **********/
    cout << '\t' << '\t'<<'\t'<< "       Use Current Date (Y/N): ";
    cin >> useCurrentDate;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(useCurrentDate, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(useCurrentDate[0] != 'Y' and useCurrentDate[0] != 'y' and useCurrentDate[0] != 'N' and useCurrentDate[0] != 'n'){
        cout << endl;
        cout << endl;
        if(useCurrentDate != "exit"){
            cout << '\t'<< '\t'<< '\t'<< "** Invalid selection. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<< "       Use Current Date (Y/N): ";
        cin >> useCurrentDate;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(useCurrentDate, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }

   if(useCurrentDate[0] == 'Y' or useCurrentDate[0] == 'y'){
        month = GetLocalMonthOrDay(1);
        day = GetLocalMonthOrDay(2);
        cout << endl;
    }else{
        cout << endl;
        cout << '\t' << '\t'<<'\t'<<"      Month of Workout (1-12): ";
        cin >> userMonth;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userMonth, 1);
        if(wantToExit){
            TrainingMenu();
        }

        //Validate userMonth
        while(userMonth != "1" and userMonth != "2" and userMonth != "3" and userMonth != "4" and userMonth != "5" and userMonth != "6" and
        userMonth != "7" and userMonth != "8" and userMonth != "9" and userMonth != "10" and userMonth != "11" and userMonth != "12"){
            cout << endl;
            cout << endl;
            if(userMonth != "exit"){
                cout << '\t'<< '\t' << '\t' << "** Invalid month. Please try again. **" << endl;
                cout << endl;
            }
            cout << '\t' << '\t'<<'\t'<<"       Month of Workout (1-12): ";
            cin>> userMonth;
            cin.ignore(100, '\n');

            wantToExit = CheckForExit(userMonth, 1);
            if(wantToExit){
                TrainingMenu();
            }
        }
        cout << endl;
        month = atoi(userMonth.c_str());

        //Set the days of the entered month for validating userDay
        SetMonthDays(validDays, month);

        cout << '\t' << '\t'<<'\t'<<"       Day of Workout: ";
        cin >> userDay;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userDay, 1);
        if(wantToExit){
            TrainingMenu();
        }

        //Validate userDay
        while(!DayIsValid(validDays, userDay)){
            cout << endl;
            cout << endl;
            if(userDay != "exit"){
                cout << '\t'<< '\t' << '\t' << "** Invalid day. Please try again. **" << endl;
                cout << endl;
            }
            cout << '\t' << '\t'<<'\t'<<"       Day of Workout: ";
            cin>> userDay;
            cin.ignore(100,'\n');

            wantToExit = CheckForExit(userDay, 1);
            if(wantToExit){
                TrainingMenu();
            }
        }
        cout << endl;
        day = atoi(userDay.c_str());
    }

    /********** Training Week Number **********/
    cout << '\t' << '\t'<<'\t'<<"       Training Week Number:  ";
    cin >> userTrainingWeek;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(userTrainingWeek, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(!ContainsOnlyNumbers(userTrainingWeek) or userTrainingWeek == "0" or userTrainingWeek.length() == 0){
        cout << endl;
        cout << endl;
        if(userTrainingWeek != "exit"){
            cout << '\t'<< '\t'<< '\t' << "** Invalid number. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<<"       Training Week Number:  ";
        cin >> userTrainingWeek;
        cin.ignore(100, '\n');
        
        wantToExit = CheckForExit(userTrainingWeek, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }
    cout << endl;
    trainingWeek = atoi(userTrainingWeek.c_str());

    /********** Duration **********/
    cout << '\t' << '\t'<<'\t'<<"       Workout Duration (minutes):  ";
    cin >> userDuration;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(userDuration, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(!ContainsOnlyNumbers(userDuration) or userDuration.length() == 0 or (atoi(userDuration.c_str())) == 0){
        cout << endl;
        cout << endl;
        if(userDuration != "exit"){
            cout << '\t'<< '\t'<< '\t' << "** Invalid duration. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<<"       Workout Duration (minutes):  ";
        cin >> userDuration;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userDuration, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }
    cout << endl;
    duration = atoi(userDuration.c_str());

    /********** Distance **********/
    cout << '\t' << '\t'<<'\t'<<"       Total Distance (miles): ";
    cin >> userDistance;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(userDistance, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(userDistance.length() == 0 or !IsAFloat(userDistance)){
        cout << endl;
        cout << endl;
        if(userDistance != "exit"){
            cout << '\t'<< '\t'<< '\t' << "** Invalid distance. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<<"       Total Distance (miles):  ";
        cin >> userDistance;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userDistance, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }
    cout << endl;
    distance = stof(userDistance);
    
    /********** Heart Rate **********/
    cout << '\t' << '\t'<<'\t'<<"       Heart Rate: ";
    cin >> userHeartRate;
    cin.ignore(100, '\n');

    wantToExit = CheckForExit(userHeartRate, 1);
    if(wantToExit){
        TrainingMenu();
    }

    while(!IsValidHR(userHeartRate)){
        cout << endl;
        cout << endl;
        if(userHeartRate!= "exit"){
            cout << '\t'<< '\t'<<'\t' << "** Invalid heart rate. Please try again. **" << endl;
            cout << endl;
        }
        cout << '\t' << '\t'<<'\t'<<"       Heart Rate:  ";
        cin >> userHeartRate;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userHeartRate, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }
    cout << endl;
    heartRate = atoi(userHeartRate.c_str());

    /********** Notes ***********/
    cout << '\t' << '\t'<<'\t'<<"       Notes: "; 
    getline(cin, notes);

    checkNotesForExit = notes.substr(0, 4);
    wantToExit = CheckForExit(checkNotesForExit, 1);
    if(wantToExit){
        TrainingMenu();
    }
    while(checkNotesForExit == "exit"){
        cout << '\t' << '\t'<<'\t'<<"       Notes: "; 
        getline(cin, notes);

        checkNotesForExit = notes.substr(0, 4);
        wantToExit = CheckForExit(checkNotesForExit, 1);
        if(wantToExit){
            TrainingMenu();
        }
    }

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

    TrainingMenu();

}

void DataAnalysis() {
    int dataAnalysisChoice = 0;

    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<"   What kind of data analysis are you looking for?" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<'\t'<< "Enter 1 to for show mean" << endl;
    cout << endl;

    cout << '\t'<<'\t'<<'\t'<< '\t'<< "Enter 2 to for show max" << endl;
    cout << endl;

    cout << '\t'<< '\t'<<'\t'<<'\t'<< "Enter 3 to go back to the Main Menu" << endl;
    cout << endl;

    cout << '\t' ;
    cout << '\t'<<'\t'<< '\t' << "    Selection: ";
   

    dataAnalysisChoice = ValidInput();
    cout << endl;

    if (dataAnalysisChoice == 1) {
        GetMean();
    } else if (dataAnalysisChoice == 2) {
        GetMax();
    } else if (dataAnalysisChoice == 3){
        OutputChoices();
        GetUserSelection();
    }

    while (dataAnalysisChoice <= 0 || dataAnalysisChoice > 3) {
        cout << endl;
        cout << '\t'<< '\t'<< '\t'<< "** Invalid selection. Please try again. **" << endl;
        cout << endl;

        cout << '\t'<<'\t'<< '\t' <<'\t' << "    Selection: ";
        dataAnalysisChoice = ValidInput();
        cout << endl;
        
        if (dataAnalysisChoice == 1) {
            GetMean();
        } else if (dataAnalysisChoice == 2) {
            GetMax();
        } else if (dataAnalysisChoice == 3){
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
    string enterAnotherTW;
    string getQuickAverage;
    string userTWChoice;
    vector<EventT> matchingTWEvents;
    vector<EventT> matchingTWAndTypeEvents;
    vector<int> trainingWeekChoices;
    vector<int> allUserTWs;
    bool keepGettingTWs = true;
    bool validTW;
    bool wantQuickAverage = false;
    bool wantToExit = false;
    bool isOnlyNumbers;
    float avgHR = 0.0;
    float avgTime = 0.0;
    float avgDist = 0.0;
    float avgSpeed = 0.0;
    float totalDist = 0.0;
    int totalHR = 0;
    int totalTime = 0;
    float totalSpeed = 0.0;
    float amtEvents = 0.0;
    size_t size;


    cout << "--------------------------------------------------------------------------------------" << endl;

    //Check if there are any events for the user. If not, return to Data Analytics menu
    if(userEvents.size() == 0){
        cout << endl;
        cout << '\t' <<  "         Whoops! It looks like there are no events logged yet." << endl; 
        cout << endl;
        cout << '\t'  << "       Please log an event before trying to calculate the mean." << endl;
        cout << endl;
    }else{
        FillTrainingWeeks(allUserTWs);

        cout << '\t' << '\t'<<"   Enter \"Exit\" at any time to exit the analyzing process." << endl;
        cout << endl;

        //Ask user if they want all events for all weeks
        cout << endl;
        cout << '\t' <<"Would you like to get the average of all events for all weeks? (Y/N): ";
        cin >> getQuickAverage;
        cout << endl;
        cout << endl;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(getQuickAverage, 2);
        if(wantToExit){
            DataAnalysis();
        }

        while(getQuickAverage[0] != 'Y' and getQuickAverage[0] != 'y' and getQuickAverage[0] != 'N' and getQuickAverage[0] != 'n'){
            cout << endl;
            if(getQuickAverage != "exit"){
                cout << '\t'<< '\t'<<'\t'<< "** Invalid selection. Please try again. **" << endl;
                cout << endl;
            }
            cout << '\t' << '\t'<<"Get the average of all events for all weeks? (Y/N): ";
            cin >> getQuickAverage;
            cin.ignore(100, '\n'); 

            wantToExit = CheckForExit(getQuickAverage, 2);
            if(wantToExit){
                DataAnalysis();
            }
        }
        
        if(getQuickAverage[0] == 'Y' or getQuickAverage[0] == 'y'){
            //put all events into vector
            wantQuickAverage = true;
            for(size_t r = 0; r < userEvents.size(); r++){
                matchingTWAndTypeEvents.push_back(userEvents[r]);
            }
        }else{
            cout << endl;
            cout << '\t'<< '\t'<<"Please enter the training week number for evaluation." << endl;
            cout << endl;
            cout << '\t'<<'\t'<< '\t' << '\t' << "    Selection: ";
            cin >> userTWChoice;
            cin.ignore(100, '\n');

            wantToExit = CheckForExit(userTWChoice, 2);
            if(wantToExit){
                DataAnalysis();
            }

            isOnlyNumbers = ContainsOnlyNumbers(userTWChoice);

            while(!isOnlyNumbers or !FindMatchingTW(stoi(userTWChoice))){
                cout << endl;
                if(userTWChoice != "exit" and !isOnlyNumbers){
                    cout << '\t'<< '\t'<< '\t'<< "**Invalid selection. Please try again.**" << endl;
                    cout << endl;
                }else if(isOnlyNumbers){
                    cout << '\t' << '\t' << "   Sorry, no logged events have that training week number." << endl;
                    cout << '\t' << '\t' << "   Please try again." << endl;
                    cout << endl;
                }
                cout << endl;
                cout << '\t'<< '\t'<<"Please enter the training week number for evaluation." << endl;
                cout << endl;
                cout << '\t'<<'\t'<< '\t' << '\t' << "    Selection: ";
                cin >> userTWChoice;
                cin.ignore(100, '\n');

                wantToExit = CheckForExit(userTWChoice, 2);
                if(wantToExit){
                    DataAnalysis();
                }
            }
            
            trainingWeekChoice = stoi(userTWChoice);
            cout << endl;

            trainingWeekChoices.push_back(trainingWeekChoice);

            while(keepGettingTWs){
                validTW = false;
                cout << '\t' << '\t' << '\t' <<"Enter another training week? (Y/N): ";
                cin >> enterAnotherTW;
                cin.ignore(100, '\n');

                wantToExit = CheckForExit(enterAnotherTW, 2);
                if(wantToExit){
                    DataAnalysis();
                }

                while(enterAnotherTW[0] != 'Y' and enterAnotherTW[0] != 'y' and enterAnotherTW[0] != 'N' and enterAnotherTW[0] != 'n'){
                    cout << endl;
                    if(enterAnotherTW != "exit"){
                        cout << '\t'<< '\t'<<'\t'<< "** Invalid selection. Please try again. **" << endl;
                        cout << endl;
                    }
                    cout << '\t' << '\t'<< '\t' <<"Enter another training week? (Y/N): ";
                    cin >> enterAnotherTW;
                    cin.ignore(100, '\n'); 

                    wantToExit = CheckForExit(enterAnotherTW, 2);
                    if(wantToExit){
                        DataAnalysis();
                    }
                }   
                cout << endl;

                if(enterAnotherTW[0] == 'Y' or enterAnotherTW[0] == 'y'){
                    if(allUserTWs.size() == 1){
                        cout << endl;
                        cout << '\t' <<'\t' << "   You have only logged events for one week so analyzing week " << trainingWeekChoice << "." << endl << endl;
                        keepGettingTWs = false;
                    }else if(allUserTWs.size() == trainingWeekChoices.size()){
                        cout << endl;
                        cout << '\t' << '\t' << "     There are no more training weeks you can analyze." << endl;
                        cout << endl;
                        keepGettingTWs = false;
                    }else{
                        while(!validTW){
                            cout << endl;
                            cout << '\t'<< '\t'<<"Please enter the training week number for evaluation." << endl;
                            cout << endl;
                            cout << '\t' << '\t' << '\t' << '\t' << "Selection: ";
                            cin >> userTWChoice;
                            cin.ignore(100, '\n');

                            wantToExit = CheckForExit(userTWChoice, 2);
                            if(wantToExit){
                                DataAnalysis();
                            }
                            while(!ContainsOnlyNumbers(userTWChoice)){
                                cout << endl;
                                if(userTWChoice != "exit"){
                                    cout << '\t'<< '\t'<< '\t'<< "**Invalid selection. Please try again.**" << endl;
                                    cout << endl;
                                }
                                cout << endl;
                                cout << '\t'<< '\t'<<"Please enter the training week number for evaluation." << endl;
                                cout << endl;
                                cout << '\t'<<'\t'<< '\t' << '\t' << "    Selection: ";
                                cin >> userTWChoice;
                                cin.ignore(100, '\n');

                                wantToExit = CheckForExit(userTWChoice, 2);
                                if(wantToExit){
                                    DataAnalysis();
                                }
                            }

                            trainingWeekChoice = stoi(userTWChoice);
                            cout << endl;

                            if(!FindMatchingTW(trainingWeekChoice)){
                                cout << endl;
                                cout << '\t' << '\t' << "   Sorry, no logged events have that training week number." << endl;
                                cout << '\t' << '\t' << "   Please try again." << endl;
                                cout << endl;
                            }else if(FindDay(trainingWeekChoices, trainingWeekChoice)){
                                cout << '\t' << '\t' << "   Whoops! You've alrady selected that training week number." << endl;
                                cout << '\t' << '\t' << "   Please try again." << endl;
                                cout << endl;
                            }else{
                                validTW = true;
                            }
                        }
                        trainingWeekChoices.push_back(trainingWeekChoice);
                    }
                }else if(enterAnotherTW[0] == 'N' or enterAnotherTW[0] == 'n'){
                    keepGettingTWs = false;
                }
            }
        
            for(size_t i = 0; i < trainingWeekChoices.size(); i++){
                for(size_t s = 0; s < userEvents.size(); s++){
                    if(userEvents[s].GetTrainingWeek() == trainingWeekChoices[i]){
                        matchingTWEvents.push_back(userEvents[s]);
                    }   
                }   
            }

            //Ask what kind of events the user would like to analyze, and validate user response
            cout << endl;
            cout << '\t' << '\t' << "   Please enter the type of event for evaluation." << endl << endl;
            cout << '\t' << "Enter 'S' for Swim, 'B' for Bike, 'R' for Run, or 'All' for all three." << endl;
            cout << endl;
            cout << '\t' << '\t' << '\t' << '\t' << "Selection: ";
            cin >> userEventType;
            cin.ignore(100,'\n');

            wantToExit = CheckForExit(userEventType, 2);
            if(wantToExit){
                DataAnalysis();
            }
            cout << endl;

            while(userEventType[0] != 'S' and userEventType[0] != 'B' and userEventType[0] != 'R' and userEventType[0] != 'A' and 
                    userEventType[0] != 's' and userEventType[0] != 'b' and userEventType[0] != 'r' and userEventType[0] != 'a'){
                cout << endl;
                if(userEventType != "exit"){
                    cout << '\t'<< '\t'<<'\t'<< "** Invalid selection. Please try again. **" << endl;
                    cout << endl;
                }
                 cout << '\t' << '\t' << "   Please enter the type of event for evaluation." << endl << endl;
                cout << '\t' << "Enter 'S' for Swim, 'B' for Bike, 'R' for Run, or 'All' for all three." << endl;
                cout << endl;
                cout << '\t'<<'\t'<< '\t'<< '\t'<< "Selection: ";
                cin >> userEventType;
                cin.ignore(100, '\n');

                wantToExit = CheckForExit(userEventType, 2);
                if(wantToExit){
                    DataAnalysis();
                }
            }

            logEventType = userEventType[0];
        
            if(logEventType == "S" or logEventType == "s"){
                matchingEventType = "Swim";
            }else if(logEventType == "B" or logEventType == "b"){
                matchingEventType = "Bike";
            }else if(logEventType == "R" or logEventType == "r"){
                matchingEventType = "Run";
            }else if(logEventType == "A" or logEventType == "a"){
                matchingEventType = "All";
            }

            //If the user wants a specific event analyzed, find the events with the matching training week and put them in a separate vector
            if(matchingEventType != "All"){
                for(size_t i = 0; i < matchingTWEvents.size(); i++){
                    if(matchingTWEvents[i].GetType() == matchingEventType){
                        matchingTWAndTypeEvents.push_back(matchingTWEvents[i]);
                    }
                }
            }else{
                //Otherwise just copy the separate vector
                for(size_t j = 0; j < matchingTWEvents.size(); j++){
                    matchingTWAndTypeEvents.push_back(matchingTWEvents[j]);
                }
            }
        }

        //Calculate the totals for heart rate, distance, speed, and time and average them
        for(size_t k = 0; k < matchingTWAndTypeEvents.size(); k++){
            totalHR += matchingTWAndTypeEvents[k].GetHeartRate();
            totalDist += matchingTWAndTypeEvents[k].GetDistance();
            totalSpeed += matchingTWAndTypeEvents[k].GetSpeed();
            totalTime += matchingTWAndTypeEvents[k].GetTime();
        }   

        if(matchingTWAndTypeEvents.size() > 0){
            amtEvents = float(matchingTWAndTypeEvents.size());
            avgHR = float(totalHR)/amtEvents;
            avgDist = totalDist/amtEvents;
            avgSpeed = totalSpeed/amtEvents;
            avgTime = float(totalTime)/amtEvents;

            cout << fixed;
            cout << setprecision(2) << endl;
            if(wantQuickAverage){
                cout << '\t' << '\t' << '\t' << '\t' << "     For All Training Weeks:" << endl << endl;
            }else if(trainingWeekChoices.size() == 1){
                cout << '\t' << '\t' << '\t' << '\t' << "     For Training Week " << trainingWeekChoice << ": " << endl << endl;
            }else{
                size = trainingWeekChoices.size();
                cout << '\t' << '\t' << '\t' << '\t' << "     For Training Weeks ";
                for(size_t t = 0; t < trainingWeekChoices.size()-1; t++){
                    cout << trainingWeekChoices[t] << ", ";
                }
                cout << trainingWeekChoices[size-1] << ": " << endl << endl;
            }
            cout << '\t' << '\t' << '\t' <<  '\t' << "Average Heart Rate: " << avgHR << "bpm" << endl << endl;
            cout << '\t' << '\t' << '\t' << '\t' << "Average Distance: " << avgDist << " miles" <<endl << endl;
            cout << '\t' << '\t'<< '\t' << '\t' << "Average Time: " << avgTime << " minutes" << endl << endl;
            cout << '\t' << '\t'<< '\t' << '\t' << "Average Speed: " << avgSpeed << "mph" << endl << endl;
            cout << endl;
        }else{
            cout << endl;
            cout << '\t' << '\t' << "No " << matchingEventType << " events logged. Please log events for analyzing." << endl;
            cout << endl;
        }
    }
    DataAnalysis();
}



void GetMax() {
    int trainingWeekChoice = 0;
    string userEventType;
    string logEventType = "X";
    string matchingEventType;
    string enterAnotherTW;
    string getQuickMax;
    string userTWChoice;
    vector<EventT> matchingTWEvents;
    vector<EventT> matchingTWAndTypeEvents;
    vector<int> trainingWeekChoices;
    vector<int> allUserTWs;
    bool keepGettingTWs = true;
    bool validTW;
    bool wantQuickMax = false;
    bool wantToExit = false;
    bool isOnlyNumbers;

    cout << "--------------------------------------------------------------------------------------" << endl;

    if(userEvents.size() == 0){
        cout << endl;
        cout << '\t' <<  "         Whoops! It looks like there are no events logged yet." << endl; 
        cout << endl;
        cout << '\t'  << "       Please log an event before trying to calculate the mean." << endl;
        cout << endl;
    }else{
        FillTrainingWeeks(allUserTWs);

        cout << '\t' << '\t'<<"   Enter \"Exit\" at any time to exit the analyzing process." << endl;
        cout << endl;

        wantToExit = CheckForExit(getQuickMax, 2);
        if(wantToExit){
            DataAnalysis();
        }

        for(size_t r = 0; r < userEvents.size(); r++){
            matchingTWAndTypeEvents.push_back(userEvents[r]);
        }
        
        cout << endl;
        cout << '\t'<< '\t'<<"Please enter the training week number for evaluation." << endl;
        cout << endl;
        cout << '\t'<<'\t'<< '\t' << '\t' << "    Selection: ";
        cin >> userTWChoice;
        cin.ignore(100, '\n');

        wantToExit = CheckForExit(userTWChoice, 2);
        if(wantToExit){
            DataAnalysis();
        }

        isOnlyNumbers = ContainsOnlyNumbers(userTWChoice);

        while(!isOnlyNumbers or !FindMatchingTW(stoi(userTWChoice))){
            cout << endl;
            if(userTWChoice != "exit" and !isOnlyNumbers){
                cout << '\t'<< '\t'<< '\t'<< "**Invalid selection. Please try again.**" << endl;
                cout << endl;
            }else if(isOnlyNumbers){
                cout << '\t' << '\t' << "   Sorry, no logged events have that training week number." << endl;
                cout << '\t' << '\t' << "   Please try again." << endl;
                cout << endl;
            }
            cout << endl;
            cout << '\t'<< '\t'<<"Please enter the training week number for evaluation." << endl;
            cout << endl;
            cout << '\t'<<'\t'<< '\t' << '\t' << "    Selection: ";
            cin >> userTWChoice;
            cin.ignore(100, '\n');

            wantToExit = CheckForExit(userTWChoice, 2);
            if(wantToExit){
                DataAnalysis();
            }
        }
        
        trainingWeekChoice = stoi(userTWChoice);
        cout << endl;

        trainingWeekChoices.push_back(trainingWeekChoice);

        while(keepGettingTWs){
            validTW = false;
            cout << '\t' << '\t' << '\t' <<"Enter another training week? (Y/N): ";
            cin >> enterAnotherTW;
            cin.ignore(100, '\n');

            wantToExit = CheckForExit(enterAnotherTW, 2);
            if(wantToExit){
                DataAnalysis();
            }

            while(enterAnotherTW[0] != 'Y' and enterAnotherTW[0] != 'y' and enterAnotherTW[0] != 'N' and enterAnotherTW[0] != 'n'){
                cout << endl;
                if(enterAnotherTW != "exit"){
                    cout << '\t'<< '\t'<<'\t'<< "** Invalid selection. Please try again. **" << endl;
                    cout << endl;
                }
                cout << '\t' << '\t'<< '\t' <<"Enter another training week? (Y/N): ";
                cin >> enterAnotherTW;
                cin.ignore(100, '\n'); 

                wantToExit = CheckForExit(enterAnotherTW, 2);
                if(wantToExit){
                    DataAnalysis();
                }
            }   
            cout << endl;

            if(enterAnotherTW[0] == 'Y' or enterAnotherTW[0] == 'y'){
                if(allUserTWs.size() == 1){
                    cout << endl;
                    cout << '\t' << "      You have only logged events for one week so analyzing week " << trainingWeekChoice << "." << endl << endl;
                    keepGettingTWs = false;
                }else if(allUserTWs.size() == trainingWeekChoices.size()){
                    cout << endl;
                    cout << '\t' << '\t' << "     There are no more training weeks you can analyze." << endl;
                    cout << endl;
                    keepGettingTWs = false;
                }else{
                    while(!validTW){
                        cout << endl;
                        cout << '\t'<< '\t'<<"Please enter the training week number for evaluation." << endl;
                        cout << endl;
                        cout << '\t' << '\t' << '\t' << '\t' << "Selection: ";
                        cin >> userTWChoice;
                        cin.ignore(100, '\n');

                        wantToExit = CheckForExit(userTWChoice, 2);
                        if(wantToExit){
                            DataAnalysis();
                        }
                        while(!ContainsOnlyNumbers(userTWChoice)){
                            cout << endl;
                            if(userTWChoice != "exit"){
                                cout << '\t'<< '\t'<< '\t'<< "**Invalid selection. Please try again.**" << endl;
                                cout << endl;
                            }
                            cout << endl;
                            cout << '\t'<< '\t'<<"Please enter the training week number for evaluation." << endl;
                            cout << endl;
                            cout << '\t'<<'\t'<< '\t' << '\t' << "    Selection: ";
                            cin >> userTWChoice;
                            cin.ignore(100, '\n');

                            wantToExit = CheckForExit(userTWChoice, 2);
                            if(wantToExit){
                                DataAnalysis();
                            }
                        }

                        trainingWeekChoice = stoi(userTWChoice);
                        cout << endl;

                        if(!FindMatchingTW(trainingWeekChoice)){
                            cout << endl;
                            cout << '\t' << '\t' << "   Sorry, no logged events have that training week number." << endl;
                            cout << '\t' << '\t' << "   Please try again." << endl;
                            cout << endl;
                        }else if(FindDay(trainingWeekChoices, trainingWeekChoice)){
                            cout << '\t' << '\t' << "   Whoops! You've alrady selected that training week number." << endl;
                            cout << '\t' << '\t' << "   Please try again." << endl;
                            cout << endl;
                        }else{
                            validTW = true;
                        }
                    }
                    trainingWeekChoices.push_back(trainingWeekChoice);
                }
            }else if(enterAnotherTW[0] == 'N' or enterAnotherTW[0] == 'n'){
                keepGettingTWs = false;
            }
        }
    
        for(size_t i = 0; i < trainingWeekChoices.size(); i++){
            for(size_t s = 0; s < userEvents.size(); s++){
                if(userEvents[s].GetTrainingWeek() == trainingWeekChoices[i]){
                    matchingTWEvents.push_back(userEvents[s]);
                }   
            }   
        }

        //Ask what kind of events the user would like to analyze, and validate user response
        cout << endl;
        cout << '\t' << '\t' << "   Please enter the type of event for evaluation." << endl << endl;
        cout << '\t' << "Enter 'S' for Swim, 'B' for Bike, 'R' for Run, or 'All' for all three." << endl;
        cout << endl;
        cout << '\t'<<'\t'<< '\t' << '\t' << "    Selection: ";
        cin >> userEventType;
        cin.ignore(100,'\n');

        wantToExit = CheckForExit(userEventType, 2);
        if(wantToExit){
            DataAnalysis();
        }
        cout << endl;

        while(userEventType[0] != 'S' and userEventType[0] != 'B' and userEventType[0] != 'R' and userEventType[0] != 'A' and 
                userEventType[0] != 's' and userEventType[0] != 'b' and userEventType[0] != 'r' and userEventType[0] != 'a'){
            cout << endl;
            if(userEventType != "exit"){
                cout << '\t'<< '\t'<<'\t'<< "** Invalid selection. Please try again. **" << endl;
                cout << endl;
            }
                cout << '\t' << '\t' << "   Please enter the type of event for evaluation." << endl << endl;
            cout << '\t' << "Enter 'S' for Swim, 'B' for Bike, 'R' for Run, or 'All' for all three." << endl;
            cout << endl;
            cout << '\t'<<'\t'<< '\t' << '\t' << "    Selection: ";
            cin >> userEventType;
            cin.ignore(100, '\n');

            wantToExit = CheckForExit(userEventType, 2);
            if(wantToExit){
                DataAnalysis();
            }
        }

        logEventType = userEventType[0];
    
        if(logEventType == "S" or logEventType == "s"){
            matchingEventType = "Swim";
        }else if(logEventType == "B" or logEventType == "b"){
            matchingEventType = "Bike";
        }else if(logEventType == "R" or logEventType == "r"){
            matchingEventType = "Run";
        }else if(logEventType == "A" or logEventType == "a"){
            matchingEventType = "All";
        }

        //If the user wants a specific event analyzed, find the events with the matching training week and put them in a separate vector
        if(matchingEventType != "All"){
            for(size_t i = 0; i < matchingTWEvents.size(); i++){
                if(matchingTWEvents[i].GetType() == matchingEventType){
                    matchingTWAndTypeEvents.push_back(matchingTWEvents[i]);
                }
            }
        }else{
            //Otherwise just copy the separate vector
            for(size_t j = 0; j < matchingTWEvents.size(); j++){
                matchingTWAndTypeEvents.push_back(matchingTWEvents[j]);
            }
        }

        //Get the max elements
        float maxDist = 0;
        for(size_t j = 0; j < matchingTWAndTypeEvents.size(); j++){
            if(matchingTWAndTypeEvents[j].GetDistance() > maxDist){
                maxDist = matchingTWAndTypeEvents[j].GetDistance();
            }
        }
        float maxSpeed = 0;
        for(size_t k = 0; k < matchingTWAndTypeEvents.size(); k++){
            if(matchingTWAndTypeEvents[k].GetSpeed() > maxSpeed){
                maxSpeed = matchingTWAndTypeEvents[k].GetSpeed();
            }
        }
    
        if (matchingTWAndTypeEvents.size() > 0){
            size_t sizeMax = 0;

            cout << fixed;
            cout << setprecision(2) << endl;
            if(wantQuickMax){
                cout << '\t' << '\t' << '\t' << '\t' << "     For All Training Weeks:" << endl << endl;
            }else if(trainingWeekChoices.size() == 1){
                cout << '\t' << '\t' << '\t' << '\t' << " For Training Week " << trainingWeekChoice << ": " << endl << endl;
            }else{
                sizeMax = trainingWeekChoices.size();
                cout << '\t' << '\t' << '\t' << '\t' << "     For Training Weeks ";
                for(size_t t = 0; t < trainingWeekChoices.size()-1; t++){
                    cout << trainingWeekChoices[t] << ", ";
                }
                cout << trainingWeekChoices[sizeMax-1] << ": " << endl << endl;
            }
            cout << endl << endl;
            cout << '\t' << '\t' << '\t' << "        Max Distance: " << maxDist << " miles" <<endl << endl;
            cout << '\t' << '\t'<< '\t' << '\t' << "  Max Speed: " << maxSpeed << " mph" << endl << endl;
            cout << endl;
        }else{
            cout << endl;
            cout << '\t' << '\t' << "No " << matchingEventType << " events logged. Please log events for analyzing." << endl;
            cout << endl;   
        }
    }
    DataAnalysis();
}

void GetOverall() {
    cout << "--------------------------------------------------------------------------------------" << endl;

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
            if(!FindDay(days, dayInt)){
                isValid = false;
            }
        }
    }else{
        isValid = false;
    }

    return isValid;
}

bool FindDay(vector<int>& vec, int key){
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
    bool onlyZeros = true;
    string beforePeriod = "0";
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
    }else if(decimalPos == 0){
        afterPeriod = str.substr(decimalPos+1);
        if(!ContainsOnlyNumbers(afterPeriod)){
            rv = false;
        }else{
            //Check for a case like ".00" (invalid)
            for(size_t i = 0; i < afterPeriod.length(); i++){
                if(afterPeriod[i] != '0'){
                    onlyZeros = false;
                }
            }
            if(onlyZeros){
                rv = false;
            }else{
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

                    //If there was a whole number round up (.995 --> 1.00)
                    if(afterPeriod == "100"){   
                        afterPeriod = "00";
                        compare = stoi(beforePeriod);
                        compare++;
                        beforePeriod = to_string(compare);
                    }
                }
                str = beforePeriod + "." + afterPeriod;
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

                    //If there was a whole number round (1.995 --> 2.00)
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

bool FindMatchingTW(int key){
    bool trainingWeekMatches = false;
    for(size_t i = 0; i < userEvents.size(); i++){
        if(userEvents[i].GetTrainingWeek() == key){
            trainingWeekMatches = true;
        }
    }

    return trainingWeekMatches;
}

void FillTrainingWeeks(vector<int>& tws){
    for(size_t i = 0; i < userEvents.size(); i++){
        if(!FindDay(tws, userEvents[i].GetTrainingWeek())){
            tws.push_back(userEvents[i].GetTrainingWeek());
        }
    }
    return;
}

bool CheckForExit(string input, int control){
    bool wantsToExit = false;
    string checkExit;
    string confirmExit;
    string process;

    if(control == 1){
        process = "logging";
    }else{
        process = "analyzing";
    }

    checkExit = input;
    for(size_t i = 0; i < checkExit.length(); i++){
        checkExit[i] = char(tolower(checkExit[i]));
    }
    
    if(checkExit == "exit"){
        cout << endl;
        cout << endl;
        cout << '\t' << '\t' << '\t' << "Are you sure you want to exit " << process << "? (Y/N): ";
        cin >> confirmExit;
        cin.ignore(100, '\n');

        while(confirmExit[0] != 'Y' and confirmExit[0] != 'y' and confirmExit[0] != 'N' and confirmExit[0] != 'n'){
            cout << endl;
            cout << endl;
            cout << '\t'<< '\t'<< '\t'<< "** Invalid selection. Please try again. **" << endl;
            cout << endl;
            cout << '\t' << '\t'<<'\t'<< "Are you sure you want to exit " << process << "? (Y/N): ";
            cin >> confirmExit;
            cin.ignore(100, '\n');
        }

        if(confirmExit[0] == 'Y' or confirmExit[0] == 'y'){
            wantsToExit = true;
        }
    }

    return wantsToExit;
}

void ReadEventsFromFile(){
    ifstream inFile;
    string line;
    string part;
    float dist;
    int hr;
    int mon;
    int d;
    int week;
    int time;
    float speed;

    inFile.open(currentUserRepo.c_str());
    while(getline(inFile, part, ';')){        
        EventT newEvent(N, numEvents);

        for(size_t i = 0; i < 9; i++){
            if(i > 0){
                getline(inFile, part, ';');
                if(i == 8){     // when we get the Notes info from the file, trim the whitespace before and after it
                    boost::trim(part);
                }
            }

            if(i == 0){             //set the event type
                if(part[i] == 'S'){
                    newEvent.SetType(S);
                }else if(part[i] == 'B'){
                    newEvent.SetType(B);
                }else if(part[i] == 'R'){
                    newEvent.SetType(R);
                }
                numEvents++;
            }else if(i == 1){       
                mon = atoi(part.c_str());
                newEvent.SetMonth(mon);
            }else if(i == 2){       
                d = atoi(part.c_str());
                newEvent.SetDay(d);
            }else if(i == 3){       
                week = atoi(part.c_str());
                newEvent.SetTrainingWeek(week);
            }else if(i == 4){       
                time = atoi(part.c_str());
                newEvent.SetTime(time);
            }else if(i == 5){       
                dist = stof(part);
                newEvent.SetDistance(dist);
            }else if(i == 6){       
                speed = stof(part);
                newEvent.SetSpeed(speed);
            }else if(i == 7){
                hr = atoi(part.c_str());
                newEvent.SetHeartRate(hr);
            }else if(i == 8){
                newEvent.SetNotes(part);
            }
        }
        getline(inFile, part, '\n');
        userEvents.push_back(newEvent);
    }
    inFile.close();
}

void WriteToFile(){
    ofstream outFile;

    outFile.open(currentUserRepo.c_str());
    for(size_t i = 0; i < userEvents.size(); i++){
        outFile<< userEvents[i].GetType() << " ; ";
        outFile<< userEvents[i].GetMonth() << " ; ";
        outFile<< userEvents[i].GetDay() << " ; ";
        outFile<< userEvents[i].GetTrainingWeek() << " ; ";
        outFile<< userEvents[i].GetTime() << " ; ";
        outFile<< userEvents[i].GetDistance() << " ; ";
        outFile<< fixed;
        outFile<< setprecision(2) << userEvents[i].GetSpeed() << " ; ";
        outFile<< userEvents[i].GetHeartRate() << " ; ";
        outFile<< userEvents[i].GetNotes() << " ; \n";
    }
    outFile.close();

    return;
}
