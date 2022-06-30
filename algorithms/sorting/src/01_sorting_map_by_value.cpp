#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <set>
#include <random>

#include "PerformanceMonitor.h"

using namespace std;

// Helper method to print a map
//  - no checks or asserts done for simplicity
template <typename Cont>
void print(Cont c) {
    // Print the sorted value
    for (auto& it : c) {
  
        cout << "       " << std::setw(16) << it.first << ": " << it.second << endl;
    }
}


//////////////////////////////////////////////////////////////////////////
// METHOD 1 - vector of pairs
//
// copy all contents from the map to the corresponding 
// vector of pairs and sort the vector of pairs according to second value 
//
  
// Function to sort the map according
// to value in a (key-value) pairs
void sort_vector_pairs(const map<string, int>& M)
{
    // Declare vector of pairs
    vector<pair<string, int> > v;
  
    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : M) {
        v.push_back(it);
    }
  
    // Sort using comparator function
    std::sort(v.begin(), v.end(), 
    [](pair<string, int>& a, pair<string, int>& b) {
        return a.second < b.second;
    });
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// METHOD 2 - set of pairs
//
// insert all the (key-value) pairs from the map into a set of pairs
// that can be constructed using a comparator function that orders 
// the pairs according to the second value.
//

// Comparison function for sorting the set by increasing order of its pair's
// second value
//
// the pair's first value is used on equal seconds
struct set_comparator {
    template <typename T>
  
    // Comparator function
    bool operator()(const T& l, const T& r) const
    {
        if (l.second != r.second) {
            return l.second < r.second;
        }
        return l.first < r.first;
    }
};
  
// Function to sort the map according
// to value in a (key-value) pairs
void sort_set(const map<string, int>& M)
{
  
    // Declare set of pairs and insert pairs according to the comparator
    set<pair<string, int>, set_comparator> S(M.begin(), M.end());
}


//////////////////////////////////////////////////////////////////////////
// METHOD 3 - multimap
//
// Multimap is similar to a map with an addition that multiple elements 
// can have the same keys.
// Rather than each element is unique, the key-value and mapped 
// value pair have to be unique in this case.
//
// The idea is to insert all pairs from the given map into multimap using 
// originals map’s value as a key in the multimap and original maps key value 
// as a value in the multimap.
//
// original map (key, value)  =>  multimap (value, key)

// Function to sort the map according
// to value in a (key-value) pairs
void sort_multimap(const map<string, int>& M)
{
  
    // Declare a multimap
    multimap<int, string> MM;
  
    // Insert every (key-value) pairs from
    // map M to multimap MM as (value-key)
    // pairs
    for (auto& it : M) {
        MM.insert({ it.second, it.first });
    }
}

class RandomNumber {
private:
    int from;
    int to;
    std::random_device                  rand_dev;
    std::mt19937                        generator;
    std::uniform_int_distribution<int>  distr;

public:
    RandomNumber(int _from, int _to) 
        : from(_from), to(_to), generator(rand_dev()), distr(from, to)
    { }

    int get() {
        return distr(generator);
    }
};

// generate a random string
std::string random_string(const int length = 16) {
     std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

     std::random_device rd;
     std::mt19937 generator(rd());

     std::shuffle(str.begin(), str.end(), generator);

     return str.substr(0, length);
}


void generate_random_data(map<string, int>& map, const unsigned int elements) {
    RandomNumber rnd(0, 2 * elements);

    for(unsigned int i = 0; i < elements; i++) {
        map.insert(std::pair<string, int>(random_string(), rnd.get()));
    }
}

void test_sorting(int elements) {
    PerfMonitor pm;

    map<string, int>M;
    pm.Start();
        generate_random_data(M, elements);
    pm.End();
    auto data_generation_time = pm.Duration();

    cout << endl << " > Sorting using a vector of pairs... " << endl;
    pm.Start();
    sort_vector_pairs(M);
    pm.End();
    auto sort_vector_pairs_time = pm.Duration();

    cout << endl << " > Sorting using a set... " << endl;
    pm.Start();
    sort_set(M);
    pm.End();
    auto sort_set_time = pm.Duration();

    cout << endl << " > Sorting using a multimap... " << endl;
    pm.Start();
    sort_multimap(M);
    pm.End();
    auto sort_multimap_time = pm.Duration();

    cout << endl;
    cout << "> Time statistics for " << elements << " elements: " << endl;
    cout << "       data generation   : " << data_generation_time   << endl;
    cout << "       sort with vector  : " << sort_vector_pairs_time << endl;
    cout << "       sort with set     : " << sort_set_time          << endl;
    cout << "       sort with multimap: " << sort_multimap_time     << endl;
    cout << endl;
}
// Driver Code
int main(int argc, char* argv[])
{
    cout << " ------------------------------------------------- " << endl;
    cout << " > START" << endl;

    //dumb but works for quick tests
    test_sorting(std::stoi(argv[1]));

    cout << " > END" << endl;
    cout << " ------------------------------------------------- " << endl;
    return 0;
}
/*
    > vector sort seems ok
--------+----------------------------------------------
        |       Time - in milliseconds
--------+----------------------------------------------
elements| generation | vector    | set     | multimap  
--------+------------+-----------+---------+-----------
3       | 1.0133     | 0.0028    | 0.0019  | 0.0020
30      | 1.5699     | 0.0134    | 0.0094  | 0.0083
300     | 1.9601     | 0.1036    | 0.0929  | 0.1268
3000    | 9.8260     | 0.7575    | 1.5565  | 0.9361
30000   | 92.4589    | 6.7395    | 19.0044 | 17.7342
300000  | 926.426    | 113.246   | 230.786 | 241.709
3000000 | 10936.8    | 1317.59   | 3765.51 | 3854.25
--------+------------+-----------+---------+-----------
*/
