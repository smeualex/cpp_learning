#include <iostream>

#include <algorithm>    // copy_if
#include <iterator>     // back_inserter
#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include <string>
#include <thread>

using std::vector;
using std::cout;
using std::endl;
using std::map;
using std::make_pair;

// SOURCES
//  https://www.nextptr.com/tutorial/ta1441164581/stdref-and-stdreference_wrapper-common-use-cases
//
//
//      A reference wrapper is a copy-constructible and copy-assignable wrapper for 
// a object of type&, which is defined in the header <functional>. 
// So you have an object, that behaves like a reference, but can be copied. 
//      In opposite to classic references, std::reference_wrapper19 objects support two
// additional use cases:
//      You can use them in containers of the Standard Template Library. 
//              std::vector<std::reference_wrapper<int>> myIntRefVector
//      You can copy instances of classes, which have std::reference_wrapper objects. 
//      That is in general not possible with references.
//
//      With the helper functions std::ref and std::cref you can easily create 
// reference wrappers to variables. 
//  std::ref will create a non constant reference wrapper, 
//  std::cref a constant one
//

///////////////////////////////////////////////////////////////////////////////////////
// 1
void foo(int i) {
    cout << "   > foo() is invoked with i = " << i << endl;
}


///////////////////////////////////////////////////////////////////////////////////////
// 2 

// invoke with a const ref param
void invokeMe(const std::string& s) {
    cout << "   > invokeMe() - const string: " << s << endl;
}

// template of doubling the parameter
template<typename T>
void doubleMe(T t) {
    t *= 2;
}

void invokeCallable() {
    typedef void callableUnit(int);
    std::reference_wrapper<callableUnit> fooRefWrap(foo);

    fooRefWrap(321);
}

///////////////////////////////////////////////////////////////////////////////////////

void ref_cref_sample() {

    std::string s{"[sample string]"};
    invokeMe(std::cref(s));

    int i = 1;
    cout << " BEFORE: i = " << i << endl;

    cout << " calling doubleMe(1) - by value" << endl;
    doubleMe(1);
    cout << " AFTER : i = " << i << endl;


    cout << " calling doubleMe(std::ref(i)) - by ref. wrap." << endl;
    doubleMe(std::ref(i));
    cout << " AFTER : i = " << i << endl;

}

///////////////////////////////////////////////////////////////////////////////////////

//      Unlike a reference, a reference_wrapper is an object and thus satisfies 
// the STL container element requirements (Erasable, to be precise). 
// Therefore, reference_wrapper can be used as a vector element type. 
void use_case_container_of_references() {
    cout << endl;
    cout << __FUNCTION__ << endl;
    std::vector<std::reference_wrapper<int>> vect_ref_wrap;
    int a=0;
    int vals[] = {1,2,3,4,5,6,7,8,9,10};
    
    vect_ref_wrap.push_back(std::ref(a));
    for(int i = 0; i < 9; i++){
        vect_ref_wrap.push_back(std::ref(vals[i]));
    }

    cout << " Vector of std::ref is: "; 
    for(const auto& val: vect_ref_wrap) {
        cout << val << " ";
    }
    cout << endl;

    cout << " Changing vals[4] to 123: " << endl;
    vals[4] = 123;
    cout << " Vector of std::ref is: ";
    for(const auto& val: vect_ref_wrap) {
        cout << val << " ";
    }
    cout << endl;

    // !!!! NOT POSSIBLE !!!!
    // cout << " Changing vect_ref_wrap[4] to 568: ";
    // vect_ref_wrap[4] = 568;

    cout << endl;
}

///////////////////////////////////////////////////////////////////////////////////////
// Passing args by reference to start-function via std::thread
//
//      We can pass arguments to the start-function when creating a new thread 
// via std::thread(startFunction, args). Those arguments are passed by value 
// from the thread creator function because the std::thread constructor
// copies or moves the creator's arguments before passing them to the start-function.
// 
//      So, a start-function's reference parameter cannot bind to a creator's argument. 
// It can only bind to a temporary created by std::thread
//

void start(int& i) { 
    cout << "       > Thread started - i = " << i << endl;
    i+= 1; 
    cout << "       > Changed to i = " << i << endl;
}

void start_const(const int& i) {
    cout << "       > Const thread started - i = " << i << endl;
    // can't do that :)
    // i+= 1; 
 }

