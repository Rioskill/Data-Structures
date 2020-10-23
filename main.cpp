#include <iostream>
#include "Heap.h"

struct Person
{
    int age;
    std::string name;

    Person(int age, std::string name): age(age), name(name){};

    int getAge(){return this->age;};
};

int main()
{
    Heap<Person, int> heap([](Person person){return person.age;});

    heap.insert(Person(5, "Vova"));

    heap.insert(Person(53, "Vladimir"));

    std::cout << heap.poll().name << ' ' << heap.poll().name << std::endl;

    return 0;
}