#pragma once

#include <utility>
#include <queue>

template <typename Key, typename Value>
class BinarySearchTree
{
    struct Node
    {
        Node(Key key,
             Value value,
             Node* parent = nullptr,
             Node* left = nullptr,
             Node* right = nullptr);

        std::pair<Key, Value> keyValuePair;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    void remove(const Key &key, Node* node);
    static Node* minNode(Node* node);
    static Node* maxNode(Node* node);


public:
    BinarySearchTree() = default;

    explicit BinarySearchTree(const BinarySearchTree& other);
    BinarySearchTree& operator=(const BinarySearchTree& other);

    explicit BinarySearchTree(BinarySearchTree&& other) noexcept;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

    ~BinarySearchTree();

    class Iterator
    {
    public:
        explicit Iterator(Node* node);

        std::pair<Key, Value>& operator*();
        const std::pair<Key, Value>& operator*() const;

        std::pair<Key, Value>* operator->();
        const std::pair<Key, Value>* operator->() const;

        Iterator operator++();
        Iterator operator++(int);

        Iterator operator--();
        Iterator operator--(int);

        bool operator==(const Iterator& other) const;

        bool operator!=(const Iterator& other) const;

    private:
        Node* _node;
    };

    class ConstIterator
    {
    public:
        explicit ConstIterator(const Node* node);

        const std::pair<Key, Value>& operator*() const;
        const std::pair<Key, Value>* operator->() const;

        ConstIterator operator++();
        ConstIterator operator++(int);

        ConstIterator operator--();
        ConstIterator operator--(int);

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

    private:
        const Node* _node;
    };

    void insert(const Key& key, const Value& value);

    void erase(const Key& key);

    ConstIterator find(const Key& key) const;
    Iterator find(const Key& key);

    std::pair<Iterator, Iterator> equalRange(const Key& key);
    std::pair<ConstIterator, ConstIterator> equalRange(const Key& key) const;

    ConstIterator min(const Key& key) const;
    ConstIterator max(const Key& key) const;

    Iterator begin();
    Iterator end();

    ConstIterator cbegin() const;
    ConstIterator cend() const;

