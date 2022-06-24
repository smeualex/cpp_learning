#include "headers.h"
#include "MyInt.h"

#include <memory>

class C {
private:
    static int count;
    int val;

public:
    C() : val(count) {
        cout << (void*)this << " - Hello: " << val << endl;
        count++;
    }

    ~C() {
        cout << (void*)this << " - Goodbye: " << val << endl;
        count--;
    }
};
// intialize static
int C::count = 0;

void unique_ptr_ops() {

    cout << "Creating new unique_ptr - 1998" << endl;
    std::unique_ptr<MyInt> ptr1 { new MyInt(1998) };
    cout << "  ptr1.get() = " << ptr1.get() << endl;

    cout << "Move ptr1 in ptr2" << endl;
    std::unique_ptr<MyInt> ptr2 { std::move(ptr1) };
    cout << "  ptr1.get() = " << ptr1.get() << endl;
    cout << "  ptr2.get() = " << ptr2.get() << endl;

    {
        cout << "Creating unique_ptr inside a scope..." << endl;
        std::unique_ptr<MyInt> localPtr { new MyInt(2003) };
    }

    cout << "Resetting ptr2 to 2011" << endl;
    ptr2.reset(new MyInt(2011));

    cout << "Releasing ptr2" << endl;
    MyInt* myInt = ptr2.release();
    cout << "Explicitly call delete" << endl;
    delete myInt;

    cout << "Creating 2 pointers for swap test" << endl;
    std::unique_ptr<MyInt> ptr3 { new MyInt(2017) };
    std::unique_ptr<MyInt> ptr4 { new MyInt(2022) };
    cout << "Before swap:" << endl;
    cout << "  ptr3.get() = " << ptr3.get() << endl;
    cout << "  ptr4.get() = " << ptr4.get() << endl;

    std::swap(ptr3, ptr4);

    cout << "After swap:" << endl;
    cout << "  ptr3.get() = " << ptr3.get() << endl;
    cout << "  ptr4.get() = " << ptr4.get() << endl;

    cout << endl;
    cout << "Creating array of unique_ptr: " << endl;
    std::unique_ptr<C[]> uniquePtrArr{ new C[4] };
}

// our main stuff go here :)
void do_stuff() {
    unique_ptr_ops();
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}