#include <iostream>
#include <string>
#include <vector>
#include <ctime>        //for getting current month/day
#include <stdlib.h>     //for atoi function
#include <iomanip>      //for setprecision

#include "userT.h"
#include "userListT.h"
#include "EventT.h"

using namespace std;

int numEvents = 0;

void LoginUser();
bool Search(string name);
void OutputChoices();
int GetUserSelection();
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
    cin >> userChoice;
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

    cin >> trainingChoice;
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
    ofstream outFile;
    outFile.open("dummyRepo.txt");


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
    while(!ContainsOnlyNumbers(userDuration) or userDuration.length() == 0 or userDuration == "0"){
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

    //For testing purposes, output created event to dummyRepo file.
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

    TrainingMenu();

}

void RunData() {
    string heartRate;
    string distance;
    string notes;
    string speed;
    string date;
    string duration;

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

    cout << '\t' << '\t'<<'\t'<<"Date of Workout (dd/mm/yy): ";
    cin >> date;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Workout Duration (minutes):  ";
    cin >> duration;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Total Distance (miles): ";
    cin >> distance;
    cout << endl;
    
    cout << '\t' << '\t'<<'\t'<<"Workout Speed (mph): ";
    cin >> speed;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Heart Rate: ";
    cin >> heartRate;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Notes: "; 
    cin >> notes;
    cout << endl;

    TrainingMenu();


}

void BikeData() {
    string heartRate;
    string distance;
    string notes;
    string speed;
    string date;
    string duration;

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

    cout << '\t' << '\t'<<'\t'<<"Enter swim training data: " << endl;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Date of Workout (dd/mm/yy): ";
    cin >> date;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Workout Duration (minutes):  ";
    cin >> duration;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Total Distance (miles): ";
    cin >> distance;
    cout << endl;
    
    cout << '\t' << '\t'<<'\t'<<"Workout Speed (mph): ";
    cin >> speed;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Heart Rate: ";
    cin >> heartRate;
    cout << endl;

    cout << '\t' << '\t'<<'\t'<<"Notes: "; 
    cin >> notes;
    cout << endl;

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
   

    cin >> dataAnalysisChoice;
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
        cin >> dataAnalysisChoice;
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
    cout << "-----------------------------------------------------------------------------" << endl;

    cout << '\t' << "Mean:" << endl;


    DataAnalysis();
}


void GetMax() {
    cout << "-----------------------------------------------------------------------------" << endl;

    cout << '\t' << "Max:" << endl;
    

    DataAnalysis();
}

void GetOverall() {
    cout << "-----------------------------------------------------------------------------" << endl;

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
            str.append(".00");
            rv = true;
        }
    }else{
        beforePeriod = str.substr(0, decimalPos);
        afterPeriod = str.substr(decimalPos+1);

        if(!ContainsOnlyNumbers(beforePeriod) or !ContainsOnlyNumbers(afterPeriod)){
            rv = false;
        }else{
            compare = atoi(beforePeriod.c_str());
            if(compare <= 10){                      //checking distance for reasonableness, if not return false
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