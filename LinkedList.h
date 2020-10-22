#include <functional>

template <class T>
class LinkedListNode
{
private:
    T data;
    LinkedListNode *prev;
    LinkedListNode *next;
public:
    LinkedListNode(T data, LinkedListNode *prev, LinkedListNode *next): data(data), prev(prev), next(next){}
    
    LinkedListNode *getNext(){return this->next;}
    LinkedListNode *getPrev(){return this->prev;}

    T &getData(){return this->data;}

    void setNext(LinkedListNode *next){this->next = next;}
    void setPrev(LinkedListNode *prev){this->prev = prev;}

    LinkedListNode &operator+(int n)
    {
        auto res = this;
        for(int i = 0; i < n; i++)
        {
            if(res == nullptr)
                break;
            res = res->getNext();
        }
        return *res;
    }
};

template <class T>
class LinkedList
{
private:
    size_t size;
    LinkedListNode<T> *head;
    LinkedListNode<T> *tail;

public:
    LinkedList();
    ~LinkedList();

    LinkedList(const LinkedList &list);

    bool is_empty();
    bool contains(const T &value);
    bool contains(std::function<bool(T)> function);

    void push_tail(const T &data);
    void push_head(const T &data);

    LinkedList &operator=(const LinkedList &list);

    T &find(std::function<bool(T)> function);

    LinkedListNode<T> *getHead()
    {
        return this->head;
    }
    LinkedListNode<T> *getTail()
    {
        return this->tail;
    }
};

template <typename T>
T &LinkedList<T>::find(std::function<bool(T)> function)
{
    for(auto it = getTail(); it != nullptr; it = it->getNext())
        if(function(it->getData()))
            return it->getData();
}

template <typename T>
LinkedList<T>::LinkedList()
{
    this->head = nullptr;
    this->tail = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList &list)
{
    for(auto it = list.getTail(); it != nullptr; it = it->getNext())
    {
        this.pushHead(it->getData());
    }
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList &list)
{
    for(auto it = list.getTail(); it != nullptr; it = it->getNext())
    {
        this.pushHead(it->getData());
    }
    return this;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    LinkedListNode<T> *iter_node = this->tail;
    while(iter_node != this->head)
    {
        iter_node = iter_node->getNext();

        delete iter_node->getPrev();
    }
    delete iter_node;
}

template <typename T>
bool LinkedList<T>::is_empty()
{
    return this->head == nullptr;
}

template <typename T>
bool LinkedList<T>::contains(const T &value)
{
    for(auto it = getTail(); it != nullptr; it = it->getNext())
    {
        if(it->getData() == value)
            return true;
    }
    return false;
}

template <typename T>
bool LinkedList<T>::contains(std::function<bool(T)> func)
{
    for(auto it = getTail(); it != nullptr; it = it->getNext())
    {
        if(func(it->getData()))
            return true;
    }
    return false;
}

template <typename T>
void LinkedList<T>::push_tail(const T &data)
{
    LinkedListNode<T> *node;
    if(this->tail != nullptr)
    {
        node = new LinkedListNode<T>(data, nullptr, this->tail);
        this->tail->setPrev(node);
        this->tail = node;
    }
    else {
        node = new LinkedListNode<T>(data, nullptr, nullptr);
        this->tail = node;
        this->head = node;
    }
}

template <typename T>
void LinkedList<T>::push_head(const T &data)
{
    LinkedListNode<T> *node;
    if(this->head != nullptr)
    {
        node = new LinkedListNode<T>(data, this->head, nullptr);
        this->head->setNext(node);
        this->head = node;
    }
    else {
        node = new LinkedListNode<T>(data, nullptr, nullptr);
        this->tail = node;        
        this->head = node;
    }
}
