#include "bst.h"
#include<iostream>

void main() {
    BST<int> bst;
    
    bst.insert(4);
    bst.insert(2);
    bst.insert(90);
    bst.insert(3);
    bst.insert(0);
    bst.insert(14);
    bst.insert(45);

   
    bst.in_order_traversal([](auto node){ 
            std::cout << node->key << std::endl;
        });
}