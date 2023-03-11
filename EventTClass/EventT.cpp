#include <iostream>
#include <string>

#include "EventT.h"

using namespace std;

EventT::EventT(EventTypeT t, int i){
    distance = 0.0;
    heartRate = 0;
    type = t;
    id = i;
    notes = "N/A";
    day = 0;
    month = 0;
    trainingWeek = 0;
    time = 0;
    speed = 0.0;
}

float EventT::GetDistance(void){
    return distance;
}

int EventT::GetHeartRate(void){
    return heartRate;
}

int EventT::GetId(void){
    return id;
}

string EventT::GetType(void){
    string rv;
    if(type == S){
        rv = "Swim";
    }else if(type == B){
        rv = "Bike";
    }else if(type == R){
        rv = "Run";
    }else{
        rv = "NONE";
    }

    return rv;
}

string EventT::GetNotes(void){
    return notes;
}

int EventT::GetDay(void){
    return day;
}

int EventT::GetMonth(void){
    return month;
}

int EventT::GetTrainingWeek(void){
    return trainingWeek;
}

int EventT::GetTime(void){
    return time;
}

float EventT::GetSpeed(void){
    return speed;
}

/*********************************************************************/

void EventT::SetDistance(float d){
    distance = d;
}

void EventT::SetHeartRate(int hr){
    heartRate = hr;
}

void EventT::SetNotes(string note){
    notes = note;
}

void EventT::SetType(EventTypeT t){
    type = t;
}

void EventT::SetDay(int d){
    day = d;
}

void EventT::SetMonth(int m){
    month = m;
}

void EventT::SetTrainingWeek(int tw){
    trainingWeek = tw;
}

void EventT::SetTime(int t){
    time = t;
}

void EventT::SetSpeed(float s){
    speed = s;
}

void EventT::CalculateSpeed(){
    speed = distance/(float(time)/float(60));
}