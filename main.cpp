#include <iostream>
#include "set.h"

int main() {
    BinarySearchTree<int, std::string> BST;

    BST.insert(16, "hello16");
    BST.insert(18, "hello18");
    BST.insert(17, "hello17");
    BST.insert(21, "hello2");
    BST.insert(19, "hello19");
    BST.insert(20, "hello20");
    BST.insert(18, "hello181");
    BST.erase(18);

    std::cout << BST.size();

    auto [st, sp] = BST.equalRange(21);

    for (; st != sp; ++st) {
        std::cout << st->second << ", ";
    }

    auto it = BST.min(20);
    auto mit = BST.max(20);

    std::cout << it->second << std::endl;
    std::cout << mit->second;

    Map<int, std::string> map;
    map.insert(15, "hello");
    map.insert(16, "world");
    std::cout << map[15] << std::endl;
    std::cout << map[6] << std::endl;
    std::cout << map.size() << std::endl;
    map.erase(15);
    std::cout << map[15] << std::endl;
    std::cout << map[16] << std::endl;
    Map<int, bool> map1;
    std::cout << map1[16] << std::endl;

    Set<int> set;
    std::cout << set.contains(20) << std::endl;
    set.insert(20);
    std::cout << set.contains(20) << std::endl;
    return 0;
}
