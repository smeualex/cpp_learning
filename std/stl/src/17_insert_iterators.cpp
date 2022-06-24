#include "headers.h"

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
    for(auto el: container)
        cout << el << " ";
    cout << endl;
}

// our main stuff go here :)
void do_stuff() {

    print(deq, "Queue");
    print(vec, "Vector");

    cout << " - copying in deq elements from vec from the position of element `13`" << endl;
    std::copy(
        std::find(vec.begin(), vec.end(), 13), vec.end(), 
        std::back_inserter(deq)
    );
    print(deq, "Queue, after copy");                                    // 90 92 93 94 95 96 13 14 15


    cout << " - copying all elements starting from position of element 7 to 11 in deq - after element 93" << endl;

    // !!! the end iterator is not inclusive - so the copy "interval" from the 2 iterators returned by find() is [start, end)
    //
    std::copy(
                                                                        // 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
                                                                        //                   ^
        std::find(vec.begin(), vec.end(), 7),                           // ------------------|
                                                                        // 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
                                                                        //                               ^
        std::find(vec.begin(), vec.end(), 11),                          // ------------------------------|
                                                                        // 91, 92, 93, 94, 95, 96
        std::inserter(deq, std::find(deq.begin(), deq.end(), 93))       //           ^
                                                                        // ---------=|
    );

    print(deq, "Queue, after copy: ");                                  // 90 92 7 8 9 10 93 94 95 96 13 14 15


    cout << " - copying all elements in vector from using a reverse iterator from begin + 11" << endl;
    std::copy(
        vec.rbegin()+11, 
        vec.rend(), 
        std::front_inserter(deq)
    );

    print(deq, "Queue, after copy: ");
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}