void use_case_thread_start_arguments() {
    cout << endl;
    cout << __FUNCTION__ << endl;
    
    int e = 10; 
    //e is copied below to a temporary
    // std::thread(start, e).join();       //Error! can't bind temporary to int&.
    std::thread(start_const, e).join(); //OK. But sort of by-value 

    ///////////////////////////////////////////////////////////////////////////////
    //  If we want to pass an argument to a start-function by reference, 
    // we do that through std::ref,
    ///////////////////////////////////////////////////////////////////////////////////////
    std::thread(start, std::ref(e)).join(); //OK. By-ref
    cout << "   > main thread: e = " << e << endl;
    std::thread(start, std::ref(e)).join(); //By-ref 
    cout << "   > main thread: e = " << e << endl;
    std::thread(start, std::ref(e)).join(); //By-ref 
    cout << "   > main thread: e = " << e << endl;
    
    std::thread(start_const, std::cref(e)).join(); //By-ref 

    cout << endl;
}

///////////////////////////////////////////////////////////////////////////////////////
// Reference as a class member
//
//      Having a reference class member poses problems, such that, it makes the class 
// non-assignable and practically immovable

class W {

private:
public:
    int& iRef;
    W(int& i):iRef(i) {
        cout << "   > W object constructed with value = " << iRef << endl;
    }

};

class W_ref {

private:
public:
    std::reference_wrapper<int> iRef;
    W_ref(int& i):iRef(i) {
        cout << "   > W_ref object constructed with value = " << iRef << endl;
    }

};

void use_case_ref_as_class_member() {
    
    cout << endl;
    cout << __FUNCTION__ << endl;

    int i = 10;
    int j = 20;

    // OK and Oook
    W w1(i);
    W w2(j);

    // assignment fails with "attempting to reference a deleted function"
    // because we do not have assignment operator
    //
    //      The common practice is to avoid references and use pointers
    //
    // w1 = w2;
    //
    // swap fails for the same reasons
    //
    // std::swap(w1, w2);

    // SOLUTION: a reference_wrapper - which offers best of both worlds
    W_ref w3(i);
    W_ref w4(j);

    cout << " BEFORE: w3 = " << w3.iRef << "; w4 = " << w4.iRef << endl;
    cout << " Changing w3 and w4... "<< endl;
    std::swap(w3, w4);
    cout << " AFTER : w3 = " << w3.iRef << "; w4 = " << w4.iRef << endl;

    cout << endl;
}

///////////////////////////////////////////////////////////////////////////////////////
// Passing a function object by reference
//
//      An std::reference_wrapper<T> can be invoked like a function as long as 
// the T is a callable. This feature is particularly useful with STL algorithms 
// if we want to avoid copying a large or stateful function object.
//
// Besides, T can be any callable – a regular function, a lambda, or a function object.

class Small {
public:
    bool operator()(int i) const {
        //Filter anything greater than 100
        return (i < 100);
    }
    //big data
};

//Small immutable data and function object
const Small small; 
std::vector<int> in1; //input vector
std::vector<int> in2; //input vector

void use_case_ref_function_object() {
    // Create test vectors
    in1.push_back(1);
    in1.push_back(2);
    in1.push_back(312);
    in1.push_back(101);
    in1.push_back(3);
    in1.push_back(3214);

    in2.push_back(1234);
    in2.push_back(4);
    in2.push_back(144);
    in2.push_back(5);
    in2.push_back(15234);
    in2.push_back(1534);
    in2.push_back(6);

    cout << "Vector in1: ";
    for(const auto& val: in1) 
        cout << val << " ";
    cout << endl;
    
    cout << "Vector in2: ";
    for(const auto& val: in2) 
        cout << val << " ";
    cout << endl;

    std::vector<int> out;
    //Pass Small by-ref to avoid copy 
    std::copy_if(in1.begin(), in1.end(), std::back_inserter(out), std::ref(small)); 
    std::copy_if(in2.begin(), in2.end(), std::back_inserter(out), std::ref(small)); 
    
    // use the filtered 'out' vector
    // print: 1 2 3 4 5 6 
    cout << "Filtered vector out: ";
    for(const auto& val: out) 
        cout << val << " ";
    cout << endl;
}

// our main stuff go here :)
void do_stuff() {
    invokeCallable();
    ref_cref_sample();
    use_case_container_of_references();
    use_case_thread_start_arguments();
    use_case_ref_as_class_member();
    use_case_ref_function_object();
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}