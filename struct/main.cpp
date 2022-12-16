#include "rb-tree.hpp"
#include <iostream>
#include <queue>
#include <cassert>

//     1
// 0       2
//             5 
//           4      
    

int check_bh(RB_Node *root) {
    if (root == RB_Tree::nil) return 1;
    int lbh = check_bh(root->left);
    int rbh = check_bh(root->right);
    assert(lbh == rbh);
    return std::max(lbh, rbh) + (root->color == RB_Node::BLACK ? 1 : 0);
}

int main () {
    RB_Tree t;
    for (int i = 0; i < 1000; ++i) {
        t.insert(rand() % 1000);
    }
    std::queue<RB_Node*> que;
    que.push(t.root);
    while (!que.empty()) {
        std::queue<RB_Node*> temp;
        while (!que.empty()) {
            auto cur = que.front();
            que.pop();
            if (cur == RB_Tree::nil) {
                std::cout << "(nil) ";
                continue;
            }
            if (cur->color == RB_Node::RED)
            assert(cur->color != cur->p->color);
            std::cout << (cur->color == RB_Node::BLACK ? "B_" : "R_") << cur->key << ",";
            temp.push(cur->left);
            temp.push(cur->right);
        }
        que.swap(temp);
        std::cout << std::endl;
    }
    check_bh(t.root);
    return 0;
}