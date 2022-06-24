#include<iostream>
#include<vector>
#include<thread>
#include<chrono>
#include<mutex>

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
    virtual~Subject() = default;
    
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

    cout << "Starting timer" << endl;

    int h = 14;
    int m = 41;
    int s = 0;

    std::mutex mtx;

    auto th1 = std::thread([&](){
        cout << "===== > Thread 1 started" << endl << endl;
        while(true) 
        {
            {
                std::lock_guard<std::mutex> lock(mtx);
                timer.SetTime(h, m, s);
                s++;
                if(s >= 15)
                    break;
            }

            std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
        }

        cout << "===== > Thread 1 done" << endl << endl;
    });

    auto th2 = std::thread([&](){
        cout << "===== > Thread 2 started" << endl << endl;
        while(true) 
        {
            {
                std::lock_guard<std::mutex> lock(mtx);
                timer.SetTime(h, m, s);
                s++;
                if(s >= 15)
                    break;
            }
            
            std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
        }
        cout << "===== > Thread 2 done" << endl << endl;
    });

    th1.join();
    th2.join();
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}