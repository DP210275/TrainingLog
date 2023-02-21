#ifndef EVENT_HEADER
#define EVENT_HEADER

#include <string>

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

        void SetType(EventTypeT t);
        void SetDistance(float d);
        void SetHeartRate(int hr);
        void SetNotes(std::string note);
    
    private:
        float distance;
        int heartRate;
        int id;
        EventTypeT type;
        std::string notes;
};

#endif