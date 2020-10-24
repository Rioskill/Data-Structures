#include <iostream>
#include "Heap.h"

int main()
{
    Heap<int> heap;

    heap.insert(1);
    heap.insert(2);
    heap.insert(59);

    std::cout << heap.poll() << ' ' << heap.poll() << ' ' << heap.poll() << std::endl;

    return 0;
}