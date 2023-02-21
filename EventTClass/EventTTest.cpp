#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>   //for the trim() function
#include <regex>        //for checking user input

#include "EventT.h"

using namespace std;

int numEvents = 0;

void AskForEvent(vector<EventT>& events);
void OutputMenu();
void WriteToFile(vector<EventT>& events, ofstream& outFile);
void ReadEventsFromFile(vector<EventT>& events);
void InputEventDataFromUser(EventT& event);
float GetDistanceFromUser();
bool IsAFloat(const string& str);
int GetHeartRateFromUser();
bool ContainsOnlyNumbers(const string& str);
string GetNotesFromUser();

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
        outFile<< events[i].GetNotes() << " ; \n";
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

    inFile.open(file.c_str());
    while(getline(inFile, part, ';')){        
        EventT newEvent(N, numEvents);

        for(size_t i = 0; i < 4; i++){
            if(i > 0){
                getline(inFile, part, ';');
                if(i == 3){     // when we get the Notes info from the file, trim the whitespace before and after it
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

    userDistance = GetDistanceFromUser();
    userHR = GetHeartRateFromUser();
    userNotes = GetNotesFromUser();

    event.SetDistance(userDistance);
    event.SetHeartRate(userHR);
    event.SetNotes(userNotes);

    return;
}

float GetDistanceFromUser(){
    string response;
    float rv;

    cout<< "Please enter the distance in miles, to 2 decimal places --> ";
    getline(cin, response);

    while(!IsAFloat(response)){
        cout<< "Please enter the distance in miles, to 2 decimal places --> ";
        getline(cin, response);
    }

    rv = stof(response);
    
    return rv;
}

bool IsAFloat(const string& str){
    return regex_match(str, regex("[+-]?([0-9]*[.])?[0-9]+"));
}

int GetHeartRateFromUser(){
    string response;
    int rv;

    cout<< "Please enter your average heart rate during the event --> ";
    getline(cin, response);

    while(!ContainsOnlyNumbers(response)){
        cout<< "Please enter your average heart rate during the event --> ";
        getline(cin, response);
    }

    rv = atoi(response.c_str());

    return rv;
}

bool ContainsOnlyNumbers(const string& str){
    return regex_match(str, regex("^[0-9]+$"));
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