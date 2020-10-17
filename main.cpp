#include <iostream>
#include "LinkedList.h"

int main()
{
    LinkedList<int> list;

    list.push_head(3);
    list.push_head(2);
    list.push_head(5);
    list.push_tail(1);

    for(auto it = list.getTail(); it != nullptr; it = it->getNext())
    {
        std::cout << it->getData() << ' ';
    }

    std::cout << std::endl;

    return 0;
}