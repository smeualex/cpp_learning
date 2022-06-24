#include "headers.h"

#include <type_traits>

#define SHOW(...) std::cout << std::setw(64) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

// Primary Type Categories
//
//      There are 14 different type categories. They are complete and don’t overlap. So each type is only a
// member of one type category. If you check a type category for your type, the request is independent
// of the const or volatile qualifiers.
//
//        template <class T> struct is_void;
//        template <class T> struct is_integral;
//        template <class T> struct is_floating_point;
//        template <class T> struct is_array;
//        template <class T> struct is_pointer;
//        template <class T> struct is_reference;
//        template <class T> struct is_member_object_pointer;
//        template <class T> struct is_member_function_pointer;
//        template <class T> struct is_enum;
//        template <class T> struct is_union;
//        template <class T> struct is_class;
//        template <class T> struct is_function;
//        template <class T> struct is_lvalue_reference;
//        template <class T> struct is_rvalue_reference;


// Composite Type Categories
//
//      Based on the 14 primary type categories, there are 6 composite type categories.
//
// Composite type categories            Primary type category
//       ------------------------------------------------------------------------------------------------
//       is_arithmetic                        is_floating_point or is_integral
//       is_fundamental                       is_arithmetic or is_void
//       is_object                            is_arithmetic or is_enum or is_pointer or is_member_pointer
//       is_reference                         is_lvalue_reference or is_rvalue_reference
//       is_compound                          complement of is_fundamental
//       is_member_pointer                    is_member_object_pointer or is_member_function_pointer
//       ------------------------------------------------------------------------------------------------

// Type Properties
//
//      In addition to the primary and composite type categories there are type properties.
//
//      template <class T> struct is_const;
//      template <class T> struct is_volatile;
//      template <class T> struct is_trivial;
//      template <class T> struct is_trivially_copyable;
//      template <class T> struct is_standard_layout;
//      template <class T> struct is_pod;
//      template <class T> struct is_literal_type;
//      template <class T> struct is_empty;
//      template <class T> struct is_polymorphic;
//      template <class T> struct is_abstract;
//
//      template <class T> struct is_signed;
//      template <class T> struct is_unsigned;
//
//      template <class T, class... Args> struct is_constructible;
//      template <class T> struct is_default_constructible;
//      template <class T> struct is_copy_constructible;
//      template <class T> struct is_move_constructible;
//
//      template <class T, class U> struct is_assignable;
//      template <class T> struct is_copy_assignable;
//      template <class T> struct is_move_assignable;
//      template <class T> struct is_destructible;
//
//      template <class T, class... Args> struct is_trivially_constructible;
//      template <class T> struct is_trivially_default_constructible;
//      template <class T> struct is_trivially_copy_constructible;
//      template <class T> struct is_trivially_move_constructible;
//      template <class T, class U> struct is_trivially_assignable;
//      template <class T> struct is_trivially_copy_assignable;
//      template <class T> struct is_trivially_move_assignable;
//
//      template <class T> struct is_trivially_destructible;
//
//      template <class T, class... Args> struct is_nothrow_constructible;
//      template <class T> struct is_nothrow_default_constructible;
//      template <class T> struct is_nothrow_copy_constructible;
//      template <class T> struct is_nothrow_move_constructible;
//
//      template <class T, class U> struct is_nothrow_assignable;
//      template <class T> struct is_nothrow_copy_assignable;
//      template <class T> struct is_nothrow_move_assignable;
//
//      template <class T> struct is_nothrow_destructible;
//      template <class T> struct has_virtual_destructor;


template <typename T>T fac(T a) {
    static_assert(std::is_integral<T>::value, "T is not integral type");
    cout << "Computing factorial of: " << a << endl;
    return a;
}

// our main stuff go here :)
void do_stuff() {
    fac(10);

    char            c = 'a';
    short int      si = 12;
    unsigned short us = 12345;
    long            l = 123414;
    unsigned long  ul = 12341234;
    __int64       i64 = 123412341234;

    //  fac(10.2);      --> fails with "T is not integral type" error message

    fac(c);
    fac(si);
    fac(us);
    fac(l);
    fac(ul);
    fac(i64);





    SHOW(std::is_void<void>::value);
    SHOW(std::is_integral<short>::value);
    SHOW(std::is_floating_point<double>::value);
    SHOW(std::is_array<int [] >::value);
    SHOW(std::is_pointer<int*>::value);
    SHOW(std::is_reference<int&>::value);
    
    struct A{
        int a;
        int f(int){ return 2011; }
    };
    SHOW(std::is_member_object_pointer<int A::*>::value);
    SHOW(std::is_member_function_pointer<int (A::*)(int)>::value);
    
    enum E{
        e= 1,
    };
    SHOW(std::is_enum<E>::value);

    union U{
        int u;
    };
    SHOW(std::is_union<U>::value);

    SHOW(std::is_class<std::string>::value);
    SHOW(std::is_function<int * (double)>::value);
    SHOW(std::is_lvalue_reference<int&>::value);
    SHOW(std::is_rvalue_reference<int&&>::value);
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}