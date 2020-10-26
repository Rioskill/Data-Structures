#include <functional>
#include <vector>

#include <iostream>

template <typename ObjectT, typename KeyT=ObjectT>
class BinaryTree
{
private:
    class Node
    {
    private:
        ObjectT value;
        Node *left;
        Node *right;

    public:
        Node(ObjectT value): value(value)
        {
            this->left = this->right = nullptr;
        }
        ~Node()
        {
            delete this->left;
            delete this->right;
        }

        Node &getLeft(){return *this->left;}
        Node &getRight(){return *this->right;}

        bool hasLeftChild(){return this->left != nullptr;}
        bool hasRightChild(){return this->right != nullptr;}

        void setLeft(Node *node){this->left = node;}
        void setRight(Node *node){this->right = node;}

        void setLeft(Node &node){this->left = &node;}
        void setRight(Node &node){this->right = &node;}

        ObjectT getData(){return this->value;}
        void setData(ObjectT value){this->value = value;}

        KeyT getKey(){return this->getKey(this->value);}

        void clear_for_removal()
        {
            setLeft(nullptr);
            setRight(nullptr);
        }
    };

    Node *root;

    unsigned int size;

    bool insert(Node &node, ObjectT value);

    Node *remove(Node &node, ObjectT value);
    Node &find_min(Node &node);
    void copy(Node &to, Node &from);

    unsigned int getHeight(Node &node);

    bool contains(Node &node, ObjectT value);

    std::function<KeyT(ObjectT &)> getKey;
public:
    Node &getRoot(){return *this->root;}

    BinaryTree()
    {
        this->root = nullptr;
        this->size = 0;

        this->getKey = [](ObjectT &object){return object;};
    }
    BinaryTree(std::function<KeyT(ObjectT &)> getKey)
    {
        this->root = nullptr;
        this->size = 0;

        this->getKey = getKey;
    }
    ~BinaryTree(){delete this->root;}

    unsigned int getSize(){return this->size;}
    unsigned int getHeight();
    bool isEmpty(){return this->getSize() == 0;}

    void insert(ObjectT value);
    void remove(ObjectT value);

    bool contains(ObjectT value);

    std::vector<ObjectT> getInOrderTraversal();

};

unsigned int max(unsigned int first, unsigned int second){return first > second ? first: second;}

template <typename ObjectT, typename KeyT>
unsigned int BinaryTree<ObjectT, KeyT>::getHeight(Node &node)
{
    if(node.hasLeftChild() && node.hasRightChild())
        return max(getHeight(node.getLeft()), getHeight(node.getRight())) + 1;

    else if(node.hasLeftChild() && !node.hasRightChild())
        return getHeight(node.getLeft()) + 1;

    else if(!node.hasLeftChild() && node.hasRightChild())
        return getHeight(node.getRight()) + 1;

    else return 1;
}

template <typename ObjectT, typename KeyT>
unsigned int BinaryTree<ObjectT, KeyT>::getHeight()
{
    return getHeight(getRoot());
}

template<typename ObjectT, typename KeyT>
bool BinaryTree<ObjectT, KeyT>::contains(Node &node, ObjectT value)
{
    ObjectT data = node.getData();
    if(value == data)
        return true;
    
    if(getKey(value) < getKey(data))
        if(node.hasLeftChild())
            return contains(node.getLeft(), value);
        else return false;

    else
        if(node.hasRightChild())
            return contains(node.getRight(), value);
        else return false;
}

template <typename ObjectT, typename KeyT>
bool BinaryTree<ObjectT, KeyT>::contains(ObjectT value)
{
    return contains(getRoot(), value);
}

template <typename ObjectT, typename KeyT>
void BinaryTree<ObjectT, KeyT>::copy(Node &to, Node &from)
{
    to.setData(from.getData());

    if(from.hasLeftChild())
        to.setLeft(from.getLeft());
    else to.setLeft(nullptr);
    
    if(from.hasRightChild())
        to.setRight(from.getRight());
    else to.setRight(nullptr);
}

template <typename ObjectT, typename KeyT>
typename BinaryTree<ObjectT, KeyT>::Node &BinaryTree<ObjectT, KeyT>::find_min(Node &node)
{
    Node *ptr = &node;

    while(ptr->hasLeftChild())
        ptr = &ptr->getLeft();
    return *ptr;
}

template <typename ObjectT, typename KeyT>
bool BinaryTree<ObjectT, KeyT>::insert(Node &node, ObjectT value)
{
    ObjectT data = node.getData();
    if(getKey(value) < getKey(data))
    {
        if(node.hasLeftChild())
            return this->insert(node.getLeft(), value);
        else 
        {
            node.setLeft(new Node(value));
            return true;
        }
    }
    else if(getKey(value) > getKey(data))
    {
        if(node.hasRightChild())
            return this->insert(node.getRight(), value);
        else 
        {
            node.setRight(new Node(value));
            return true;
        }
    }
    else
        return false;
}

template <typename ObjectT, typename KeyT>
void BinaryTree<ObjectT, KeyT>::insert(ObjectT value)
{
    bool is_new;
    if(isEmpty())
    {
        this->root = new Node(value);
        is_new = true;
    }
    else {
        is_new = this->insert(this->getRoot(), value);
    }
    if(is_new)
        this->size++;
}

template <typename ObjectT, typename KeyT>
typename BinaryTree<ObjectT, KeyT>::Node *BinaryTree<ObjectT, KeyT>::remove(Node &node, ObjectT value)
{
    // std::cout << "Node " << node.getData() << std::endl;

    // if(node.hasRightChild())
    //     std::cout << "right " << node.getRight().getData() << std::endl;

    ObjectT data = node.getData();

    if(getKey(data) != getKey(value))
    {
        if(getKey(value) < getKey(data) && node.hasLeftChild())
        {
            node.setLeft(remove(node.getLeft(), value));
            
            return &node;
        }
        else if(getKey(value) > getKey(data) && node.hasRightChild())
        {
            node.setRight(remove(node.getRight(), value));

            return &node;
        }
    }

    else
    {
        if(!node.hasLeftChild() && !node.hasRightChild())
        {
            delete &node;

            this->size--;

            return nullptr;
        }

        else if(node.hasLeftChild() && !node.hasRightChild())
        {
            Node *left = &node.getLeft();
            copy(node, *left);
            left->clear_for_removal();
            delete left;

            this->size--;

            return &node;
        }

        else if(node.hasRightChild() && !node.hasLeftChild())
        {
            Node *right = &node.getRight();
            copy(node, *right);
            right->clear_for_removal();
            delete right;

            this->size--;

            return &node;
        }

        else
        {
            Node *right_min = &find_min(node.getRight());
            node.setData(right_min->getData());
            node.setRight(remove(node.getRight(), node.getData()));
            
            return &node;
        }
    }
    return &node;
}

template <typename ObjectT, typename KeyT>
void BinaryTree<ObjectT, KeyT>::remove(ObjectT value)
{
    this->root = remove(getRoot(), value);
}

template <typename ObjectT, typename KeyT>
std::vector<ObjectT> BinaryTree<ObjectT, KeyT>::getInOrderTraversal()
{
    std::vector<ObjectT> res_vector;
    res_vector.reserve(this->getSize());

    std::function<void(Node &)> func;
    func = [&res_vector, &func](Node &node)
    {
        if(node.hasLeftChild())
        {
            func(node.getLeft());
        }

        res_vector.push_back(node.getData());

        if(node.hasRightChild())
        {
            func(node.getRight());
        }
    };

    func(this->getRoot());

    return res_vector;
}