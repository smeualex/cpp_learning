#include "headers.h"

#include <random>
#include <chrono>

using std::chrono::duration;
static const long long mapSize= 20000000;
static const long long accSize= 10000000;

// Memory ~1.8Gb RAM
//  2 maps of 20M elements with random access to 10M
//
// ---------------------------------------------------------
// start
// Creating a map and an unordered map with 20000000 elements.
// time for creating: 9.43728 seconds
// Creating 10000000 random values
// time for creating random values: 0.0007212 seconds
// time for std::map: 8.72928 seconds
// time for std::unordered_map: 1.04724 seconds

// end
// ---------------------------------------------------------

// our main stuff go here :)
void do_stuff() {

    cout << "Creating a map and an unordered map with " << mapSize << " elements." << endl;
    std::map<long long,long long> myMap;
    std::unordered_map<long long,long long> myHash;

    auto start0 = std::chrono::system_clock::now();
    for ( long long i=0; i < mapSize; ++i ){
        myMap[i]=i;
        myHash[i]= i;
    }
    std::chrono::duration<double> dur0= std::chrono::system_clock::now() - start0;
    std::cout << "time for creating: " << dur0.count() << " seconds" << std::endl;

    start0 = std::chrono::system_clock::now();
    cout << "Creating " << accSize << " random values" << endl;
    std::vector<long long> randValues;
    randValues.reserve(accSize);
    dur0= std::chrono::system_clock::now() - start0;
    std::cout << "time for creating random values: " << dur0.count() << " seconds" << std::endl;

    // random values
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<> uniformDist(0,mapSize);
    for ( long long i=0 ; i< accSize ; ++i) 
        randValues.push_back(uniformDist(engine));


    // read 1 million arbitrary values from a std::map
    // with 10 million values from randValues
    auto start = std::chrono::system_clock::now();
    for ( long long i=0; i < accSize; ++i){
        myMap[randValues[i]];
    }
    std::chrono::duration<double> dur= std::chrono::system_clock::now() - start;
    std::cout << "time for std::map: " << dur.count() << " seconds" << std::endl;

    auto start2 = std::chrono::system_clock::now();
    for ( long long i=0; i < accSize; ++i){
        myHash[randValues[i]];
    }
    std::chrono::duration<double> dur2= std::chrono::system_clock::now() - start2;
    std::cout << "time for std::unordered_map: " << dur2.count() << " seconds" << std::endl;

    std::cout << std::endl;

}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}   