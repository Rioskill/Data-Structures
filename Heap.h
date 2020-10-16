#include <vector>

template <typename T>
class Heap
{
private:
    std::vector<T> data;

    void swap(unsigned int first_id, unsigned int second_id)
    {
        int t = this->data[first_id];
        this->data[first_id] = this->data[second_id];
        this->data[second_id] = t;
    }

    void swap_with_parent(unsigned int id){this->swap(id, this->get_parent_id(id));}

    bool less(unsigned int first_id, unsigned int second_id)
    {
        return this->data[first_id] < this->data[second_id];
    }

    bool less_than_parent(unsigned int id)
    {
        if(id == 0)
            return false;
        else return this->data[id] < this->data[get_parent_id(id)];
    }

    unsigned int get_left_child_id(unsigned int id){return id * 2 + 1;}
    unsigned int get_right_child_id(unsigned int id){return id * 2 + 2;}

    unsigned int get_parent_id(unsigned int id){return (id - 1) / 2;}

    void swim(unsigned int id);
    void sink(unsigned int id);

public:
    void insert(T value);
    T poll();
};

template <typename T>
void Heap<T>::insert(T value)
{
    this->data.push_back(value);
    swim(this->data.size() - 1);
}

template <typename T>
T Heap<T>::poll()
{
    this->swap(0, this->data.size() - 1);

    int res = this->data[this->data.size() - 1];
    this->data.pop_back();

    this->sink(0);

    return res;
}

template <typename T>
void Heap<T>::swim(unsigned int id)
{
    while(id > 0 && less_than_parent(id))
    {
        swap_with_parent(id);
        id = get_parent_id(id);
    }
}

template <typename T>
void Heap<T>::sink(unsigned int id)
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