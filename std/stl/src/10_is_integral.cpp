#include "headers.h"

#include <type_traits>

class A {};

template <class T>
T f(T i) {
    static_assert(std::is_integral<T>::value, "Integral required!!");
    return i;
}

#define SHOW(...) std::cout << std::setw(64) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'


// our main stuff go here :)
void do_stuff() {

    cout << std::boolalpha;
    SHOW(std::is_integral<A>::value);
    //SHOW(std::is_integral<E>::value);
    SHOW(std::is_integral<float>::value);
    SHOW(std::is_integral<int>::value);
    SHOW(std::is_integral<const int>::value);
    SHOW(std::is_integral<bool>::value);
    SHOW(f(123));

    int a = 1;
    int b = 123;
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}