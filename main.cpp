#include <iostream>
#include "BinarySearchTree.h"

int main() {
    BinarySearchTree<int, std::string> BST;

    BST.insert(22, "huy");
    BST.insert(21, "21c");
    BST.insert(21, "21");
    BST.insert(16, "hell16");
    BST.insert(18, "hell18");
    BST.insert(17, "hell17");
    BST.insert(21, "hell2");
    BST.insert(19, "hell19");
    BST.insert(20, "hell20");
    BST.erase(21);

    std::cout << BST.size();

    auto [st, sp] = BST.equalRange(21);

    for (; st != sp; ++st) {
        std::cout << st->second << ", ";
    }

    auto it = BST.min(20);
    auto mit = BST.max(20);

    std::cout << it->second << std::endl;
    std::cout << mit->second;

    return 0;
}
