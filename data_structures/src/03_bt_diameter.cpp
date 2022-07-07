//  The diameter of a tree (sometimes called the width) is the number of 
// nodes on the longest path between two end nodes.
//
// The diameter of a tree T is the largest of the following quantities:
//      the diameter of T’s left subtree.
//      the diameter of T’s right subtree.
//      the longest path between leaves that goes through the root of T 
//      (this can be computed from the heights of the subtrees of T)

#include <iostream>

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

inline int max(const int a, const int b) { return (a > b) ? a : b; }

int height(struct Node* node) {
    if(node == nullptr)
        return 0;

    return 1 + max( height(node->left), height(node->right) );
}

int diameter(Node* tree) {
    if(tree == nullptr)
        return 0;

    // height of left and right sub-trees
    int leftHeight = height(tree->left);
    int rightHeight = height(tree->right);

    // diameters of left and right and right sub-trees
    int leftDiameter = diameter(tree->left);
    int rightDiameter = diameter(tree->right);

    return max( leftHeight + rightHeight + 1, max(leftDiameter, rightDiameter));
}

// Driver Code
int main()
{
  
    /* Constructed binary tree is
            1
            / \
        2     3
        / \
    4     5
    */
    struct Node* root    = newNode(1);
    root->left           = newNode(2);
    root->right          = newNode(3);
    root->left->left     = newNode(4);
    root->left->right    = newNode(5);
     
    int height = 0;
    // Function Call
    cout << "Diameter of the given binary tree is " << diameter(root);
  
    return 0;
}
