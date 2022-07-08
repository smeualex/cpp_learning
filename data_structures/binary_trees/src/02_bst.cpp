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

    cout << "Tree: " << endl << endl;
    cout << "             4     " << endl;
    cout << "            / \\    " << endl;
    cout << "           /   \\   " << endl;
    cout << "          2    90  " << endl;
    cout << "         / \\  /   " << endl;
    cout << "        0   3 14   " << endl;
    cout << "               \\   " << endl;
    cout << "               45  " << endl;
    cout << endl;
    cout << "bst.size    = " << bst.size()    << endl;
    cout << "bst.height  = " << bst.height()  << endl;
    cout << "bst.minimum = " << bst.minimum()->key << endl;
    cout << "bst.maximum = " << bst.maximum()->key << endl;
    cout << "------------------------------------------------" << endl;

    cout << "Preorder traversal:  ";
    bst.preorder([](auto key) {
        cout << key << " ";
    });
    cout << endl;

    cout << "Inorder traversal:   ";
    bst.inorder([](auto key) {
        cout << key << " ";
    });
    cout << endl;

    cout << "Postorder traversal: ";
    bst.postorder([](auto key) {
        cout << key << " ";
    });
    cout << endl;

    cout << "------------------------------------------------" << endl;
    
    cout << "bfs: ";
    bst.bfs([](auto key) {
        cout << key << " ";
    });
    cout << endl;

    cout << "------------------------------------------------" << endl;

    //////////////////////////////////////////////////////////////////////
    // predecessors
    cout << "     bst.predecessor(14) = ";
    auto tmp = bst.predecessor(14);
    if (tmp)
        cout << tmp->key << endl;
    else
        cout << "none" << endl;

    cout << "     bst.predecessor(0)  = ";
    tmp = bst.predecessor(0);
    if (tmp)
        cout << tmp->key << endl;
    else
        cout << "none" << endl;

    cout << "     bst.predecessor(4)  = ";
    tmp = bst.predecessor(4);
    if (tmp)
        cout << tmp->key << endl;
    else
        cout << "none" << endl;

    cout << "     bst.predecessor(90) = ";
    tmp = bst.predecessor(90);
    if (tmp)
        cout << tmp->key << endl;
    else
        cout << "none" << endl;
    
    cout << "------------------------------------------------" << endl;
    
    //////////////////////////////////////////////////////////////////////
    // successors
    cout << "     bst.successor(14)   = ";
    tmp = bst.successor(14);
    if (tmp)
        cout << tmp->key << endl;
    else
        cout << "none" << endl;

    cout << "     bst.successor(0)    = ";
    tmp = bst.successor(0);
    if (tmp)
        cout << tmp->key << endl;
    else
        cout << "none" << endl;

    cout << "     bst.successor(4)    = ";
    tmp = bst.successor(4);
    if (tmp)
        cout << tmp->key << endl;
    else
        cout << "none" << endl;

    cout << "     bst.successor(90)   = ";
    tmp = bst.successor(90);
    if (tmp)
        cout << tmp->key << endl;
    else
        cout << "none" << endl;

    cout << "------------------------------------------------" << endl;
}