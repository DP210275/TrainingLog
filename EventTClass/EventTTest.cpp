#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>   //for the trim() function
#include <cctype>
#include <ctime>
#include <iomanip>

#include "EventT.h"

using namespace std;

//Globals
int numEvents = 0;

//Function Declarations
void AskForEvent(vector<EventT>& events);
void OutputMenu();
void WriteToFile(vector<EventT>& events, ofstream& outFile);
void ReadEventsFromFile(vector<EventT>& events);
void InputEventDataFromUser(EventT& event);
float GetDistanceFromUser();
bool IsAFloat(string& str, int reason);
int GetHeartRateFromUser();
bool ContainsOnlyNumbers(const string& str);
string GetNotesFromUser();
bool UseCurrentDay();
int GetMonthFromUser();
int GetDayFromUser(int mon);
void SetMonthDays(vector<int>& days, int mon);
bool DayIsValid(vector<int>& days, string day);
bool Find(vector<int> vec, int key);
int GetLocalMonthOrDay(int control);
int GetTrainingWeekFromUser();
bool IsValidHR(string resp);
int GetTimeFromUser();
bool IsReasonableTime(string rsp);

int main(){
    vector<EventT> createdEvents;
    ofstream outFile;

    //Make a function that reads in from that output file and creates events, pushing them
    //into the createdEvents vector. Once this is complete, make sure that id's of new 
    //events created in AskForEvent match the total amount of events 
    //(events from file + created events)
    ReadEventsFromFile(createdEvents);
    
    outFile.open("dummyREPO.txt");

    AskForEvent(createdEvents);
    AskForEvent(createdEvents);

    for(size_t i = 0; i<createdEvents.size(); i++){
        cout<< "Event ID: " << createdEvents[i].GetId() << endl;
        cout<< "Event Type: " << createdEvents[i].GetType() << endl;
        cout<< "Event HeartRate: " << createdEvents[i].GetHeartRate() << endl;
        cout<< "Event Distance: " << createdEvents[i].GetDistance() << endl;
        cout<< endl << "------------------------------------" << endl;
    }

    //Make a function that will create an output file and store the contents of the
    //createdEvents vector to the file to persist.
    WriteToFile(createdEvents, outFile);

    outFile.close();

    return 0;
}

void AskForEvent(vector<EventT>& events){
    string userChoice;
    EventTypeT userEventChoice = N;

    OutputMenu();
    getline(cin, userChoice);
    while(userChoice != "1" and userChoice != "2" and userChoice != "3"){
        cout<< "Please select one of the options below." << endl;
        OutputMenu();
        getline(cin, userChoice);
    }

    if(userChoice == "1"){
        userEventChoice = S;
    }else if(userChoice == "2"){
        userEventChoice = B;
    }else if(userChoice == "3"){
        userEventChoice = R;
    }

    EventT newEvent(userEventChoice, numEvents);    
    numEvents++;

    //Make another function here that shows we can input event data from the user and
    //put it into the event object and it saves
    InputEventDataFromUser(newEvent);

    events.push_back(newEvent);
    
    return;
}

void OutputMenu(){
    cout<< "Which event are you logging? Please enter the corresponding number:" << endl;
    cout<< "1 - Swim" << endl;
    cout<< "2 - Bike" << endl;
    cout<< "3 - Run" << endl;
    cout<< "--> ";
}

void WriteToFile(vector<EventT>& events, ofstream& outFile){
    for(size_t i = 0; i<events.size(); i++){
        outFile<< events[i].GetType() << " ; ";
        outFile<< events[i].GetDistance() << " ; ";
        outFile<< events[i].GetHeartRate() << " ; ";
        outFile<< events[i].GetNotes() << " ; ";
        outFile<< events[i].GetMonth() << " ; ";
        outFile<< events[i].GetDay() << " ; ";
        outFile<< events[i].GetTrainingWeek() << " ; ";
        outFile<< events[i].GetTime() << " ; ";
        outFile<< fixed;
        outFile<< setprecision(2) << events[i].GetSpeed() << " ; \n";
    }
    return;
}

