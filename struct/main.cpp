#include "rb-tree.hpp"
#include <iostream>
#include <queue>
#include <cassert>

//     1
// 0       2
//             5 
//           4      
    

int main () {
    RB_Tree t;
    t.insert(2);
    t.insert(0);
    t.insert(1);
    t.insert(5);
    t.insert(4);
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
            std::cout << "(" << cur->key << "," << (cur->color == RB_Node::BLACK ? "B" : "R") << ") ";
            temp.push(cur->left);
            temp.push(cur->right);
        }
        que.swap(temp);
        std::cout << std::endl;
    }
    return 0;
}