    std::size_t size() const;

private:
    std::size_t _size = 0;
    Node* _root = nullptr;
};

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::ConstIterator::ConstIterator(const BinarySearchTree::Node *node): _node(node) {
}

template<typename Key, typename Value>
const std::pair<Key, Value> &BinarySearchTree<Key, Value>::ConstIterator::operator*() const {
    return _node->keyValuePair;
}

template<typename Key, typename Value>
const std::pair<Key, Value> *BinarySearchTree<Key, Value>::ConstIterator::operator->() const {
    return &_node->keyValuePair;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator++() {
    if (_node == nullptr) {
        return *this;
    }
    if (_node->right != nullptr) {
        _node = minNode(_node->right);
    } else {
        while (_node->parent != nullptr && _node->parent->right == _node) {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator++(int) {
    ConstIterator parent = *this;
    ++(*this);
    return parent;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator--() {
    if (_node == nullptr) {
        return *this;
    }
    if (_node->left != nullptr) {
        _node = maxNode(_node->left);
    } else {
        while (_node->parent != nullptr && _node->parent->left == _node) {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator--(int) {
    ConstIterator parent = *this;
    --(*this);
    return parent;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::ConstIterator::operator==(const BinarySearchTree::ConstIterator &other) const {
    return _node == other._node;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::ConstIterator::operator!=(const BinarySearchTree::ConstIterator &other) const {
    return _node != other._node;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::Iterator::Iterator(BinarySearchTree::Node *node): _node(node) {
}

template<typename Key, typename Value>
std::pair<Key, Value> &BinarySearchTree<Key, Value>::Iterator::operator*() {
    return _node->keyValuePair;
}

template<typename Key, typename Value>
const std::pair<Key, Value> &BinarySearchTree<Key, Value>::Iterator::operator*() const {
    return _node->keyValuePair;
}

template<typename Key, typename Value>
std::pair<Key, Value> *BinarySearchTree<Key, Value>::Iterator::operator->() {
    return &_node->keyValuePair;
}

template<typename Key, typename Value>
const std::pair<Key, Value> *BinarySearchTree<Key, Value>::Iterator::operator->() const {
    return &_node->keyValuePair;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator++() {
    if (_node == nullptr) {
        return *this;
    }
    if (_node->right != nullptr) {
        _node = minNode(_node->right);
    } else {
        while (_node->parent != nullptr && _node->parent->right == _node) {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator++(int) {
    Iterator parent = *this;
    ++(*this);
    return parent;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator--() {
    if (_node == nullptr) {
        return *this;
    }
    if (_node->left != nullptr) {
        _node = maxNode(_node->left);
    } else {
        while (_node->parent != nullptr && _node->parent->left == _node) {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator--(int) {
    Iterator parent = *this;
    --(*this);
    return parent;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::Iterator::operator!=(const BinarySearchTree::Iterator &other) const {
    return _node != other._node;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::Iterator::operator==(const BinarySearchTree::Iterator &other) const {
    return _node == other._node;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key &key, BinarySearchTree::Node *node) {
    if (node == nullptr)  {
        return;
    }
    if (key > node->keyValuePair.first) {
        remove(key, node->right);
    }
    else if (key < node->keyValuePair.first) {
        remove(key, node->left);
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {
            if (node->parent->left == node) {
                node->parent->left = nullptr;
            }
            else {
                node->parent->right = nullptr;
            }
            delete node;
            _size--;
        }
        else if (node->left == nullptr || node->right == nullptr) {
            Node* nodeToDel;
            if (node->left == nullptr) {
                nodeToDel = node->right;
            }
            else {
                nodeToDel = node->left;
            }
            node->keyValuePair = nodeToDel->keyValuePair;
            node->left = nodeToDel->left;
            node->right = nodeToDel->right;
            if (node->right != nullptr) {
                node->right->parent = node;
            }
            if (node->left != nullptr) {
                node->left->parent = node;
            }
            delete nodeToDel;
            _size--;
        }
        else {
            if (node->right->left == nullptr) {
                node->keyValuePair = node->right->keyValuePair;
                Node* newNode = node->right->right;
                delete node->right;
                node->right = newNode;
                _size--;
            }
            else {
                Node* curNode = minNode(node->right);
                node->keyValuePair = curNode->keyValuePair;
                remove(curNode->keyValuePair.first, curNode);
            }
        }
    }
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree(const BinarySearchTree &other) {
    if (other._root != nullptr) {
        std::queue<Node*> children;
        children.push(other._root);
        while (!children.empty()) {
            Node* curNode = children.front();
            insert(curNode->keyValuePair);
            _size++;
            if (curNode->left != nullptr) {
                children.push(curNode->left);
            }
            if (curNode->right != nullptr) {
                children.push(curNode->right);
            }
            children.pop();
        }
    }
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value> &BinarySearchTree<Key, Value>::operator=(const BinarySearchTree &other) {
    if (this != other) {
        BinarySearchTree newBST(other);
        *this = std::move(newBST);
    }
    return *this;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree(BinarySearchTree &&other) noexcept {
    std::swap(_root, other._root);
    std::swap(_size, other._size);
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value> &BinarySearchTree<Key, Value>::operator=(BinarySearchTree &&other) noexcept {
    if (this != other) {
        delete _root;
        _root = nullptr;
        _size = 0;
        std::swap(_root, other._root);
        std::swap(_size, other._size);
    }
    return *this;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() {
    if (_root != nullptr) {
        std::queue<Node*> children;
        children.push(_root);
        while (!children.empty()) {
            Node* curNode = children.front();
            if (curNode->left != nullptr) {
                children.push(curNode->left);
            }
            if (curNode->right != nullptr) {
                children.push(curNode->right);
            }
            delete curNode;
            children.pop();
        }
    }
    _size = 0;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const Key &key, const Value &value) {
    if (_root != nullptr) {
        Node* curNode = _root;
        Key curKey = curNode->keyValuePair.first;
        while ((curKey >= key && curNode->left != nullptr)
               || (curKey < key && curNode->right != nullptr)) {
            curNode = curKey >= key ? curNode->left: curNode->right;
            curKey = curNode->keyValuePair.first;
        }
        curKey >= key? curNode->left: curNode->right = new Node(key, value, curNode);
    }
    else {
        _root = new Node(key, value);
    }
    _size++;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::erase(const Key &key) {
    while (find(key) != end()) {
        remove(key, _root);
    }
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::find(const Key &key) const {
    Node* curNode = _root;
    while(curNode != nullptr) {
        if (curNode->keyValuePair.first > key) {
            curNode = curNode->left;
        }
        else if (curNode->keyValuePair.first < key){
            curNode = curNode->right;
        }
        else {
            break;
        }
    }
    return ConstIterator(curNode);
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::find(const Key &key) {
    Node* curNode = _root;
    while (curNode != nullptr) {
        if (curNode->keyValuePair.first > key) {
            if (curNode->left == nullptr) {
                return Iterator(nullptr);
            }
            curNode = curNode->left;
        }
        else if (curNode->keyValuePair.first < key){
            if (curNode->right == nullptr) {
                return Iterator(nullptr);
            }
            curNode = curNode->right;
        }
        else {
            break;
        }
    }
    return Iterator(curNode);
}

template<typename Key, typename Value>
std::pair<typename BinarySearchTree<Key, Value>::Iterator, typename BinarySearchTree<Key, Value>::Iterator>
        BinarySearchTree<Key, Value>::equalRange(const Key &key) {
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

template<typename Key, typename Value>
std::pair<typename BinarySearchTree<Key, Value>::ConstIterator, typename BinarySearchTree<Key, Value>::ConstIterator>
        BinarySearchTree<Key, Value>::equalRange(const Key &key) const {
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

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::min(const Key &key) const {
    std::pair<ConstIterator, ConstIterator> keyValues = equalRange(key);
    ConstIterator minPairIterator = ConstIterator(keyValues.first);
    for (ConstIterator iterator = keyValues.first; iterator != keyValues.second; ++iterator) {
        if (iterator->second < minPairIterator->second) {
            minPairIterator = iterator;
        }
    }
    return minPairIterator;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::max(const Key &key) const {
    std::pair<ConstIterator, ConstIterator> keyValues = equalRange(key);
    ConstIterator maxPairIterator = ConstIterator(keyValues.first);
    for (ConstIterator iterator = keyValues.first; iterator != keyValues.second; ++iterator) {
        if (iterator->second > maxPairIterator->second) {
            maxPairIterator = iterator;
        }
    }
    return maxPairIterator;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::begin() {
    return BinarySearchTree::Iterator(minNode(_root));
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::end() {
    return BinarySearchTree::Iterator(nullptr);
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::cbegin() const {
    return BinarySearchTree::ConstIterator(minNode(_root));
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::cend() const {
    return BinarySearchTree::ConstIterator(nullptr);
}

template<typename Key, typename Value>
std::size_t BinarySearchTree<Key, Value>::size() const {
    return _size;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node *BinarySearchTree<Key, Value>::minNode(BinarySearchTree::Node *node) {
    auto CurNode = node;
    while (CurNode->left != nullptr) {
        CurNode = CurNode->left;
    }
    return CurNode;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node *BinarySearchTree<Key, Value>::maxNode(BinarySearchTree::Node *node) {
    auto CurNode = node;
    while (CurNode->right != nullptr) {
        CurNode = CurNode->right;
    }
    return CurNode;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::Node::Node(Key key, Value value, BinarySearchTree::Node *parent,
                                         BinarySearchTree::Node *left, BinarySearchTree::Node *right):
                                         keyValuePair(std::make_pair(key, value)),
                                         parent(parent), left(left), right(right)
                                         }