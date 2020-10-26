#include <iostream>
#include "BinaryTree.h"

struct Person
{
    unsigned int age;
    std::string name;

    Person(std::string name, unsigned int age): name(name), age(age){};

    bool operator==(const Person &person){return this->age == person.age && this->name == person.name;}
};

int main()
{
    BinaryTree<Person, int> tree([](Person &person){return person.age;});

    tree.insert(Person("Ivan", 17));
    tree.insert(Person("Grisha", 25));
    tree.insert(Person("Vova", 65));

    for(auto &i: tree.getInOrderTraversal())
        std::cout << i.name << ' ' << i.age << std::endl;

    tree.remove(Person("Ivan", 17));

    for(auto &i: tree.getInOrderTraversal())
        std::cout << i.name << ' ' << i.age << std::endl;

    return 0;
}