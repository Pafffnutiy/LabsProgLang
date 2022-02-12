#include "Queue.h"
#include <algorithm>

Queue::Queue()
    :data{ nullptr }, size{ 1 }, count{ 0 }, rear{ 0 }, front{ -1 }
{}

Queue::Queue(const Queue& other)
    : size{ other.size }, count{ other.count }, rear{ other.rear },
      front{ other.front }
{
    data = new ADT * [size];

    std::copy(other.data, other.data + size, data);
}

Queue::Queue(std::size_t size)
    : size{ size }, count{ 0 }, rear{ 0 }, front{ -1 }
{
    data = new ADT * [size];

    std::fill(data, data + size, nullptr);
}

Queue::~Queue()
{
    if (data != nullptr)
    {
        delete[] data;
        data = nullptr;
    }
}

void Queue::erase(std::size_t index)
{
    if (index >= size)
        throw std::runtime_error
            ("Index is outside the bounds of the queue");

    if (index == front) pop_front();
    else if (index != rear)
    {
        int ind = index;
        std::size_t end = (ind > rear) ? (rear + size) : rear;

        for (std::size_t i{ index + 1 }; i < end; ++i)
        {
            ADT* temp = (*this)[i % size];
            (*this)[i % size] = (*this)[(i - 1) % size];
            (*this)[(i - 1) % size] = temp;
        }
        int a = rear - 1;
        a = (a >= 0) ? a : (a + size);
        std::swap((*this)[rear], (*this)[a]);

        (*this)[rear] = 0;

        --count;
    }
}

void Queue::insert(std::size_t index, ADT* val)
{
    if (index >= size) 
        throw std::runtime_error
            ("Index is outside the bounds of the queue");

    if (index == rear+1) push_back(val);

    if ((*this)[index] == nullptr)
        (*this)[index] = val;
    else {
        if (index != front)
        {
            std::size_t end = (index - rear > 0) ? rear + size : rear;
            for (std::size_t i{ index + 1 }; i < end; ++i)
            {
                ADT* temp = (*this)[i % size];
                (*this)[i % size] = (*this)[(i - 1) % size];
                (*this)[(i - 1) % size] = temp;
            }
            std::swap((*this)[index], (*this)[rear]);
            (*this)[index] = val;
        }
    }
}

void Queue::pop_front()
{
    if (count == 0) 
        throw std::runtime_error
            ("Queue is empty");

    (*this)[front] = nullptr;

    for (std::size_t i = front; i < size + front; ++i)
    {
        ADT* temp = (*this)[i % size];
        (*this)[i % size] = (*this)[(i - 1) % size];
        (*this)[(i - 1) % size] = temp;
    }

    rear = (rear - 1) % size;

    rear = (rear >= 0) ? rear : rear + size;

    int a = (rear) % size;
    int b = (front - 1) % size;
    b = (b >= 0) ? b : b + size;

    std::swap((*this)[a], (*this)[b]);

    --count;
}

void Queue::push_back(ADT* val)
{
    if ((rear + 1) % size == front)
        front = (front + 1) % size;

    if (count == 0)
        ++front;

    if (count < size)
        ++count;

    if ((*this)[rear] != nullptr)
        rear = (rear + 1) % size;

    (*this)[rear] = val;
}

std::size_t Queue::length() const
{
	return size;
}

ADT*& Queue::operator[](std::size_t index)
{
    if (index >= size)
        throw std::runtime_error
            ("Index is outside the bounds of the queue");

    return data[index];
}

ADT*& Queue::operator[](std::size_t index) const
{
    if (index >= size)
        throw std::runtime_error
            ("Index is outside the bounds of the queue");

    return data[index];
}
