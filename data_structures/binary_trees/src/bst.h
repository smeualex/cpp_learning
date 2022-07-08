#pragma once

#include <algorithm>
#include <functional>
#include <queue>
#include <map>
#include <memory>
#include <vector>

#ifdef _DEBUG
using namespace std;
#endif

enum class DiagonalDirection {
    leftToRight,
    rightToLeft
};

// binary search tree
// https://codereview.stackexchange.com/questions/191211/binary-search-tree-data-structure-implementation-in-c11-using-smart-pointers
//
// https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/

template <typename key_t>
class BST {
private:

    struct node {
        key_t key;                  
        node* parent{ nullptr };
        node* left  { nullptr };
        node* right { nullptr };

        explicit node(const key_t _key) 
            : key(_key)
        { }

#ifdef _DEBUG
        ~node() {
            cout << "   > destroying node: " << key << endl;
            delete left;
            delete right;
        }
#endif
    };

    std::shared_ptr<node> root;
    
    typedef std::function< void(const key_t&) > traversal_handler;

    void preorder(node* x, traversal_handler handler) const {
        if (x == nullptr)
            return;

        handler(x->key);

        preorder(x->left, handler);
        preorder(x->right, handler);
    }

    void inorder(node* x, traversal_handler handler) const{
        if (x == nullptr) 
            return;
        
        inorder(x->left, handler);
        
        handler(x->key);
        
        inorder(x->right, handler);
    }

    void postorder(node* x, traversal_handler handler) const {
        if (x == nullptr) 
            return;
        
        postorder(x->left, handler);
        postorder(x->right, handler);
        
        handler(x->key);
    }

    void bfs(node* x, traversal_handler handler) const {
        if (x == nullptr) 
            return;
        
        std::queue <node*> queue;
        
        queue.push(x);
        while(queue.empty() == false) {
            node* y = queue.front();
            handler(y->key);
            queue.pop();
            
            if (y->left != nullptr)
                queue.push(y->left);
            if (y->right != nullptr)
                queue.push(y->right);
        }
    }

    void diagonalTraversalLR(node* root, int distance, 
        std::map<int, std::vector<key_t>> &diagonals) const {

        if (!root)
            return;

        diagonals[distance].push_back(root->key);

        // vertical distance increases on the left
        diagonalTraversalLR(root->left,  distance + 1, diagonals);
        // but remains the same on the right
        diagonalTraversalLR(root->right, distance    , diagonals);
    }

    void diagonalTraversalRL(node* root, int distance,
        std::map<int, std::vector<key_t>>& diagonals) const {

        if (!root)
            return;

        diagonals[distance].push_back(root->key);

        // vertical distance increases to the right
        diagonalTraversalRL(root->right, distance + 1, diagonals);
        // but stays the same to the left
        diagonalTraversalRL(root->left,  distance,     diagonals);
    }

    const unsigned long long height(node* x) const {
        if (x == nullptr)   
            return 0;
        return std::max(height(x->left), height(x->right)) + 1;
    }

    const unsigned long long size(node* x) const {
        if (x == nullptr) 
            return 0;
        return size(x->left) + size(x->right) + 1;
    }

public:

#ifdef _DEBUG
    ~BST() {
        cout << endl;
        cout << "================================================" << endl;
        cout << "Destroying BST " << endl;
    }
#endif

    void preorder(traversal_handler handler) const {
        preorder(root.get(), handler);
    }

    void inorder(traversal_handler handler) const {
        inorder(root.get(), handler);
    }

    void postorder(traversal_handler handler) const {
        postorder(root.get(), handler);
    }

    void bfs(traversal_handler handler) const {
        bfs(root.get(), handler);
    }

    auto diagonalTraversal(const DiagonalDirection direction = DiagonalDirection::leftToRight) const {
        std::map<int, std::vector<key_t>> diagonals;
        
        switch (direction) {
        case DiagonalDirection::leftToRight:
            diagonalTraversalLR(root.get(), 0, diagonals);
            break;

        case DiagonalDirection::rightToLeft:
            diagonalTraversalRL(root.get(), 0, diagonals);
            break;
        }
        return diagonals;
    }

/// <summary>
/// Insert a new node in the tree
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
/// Suppose we wanted to insert 5:
///     - after the first while we have:
///         parent = 14 (actually the node with the key=14)
///         
///     - we create the node for current and set up its parent
///         current = std::make_shared<node>(key);
///         current->parent = parent;
///     - now we have:
///             4
///            / \
///           /   \
///          2    90
///         / \   /
///        0   3 14 <--------- parent
///               \
///               45
///         and somewhere a current node with parent set to 14
///         
///     - we set up the left or right links of the parent
///         if the new node has key > parent's key - parent->left = current
///         otherwise parent->right = current
/// 
///     -> exceptional case when we have an empty tree and we set 
///        the new node to be the root
/// 
///             4
///            / \
///           /   \
///          2     90
///         / \    /
///        0   3  14
///              / \
///             5  45
///             ^------------ new inserted node
/// </summary>
    bool insert(const key_t& key) {

        node* current = root.get();
        node* parent = nullptr;

        // search the tree to get the right place to insert
        while(current!=nullptr) {
            
            parent = current;

            if (key > current->key) {
                current = current->right;
            } else if (key < current->key) {
                current = current->left;
            } else {
                // node already exists
                return false;
            }
        }
        
        // create the current node
        current = new node(key);
        current->parent = parent;
        
        // set up parent link to the current node
        if(parent == nullptr) {
            root = std::make_unique<node>(*current);
        } else if (current->key > parent->key) {
            parent->right = current;
        } else if (current->key < parent->key) {
            parent->left = current;
        }

        return true;
    }
   
    const std::shared_ptr<node> search(const key_t key) const {
        node* x = root;
        while (x != nullptr) {
            if (key > x->key) {
               x = x->right;
            } else if (key < x->key) {
                x = x->left;
            } else {
                return x;
            }
        }
        return nullptr;
    }
    
    const node* minimum() const {
        if (root == nullptr) 
            return nullptr;

        node* x = root.get();
        while(x->left != nullptr) 
            x = x->left;
        return x;
    }
    
    const node* maximum() const {
        if (root == nullptr) 
            return nullptr;
        
        node* x = root.get();
        while(x->right != nullptr)
            x = x->right;
        return x;
    }
     
    const node* successor(const key_t& key) const {
        
        node* x = root.get();

        while (x != nullptr) {
            if (key > x->key) {
                x = x->right;
            } else if (key < x->key) {
                x = x->left;
            } else {
            if (x->right != nullptr) {
                x = x->right;
                while(x->left != nullptr) 
                    x = x->left;
                return x;
            }

            node* parent = x->parent;
            while (parent != nullptr && x == parent->right) {
                x = parent;
                parent = parent->parent;
            }

            return parent;
            }
        }
        return nullptr;
    }
    
    const node* predecessor(const key_t& key) const {
        
        node* x = root.get();

        while (x != nullptr) {
            if (key > x->key) {
                x = x->right;
            } else if (key < x->key) {
                x = x->left;
            } else {
                if (x->left != nullptr) {
                    x = x->left;
                    while(x->right != nullptr) 
                        x = x->right;
                    
                    return x;
                }

                node* parent = x->parent;
                while (parent != nullptr && x == parent->left) {
                    x = parent;
                    parent = parent->parent;
                }

                return parent;
            }
        }
        return nullptr;
    }

    const unsigned long long height() const {
        return height(root.get());
    }

    const unsigned long long size() const {
        return size(root.get());
    }

    const bool isEmpty() const {
        return (root == nullptr);
    }
};