#include "bst.h"
#include<iostream>

using std::cout;
using std::endl;

/// <summary>
/// Create a demo-tree and run our class
/// 
/// Tree:
/// 
///             4
///            / \
///           /   \
///          2    90
///         / \   /
///        0   3 14
///               \
///               45
/// 
/// </summary>
void main() {
    BST<int> bst;
    
    bst.insert(4);
    bst.insert(2);
    bst.insert(90);
    bst.insert(3);
    bst.insert(0);
    bst.insert(14);
    bst.insert(45);

    cout << "Preorder traversal:  ";
    bst.pre_order_traversal([](auto key) {
        cout << key << " ";
    });
    cout << endl;

    cout << "Inorder traversal:   ";
    bst.in_order_traversal([](auto key) {
        cout << key << " ";
    });
    cout << endl;

    cout << "Postorder traversal: ";
    bst.post_order_traversal([](auto key) {
        cout << key << " ";
    });
    cout << endl;

}