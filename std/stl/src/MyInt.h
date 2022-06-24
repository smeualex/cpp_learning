#pragma once
#include <iostream>

class MyInt {
public:
    int i;
    MyInt(int _i) : i(_i) {
        std::cout << "> MyInt() constructor; i="<< i << std::endl;
    }
    ~MyInt() {
        std::cout << "> ~MyInt() destructor; i=" << i << std::endl;
    }
};