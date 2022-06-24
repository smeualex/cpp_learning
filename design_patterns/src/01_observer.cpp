#include<iostream>
#include<vector>

class Subject;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void Update(Subject&) = 0;
};

class Subject {
private:
    std::vector<Observer*> observers;

public:
    virtual~Subject() = default;
    
    void Attach(Observer& o) {
        observers.push_back(&o);
    }

    void Detach(Observer& o) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), &o)
        );
    }

    void Notify() {
        for(auto* o: observers) {
            o->Update(*this);
        }
    }
};

////////////////////////////////////////////////////////////////////////

class ClockTimer : public Subject {
private:
    int hour;
    int minute;
    int second;

public:
    void SetTime(int _hour, int _minute, int _second) { 
        hour = _hour;
        minute = _minute;
        second = _second;
    }

    int GetHour() const { return hour; }
    int GetMinute() const { return minute; }
    int GetSecond() const { return second; }
};


class DigitalClock : public Observer {
private:
    ClockTimer& subject;

public:
    explicit DigitalClock(ClockTimer& s) : subject(s) {
        subject.Attach(*this);
    }

    ~DigitalClock() {
        subject.Detach(*this);
    }

    void Update(Subject& newSubject) override {
        if(&newSubject == &subject) {
            Draw();
        }
    }

    void Draw() {
        int hour   = subject.GetHour(); 
        int minute = subject.GetMinute(); 
        int second = subject.GetSecond(); 

        std::cout << "Digital time is " << hour << ":" 
                  << minute << ":" 
                  << second << std::endl; 
    }
};

class AnalogClock : public Observer {
private:
    ClockTimer& subject;

public:
    explicit AnalogClock(ClockTimer& s) : subject(s) {
        subject.Attach(*this);
    }

    ~AnalogClock() { 
        subject.Detach(*this); 
    }

    void Update(Subject& newSubject) override {
        if(&newSubject == &subject) {
            Draw();
        }
    }

    void Draw() {
        int hour   = subject.GetHour(); 
        int minute = subject.GetMinute(); 
        int second = subject.GetSecond(); 

        std::cout << "Analog time is " << hour << ":" 
                  << minute << ":" 
                  << second << std::endl; 
    }
};


int main() {
    ClockTimer timer;

    DigitalClock dc(timer);
    AnalogClock  ac(timer);

    timer.SetTime(14, 41, 15);
}