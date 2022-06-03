#include <iostream>
#include "set.h"

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
