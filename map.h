#ifndef BST_MAP_H
#define BST_MAP_H
#include "BinarySearchTree.h"

template <typename Key, typename Value>
class Map
{
    BinarySearchTree<Key, Value> _tree;
public:
    using MapIterator = typename BinarySearchTree<Key, Value>::Iterator;
    using ConstMapIterator = typename BinarySearchTree<Key, Value>::ConstIterator;

    Map() = default;

    explicit Map(const Map& other);
    Map& operator=(const Map& other);

    explicit Map(Map&& other) noexcept;
    Map& operator=(Map&& other) noexcept;

    ~Map() = default;

    void insert(const Key& key, const Value& value);
    void erase(const Key& key);

    ConstMapIterator find(const Key& key) const;
    MapIterator find(const Key& key);

    const Value& operator[](const Key& key) const;
    Value& operator[](const Key& key);

    MapIterator begin();
    MapIterator end();

    ConstMapIterator cbegin() const;
    ConstMapIterator cend() const;

    std::size_t size() const;
};

template<typename Key, typename Value>
Map<Key, Value>::Map(const Map &other): _tree(other._tree){
}

template<typename Key, typename Value>
Map<Key, Value>& Map<Key, Value>::operator=(const Map &other) {
    Map newMap = Map(other);
    std::swap(newMap, *this);
    delete newMap;
    return *this;
}

template<typename Key, typename Value>
Map<Key, Value>::Map(Map &&other) noexcept {
    if (this != other) {
        std::swap(_tree, other._tree);
        delete other;
    }
}

template<typename Key, typename Value>
Map<Key, Value>& Map<Key, Value>::operator=(Map &&other) noexcept {
    if (this != other) {
        std::swap(_tree, other._tree);
        delete other;
        return *this;
    }
}

template<typename Key, typename Value>
void Map<Key, Value>::insert(const Key &key, const Value &value) {
    if (find(key) != end()) {
        erase(key);
    }
    else
        _tree.insert(key, value);
}

template<typename Key, typename Value>
void Map<Key, Value>::erase(const Key &key) {
    _tree.erase(key);
}

template<typename Key, typename Value>
typename Map<Key, Value>::ConstMapIterator Map<Key, Value>::find(const Key &key) const {
    return ConstMapIterator(_tree.find(key));
}

template<typename Key, typename Value>
typename Map<Key, Value>::MapIterator Map<Key, Value>::find(const Key &key) {
    return MapIterator (_tree.find(key));
}

template<typename Key, typename Value>
const Value &Map<Key, Value>::operator[](const Key &key) const {
    if (find(key) == end()) {
        insert(key, std::iterator_traits<Value>::value_type);
    }
    return _tree.find(key)->second;
}

template<typename Key, typename Value>
Value &Map<Key, Value>::operator[](const Key &key) {
    if (find(key) == end()) {
        _tree.insert(key, Value());
    }
    return _tree.find(key)->second;
}

template<typename Key, typename Value>
typename Map<Key, Value>::MapIterator Map<Key, Value>::begin() {
    return MapIterator(_tree.begin());
}

template<typename Key, typename Value>
typename Map<Key, Value>::MapIterator Map<Key, Value>::end() {
    return MapIterator(_tree.end());
}

template<typename Key, typename Value>
typename Map<Key, Value>::ConstMapIterator Map<Key, Value>::cbegin() const {
    return ConstMapIterator(_tree.cbegin());
}

template<typename Key, typename Value>
typename Map<Key, Value>::ConstMapIterator Map<Key, Value>::cend() const {
    return ConstMapIterator(_tree.cend());
}

template<typename Key, typename Value>
std::size_t Map<Key, Value>::size() const {
    return _tree.size();
}


#endif //BST_MAP_H
