#include "headers.h"
#include "PerformanceMonitor.h"


void testPerfMonitorClass() {
    cout << endl << "-----------------------------------------------------------------------" << endl;
    cout << " Basic test of perf monitor" << endl;
    std::vector<int> bigVector(10000000, 2011);
    std::vector<int> v2;


    PerfMonitor pm;

    pm.Start();
    v2 = bigVector;
    pm.End();

    std::cout << "  > time to copy big vector milliseconds - " 
              << bigVector.size() << " elements: " 
              << pm.Duration() << endl;

    std::cout << "  > time to copy big vector microseconds - " 
              << bigVector.size() << " elements: " 
              << pm.Duration<std::micro>() << endl;

    std::cout << "  > time to copy big vector nanoseconds - " 
              << bigVector.size() << " elements: " 
              << pm.Duration<std::nano>() << endl;
}


// our main stuff go here :)
void do_stuff() {
    testPerfMonitorClass();
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}