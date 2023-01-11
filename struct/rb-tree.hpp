#include <iostream>
#include <cassert>

struct RB_Node {
    enum RB_COLOR{RED, BLACK};
    RB_COLOR color;
    int key; // TODO template
    RB_Node *left, *right, *p;
    RB_Node(const int &key, RB_COLOR color, RB_Node *left, RB_Node *right, RB_Node *p) : 
        key(key),
        color(color),
        left(left),
        right(right),
        p(p) {}
};

class RB_Tree {
private:
    static RB_Node *create_node(const int &key) {
        return new RB_Node(key, RB_Node::RED, nil, nil, nil);
    }

    RB_Node *search(RB_Node* node, const int &key) {
        if (node == nil || node->key == key) return node;
        if (key < node->key) return search(node->left, key);
        else return search(node->right, key);
    }

    RB_Node *min(RB_Node* node) {
        while (node->left != nil) node = node->left;
        return node;
    }

    RB_Node *max(RB_Node* node) {
        while (node->right != nil) node = node->right;
        return node;
    }

    void left_rotate(RB_Node* node) {
        RB_Node* temp = node->right;
        node->right = temp->left;
        if (temp->left != nil) 
            temp->left->p = node;
        temp->p = node->p;
        if (node->p == nil) 
            root = temp;
        else if (node == node->p->left) 
            node->p->left = temp;
        else 
            node->p->right = temp;
        temp->left = node;
        node->p = temp;
    }

    void right_rotate(RB_Node* node) {
        RB_Node* temp = node->left;
        node->left = temp->right;
        if (temp->right != nil) 
            temp->right->p = node;
        temp->p = node->p;
        if (node->p == nil) 
            root = temp;
        else if (node == node->p->left) 
            node->p->left = temp;
        else 
            node->p->right = temp;
        temp->right = node;
        node->p = temp;
    }

    void insert_fixup(RB_Node *node) {
        while (node->p->color == RB_Node::RED) {
            if (node->p == node->p->p->left) {
                RB_Node *uncle = node->p->p->right;
                if (uncle->color == RB_Node::RED) {
                    node->p->p->color = RB_Node::RED;
                    node->p->p->left->color = node->p->p->right->color = RB_Node::BLACK;
                    node = node->p->p;
                } else {
                    if (node == node->p->right) {
                        node = node->p;
                        left_rotate(node);
                    }
                    node->p->color = RB_Node::BLACK;
                    node->p->p->color = RB_Node::RED;
                    right_rotate(node->p->p);
                }
            } else {
                RB_Node *uncle = node->p->p->left;
                if (uncle->color == RB_Node::RED) {
                    node->p->p->color = RB_Node::RED;
                    node->p->p->left->color = node->p->p->right->color = RB_Node::BLACK;
                    node = node->p->p;
                } else {
                    if (node == node->p->left) {
                        node = node->p;
                        right_rotate(node);
                    }
                    node->p->color = RB_Node::BLACK;
                    node->p->p->color = RB_Node::RED;
                    left_rotate(node->p->p);
                }
            }
        }
        root->color = RB_Node::BLACK;
    }

    void transplant(RB_Node *u, RB_Node *v) {
        if (u->p == nil) {
            root = v;
        } else if (u->p->left == u) {
            u->p->left = v;
        } else {
            u->p->right = v;
        }
        v->p = u->p;
    }

    void remove_fixup(RB_Node *x) {
        RB_Node *w = nil;
        while ((x != root) && (x->color == RB_Node::BLACK)) {
            if (x == x->p->left) {
                w = x->p->right;
                if (w->color == RB_Node::RED) {
                    w->color = RB_Node::BLACK;
                    x->p->color = RB_Node::RED;
                    left_rotate(x->p);
                    w = x->p->right;
                }
                if (w->left->color == RB_Node::BLACK && w->right->color == RB_Node::BLACK) { // 如果x->p为红怎么办
                    w->color = RB_Node::RED;
                    x = x->p;
                } else {
                    if (w->right->color == RB_Node::BLACK) {
                        w->left->color = RB_Node::BLACK;
                        w->color = RB_Node::RED;
                        right_rotate(w);
                        w = x->p->right;
                    }
                    w->color = x->p->color;
                    x->p->color = RB_Node::BLACK;
                    w->right->color = RB_Node::BLACK;
                    left_rotate(x->p);
                    x = root;
                }
            } else {
                w = x->p->left;
                if (w->color == RB_Node::RED) {
                    w->color = RB_Node::BLACK;
                    x->p->color = RB_Node::RED;
                    right_rotate(x->p);
                    w = x->p->left;
                }
                if (w->left->color == RB_Node::BLACK && w->right->color == RB_Node::BLACK) { // 如果x->p为红怎么办
                    w->color = RB_Node::RED;
                    x = x->p;
                } else {
                    if (w->left->color == RB_Node::BLACK) {
                        w->right->color = RB_Node::BLACK;
                        w->color = RB_Node::RED;
                        left_rotate(w);
                        w = x->p->left;
                    }
                    w->color = x->p->color;
                    x->p->color = RB_Node::BLACK;
                    w->left->color = RB_Node::BLACK;
                    right_rotate(x->p);
                    x = root;
                }
            }
        }
        x->color = RB_Node::BLACK;
    }

public:
    static RB_Node *nil;
    RB_Node *root;
    RB_Tree () {
        root = nil;
    }
    ~RB_Tree() {
        // TODO
    }

    RB_Node *search(int key) {
        // 递归版
        // return search(root, key);

        // 迭代版
        RB_Node *temp = root;
        while (temp != nil && temp->key != key) {
            if (key < temp->key) temp = temp->left;
            else temp = temp->right;
        }
        return temp;
    }

    RB_Node *min() {
        return min(root);
    }

    RB_Node *max() {
        return max(root);
    }

    void insert(int key) {
        RB_Node *y = nil;
        RB_Node *x = root;
        RB_Node *z = create_node(key);
        while (x != nil) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->p = y;
        if (y == nil) {
            root = z;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
        // std::cout << "cur key " << z->key << ", p " << z->p->key << "'s " << (z == z->p->left ? "L" : "R") << std::endl;
        insert_fixup(z);
    }

    void remove(int key) {
        // std::cout << "remove " << key << std::endl;
        RB_Node *z = root;
        while (z->key != key && z != nil) {
            if (key < z->key) {
                z = z->left;
            } else if (key > z->key) {
                z = z->right;
            }
        }
        if (z == nil) return;

        RB_Node *x = nil;
        RB_Node *y = z;
        RB_Node::RB_COLOR y_org = y->color;
        if (z->left == nil) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = min(z->right);
            y_org = y->color;
            x = y->right;
            if (y->p == z) {
                x->p = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->p = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->p = y;
            y->color = z->color;
        }
        // std::cout << "y " << y->key << ", x " << x->key << std::endl;
        // std::cout << "remove " << z->key << ", to fixup " << x->key << " isnil=" << (x == nil) << std::endl;
        // std::cout << "x->p " << x->p->key << ", x->p->p " << x->p->p->key << std::endl; 
        if (y_org == RB_Node::BLACK) {
            remove_fixup(x);
        }
        // std::cout << "remove " << z->key << " over" << std::endl;
    }
    
    static void init_nil() {
        nil->left = nil->right = nil->p = nil;
    }
};

RB_Node *RB_Tree::nil = new RB_Node(0, RB_Node::BLACK, nullptr, nullptr, nullptr);