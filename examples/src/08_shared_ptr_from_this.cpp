#include <iostream>

#include <string>
#include <iostream>
#include <functional>
#include <map>

#include <memory>

using std::cout;
using std::endl;
using std::map;
using std::make_pair;

//      You can create with the class std::enable_shared_from_this26 objects which return a 
// std::shared_ptr on itself. For that you have to derive the class public from 
// std::enable_shared_from_this. So the class support the method shared_from_this to
// return std::shared_ptr to this
//
//  https://www.nextptr.com/tutorial/ta1414193955/enable_shared_from_this-overview-examples-and-internals
//
//  https://stackoverflow.com/questions/712279/what-is-the-usefulness-of-enable-shared-from-this?noredirect=1&lq=1
//
//  https://stackoverflow.com/questions/36041012/what-is-the-need-for-enable-shared-from-this
class ShareMe : public std::enable_shared_from_this<ShareMe> {

private:
    int val;

public:
    ShareMe(int _val) : val(_val) { 
        cout << __FUNCTION__ << "; val = " << val << endl;
    }
    
    ~ShareMe() { 
        cout << __FUNCTION__ << "; val = " << val << endl;
    }

    std::shared_ptr<ShareMe> getShared() {
        return shared_from_this();
    }
};

// our main stuff go here :)
void do_stuff() {
    std::shared_ptr<ShareMe> sh1(new ShareMe(100));
    std::shared_ptr<ShareMe> sh2 = sh1->getShared();
    auto sh3 = sh1;

    std::shared_ptr<ShareMe> sh4(new ShareMe(230));

    cout << " sh1 = " << (void*)sh1.get() << endl;
    cout << " sh2 = " << (void*)sh2.get() << endl;
    cout << " sh3 = " << (void*)sh3.get() << endl;
    cout << "   count: " << sh1.use_count() << endl;
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}