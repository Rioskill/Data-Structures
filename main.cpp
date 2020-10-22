#include <iostream>
#include "SeparateChainingHashTable.h"

int main()
{
    SeparateChainingHashTable<std::string, int> table(10);

    table["one"] = 1;
    table["two"] = 2;
    table["three"] = 3;

    std::cout << table.getCapacity() << ' ' << table << std::endl;

    table.resize(25);

    table.get("four") = 4;

    std::cout << table.getCapacity() << ' ' << table << std::endl;

    return 0;
}