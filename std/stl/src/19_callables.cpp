#include "headers.h"


std::vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
std::vector<int> v0(v);

// function
void square(int& i) { i *= i; }

// function object
//      - object with operator() implemented
struct Square {
    void operator()(int& i) { 
        i*=i;
    }
};



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

template <typename Cont>
void print_map(const Cont& m, const std::string& descr) {
    cout << "   > " << descr << ":" << endl;
    cout << "       -> [" << std::setw(2) << m.size() << "] ";

    for(const auto& p: m)
        cout << "   { " << p.first << ", " << p.second << " } ";
    cout << endl;
}


void test_predefinedFunctionObjects() {

    cout << " --- predefined function objects in map definition: " << endl;

    std::map<int, std::string> defaultMap {         // uses std::less<int> by default
        { 1, "1" },
        { 2, "2" },
        { 3, "3"}
    };

    std::map<int, std::string, std::greater<int>> greaterThanMap {
        { 1, "1" },
        { 2, "2" },
        { 3, "3" }
    };

    print_map(defaultMap,     "Default map - std::less<int>   ");
    print_map(greaterThanMap, "Default map - std::greater<int>");
}

// our main stuff go here :)
void do_stuff() {
    print(v, "Initial state: ");
    
    std::for_each(v.begin(), v.end(), square);
    print(v, "Squared vector - function");

    v = v0;
    std::for_each(v.begin(), v.end(), Square());
    print(v, "Squared vector - function object");

    v = v0;
    std::for_each(v.begin(), v.end(), [](int& i){ i*=i; });
    print(v, "Squared vector - lambda");

    test_predefinedFunctionObjects();
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}