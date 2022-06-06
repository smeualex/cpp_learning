#include <iostream>

#include <string>
#include <iostream>
#include <functional>
#include <map>
#include <set>
#include <unordered_map>

using std::cout;
using std::endl;
using std::map;
using std::make_pair;

template <typename Cont>
void print_map(const Cont& m){
    cout << " > Map - size = " << m.size() << ": " << endl;
    for(const auto& p: m)
        cout << "   { " << p.first << ", " << p.second << "}" << endl;
    cout << endl;
}

template <typename Cont>
void test_map() {
    Cont stringIntMap {
        {"one", 1},
        {"two", 2}
    };

    print_map(stringIntMap);

    cout << " - Adding a new element" << endl;
    stringIntMap["three"] = 3;
    print_map(stringIntMap);

    cout << " - erasing a element \"two\"" << endl;
    stringIntMap.erase("two");
    print_map(stringIntMap);

    cout << " - clearing map" << endl;
    stringIntMap.clear();
    print_map(stringIntMap);
    
}


// ---------------------------------------------------------------------------------------
// Comparator example

struct StringLengthComparator {
    bool operator()(const std::string& a, const std::string& b) const {
        return a.length() < b.length();
    }
};

void test_map_comparator() {
    cout << endl << " ---- test map with string length comparator" << endl;
    std::map<std::string, int, StringLengthComparator> m {
        {"three", 3},
        {"one", 1},
        {"five", 5}
    };

    print_map(m);

    
    cout << " - inserting element with key=\"two\" - which has a duplicate length;" << endl;

    // insert returns a pair with an iterator to the map element and a bool
    // if the insert is ok , pai -> second is true, otherwise it's false
    auto tmp = m.insert(std::make_pair("two", 2));
    if(tmp.second) 
        cout << "  > insert OK" << endl;
    else
        cout << "  > insert failed. key exists already!" << endl;
    print_map(m);
    cout << endl;

    cout << " - inserting element with key=\"seventy\"" << endl;
    // !!!! If we care about performance this is the way
    //      - there is no extra constructor or parameter type deduction performed (as oposed to std::make_pair)
    tmp = m.insert(std::pair<std::string, int>{"seventy", 70});
    if(tmp.second) 
        cout << "  > insert OK" << endl;
    else
        cout << "  > insert failed. key exists already!" << endl;
    print_map(m);

}


// our main stuff go here :)
void do_stuff() {
    cout << " ------ Ordered Map   ------" << endl;
    test_map<std::map<std::string, int>>();
    cout << " ---------------------------" << endl << endl;

    cout << " ------ Unordered Map ------" << endl;
    test_map<std::unordered_map<std::string, int>>();
    cout << " ---------------------------" << endl << endl;

    test_map_comparator();
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}