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

// SOURCE
//   https://www.nextptr.com/question/qa1366990479/unique_ptr-with-custom-deleter

struct Resource {
    // stuff...

    Resource() : val(0) {
        cout << "   > Resource() constructor: " << val << endl;
    }
    ~Resource() {
        cout << "   > ~Resource() destructor: " << val << endl;
    }
    int val;
    bool isFree{true};
};

// Resource pool
class Pool {
    
private:
    // our resource pool cache
    Resource resources[3];

public:
    // Custom Resource deleter
    struct Deleter {
        // called by unique_ptr to destroy/free the resource
        void operator()(Resource* r) {
            if(r) {
                cout << " ------> "<< __FUNCTION__ << ": r=" << r->val <<endl;
                r->isFree = true;   // mark the resource as free
            }
        }
    };

    // return a free Resource from the pool
    auto get() {
        // create an unique_ptr with nullptr
        auto rp = std::unique_ptr<Resource, Deleter>(nullptr, Deleter());

        cout << endl << "    " << __FUNCTION__ << endl;
        // find first free Resource
        for(auto& r: resources) {
            cout << "       r.isFree=" << r.isFree << endl;
            if(r.isFree) {
                r.isFree = false;       // mark the resource as not-free
                rp.reset(&r);           // reset the unique_ptr to this new Resource*
                break;
            }
        }
        cout << endl;

        return rp;
    }


};


// our main stuff go here :)
void do_stuff() {
    using ResourcePtr = std::unique_ptr<Resource, Pool::Deleter>;
    cout << "Initializing a pool with 3 resources" << endl;
    Pool pool;
    
    cout << "Trying to get a resource" << endl;
    ResourcePtr rp = pool.get();
    if(rp) {
        cout << "Resource 1 retrieved; Changing value to 123. " << endl;
        rp->val = 123;
    } else {
        cout << "No resource free in the pool" << endl;
    }

    cout << "Trying to get a resource" << endl;
    ResourcePtr rp2 = pool.get();
    if(rp2) {
        cout << "Resource 2 retrieved; Changing value to 321. " << endl;
        rp2->val = 321;
    } else {
        cout << "No resource free in the pool" << endl;
    }

    cout << "Trying to get a resource" << endl;
    ResourcePtr rp3 = pool.get();
    if(rp3) {
        cout << "Resource 3 retrieved; Changing value to 444. " << endl;
        rp3->val = 444;
    } else {
        cout << "No resource free in the pool" << endl;
    }

    // here we should get a nullptr back
    cout << "Trying to get a resource - we expect an error" << endl;
    ResourcePtr rp4 = pool.get();
    if(rp4) {
        cout << "Resource 4 retrieved; Changing value to 324. " << endl;
        rp4->val = 324;
    } else {
        cout << "No resource free in the pool" << endl;
    }

    cout << "Releasing rp3..." << endl;
    Resource* tmp = rp3.release();
    delete tmp;

    cout << "~~~~~~~~~~~~~~~~~~~~~~~ Trying to get a resource again" << endl;
    rp4 = pool.get();
    if(rp4) {
        cout << "Resource 4 retrieved; Changing value to 324. " << endl;
        rp4->val = 324;
    } else {
        cout << "No resource free in the pool" << endl;
    }
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}