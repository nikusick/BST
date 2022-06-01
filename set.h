#ifndef BST_SET_H
#define BST_SET_H

#include "map.h"

template <typename Value>
class Set
{
    Map<Value, Value> _map;

public:
    using SetIterator = typename Map<Value, Value>::MapIterator;
    using ConstSetIterator = typename Map<Value, Value>::ConstMapIterator;

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

template<typename Value>
Set<Value>::Set(const Set &other): _map(other._map) {
}

template<typename Value>
Set<Value>& Set<Value>::operator=(const Set &other) {
    Set newSet = Set(other);
    std::swap(newSet, *this);
    delete newSet;
    return *this;
}

template<typename Value>
Set<Value>::Set(Set &&other) noexcept {
    if (this != other) {
        std::swap(_map, other._map);
        delete other;
    }
}

template<typename Value>
Set<Value>& Set<Value>::operator=(Set &&other) noexcept {
    if (this != other) {
        std::swap(_map, other._map);
        delete other;
        return *this;
    }
}

template<typename Value>
void Set<Value>::insert(const Value &value) {
    _map.insert(value, value);
}

template<typename Value>
void Set<Value>::erase(const Value &value) {
    _map.erase(value);
}

template<typename Value>
typename Set<Value>::ConstSetIterator Set<Value>::find(const Value &value) const {
    return _map.find(value);
}

template<typename Value>
typename Set<Value>::SetIterator Set<Value>::find(const Value &key) {
    return _map.find(key);
}

template<typename Value>
bool Set<Value>::contains(const Value &value) const {
    return find(value) != ConstSetIterator(nullptr);
}

#endif //BST_SET_H
