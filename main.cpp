#include <iostream>
#include "SeparateChainingHashTable.h"

int main()
{
    SeparateChainingHashTable<std::string, int> table(10);

    table["kek"] = 5;

    table.get("kek") = 98;

    std::cout << table.get("kek") << std::endl;

    return 0;
}