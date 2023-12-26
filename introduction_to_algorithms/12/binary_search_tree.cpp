#include <iostream>

struct Node {
    int val;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    Node() {}
    Node(int key) : val(key) {}
};

struct Tree {
    Node *root = nullptr;
};

void walk(Node* root) {
    if (root == nullptr) return;
    walk(root->left);
    std::cout << root->val << ",";
    walk(root->right);
}

// 递归方式
Node* search(Node *root, int key) {
    if (root == nullptr || root->val == key) return root;
    if (key < root->val) {
        return search(root->left, key);
    } else return search(root->right, key);
}
// 非递归方式
Node* search_loop(Node *root, int key) {
    while (root && root->val != key) {
        if (key < root->val) root = root->left;
        else root = root->right;
    }
    return root;
}

// 对于所有节点而言其左子树全<=自身
Node* min_node(Node *root) {
    while (root->left) root = root->left;
    return root;
}

// 对于所有节点而言其右子树全>=自身
Node* max_node(Node *root) {
    while (root->right) root = root->right;
    return root;
}

// 递归版本
Node* min_node_recursion(Node *root) {
    if (root->left == nullptr) return root;
    return min_node_recursion(root->left);
}

Node* max_node_recursion(Node *root) {
    if (root->right == nullptr) return root;
    return max_node_recursion(root->right);
}

// 后继节点，即第一个大于自身的节点
// 如果有右子树，则后继节点是右子树最小节点
// 如果没有右子树，则后继节点是最底层祖先（自身为右子树，向上找到第一个不为右子树的祖先即为后继节点）
// 例如：下图中6的后继为8，8的后继为10
//         15
//     10
//  4
//    6
//      8
Node* successor(Node *node) {
    if (node->right) return min_node(node->right);
    Node *y = node->parent;
    while ((y != nullptr) && (node == y->right)) {
        node = y;
        y = node->parent;
    }
    return y;
}

// 与successor对称
Node* predecessor(Node *node) {
    if (node->left) return max_node(node->left);
    Node *y = node->parent;
    while (y != nullptr && node == y->left) {
        node = y;
        y = node->parent;
    } 
    return y;
}

void output_node(Node* node) {
    if (node == nullptr) std::cout << "NULL" << std::endl;
    else std::cout << node->val << std::endl;
}



void tree_insert(Tree &t, Node* z) {
    // 记录父节点
    Node *y = nullptr;
    // 记录当前节点
    Node *x = t.root;
    // 遍历到空节点表示找到了目标位置
    while (x != nullptr) {
        y = x;
        if (z->val < x->val) x = x->left;
        else x = x->right;
    }
    // 树为空
    if (y == nullptr) t.root = z;
    else if (z->val < y->val) y->left = z;
    else y->right = z;
    z->parent = y;
}

// 用target树替换pick子树
// 执行后pick子树将从树上摘下来，将target接到pick的位置
// 仅修改target的父节点与target的关系
void transplant(Tree &t, Node *pick, Node *target) {
    if (pick->parent == nullptr) t.root = target;
    else if (pick == pick->parent->left) pick->parent->left = target;
    else pick->parent->right = target;
    if (target != nullptr) target->parent = pick->parent;
}

void tree_delete(Tree &t, Node *z) {
    // 左子树为空，或两个子树都为空。将右子树移动到目标位置
    if (z->left == nullptr) transplant(t, z, z->right);
    // 左子树不为空且右子树为空。将左子树移动到目标位置
    else if (z->right == nullptr) transplant(t, z, z->left);
    // 两棵子树都不为空，需要找到z的后继节点，将其从原本位置摘下来后，再放到当前位置
    else {
        Node *y = min_node(z->right);
        // y不为z的右孩子，则需要先将y的右子树放到y的位置取下y
        if (y->parent != z) {
            // y的左子树为空，下一步补充，右子树赋值为z的右子树
            transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        // 将y放到z位置后只需要将z的左子树给y
        transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

int main() {
    // 2,4,5,6,7,8
    Node *root = nullptr;
    {
        // Node方式
        root = new Node(6);
        root->left = new Node(4);
        root->left->parent = root;
        root->left->left = new Node(2);
        root->left->left->parent = root->left;
        root->left->right = new Node(5);
        root->left->right->parent = root->left;
        root->right = new Node(7);
        root->right->parent = root;
        root->right->right = new Node(8);
        root->right->right->parent = root->right;
    }
    Tree t;
    {
        //Tree insert 方式
        tree_insert(t, new Node(6));
        tree_insert(t, new Node(4));
        tree_insert(t, new Node(2));
        tree_insert(t, new Node(5));
        tree_insert(t, new Node(7));
        tree_insert(t, new Node(8));
        root = t.root;
    }
    walk(root);
    std::cout << std::endl;
    Node* node = nullptr;
    node = search(root, 8);
    output_node(node);
    node = search(root, 3);
    output_node(node);
    node = search_loop(root, 8);
    output_node(node);
    node = search_loop(root, 3);
    output_node(node);
    std::cout << "min: ";
    output_node(min_node(root));
    std::cout << "max: ";
    output_node(max_node(root));
    std::cout << "min_rec: ";
    output_node(min_node(root));
    std::cout << "max_rec: ";
    output_node(max_node(root));
    std::cout << root->left->left->val << " successor: ";
    output_node(successor(root->left->left));
    std::cout << root->left->val << " successor: ";
    output_node(successor(root->left));
    std::cout << root->left->right->val << " successor: ";
    output_node(successor(root->left->right));
    std::cout << root->right->val << " successor: ";
    output_node(successor(root->right));
    std::cout << root->right->right->val << " successor: ";
    output_node(successor(root->right->right));


    std::cout << root->left->left->val << " predecessor: ";
    output_node(predecessor(root->left->left));
    std::cout << root->left->val << " predecessor: ";
    output_node(predecessor(root->left));
    std::cout << root->left->right->val << " predecessor: ";
    output_node(predecessor(root->left->right));
    std::cout << root->right->val << " predecessor: ";
    output_node(predecessor(root->right));
    std::cout << root->right->right->val << " predecessor: ";
    output_node(predecessor(root->right->right));

    {
        // 不断删除节点
        while (t.root != nullptr) {
            std::cout << "remove " << t.root->val << std::endl;
            tree_delete(t, t.root);
        }
    }
    return 0;
}