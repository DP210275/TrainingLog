#ifndef EVENT_HEADER
#define EVENT_HEADER

#include <string>
//#include <ctime>

enum EventTypeT{
    S,
    R,
    B,
    N
};

class EventT{
    public:
        EventT(EventTypeT t, int i);
        ~EventT() = default;

        float GetDistance(void);
        int GetHeartRate(void);
        int GetId(void);
        std::string GetType(void);
        std::string GetNotes(void);
        int GetDay(void);
        int GetMonth(void);
        int GetTrainingWeek(void);
        int GetTime(void);
        float GetSpeed(void);

        void SetType(EventTypeT t);
        void SetDistance(float d);
        void SetHeartRate(int hr);
        void SetNotes(std::string note);
        void SetDay(int d);
        void SetMonth(int m);
        void SetTrainingWeek(int tw);
        void SetTime(int t);
        void SetSpeed(float s);
        void CalculateSpeed(void);
    
    private:
        float distance;
        int heartRate;
        int id;
        EventTypeT type;
        std::string notes;
        int day;
        int month;
        int trainingWeek;
        float speed;
        int time;
};

#endif