#pragma once

#include <algorithm>
#include <queue>
#include <memory>
#include <functional>

// binary search tree
// https://codereview.stackexchange.com/questions/191211/binary-search-tree-data-structure-implementation-in-c11-using-smart-pointers


template <typename key_t>
class BST {
private:

    struct node {
        key_t key;                  
        std::weak_ptr<node> parent; 
        std::shared_ptr<node> left; 
        std::shared_ptr<node> right;

        node(const key_t key) {
            this->key = key;
            this->parent.reset();
            this->left = nullptr;
            this->right = nullptr;
        }
    };

    std::shared_ptr<node> root;
    
    typedef std::function< void(const key_t&) > traversal_handler;

    void pre_order_traversal(const std::shared_ptr<node>& x, traversal_handler handler) const {
        if (x == nullptr)
            return;

        handler(x->key);

        pre_order_traversal(x->left, handler);
        pre_order_traversal(x->right, handler);
    }

    void in_order_traversal(const std::shared_ptr<node> &x, traversal_handler handler) const{
        if (x == nullptr) 
            return;
        
        in_order_traversal(x->left, handler);
        
        handler(x->key);
        
        in_order_traversal(x->right, handler);
    }

    void post_order_traversal(const std::shared_ptr<node> &x, traversal_handler handler) const {
        if (x == nullptr) 
            return;
        
        post_order_traversal(x->left, handler);
        post_order_traversal(x->right, handler);
        
        handler(x->key);
    }

    void breadth_first_traversal(const std::shared_ptr<node> &x, traversal_handler handler) const {
        if (x == nullptr) 
            return;
        
        std::queue <std::shared_ptr<node> > queue;
        
        queue.push(x);
        while(queue.empty() == false) {
            std::shared_ptr<node> y = queue.front();
            handler(y);
            queue.pop();
            
            if (y->left != nullptr)
                queue.push(y->left);
            if (y->right != nullptr)
                queue.push(y->right);
        }
    }

    const unsigned long long height(const std::shared_ptr<node> &x) const {
        if (x == nullptr)   
            return 0;
        return std::max(height(x->left), height(x->right)) + 1;
    }

    const unsigned long long size(const std::shared_ptr<node> &x) const {
        if (x == nullptr) 
            return 0;
        return size(x->left) + size(x->right) + 1;
    }

public:

    void pre_order_traversal(traversal_handler handler) const {
        pre_order_traversal(root, handler);
    }

    void in_order_traversal(traversal_handler handler) const {
        in_order_traversal(root, handler);
    }

    void post_order_traversal(traversal_handler handler) const {
        post_order_traversal(root, handler);
    }

    void breadth_first_traversal(traversal_handler handler) const {
        breadth_first_traversal(root, handler);
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

        std::shared_ptr<node> current = root;
        std::shared_ptr<node> parent = nullptr;

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
        current = std::make_shared<node>(key);
        current->parent = parent;
        
        // set up parent link to the current node
        if(parent == nullptr) {
            root = current;
        } else if (current->key > parent->key) {
            parent->right = current;
        } else if (current->key < parent->key) {
            parent->left = current;
        }

        return true;
    }
   
    const std::shared_ptr<node> search(const key_t key) const {
        std::shared_ptr<node> x = root;
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
    
    const std::shared_ptr<node> minimum() const {
        if (x == nullptr) 
            return nullptr;

        std::shared_ptr<node> x = root;
        while(x->left != nullptr) 
            x = x->left;
        return x;
    }
    
    const std::shared_ptr<node> maximum() const {
        if (x == nullptr) 
            return nullptr;
        
        std::shared_ptr<node> x = root;
        while(x->right != nullptr)
            x = x->right;
        return x;
    }
     
    const std::shared_ptr<node> successor(const key_t key) const {
        std::shared_ptr<node> x = root;
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

            std::shared_ptr<node> parent = x->parent.lock();
            while (parent != nullptr && x == parent->right) {
                x = parent;
                parent = parent->parent.lock();
            }

            return parent;
            }
        }
        return nullptr;
    }
    
    const std::shared_ptr<node> predecessor(const key_t key) const {
        std::shared_ptr<node> x = root;
        while (x != nullptr) {
            if (key > x->key) {
                x = x->right;
            } else if (key < x->key) {
                x = x->left;
            } else {
                if (x->left != nullptr) {
                    x = x->left;
                    while(x->right != nullptr) x = x->right;
                    return x;
                }

                std::shared_ptr<node> parent = x->parent.lock();
                while (parent != nullptr && x == parent->left) {
                    x = parent;
                    parent = parent->parent.lock();
                }
                return parent;
            }
        }
        return nullptr;
    }

    const unsigned long long height() const {
        return height(root);
    }

    const unsigned long long size() const {
        return size(root);
    }

    const bool empty() const {
        return (root == nullptr);
    }
};