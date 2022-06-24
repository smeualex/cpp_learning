#include "headers.h"

template <typename Cont>
void print(Cont cont, const std::string& msg) {
    cout << msg << ": " << endl;

    cout << " > [size=" << std::setw(3) << cont.size() << "]: ";
    for(const auto c: cont)
        std::cout << c << " ";
    cout << endl;
}

// do the same "stuff" on different containers
//
template<typename Cont, typename T>
void do_algorithm(Cont cont, T t) {

    print(cont, "Initial container");

    std::reverse(cont.begin(), cont.end());
    print(cont, "Reversed 1");

    std::reverse(cont.begin(), cont.end());
    print(cont, "Reversed 2");

    cout << "Finding element [" << t << "] in the container" << endl;
    auto it = std::find(cont.begin(), cont.end(), t);
    if(it == cont.end()) {
        cout << " > element NOT found" << endl;
        return;
    }
    cout << " > element found" << endl;

    cout << "Reversing container from the found element up to the end" << endl;
    std::reverse(it, cont.end());

    print(cont, "Resulting container");
}

// our main stuff go here :)
void do_stuff() {
    std::vector<int>        myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::deque<std::string> myDeq({"A", "B", "C", "D", "E", "F", "G", "H", "I"});
    std::list<char>         myList({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'});

    do_algorithm(myVec, 5);
    do_algorithm(myDeq, "D");
    do_algorithm(myList, 'd');

}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}