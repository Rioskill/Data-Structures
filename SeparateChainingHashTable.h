#include "LinkedList.h"
#include <string>
#include <iostream>

unsigned long hashing( std::string const& s )
{
    unsigned long result = 2166136261U ;
    std::string::const_iterator end = s.end() ;
    for ( std::string::const_iterator iter = s.begin() ;
            iter != end ;
            ++ iter ) {
        result = (16777619 * result)
                ^ static_cast< unsigned char >( *iter ) ;
    }
    return result ;
}

template <typename KeyT, typename ValueT>
class Pair
{
private:
    // unsinged long hash;
    KeyT key;
    ValueT value;
public:
    Pair(KeyT key, ValueT value): key(key), value(value){};
    Pair(const Pair &pair);

    Pair()
    {
        key = KeyT();
        value = ValueT();
    }

    Pair &operator=(const Pair &pair);
    
    const KeyT &getKey(){return key;};
    ValueT &getValue(){return value;};

    void setKey(KeyT &key){this->key = key;};
    void setValue(ValueT &value){this->value = value;};

    unsigned long size(){return this->size;}
};

template <typename KeyT, typename ValueT>
Pair<KeyT, ValueT>::Pair(const Pair &pair)
{
    this->key = pair.key;
    this->value = pair.value;
}

template <typename KeyT, typename ValueT>
Pair<KeyT, ValueT> &Pair<KeyT, ValueT>::operator=(const Pair &pair)
{
    this->key = pair.key;
    this->value = pair.value;

    return *this;
}

template <typename KeyT, typename ValueT>
class SeparateChainingHashTable
{
private:
    unsigned int capacity;

    LinkedList<Pair<KeyT, ValueT>> *pairs;
public:
    SeparateChainingHashTable(unsigned int capacity);
    ~SeparateChainingHashTable();

    bool exists(const KeyT &key);

    ValueT &get(const KeyT &key);
    ValueT &operator[](const KeyT &key){return this->get(key);}
};

template <typename KeyT, typename ValueT>
SeparateChainingHashTable<KeyT, ValueT>::SeparateChainingHashTable(unsigned int capacity): capacity(capacity)
{
    this->pairs = new LinkedList<Pair<KeyT, ValueT>>[capacity];
}

template <typename KeyT, typename ValueT>
SeparateChainingHashTable<KeyT, ValueT>::~SeparateChainingHashTable()
{
    delete[] this->pairs;
}

template <typename KeyT, typename ValueT>
ValueT &SeparateChainingHashTable<KeyT, ValueT>::get(const KeyT &key)
{
    unsigned long hash = hashing(key);

    LinkedList<Pair<KeyT, ValueT>> *pair_list = &this->pairs[hash % this->capacity];

    if(pair_list->contains([key](Pair<KeyT, ValueT> pair){return pair.getKey() == key;}))
        return pair_list->find([key](Pair<KeyT, ValueT> pair){return pair.getKey() == key;}).getValue();
    
    pair_list->push_head(Pair<KeyT, ValueT>(key, ValueT()));
    return pair_list->getHead()->getData().getValue();
}

template <typename KeyT, typename ValueT>
bool SeparateChainingHashTable<KeyT, ValueT>::exists(const KeyT &key)
{
    unsigned long hash = hashing(key);

    LinkedList<Pair<KeyT, ValueT>> *pair_list = &this->pairs[hash % this->capacity];

    return pair_list->contains([key](Pair<KeyT, ValueT> pair){return pair.getKey() == key;});
}