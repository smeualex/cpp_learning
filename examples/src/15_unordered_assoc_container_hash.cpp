#include <iostream>

#include <string>
#include <iostream>
#include <functional>
#include <map>

#include <unordered_map>

using std::cout;
using std::endl;
using std::map;
using std::make_pair;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Hash Function
//
//  The reason for the constant access time of the unordered associative container is the hash function,
// which is schematically shown here. The hash function maps the key to its value the so-called has
// value. 
//  A hash function is good if it produces as few collisions as possible and equally distributes the
// keys onto the buckets. Because the execution of the hash function takes a constant amount of time,
// the access of the elements is in the base case also constant.
//
// The hash function
// > is already defined for the built-in types like boolean, natural numbers and floating point
//   numbers,
// > is available for std::string and std::wstring,
// > generates for a C string const char a hash value of the pointer address,
// > can be defined for user-defined data types
//////////////////////////////////////////////////////////////////////////////////////////////////////////


class MyInt {
private:
    int val;

public :
    MyInt(int _val) : val(_val) {}

    // we can use our class as key in an unordered map
    // because it's comparable now
    bool operator== (const MyInt& other) const  {
        return val == other.val;
    }

    int getVal() const {
        return val;
    }
};

// our hash function to use in an unordered container
struct MyHash {
    std::size_t operator()(MyInt m) const {
        std::hash<int> hashVal;
        return hashVal(m.getVal());
    }
};

std::ostream& operator<< (std::ostream& s, const MyInt& m) {
    s << m.getVal();
    return s;
}


// type alias for our map to keep things simple
typedef std::unordered_map<MyInt, int, MyHash> MyIntMap;


// our main stuff go here :)
void do_stuff() {
    MyIntMap map {
        { MyInt(-2)  , -2  },
        { MyInt(32)  , 32  },
        { MyInt(312) , 312 },
        { MyInt(-42) , -42 },
        { MyInt(-1)  , 1   },
        { MyInt(0)   , 0   }
    };

    cout << "Printing map: " << endl;
    for (const auto m: map)
        cout << "  { " << m.first << ", " << m.second << "} ";
    cout << endl;
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}