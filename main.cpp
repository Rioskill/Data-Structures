#include <iostream>
#include "BinaryTree.h"

template <typename T>
void print(std::vector<T> arr)
{
    for(auto &i: arr)
        std::cout << i << ' ';
    std::cout << std::endl;
}

template <typename T>
void print(BinaryTree<T> &tree){print(tree.getInOrderTraversal());}

int main()
{
    BinaryTree<char> tree;

    tree.add('c');
    tree.add('e');
    tree.add('a');
    tree.add('d');

    print(tree);

    std::cout << tree.getHeight() << std::endl;

    tree.remove('c');

    print(tree);

    std::cout << tree.getHeight() << std::endl;

    return 0;
}