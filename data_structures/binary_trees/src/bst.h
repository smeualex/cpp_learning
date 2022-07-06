#include <algorithm>
#include <queue>
#include <memory>

// binary search tree
// https://codereview.stackexchange.com/questions/191211/binary-search-tree-data-structure-implementation-in-c11-using-smart-pointers

template <typename key_t>
class BST {
private:

    template <typename key_t>
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

    std::shared_ptr<node <key_t> > root;
    
    void pre_order_traversal(const std::shared_ptr<node <key_t> > &x, void handler(std::shared_ptr<node <key_t> >)) const {
        if (x == nullptr) 
            return;
        
        handler(x);
        
        pre_order_traversal(x->left, handler);
        pre_order_traversal(x->right, handler);
    }
    void in_order_traversal(const std::shared_ptr<node <key_t> > &x, void handler(std::shared_ptr<node <key_t> >)) const{
        if (x == nullptr) 
            return;
        
        in_order_traversal(x->left, handler);
        
        handler(x);
        
        in_order_traversal(x->right, handler);
    }
    void post_order_traversal(const std::shared_ptr<node <key_t> > &x, void handler(std::shared_ptr<node <key_t> >)) const {
        if (x == nullptr) 
            return;
        
        post_order_traversal(x->left, handler);
        post_order_traversal(x->right, handler);
        
        handler(x);
    }

    void breadth_first_traversal(const std::shared_ptr<node <key_t> > &x, void handler(std::shared_ptr<node <key_t> >)) const {
        if (x == nullptr) 
            return;
        
        std::queue <std::shared_ptr<node <key_t> > > queue;
        
        queue.push(x);
        while(queue.empty() == false) {
            std::shared_ptr<node <key_t> > y = queue.front();
            handler(y);
            queue.pop();
            
            if (y->left != nullptr)
                queue.push(y->left);
            if (y->right != nullptr)
                queue.push(y->right);
        }
    }

    const unsigned long long height(const std::shared_ptr<node <key_t> > &x) const {
        if (x == nullptr)   
            return 0;
        return std::max(height(x->left), height(x->right)) + 1;
    }

    const unsigned long long size(const std::shared_ptr<node <key_t> > &x) const {
        if (x == nullptr) 
            return 0;
        return size(x->left) + size(x->right) + 1;
    }

public:

    void pre_order_traversal(void handler(std::shared_ptr<node <key_t> >)) const {
        pre_order_traversal(root, handler);
    }
    
    void in_order_traversal(void handler(std::shared_ptr<node <key_t> >)) const {
        in_order_traversal(root, handler);
    }

    void post_order_traversal(void handler(std::shared_ptr<node <key_t> >)) const {
        post_order_traversal(root, handler);
    }

    void breadth_first_traversal(void handler(std::shared_ptr<node <key_t> >)) const {
        breadth_first_traversal(root, handler);
    }

    const std::shared_ptr<node <key_t> > insert(const key_t key) {
        std::shared_ptr<node <key_t> > current = root;
        std::shared_ptr<node <key_t> > parent = nullptr;

        while(current!=nullptr) {
            parent = current;
            if (key > current->key) {
                current = current->right;
            } else if (key < current->key) {
                current = current->left;
            } else {
                return nullptr;
            }
        }
        
        current = std::make_shared<node <key_t> >(key);
        current->parent = parent;
        
        if(parent == nullptr) {
            root = current;
        } else if (current->key > parent->key) {
            parent->right = current;
        } else if (current->key < parent->key) {
            parent->left = current;
        }
        return current;
    }
   
    const std::shared_ptr<node <key_t> > search(const key_t key) const {
        std::shared_ptr<node <key_t> > x = root;
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
    
    const std::shared_ptr<node <key_t> > minimum() const {
        if (x == nullptr) 
            return nullptr;

        std::shared_ptr<node <key_t> > x = root;
        while(x->left != nullptr) 
            x = x->left;
        return x;
    }
    
    const std::shared_ptr<node <key_t> > maximum() const {
        if (x == nullptr) 
            return nullptr;
        
        std::shared_ptr<node <key_t> > x = root;
        while(x->right != nullptr)
            x = x->right;
        return x;
    }
     
    const std::shared_ptr<node <key_t> > successor(const key_t key) const {
        std::shared_ptr<node <key_t> > x = root;
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

            std::shared_ptr<node <key_t> > parent = x->parent.lock();
            while (parent != nullptr && x == parent->right) {
                x = parent;
                parent = parent->parent.lock();
            }

            return parent;
            }
        }
        return nullptr;
    }
    
    const std::shared_ptr<node <key_t> > predecessor(const key_t key) const {
        std::shared_ptr<node <key_t> > x = root;
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

                std::shared_ptr<node <key_t> > parent = x->parent.lock();
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