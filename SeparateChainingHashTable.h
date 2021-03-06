#ifndef SEPARATE_CHAINING_HASH_TABLE_HEADER
#define SEPARATE_CHAINING_HASH_TABLE_HEADER

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

    bool contains(const KeyT &key);

    ValueT &get(const KeyT &key);
    ValueT &operator[](const KeyT &key){return this->get(key);}

    unsigned long getCapacity(){return this->capacity;}
    void resize(unsigned long new_size);

    template <typename T1, typename T2>
    friend std::ostream &operator<<(std::ostream &out, const SeparateChainingHashTable<T1, T2> &table);
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
void SeparateChainingHashTable<KeyT, ValueT>::resize(unsigned long new_size)
{
    LinkedList<Pair<KeyT, ValueT>> *new_pairs = new LinkedList<Pair<KeyT, ValueT>>[new_size];

    

    for(unsigned int i = 0; i < this->capacity; i++)
    {
        auto row = &this->pairs[i];
        if(!row->is_empty())
        {
            for(LinkedListNode<Pair<KeyT, ValueT>> *it = row->getTail(); it != nullptr; it = it->getNext())
            {
                auto data = it->getData();
                auto hash = hashing(data.getKey());

                new_pairs[hash % new_size].push_head(data);
            }
        }
    }

    delete[] this->pairs;

    this->capacity = new_size;
    this->pairs = new_pairs;
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
bool SeparateChainingHashTable<KeyT, ValueT>::contains(const KeyT &key)
{
    unsigned long hash = hashing(key);

    LinkedList<Pair<KeyT, ValueT>> *pair_list = &this->pairs[hash % this->capacity];

    return pair_list->contains([key](Pair<KeyT, ValueT> pair){return pair.getKey() == key;});
}

template <typename KeyT, typename ValueT>
std::ostream &operator<<(std::ostream &out, const SeparateChainingHashTable<KeyT, ValueT> &table)
{
    out << "{";
    std::string sep = "";
    for(unsigned int i = 0; i < table.capacity; i++)
    {
        auto row = &table.pairs[i];
        if(!row->is_empty())
        {
            for(LinkedListNode<Pair<KeyT, ValueT>> *it = row->getTail(); it != nullptr; it = it->getNext())
            {
                out << sep << it->getData().getKey() << ": " << it->getData().getValue();
                if(sep == "")
                    sep = ", ";
            }
        }
    }
    out << "}";
    return out;
}

#endif