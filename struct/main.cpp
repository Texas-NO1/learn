#include "rb-tree.hpp"
#include <iostream>
#include <queue>
#include <cassert>
#include <map>
#include <unordered_set>

//     1
// 0       2
//             5 
//           4      
void output(RB_Node *root) {
    std::queue<RB_Node*> que;
    que.push(root);
    while (!que.empty()) {
        std::queue<RB_Node*> temp;
        while (!que.empty()) {
            auto cur = que.front();
            que.pop();
            if (cur == RB_Tree::nil) {
                std::cout << "(" << (cur->color == RB_Node::BLACK ? "B_" : "R_") << "nil) ";
                continue;
            }
            std::cout << (cur->color == RB_Node::BLACK ? "B_" : "R_") << cur->key << ",";
            temp.push(cur->left);
            temp.push(cur->right);
        }
        que.swap(temp);
        std::cout << std::endl;
    }
}

int check_bh(RB_Node *root) {
    if (root == RB_Tree::nil) return 1;
    int lbh = check_bh(root->left);
    int rbh = check_bh(root->right);
    if (lbh != rbh) {
        std::cout << lbh << "!=" << rbh << std::endl;
        output(root);
    }
    assert(lbh == rbh);
    return lbh + (root->color == RB_Node::BLACK ? 1 : 0);
}

bool check_color(RB_Node *root) {
    if (root == RB_Tree::nil) return true;
    bool lcolor = check_color(root->left);
    bool rcolor = check_color(root->right);
    bool cur_color = false;
    switch (root->color) {
        case RB_Node::BLACK : cur_color = true; break;
        case RB_Node::RED : cur_color = true; break;
        default: cur_color == false; break;
    }
    assert(lcolor && rcolor && cur_color);
    return lcolor && rcolor && cur_color;
}

bool check_has_near_red_node(RB_Node *root) {
    if (root == RB_Tree::nil) return false;
    bool lcolor = check_color(root->left);
    bool rcolor = check_color(root->right);
    bool is_red_node = (root->color == RB_Node::RED);
    bool has_red_child = false;
    if (root->left != RB_Tree::nil && root->left->color == RB_Node::RED) has_red_child = true;
    if (root->right != RB_Tree::nil && root->right->color == RB_Node::RED) has_red_child = true;
    assert(!(is_red_node && has_red_child));
    return is_red_node && has_red_child && lcolor && rcolor;
}

bool check_is_rb_tree(RB_Tree &t) {
    RB_Node *root = t.root;
    check_color(root); // 性质1
    assert(root->color == RB_Node::BLACK); // 性质2
    assert(RB_Tree::nil->color == RB_Node::BLACK); // 性质3
    check_has_near_red_node(root); // 性质4
    check_bh(root); // 性质5
}

int main () {
    RB_Tree::init_nil();
    int max = 100000;
    std::vector<int> all_items;
    RB_Tree t;
    for (int i = 0; i < 1000; ++i) {
        int x = rand() % max + 1;
        t.insert(x);
        all_items.push_back(x);
    }
    // output(t);
    check_is_rb_tree(t);

    // delete check
    // output(t.root);

    for (auto i : all_items) {
        // std::cout << "----org---" << std::endl;
        // output(t.search(i));
        t.remove(i);
        // std::cout << "----remove---" << std::endl;
        // output(new_y);
        check_is_rb_tree(t);
    }
    output(t.root);
    check_is_rb_tree(t);
    return 0;
}