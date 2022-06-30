#include <iostream>
#include <string>
#include <type_traits>

using std::cout;
using std::endl;

///////////////////////////////////////////////////////////////////////////////
//
//  Both max1 and max2 variants - using std::decay_t and std::common_type
// prevent returing a reference
//

template <typename T1, typename T2,
          typename ReturnType = std::decay_t<decltype(true ? T1() : T2())>>
    ReturnType max1(T1 a, T2 b)
{
    return b < a ? a : b;
}


template <typename T1, typename T2,
    typename ReturnType = std::common_type<T1, T2>>
    ReturnType max2(T1 a, T2 b)
{
    return b < a ? a : b;
}


// our main stuff go here :)
void do_stuff() {
    cout << "Testing max1 - std::decay_t" << endl;

    // m1 will be double
    auto a1 = max1(4, 7.2);

    // specify the return type explicitly
    auto b1 = max1<double, int, long double>(7.2, 5);
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}