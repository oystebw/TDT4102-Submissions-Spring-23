#include "Meeting.h"

ostream& operator<<(ostream& os, const Campus& c){
    switch (c){
        case Campus::Trondheim:
            os << "Trondheim";
            break;
        case Campus::Ålesund:
            os << "Ålesund";
            break;
        case Campus::Gjøvik:
            os << "Gjøvik";
            break;
        case Campus::Stavanger:
            os << "Stavanger";
            break;
        default:
            os << "Invalid input";
    }
    return os;
}

void Meeting::addParticipant(shared_ptr<Person> p){
    participants.push_back(p);
}

Meeting::Meeting(int day, int start, int end, Campus location, string subject, shared_ptr<Person> leader):
day{day}, startTime{start}, endTime{end}, location{location}, subject{subject}, leader{leader}{
    addParticipant(leader);
} 

vector<string> Meeting::getParticipants() const{
    vector<string> names;
    for(auto& person: participants){
        names.push_back(person->getName());
    }
    return names;
}

ostream& operator<<(ostream& os, Meeting& m){
    vector<string> participants = m.getParticipants();
    os << "Subject: " << m.getSubject() << '\n';
    os << "Location: " << m.getLocation() << '\n';
    os << "Start time: " << m.getStartTime() << '\n';
    os << "End time: " << m.getEndTime() << '\n';
    os << "Meeting leader: " << m.getLeader()->getName() << '\n' << '\n';
    os << "Participants: " << '\n';
    int x{1};
    for(auto& person: participants){
        os << to_string(x) << ": " << person << '\n';
        x++;
    }
    return os;
}

vector<shared_ptr<Person>> Meeting::findPotentialCoDriving(Meeting& m){
    vector<shared_ptr<Person>> vec;
    if(this->location != m.location){
        return vec;
    }
    if(this->day != m.day){
        return vec;
    }
    if(abs(this->startTime - m.startTime) > 100){
        return vec;
    }
    if(abs(this->endTime - m.endTime) > 100){
        return vec;
    }
    for(auto& person: m.participants){
        if(person->hasAvailableSeats()){
            vec.push_back(person);
        }
    }
    return vec;
}