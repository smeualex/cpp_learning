#include <iostream>

#include <string>
#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include <iterator>
#include <queue>
#include <iomanip>

using std::cout;
using std::endl;
using std::map;
using std::make_pair;

std::deque<int>  deq{91, 92, 93, 94, 95, 96};
std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

//    begin+1 --|
//      begin ----------------------------------------------> end
//          1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
//       rend <---------------------------------------------- rbegin
//                                                       |--- rbegin + 1

template <typename Cont>
void print(const Cont& container, const std::string& descr) {

    cout << "   > " << descr << ":" << endl;
    cout << "       -> [" << std::setw(2) << container.size() << "] ";

    std::copy(
        container.begin(), container.end(), 
        // this is not nise, that it's only for int, but works for our example :)
        std::ostream_iterator<int>(std::cout, ", ")
    );

    cout << endl;
}

// our main stuff go here :)
void do_stuff() {

    print(deq, "Queue");
    print(vec, "Vector");

    
    print(deq, "Queue, after copy: ");}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}