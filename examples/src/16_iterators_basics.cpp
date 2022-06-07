#include <iostream>

#include <string>
#include <iostream>
#include <functional>
#include <map>
#include <vector>

using std::cout;
using std::endl;
using std::map;
using std::make_pair;


void map_iterator() {
    std::map<std::string, int> myMap{
        {"Rainer", 1966}, 
        {"Beatrix", 1966}, 
        {"Juliette", 1997},
        {"Marius", 1999}
    };

    // explicit type    ==> better to use `auto` always for iterators
    std::map<std::string, int>::iterator endIt = myMap.end();

    cout << "Iterate map: " << endl;
    for(auto it = myMap.begin(); it != endIt; it++)
        cout << "  { " << it->first << ", " << it->second << " }" << endl;

    cout << endl;
}

void vector_iterator() {
    std::vector<int> myVec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int>::const_iterator vecEndIt= myVec.cend();
    std::vector<int>::iterator vecIt;

    cout << "Iterate vector: " << endl;
    for (vecIt= myVec.begin(); vecIt != vecEndIt; ++vecIt) 
        cout << *vecIt << " ";
    cout << endl;

    cout << "Reverse iterate vector: " << endl;
    for (auto revIt= myVec.rbegin(); revIt != myVec.rend(); ++revIt)
        cout << *revIt << " ";
    cout << endl;
}


// our main stuff go here :)
void do_stuff() {
    map_iterator();
    vector_iterator();
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}