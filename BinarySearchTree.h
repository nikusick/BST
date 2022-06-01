#pragma once

#include <utility>
#include <queue>

/*!
    Имплементация бинарного дерева поиска
    Допускается дублирование ключей (аналог multimap)
*/
template <typename Key, typename Value>
class BinarySearchTree
{
    struct Node
    {
        Node(Key key,
             Value value,
             Node* parent = nullptr,
             Node* left = nullptr,
             Node* right = nullptr): _keyValuePair(std::make_pair(key, value)), _parent(parent), _left(left), _right(right) {
        }

        std::pair<Key, Value> _keyValuePair;
        Node* _parent = nullptr;
        Node* _left = nullptr;
        Node* _right = nullptr;
    };

    void remove(const Key &key, Node* node) {
        if (node == nullptr)  {
            return;
        }
        if (key > node->_keyValuePair.first) {
            remove(key, node->_right);
        }
        else if (key < node->_keyValuePair.first) {
            remove(key, node->_left);
        }
        else {
            if (node->_left == nullptr && node->_right == nullptr) {
                if (node->_parent->_left == node) {
                    node->_parent->_left = nullptr;
                }
                else {
                    node->_parent->_right = nullptr;
                }
                delete node;
                _size--;
            }
            else if (node->_left == nullptr) {
                Node* right = node->_right;
                node->_keyValuePair = right->_keyValuePair;
                node->_left = right->_left;
                node->_right = right->_right;
                if (node->_right != nullptr) {
                    node->_right->_parent = node;
                }
                if (node->_left != nullptr) {
                    node->_left->_parent = node;
                }
                delete right;
                _size--;
            }
            else if (node->_right == nullptr){
                Node* left = node->_left;
                node->_keyValuePair = left->_keyValuePair;
                node->_left = left->_left;
                node->_right = left->_right;
                if (node->_right != nullptr) {
                    node->_right->_parent = node;
                }
                if (node->_left != nullptr) {
                    node->_left->_parent = node;
                }
                delete left;
                _size--;
            }
            else {
                if (node->_right->_left == nullptr) {
                    node->_keyValuePair = node->_right->_keyValuePair;
                    Node* newNode = node->_right->_right;
                    delete node->_right;
                    node->_right = newNode;
                    _size--;
                }
                else {
                    Node* minNode(node->_right);
                    while (minNode->_left != nullptr) {
                        minNode = minNode->_left;
                    }
                    node->_keyValuePair = minNode->_keyValuePair;
                    remove(minNode->_keyValuePair.first, minNode);
                }
            }
        }
    }

public:
    BinarySearchTree() = default;

