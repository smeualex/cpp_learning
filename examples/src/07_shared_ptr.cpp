#include <iostream>

#include <string>
#include <iostream>
#include <functional>
#include <map>

#include <memory>

#include "MyInt.h"

using std::cout;
using std::endl;
using std::map;
using std::make_pair;

//  The helper function std::make_shared25 creates the resource and returns it in a std::shared_ptr.
// You should use std::make_shared instead of the direct creation of a std::shared_ptr, because
// std::make_shared is a lot faster.


void f_non_const_shared_ptr(std::shared_ptr<MyInt> f) {
    cout << "       " << __FUNCTION__ << " called; val: " << f->i  << "; count: " << f.use_count() << endl;
    f->i = 123;
}

// !!!!!!! passing a shared_ptr as a const ref => reference counter is not incremented
void f_const_ref_shared_ptr(const std::shared_ptr<MyInt>& f) {
    cout << "       " << __FUNCTION__ << " called; val: " << f->i  << "; count: " << f.use_count() << endl;
    f->i = 9999;
}

// our main stuff go here :)
void do_stuff() {

    auto s1 = std::make_shared<MyInt>(1998);
    cout << "shared ptr count: " << s1.use_count() << endl;

    {
        cout << "----------- BLOCK START ---------------" << endl;
        cout << "   New shared ptr from previous one, inside a block" << endl;
        std::shared_ptr<MyInt> s2(s1);
        cout << "   shared ptr 1 count: " << s1.use_count() << endl;
        cout << "   shared ptr 2 count: " << s1.use_count() << endl;
        cout << "----------- BLOCK END   ---------------" << endl;
    }
    cout << "shared ptr 1 cout: " << s1.use_count() << endl;

    cout << endl;
    cout << "Creating a new shared ptr through assignment operator" << endl;
    std::shared_ptr<MyInt> s3 = s1;
    cout << "shared ptr 1 cout: " << s1.use_count() << endl;
    cout << "shared ptr 3 cout: " << s3.use_count() << endl;
    cout << endl;
    
    cout << "Resetting s3" << endl;
    s3.reset();
    cout << "shared ptr 1 cout: " << s1.use_count() << endl;


    cout << endl;
    cout << "------- FUNCTION CALLS --------" << endl;

    cout << "Calling f with non constant shared_ptr" << endl;
    cout << "   BEFORE: shared ptr 1 val:" << s1->i << "; count: " << s1.use_count() << endl;
    f_non_const_shared_ptr(s1);
    cout << "   AFTER:  shared ptr 1 val:" << s1->i << "; count: " << s1.use_count() << endl;
    
    cout << endl;
    cout << "Calling f with constant shared_ptr reference " << endl;
    cout << "   BEFORE: shared ptr 1 val:" << s1->i << "; count: " << s1.use_count() << endl;
    f_const_ref_shared_ptr(s1);
    cout << "   AFTER:  shared ptr 1 val:" << s1->i << "; count: " << s1.use_count() << endl;

    cout << "------- FUNCTION CALLS --------" << endl;
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}