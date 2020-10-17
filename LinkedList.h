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

    T getData(){return this->data;}

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

    void push_tail(const T &data);
    void push_head(const T &data);

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
LinkedList<T>::LinkedList()
{
    this->head = nullptr;
    this->tail = nullptr;
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

