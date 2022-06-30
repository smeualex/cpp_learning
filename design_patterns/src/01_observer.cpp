#include<iostream>
#include<vector>
#include<thread>
#include<chrono>


///////////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION
// 
// 1. Objects (DigitalClock or AnalogClock object) use the Subject interfaces 
//    (Attach() or Detach()) either to subscribe (register) as observers or 
//    unsubscribe (remove) themselves from being observers 
//    (subject.Attach(*this); , subject.Detach(*this);.
//
// 2. Each subject can have many observers( vector<Observer*> observers;).
//
// 3. All observers need to implement the Observer interface. 
//    This interface just has one method, Update(), that gets called when 
//    the Subject's state changes (Update(Subject &))
//
// 4. In addition to the Attach() and Detach() methods, the concrete subject 
//    implements a Notify() method that is used to update all the current observers 
//    whenever state changes. 
//    But in this case, all of them are done in the parent class, 
//      Subject (Subject::Attach (Observer&), 
//      void Subject::Detach(Observer&) and 
//      void Subject::Notify() .
//
// 5. The Concrete object may also have methods for setting and getting its state.
//
// 6. Concrete observers can be any class that implements the Observer interface.
//    Each observer subscribe (register) with a concrete subject to receive update 
//    (subject.Attach(*this); ).
//
// 7. The two objects of Observer Pattern are loosely coupled, they can interact
//    but with little knowledge of each other.
//
///////////////////////////////////////////////////////////////////////////////////
using std::cout;
using std::endl;

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
    virtual ~Subject() = default;
    
    void Attach(Observer& o) {
        cout << "  > Attaching observer... " << endl;
        observers.push_back(&o);
    }

    void Detach(Observer& o) {
        cout << "  > Detaching observer... " << endl;
        observers.erase(
            std::remove(observers.begin(), observers.end(), &o)
        );
    }

    void Notify() {
        cout << "  > Notifying observers... " << endl;
        for(auto* o: observers) {
            o->Update(*this);
        }
    }
};

/////////////////////////////////////////////////////////////////////////////////////

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
        // notify all
        Notify();
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

        std::cout << "          Digital time is " << hour << ":" 
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

        std::cout << "          Analog time is " << hour << ":" 
                  << minute << ":" 
                  << second << std::endl; 
    }
};


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void do_stuff() {
    ClockTimer timer;

    DigitalClock dc(timer);
    AnalogClock  ac(timer);

    cout << "Setting time to 14:41:15" << endl;

    int h = 14;
    int m = 41;

    for(int s = 0; s < 11; s ++) {
        timer.SetTime(h, m, s);
        std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    }
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}