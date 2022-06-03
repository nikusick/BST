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
    ~Set() = default;

    void insert(const Value& value);
    void erase(const Value& value);

    ConstSetIterator find(const Value& value) const;
    SetIterator find(const Value& key);

    bool contains(const Value& value) const;
};

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
