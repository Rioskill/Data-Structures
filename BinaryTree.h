#include <functional>
#include <vector>

#include <iostream>

template <typename T>
class BinaryTree
{
private:
    class Node
    {
    private:
        T value;
        Node *left;
        Node *right;
    public:
        Node(T value): value(value){this->left = this->right = nullptr;}
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

        T getData(){return this->value;}
        void setData(T value){this->value = value;}

        void clear_for_removal()
        {
            setLeft(nullptr);
            setRight(nullptr);
        }
    };

    Node *root;

    unsigned int size;

    bool add(Node &node, T value);

    Node *remove(Node &node, T value);
    Node &find_min(Node &node);
    void copy(Node &to, Node &from);

    unsigned int getHeight(Node &node);

    bool contains(Node &node, T value);
public:
    Node &getRoot(){return *this->root;}

    BinaryTree()
    {
        this->root = nullptr;
        this->size = 0;
    }
    ~BinaryTree(){delete this->root;}

    unsigned int getSize(){return this->size;}
    unsigned int getHeight();
    bool isEmpty(){return this->getSize() == 0;}

    void add(T value);
    void remove(T value);

    bool contains(T value);

    std::vector<T> getInOrderTraversal();

};

unsigned int max(unsigned int first, unsigned int second){return first > second ? first: second;}

template <typename T>
unsigned int BinaryTree<T>::getHeight(Node &node)
{
    if(node.hasLeftChild() && node.hasRightChild())
        return max(getHeight(node.getLeft()), getHeight(node.getRight())) + 1;

    else if(node.hasLeftChild() && !node.hasRightChild())
        return getHeight(node.getLeft()) + 1;

    else if(!node.hasLeftChild() && node.hasRightChild())
        return getHeight(node.getRight()) + 1;

    else return 1;
}

template <typename T>
unsigned int BinaryTree<T>::getHeight()
{
    return getHeight(getRoot());
}

template<typename T>
bool BinaryTree<T>::contains(Node &node, T value)
{
    T data = node.getData();
    if(value == data)
        return true;
    
    if(value < data)
        if(node.hasLeftChild())
            return contains(node.getLeft(), value);
        else return false;

    else
        if(node.hasRightChild())
            return contains(node.getRight(), value);
        else return false;
}

template <typename T>
bool BinaryTree<T>::contains(T value)
{
    return contains(getRoot(), value);
}

template <typename T>
void BinaryTree<T>::copy(Node &to, Node &from)
{
    to.setData(from.getData());

    if(from.hasLeftChild())
        to.setLeft(from.getLeft());
    else to.setLeft(nullptr);
    
    if(from.hasRightChild())
        to.setRight(from.getRight());
    else to.setRight(nullptr);
}

template <typename T>
typename BinaryTree<T>::Node &BinaryTree<T>::find_min(Node &node)
{
    Node *ptr = &node;

    while(ptr->hasLeftChild())
        ptr = &ptr->getLeft();
    return *ptr;
}

template <typename T>
bool BinaryTree<T>::add(Node &node, T value)
{
    if(value < node.getData())
    {
        if(node.hasLeftChild())
            return this->add(node.getLeft(), value);
        else 
        {
            node.setLeft(new Node(value));
            return true;
        }
    }
    else if(value > node.getData())
    {
        if(node.hasRightChild())
            return this->add(node.getRight(), value);
        else 
        {
            node.setRight(new Node(value));
            return true;
        }
    }
    else
        return false;
}

template <typename T>
void BinaryTree<T>::add(T value)
{
    bool is_new;
    if(isEmpty())
    {
        this->root = new Node(value);
        is_new = true;
    }
    else {
        is_new = this->add(this->getRoot(), value);
    }
    if(is_new)
        this->size++;
}

template <typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::remove(Node &node, T value)
{
    // std::cout << "Node " << node.getData() << std::endl;

    // if(node.hasRightChild())
    //     std::cout << "right " << node.getRight().getData() << std::endl;

    if(node.getData() != value)
    {
        if(value < node.getData() && node.hasLeftChild())
        {
            node.setLeft(remove(node.getLeft(), value));
            
            return &node;
        }
        else if(value > node.getData() && node.hasRightChild())
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

template <typename T>
void BinaryTree<T>::remove(T value)
{
    this->root = remove(getRoot(), value);
}

template <typename T>
std::vector<T> BinaryTree<T>::getInOrderTraversal()
{
    std::vector<T> res_vector;
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