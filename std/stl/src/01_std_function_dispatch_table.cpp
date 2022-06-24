#include "headers.h"

int main(int argc, char** argv) {
    
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    // function dispatch table
    map<const char, std::function<double(double, double)>> tab;

    tab.insert(make_pair('+', [](double a, double b) {return a + b;} ));
    tab.insert(make_pair('-', [](double a, double b) {return a - b;} ));
    tab.insert(make_pair('*', [](double a, double b) {return a * b;} ));
    tab.insert(make_pair('/', [](double a, double b) {return a / b;} ));

    cout << "\t5 + 3 = "     << tab['+'](5, 3) << endl;
    cout << "\t3.5 - 4.5 = " << tab['-'](3.5, 4.5) << endl;
    cout << "\t3.5 * 4.5 = " << tab['*'](3.5, 4.5) << endl;
    cout << "\t3.5 / 4.5 = " << tab['/'](3.5, 4.5) << endl;
    tab['S'](1, 2);

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}