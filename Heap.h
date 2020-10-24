#include <vector>
#include <functional>

template <typename ObjectT, typename KeyT=ObjectT>
class Heap
{
private:
    std::vector<ObjectT> data;
    std::function<KeyT(ObjectT)> getKey;


    void swap(unsigned int first_id, unsigned int second_id)
    {
        ObjectT t = this->data[first_id];
        this->data[first_id] = this->data[second_id];
        this->data[second_id] = t;
    }

    void swap_with_parent(unsigned int id){this->swap(id, this->get_parent_id(id));}

    bool less(unsigned int first_id, unsigned int second_id)
    {
        return getKey(this->data[first_id]) < getKey(this->data[second_id]);
    }

    bool less_than_parent(unsigned int id)
    {
        if(id == 0)
            return false;
        else return less(id, get_parent_id(id));
    }

    unsigned int get_left_child_id(unsigned int id){return id * 2 + 1;}
    unsigned int get_right_child_id(unsigned int id){return id * 2 + 2;}

    unsigned int get_parent_id(unsigned int id){return (id - 1) / 2;}

    void swim(unsigned int id);
    void sink(unsigned int id);

public:
    Heap()
    {
        this->getKey = [](ObjectT object){return object;};
    }

    Heap(std::function<KeyT(ObjectT)> function)
    {
        this->getKey = function;
    }


    void insert(ObjectT value);
    ObjectT poll();
};

template <typename ObjectT, typename KeyT>
void Heap<ObjectT, KeyT>::insert(ObjectT value)
{
    this->data.push_back(value);
    swim(this->data.size() - 1);
}

template <typename ObjectT, typename KeyT>
ObjectT Heap<ObjectT, KeyT>::poll()
{
    this->swap(0, this->data.size() - 1);

    ObjectT res = this->data[this->data.size() - 1];
    this->data.pop_back();

    this->sink(0);

    return res;
}

template <typename ObjectT, typename KeyT>
void Heap<ObjectT, KeyT>::swim(unsigned int id)
{
    while(id > 0 && less_than_parent(id))
    {
        swap_with_parent(id);
        id = get_parent_id(id);
    }
}

template <typename ObjectT, typename KeyT>
void Heap<ObjectT, KeyT>::sink(unsigned int id)
{
    while(1)
    {
        unsigned int left_id = get_left_child_id(id);
        unsigned int right_id = get_right_child_id(id);

        unsigned int smallest_id = left_id;
        if(right_id < this->data.size() && less(right_id, left_id))
            smallest_id = right_id;

        if(left_id >= this->data.size() || less(id, smallest_id))
            break;
        
        this->swap(smallest_id, id);
        id = smallest_id;
    }
}