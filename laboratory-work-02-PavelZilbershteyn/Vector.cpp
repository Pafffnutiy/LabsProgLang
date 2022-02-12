#include <iostream>
#include "Vector.h"

Vector::Vector()
    :data{ nullptr }, size{ 0 }, capacity{ 0 }
{}

Vector::Vector(std::size_t s)
    : size{ s }, capacity{ 2 * s }
{
    data = new ADT * [2 * s];
}

Vector::Vector(const Vector& other)
    : size{ other.size }, capacity{ other.capacity }
{
    data = new ADT * [capacity];

    for (std::size_t i{ 0 }; i < size; ++i)
        data[i] = other.data[i];
}

Vector::~Vector()
{
    if (data != nullptr)
    {
        delete[] data;
        data = nullptr;
    }
}

void Vector::erase(std::size_t pos)
{
    if (pos >= size)
        throw std::runtime_error
            ("Index is outside the bounds of the vector");

    for (std::size_t i{ pos }; i < size-1; ++i)
    {
        (*this)[i] = (*this)[i + 1];
    }

    --size;
}

void Vector::insert(std::size_t pos, ADT* val)
{
    if(pos >= size) 
        throw std::runtime_error
            ("Index is outside the bounds of the vector");

    if (size + 1 > capacity)
    {
        Vector temp(*this);
        this->Resize(size+1);
        for (std::size_t i{ 0 }; i < size-1; ++i)
        {
            (*this)[i] = temp[i];
        }
    }
    else
    {
        ++size;
    }


    for (std::size_t i{ size-1 }; i > pos; --i)
    {
        ADT* temp = (*this)[i];
        (*this)[i] = (*this)[i - 1];
        (*this)[i - 1] = temp;
    }

    (*this)[pos] = val;

}

void Vector::push_back(ADT* value)
{
    if (size + 1 > capacity)
    {
        Vector res(*this);

        this->Resize(size + 1);

        for (std::size_t i{ 0 }; i < size; ++i)
            (*this)[i] = res[i];
    }
    else
    {
        ++size;
    }

    (*this)[size - 1] = value;
}

void Vector::Resize(std::size_t NewSize)
{
		data = new ADT * [2 * NewSize];

		capacity = 2 * NewSize; 
		size = NewSize;
}

std::size_t Vector::length() const
{
    return size;
}

ADT*& Vector::operator[](std::size_t index)
{
    if (index >= size) 
        throw std::runtime_error
            ("Index is outside the bounds of the vector");

    return data[index];    
}

ADT*& Vector::operator[](std::size_t index) const
{
    if (index >= size) 
        throw std::runtime_error
            ("Index is outside the bounds of the vector");

    return data[index];
}

Vector& Vector::operator=(const Vector& other)
{
    if (this != &other)
    {
        if (data != nullptr)
        {
            delete[] data;
            data = nullptr;
        }

        size = other.size;
        capacity = other.capacity;
        data = new ADT * [capacity];

        for (std::size_t i{ 0 }; i < size; ++i)
            data[i] = other.data[i];
    }

    return *this;
}