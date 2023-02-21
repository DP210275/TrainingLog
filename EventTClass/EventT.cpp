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