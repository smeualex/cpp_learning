#include <iostream>

#include <string>
#include <iostream>
#include <functional>
#include <map>
#include <vector>

#include <chrono>

using std::cout;
using std::endl;
using std::map;
using std::make_pair;


using SteadyClock  = std::chrono::steady_clock;
using HighResClock = std::chrono::high_resolution_clock;
using TimePoint    = std::chrono::time_point<SteadyClock>;

void performanceMeasurement() {
    std::vector<int> bigVector(10000000, 2011);
    std::vector<int> v2;

    auto begin = std::chrono::high_resolution_clock::now();
    v2 = bigVector;
    auto end = std::chrono::high_resolution_clock::now();

    auto timeInSeconds = std::chrono::duration<double>(end - begin).count();
    std::cout << "  > time to copy big vector - " << bigVector.size() << " elements: " << timeInSeconds << endl;
}

// our main stuff go here :)
void do_stuff() {
    performanceMeasurement();
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}