void ReadEventsFromFile(vector<EventT>& events){
    ifstream inFile;
    string line;
    string part;
    string file = "dummyREPO.txt";
    float dist;
    int hr;
    int mon;
    int d;
    int week;
    int time;
    float speed;

    inFile.open(file.c_str());
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
                    newEvent.SetType(S);
                }
                numEvents++;
            }else if(i == 1){       //set the distance
                dist = stof(part);
                newEvent.SetDistance(dist);
            }else if(i == 2){       //set the heart rate
                hr = atoi(part.c_str());
                newEvent.SetHeartRate(hr);
            }else if(i == 3){       //set the notes
                newEvent.SetNotes(part);
            }else if(i == 4){       //set the month
                mon = atoi(part.c_str());
                newEvent.SetMonth(mon);
            }else if(i == 5){       //set the day
                d = atoi(part.c_str());
                newEvent.SetDay(d);
            }else if(i == 6){       //set the training week number
                week = atoi(part.c_str());
                newEvent.SetTrainingWeek(week);
            }else if(i == 7){
                time = atoi(part.c_str());
                newEvent.SetTime(time);
            }else if(i == 8){
                speed = stof(part);
                newEvent.SetSpeed(speed);
            }
        }
        getline(inFile, part, '\n');
        events.push_back(newEvent);
    }
    inFile.close();
}

void InputEventDataFromUser(EventT& event){
    float userDistance;
    int userHR;
    string userNotes;
    int eventDay; 
    int eventMonth;
    int eventWeek;
    int userTime;

    //Get all info from user
    if(!UseCurrentDay()){
        eventMonth = GetMonthFromUser();
        eventDay = GetDayFromUser(eventMonth);
    }else{                                          
        eventMonth = GetLocalMonthOrDay(1);         //Use the current month and day automatically
        eventDay = GetLocalMonthOrDay(2);
    }
    eventWeek = GetTrainingWeekFromUser();
    userDistance = GetDistanceFromUser();
    userHR = GetHeartRateFromUser();
    userNotes = GetNotesFromUser();
    userTime = GetTimeFromUser();

    //Set the object data
    event.SetDistance(userDistance);
    event.SetHeartRate(userHR);
    event.SetNotes(userNotes);
    event.SetMonth(eventMonth);
    event.SetDay(eventDay);
    event.SetTrainingWeek(eventWeek);
    event.SetTime(userTime);
    event.CalculateSpeed();

    return;
}

float GetDistanceFromUser(){
    string response;
    float rv;

    cout<< "Please enter the distance in miles, to 2 decimal places --> ";
    getline(cin, response);

    while(response.length() == 0 or !IsAFloat(response, 10)){
        cout<< "Please enter the distance in miles, to 2 decimal places --> ";
        getline(cin, response);
    }

    rv = stof(response);
    
    return rv;
}

