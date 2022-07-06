#include<iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* newNode(int data) {
    Node* node = new Node();

    node->data = data;
    node->left = nullptr;
    node->right = nullptr;

    return node;
}

// Preorder - data - left - right
void preorder(Node* tree) {
    if(tree != nullptr) {
        cout << " " << tree->data;
        preorder(tree->left);
        preorder(tree->right);
    }
}

// Inorder - left - data - right
void inorder(Node* tree) {
    if(tree != nullptr) {
        inorder(tree->left);
        cout << " " << tree->data;
        inorder(tree->right);
    }
}

// Postorder - left - right - data
void postorder(Node* tree) {
    if(tree != nullptr) {
        postorder(tree->left);
        postorder(tree->right);
        cout << " " << tree->data;
    }
} 

/*
        1
       / \
      2   3
     / \   \
    4   5   6
*/
int main() {
    Node* root = newNode(1);

    root->left  = newNode(2);
    root->right = newNode(3);

    root->left->left  = newNode(4);
    root->left->right = newNode(5);

    root->right->right = newNode(6);


    cout << "preorder traversal:  ";
    preorder(root);
    cout << endl;

    cout << "inorder traversal:   ";
    inorder(root);
    cout << endl;
    
    cout << "postorder traversal: ";
    postorder(root);
    cout << endl;
}