    explicit BinarySearchTree(const BinarySearchTree& other) {
        if (other._root != nullptr) {
            std::queue<Node*> children;
            children.push(other._root);
            while (!children.empty()) {
                Node* curNode = children.front();
                insert(curNode->_keyValuePair);
                _size++;
                if (curNode->left != nullptr) {
                    children.push(curNode->_left);
                }
                if (curNode->right != nullptr) {
                    children.push(curNode->_right);
                }
                children.pop();
            }
        }
    }
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this != other) {
            BinarySearchTree newBST(other);
            *this = std::move(newBST);
        }
        return *this;
    }

    explicit BinarySearchTree(BinarySearchTree&& other) noexcept {
        std::swap(_root, other._root);
        std::swap(_size, other._size);
    }
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        if (this != other) {
            delete _root;
            _root = nullptr;
            _size = 0;
            std::swap(_root, other._root);
            std::swap(_size, other._size);
        }
        return *this;
    }

    ~BinarySearchTree() {
        if (_root != nullptr) {
        std::queue<Node*> children;
        children.push(_root);
        while (!children.empty()) {
            Node* curNode = children.front();
            if (curNode->_left != nullptr) {
                children.push(curNode->_left);
            }
            if (curNode->_right != nullptr) {
                children.push(curNode->_right);
            }
            delete curNode;
            children.pop();
        }
    }
    _size = 0;
}

    class Iterator
    {
    public:
        explicit Iterator(Node* node): _node(node) {
        }

        std::pair<Key, Value>& operator*() {
            return _node->_keyValuePair;
        }
        const std::pair<Key, Value>& operator*() const {
            return _node->_keyValuePair;
        }

        std::pair<Key, Value>* operator->() {
            return &_node->_keyValuePair;
        }
        const std::pair<Key, Value>* operator->() const {
            return &_node->_keyValuePair;
        }

        Iterator operator++() {
            if (_node == nullptr) {
                return *this;
            }
            if (_node->_right != nullptr) {
                _node = _node->_right;
                while (_node->_left != nullptr) {
                    _node = _node->_left;
                }
            } else {
                while (_node->_parent != nullptr && _node->_parent->_right == _node) {
                    _node = _node->_parent;
                }
                _node = _node->_parent;
            }
            return *this;
        }
        Iterator operator++(int) {
            Iterator parent = *this;
            ++(*this);
            return parent;
        }

        Iterator operator--() {
            if (_node == nullptr) {
                return *this;
            }
            if (_node->_left != nullptr) {
                _node = _node->_left;
                while (_node->_right != nullptr) {
                    _node = _node->_right;
                }
            } else {
                while (_node->_parent != nullptr && _node->_parent->_left == _node) {
                    _node = _node->_parent;
                }
                _node = _node->_parent;
            }
            return *this;
        }
        Iterator operator--(int) {
            Iterator parent = *this;
            --(*this);
            return parent;
        }

        bool operator==(const Iterator& other) const {
            return _node == other._node;
        }

        bool operator!=(const Iterator& other) const {
            return _node != other._node;
        }

    private:
        Node* _node;
    };

    class ConstIterator
    {
    public:
        explicit ConstIterator(const Node* node): _node(node) {
        }

        const std::pair<Key, Value>& operator*() const {
            return _node->_keyValuePair;
        }
        const std::pair<Key, Value>* operator->() const {
            return &_node->_keyValuePair;
        }

        ConstIterator operator++() {
            if (_node == nullptr) {
                return *this;
            }
            if (_node->_right != nullptr) {
                _node = _node->_right;
                while (_node->_left != nullptr) {
                    _node = _node->_left;
                }
            } else {
                while (_node->_parent != nullptr && _node->_parent->_right == _node) {
                    _node = _node->_parent;
                }
                _node = _node->_parent;
            }
            return *this;
        }
        ConstIterator operator++(int) {
            ConstIterator parent = *this;
            ++(*this);
            return parent;
        }

        ConstIterator operator--() {
            if (_node == nullptr) {
                return *this;
            }
            if (_node->_left != nullptr) {
                _node = _node->_left;
                while (_node->_right != nullptr) {
                    _node = _node->_right;
                }
            } else {
                while (_node->_parent != nullptr && _node->_parent->_left == _node) {
                    _node = _node->_parent;
                }
                _node = _node->_parent;
            }
            return *this;
        }
        ConstIterator operator--(int) {
            ConstIterator parent = *this;
            --(*this);
            return parent;
        }

        bool operator==(const ConstIterator& other) const {
            return _node == other._node;
        }
        bool operator!=(const ConstIterator& other) const {
            return _node != other._node;
        }

    private:
        const Node* _node;
    };

    void insert(const Key& key, const Value& value) {
        if (_root != nullptr) {
            Node* curNode = _root;
            Key curKey = curNode->_keyValuePair.first;
            while ((curKey >= key && curNode->_left != nullptr)
                   || (curKey < key && curNode->_right != nullptr)) {
                if (curKey >= key) {
                    curNode = curNode->_left;
                }
                else {
                    curNode = curNode->_right;
                }
                curKey = curNode->_keyValuePair.first;
            }
            if (curKey >= key) {
                curNode->_left = new Node(key, value, curNode);
            }
            else {
                curNode->_right = new Node(key, value, curNode);
            }
        }
        else {
            _root = new Node(key, value);
        }
        _size++;
    }

    void erase(const Key& key) {
        while (find(key) != end()) {
            remove(key, _root);
        }
    }

    ConstIterator find(const Key& key) const {
        Node* curNode = _root;
        while(curNode != nullptr) {
            if (curNode->_keyValuePair.first > key) {
                curNode = curNode->_left;
            }
            else if (curNode->_keyValuePair.first < key){
                curNode = curNode->_right;
            }
            else {
                break;
            }
        }
        return ConstIterator(curNode);
    }
    Iterator find(const Key& key) {
        Node* curNode = _root;
        while (curNode != nullptr) {
            if (curNode->_keyValuePair.first > key) {
                if (curNode->_left == nullptr) {
                    return Iterator(nullptr);
                }
                curNode = curNode->_left;
            }
            else if (curNode->_keyValuePair.first < key){
                if (curNode->_right == nullptr) {
                    return Iterator(nullptr);
                }
                curNode = curNode->_right;
            }
            else {
                break;
            }
        }
        return Iterator(curNode);
    }

    std::pair<Iterator, Iterator> equalRange(const Key& key) {
        Iterator start = find(key);
        Iterator stop(start);
        if (start == end()) {
            return std::make_pair(start, stop);
        }
        if (begin()->first == key) {
            return std::make_pair(begin(), ++stop);
        }
        while (start != begin() && start->first == key) {
            --start;
        }
        return std::make_pair(++start, ++stop);
    }
    std::pair<ConstIterator, ConstIterator> equalRange(const Key& key) const {
        ConstIterator start = find(key);
        ConstIterator stop(start);
        if (start == cend()) {
            return std::make_pair(start, stop);
        }
        if (cbegin()->first == key) {
            return std::make_pair(cbegin(), ++stop);
        }
        while (start != cbegin() && start->first == key) {
            --start;
        }
        return std::make_pair(++start, ++stop);
    }

    ConstIterator min(const Key& key) const {
        std::pair<ConstIterator, ConstIterator> keyValues = equalRange(key);
        ConstIterator minPairIterator = ConstIterator(keyValues.first);
        for (ConstIterator iterator = keyValues.first; iterator != keyValues.second; ++iterator) {
            if (iterator->second < minPairIterator->second) {
                minPairIterator = iterator;
            }
        }
        return minPairIterator;
    }
    ConstIterator max(const Key& key) const {
        std::pair<ConstIterator, ConstIterator> keyValues = equalRange(key);
        ConstIterator maxPairIterator = ConstIterator(keyValues.first);
        for (ConstIterator iterator = keyValues.first; iterator != keyValues.second; ++iterator) {
            if (iterator->second > maxPairIterator->second) {
                maxPairIterator = iterator;
            }
        }
        return maxPairIterator;
    }

    Iterator begin() {
        Node* curNode = _root;
        while  (curNode->_left != nullptr) {
            curNode = curNode->_left;
        }
        return BinarySearchTree::Iterator(curNode);
    }
    Iterator end() {
        return BinarySearchTree::Iterator(nullptr);
    }

    ConstIterator cbegin() const {
        Node* curNode = _root;
        while  (curNode->_left != nullptr) {
            curNode = curNode->_left;
        }
        return BinarySearchTree::ConstIterator(curNode);
    }
    ConstIterator cend() const {
        return BinarySearchTree::ConstIterator(nullptr);
    }

    std::size_t size() const {
        return _size;
    }

