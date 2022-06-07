#include "headers.h"
#include <utility>          // needed by pair ?!
#include <tuple>            // for tuples, dooh

void pair_demo() {
    std::pair<const char*, double> charDoub1("str1", 3.14);
    std::pair<const char*, double> charDoub2 = make_pair("str2", 3.14);

    // even more convenient way of doing things :)
    auto charDoub3 = make_pair("str3", 3.14);

    cout << "Pairs: " << endl;
    cout << "\t1. " << charDoub1.first <<", " << charDoub1.second << std::endl;
    cout << "\t2. " << charDoub2.first <<", " << charDoub2.second << std::endl;
    cout << "\t3. " << charDoub3.first <<", " << charDoub3.second << std::endl;

    cout << "Changing charDoub2 key to STR and the value to 4.14" << std::endl;
    // direct access to first , or second :)
    charDoub2.first = "STR";
    // through get<>
    std::get<1>(charDoub2) = 4.14;

    cout << "\t2. " << charDoub2.first <<", " << charDoub2.second << std::endl;
}

void tuples_demo() {
    cout << "tuples: " << endl;
    // tuples are just pairs with an arbitrary length of elements
    std::tuple<std::string, int, float> tup1("first", 3, 4.17f);
    auto tup2= std::make_tuple("second", 4, 1.1);
    
    std::cout << std::get<0>(tup1) << ", " 
              << std::get<1>(tup1) << ", "
              << std::get<2>(tup1) << std::endl; // first, 3, 4.17

    std::cout << std::get<0>(tup2) << ", " 
              << std::get<1>(tup2) << ", "
              << std::get<2>(tup2) << std::endl; // second, 4, 1.1

    std::cout << (tup1 < tup2) << std::endl; // true
    
    std::get<0>(tup2)= "Second";
    std::cout << std::get<0>(tup2) << ", " 
              << std::get<1>(tup2) << ", "
              << std::get<2>(tup2) << std::endl; // Second, 4, 1.1

    std::cout << (tup1 < tup2) << std::endl; // false
    
    auto pair= std::make_pair(1, true);
    std::tuple<int, bool> tup= pair;
}
// our main stuff go here :)
void do_stuff() {

    pair_demo();

    tuples_demo();
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}