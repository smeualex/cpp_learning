#include "bst.h"
#include<iostream>

using std::cout;
using std::endl;

void main() {
    BST<int> bst;
    
    bst.insert(4);
    bst.insert(2);
    bst.insert(90);
    bst.insert(3);
    bst.insert(0);
    bst.insert(14);
    bst.insert(45);

    cout << "Preorder traversal: ";
    bst.pre_order_traversal([](auto node) {
        cout << node->key << " ";
    });
    cout << endl;

}