/*
    This function will return whether or not a string given by the user is a float. It will modify the string by rounding the number to the nearest hundredth if
    the decimal exceeds 2 places, and will give a true or false if the string is a float or not.
*/
bool IsAFloat(string& str, int reason){
    size_t decimalPos = str.find(".");
    bool rv;
    int compare;
    string beforePeriod;
    string afterPeriod;
    string round;

    if(decimalPos == string::npos){
        if(!ContainsOnlyNumbers(str)){
            rv = false;
        }else{
            compare = stoi(str);
            if(compare <= reason){               //check the distance for reasonableness, if not then returns false
                str.append(".00");
                rv = true;
            }else{          
                rv = false;
            }
        }
    }else{
        beforePeriod = str.substr(0, decimalPos);
        afterPeriod = str.substr(decimalPos+1);

        if(!ContainsOnlyNumbers(beforePeriod) or !ContainsOnlyNumbers(afterPeriod)){
            rv = false;
        }else{
            compare = stoi(beforePeriod);
            if(compare <= 10){                      //checking distance for reasonableness, if not return false
                if(afterPeriod.length() > 2){
                    round = afterPeriod.substr(0, 3);
                    
                    //Case for rounding up
                    if(round[2] == '5' or round[2] == '6' or round[2] == '7' or round[2] == '8' or round[2] == '9'){
                        compare = stoi(round.substr(0,2));
                        compare++;                        
                    }else{
                        compare = stoi(round.substr(0,2));
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

int GetHeartRateFromUser(){
    string response;
    int rv;

    cout<< "Please enter your average heart rate during the event --> ";
    getline(cin, response);

    while(!IsValidHR(response)){
        cout<< "Please enter your average heart rate during the event --> ";
        getline(cin, response);
    }

    rv = atoi(response.c_str());

    return rv;
}

//This function steps through a string and returns true if all characters are numbers.
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

string GetNotesFromUser(){
    string response;

    cin.clear();
    cin.sync();
    cout<< "Please enter any notes you want to record for the event. --> \n";
    getline(cin, response);
    

    if(response.size() == 0){
        response = "N/A";
    }
    
    return response;
}

bool UseCurrentDay(){
    bool rv = false;
    string resp;

    cout<< "Would you like to log this event for the current day? Y/N: ";
    getline(cin, resp);
    while(resp[0] != 'n' and resp[0] != 'N' and resp[0] != 'y' and resp[0] != 'Y'){
        cout<< "Would you like to log this event for the current day? Y/N: ";
        getline(cin, resp);
    }

    if(resp[0] == 'y' or resp[0] == 'Y'){
        rv = true;    
    }

    return rv;
}

int GetMonthFromUser(){
    int rv;
    string response;

    cout<< "Please enter the month (1-12) --> ";
    getline(cin, response);

    //Make sure it is a valid month (Jan-Dec)
    while(response != "1" and response != "2" and response != "3" and response != "4" and response != "5" and response != "6" and
        response != "7" and response != "8" and response != "9" and response != "10" and response != "11" and response != "12"){
            cout<< "Please enter the month (1-12) --> ";
            getline(cin, response);
    }

    rv = atoi(response.c_str());
    
    return rv;
}

int GetDayFromUser(int mon){
    int rv;
    vector<int> validDays;
    string response;

    cout<< "Please enter the day --> ";
    getline(cin, response);

    //Fill a vector with the valid days the month can have (e.g., month 1 will have 31, month 2 will have 28, etc.)
    SetMonthDays(validDays, mon);

    while(!DayIsValid(validDays, response)){
        cout<< "Please enter the day. --> ";
        getline(cin, response);
    }

    rv = atoi(response.c_str());

    return rv;
}

void SetMonthDays(vector<int>& days, int mon){
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

int GetTrainingWeekFromUser(){
    string response;
    int rv;

    cout<< "Please enter the training week number --> ";
    getline(cin, response);

    while(!ContainsOnlyNumbers(response) or response == "0" or response.length() == 0){
        cout<< "Please enter the training week number --> ";
        getline(cin, response);
    }

    rv = atoi(response.c_str());

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

int GetTimeFromUser(){
    string response;
    int rv;

    cout<< "Please enter the time in minutes --> ";
    getline(cin, response);

    while(response.length() == 0 or !ContainsOnlyNumbers(response) or !IsReasonableTime(response)){
        cout<< "Please enter the time in minutes --> ";
        getline(cin, response);
    }

    rv = atoi(response.c_str());
    
    return rv;
}

bool IsReasonableTime(string rsp){
    bool isReasonable = false;
    int t = atoi(rsp.c_str());

    if(t <= 180 and t > 0){
        isReasonable = true;
    }

    return isReasonable;
}