private:
    std::size_t _size = 0;
    Node* _root = nullptr; //!< корневой узел дерева
};

template <typename Key, typename Value>
class Map
{
    BinarySearchTree<Key, Value> _tree;
public:
    using MapIterator = typename BinarySearchTree<Key, Value>::Iterator;
    using ConstMapIterator = typename BinarySearchTree<Key, Value>::ConstIterator;

    Map() = default;

    explicit Map(const Map& other): _tree(other._tree){
    }
    Map& operator=(const Map& other) {
        Map newMap = Map(other);
        std::swap(newMap, *this);
        delete newMap;
        return *this;
    }

    explicit Map(Map&& other) noexcept {
        std::swap(_tree, other._tree);
    }
    Map& operator=(Map&& other) noexcept {
        std::swap(_tree, other._tree);
        return *this;
    }

    ~Map() = default;

    // вставить элемент с ключем key и значением value
    // если узел с ключем key уже представлен, то заменить его значение на value
    void insert(const Key& key, const Value& value) {
        if (find(key) != end()) {
            erase(key);
        }
        else
            _tree.insert(key, value);
    }

    // удалить элемент с ключем key
    void erase(const Key& key) {
        _tree.erase(key);
    }

    // найти элемент, равный ключу key
    ConstMapIterator find(const Key& key) const {
        return ConstMapIterator(_tree.find(key));
    }
    MapIterator find(const Key& key) {
        return MapIterator (_tree.find(key));
    }

    // доступ к элементу по ключу
    // если в момент обращения элемента не существует, создать его,
    // ключ равен key, value равно дефолтному значению для типа Value
    const Value& operator[](const Key& key) const {
        if (find(key) == end()) {
            insert(key, std::iterator_traits<Value>::value_type);
        }
        return _tree.find(key)->second;
    }
    Value& operator[](const Key& key) {
        if (find(key) == end()) {
            _tree.insert(key, Value());
        }
        return _tree.find(key)->second;
    }

    MapIterator begin() {
        return MapIterator(_tree.begin());
    }
    MapIterator end() {
        return MapIterator(_tree.end());
    }

    ConstMapIterator cbegin() const {
        return ConstMapIterator(_tree.cbegin());
    }
    ConstMapIterator cend() const {
        return ConstMapIterator(_tree.cend());
    }

    size_t size() const {
        return _tree.size();
    }
};
/*
template <typename Value>
class Set
{
    Map<Value, Value> _map;

public:
    using SetIterator = Map::MapIterator;
    using ConstSetIterator = Map::ConstMapIterator;

    Set() = default;

    explicit Set(const Set& other);
    Set& operator=(const Set& other);

    explicit Set(Set&& other) noexcept;
    Set& operator=(Set&& other) noexcept;

    ~Set() = default;

    void insert(const Value& value);

    void erase(const Value& value);

    ConstSetIterator find(const Value& value) const;
    SetIterator find(const Value& key);

    bool contains(const Value& value) const;
};
*/