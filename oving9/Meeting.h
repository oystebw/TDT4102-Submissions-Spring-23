#pragma once
#include "std_lib_facilities.h"
#include "Person.h"

enum class Campus{Trondheim, Ålesund, Gjøvik, Stavanger};

ostream& operator<<(ostream&, const Campus&);

class Meeting{
    private:
        int day;
        int startTime;
        int endTime;
        Campus location;
        string subject;
        const shared_ptr<Person> leader;
        vector<shared_ptr<Person>> participants;
    public:
        Meeting(int day, int start, int end, Campus location, string subject, shared_ptr<Person> leader);

        int getDay() const {return day;}
        int getStartTime() const {return startTime;}
        int getEndTime() const {return endTime;}
        Campus getLocation() const {return location;}
        string getSubject() const {return subject;}
        shared_ptr<Person> getLeader() const {return leader;}
        vector<string> getParticipants() const;

        void addParticipant(shared_ptr<Person>);

        vector<shared_ptr<Person>> findPotentialCoDriving(Meeting&);
};

ostream& operator<<(ostream&, Meeting&);