#ifndef Vector_H
#define Vector_H

#include <cstddef>
#include <iterator>
#include <algorithm>

template <typename T>
class Vector
{
private:
	T* data;
	std::size_t size, capacity;

public:
	struct Iterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = value_type*;  
		using reference = value_type&;

		Iterator(pointer ptr) : m_ptr(ptr) {}
		Iterator(const Iterator& mit) : m_ptr(mit.m_ptr) {}

		bool operator< (const Iterator& tmp) const 
        { return m_ptr < tmp.m_ptr; }

		difference_type operator-(const Iterator& rhs) const 
        { return m_ptr - rhs.m_ptr; }

		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		Iterator operator+(std::size_t x) const	
        { return Iterator(m_ptr + x); }
		Iterator operator-(std::size_t x) const 
        { return Iterator(m_ptr - x); }

		Iterator& operator++() { m_ptr++; return *this; }
		Iterator operator++(int) 
        { Iterator tmp = *this; ++(*this); return tmp; }
		Iterator& operator--()	{ --m_ptr;	return *this; }
		Iterator operator--(int)
        { Iterator tmp(*this); --m_ptr; return tmp; }

		friend bool operator==
            (const Iterator& a, const Iterator& b) 
        { return a.m_ptr == b.m_ptr; };
		friend bool operator!= 
            (const Iterator& a, const Iterator& b)
        { return a.m_ptr != b.m_ptr; };

	private:
		pointer m_ptr;
	};

	Iterator begin() { return Iterator(&data[0]); }
	Iterator end() { return Iterator(&data[size]); }

		Vector();
		Vector(std::size_t s);
		Vector(const Vector & other);
		~Vector();

		void erase(std::size_t pos);
		void insert(std::size_t pos, T val);
		void push_back(T value);
		void Resize(std::size_t NewSize); // with losing data
		std::size_t length() const;

		T& operator[](std::size_t index);
		T& operator[](std::size_t index) const;
		Vector& operator=(const Vector & other);
};


template <typename T>
Vector<T>::Vector()
    :data{ nullptr }, size{ 0 }, capacity{ 0 }
{}

template <typename T>
Vector<T>::Vector(std::size_t s)
    : size{ s }, capacity{ 2 * s }
{
    data = new T[2 * s];
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
    : size{ other.size }, capacity{ other.capacity }
{
    data = new T[size];

    std::copy(other.data, other.data + size, data);
}

template<typename T>
Vector<T>::~Vector()
{
    if (data != nullptr)
    {
        delete[] data;
        data = nullptr;
    }
}

template<typename T>
void Vector<T>::erase(std::size_t pos)
{
    if (pos >= size)
        throw std::runtime_error
        ("Index is outside the bounds of the vector");

    for (std::size_t i{ pos }; i < size - 1; ++i)
    {
        (*this)[i] = (*this)[i + 1];
    }

    --size;
}

template<typename T>
void Vector<T>::insert(std::size_t pos, T val)
{
    if (pos >= size)
        throw std::runtime_error
        ("Index is outside the bounds of the vector");

    if (size + 1 > capacity)
    {
        Vector temp(*this);
        this->Resize(size + 1);
        for (std::size_t i{ 0 }; i < size - 1; ++i)
        {
            (*this)[i] = temp[i];
        }
    }
    else
    {
        ++size;
    }


    for (std::size_t i{ size - 1 }; i > pos; --i)
    {
        T temp = (*this)[i];
        (*this)[i] = (*this)[i - 1];
        (*this)[i - 1] = temp;
    }

    (*this)[pos] = val;

}

template<typename T>
void Vector<T>::push_back(T value)
{
    if (size + 1 > capacity)
    {
        Vector res(*this);

        Resize(size + 1);

        for (std::size_t i{ 0 }; i < size; ++i)
            (*this)[i] = res[i];
    }
    else
    {
        ++size;
    }

    (*this)[size - 1] = value;
}

template<typename T>
void Vector<T>::Resize(std::size_t NewSize)
{
    data = new T[2 * NewSize];

    capacity = 2 * NewSize;
    size = NewSize;
}

template<typename T>
std::size_t Vector<T>::length() const
{
    return size;
}

template<typename T>
T& Vector<T>::operator[](std::size_t index)
{
    if (index >= size)
        throw std::runtime_error
        ("Index is outside the bounds of the vector");

    return data[index];
}

template<typename T>
T& Vector<T>::operator[](std::size_t index) const
{
    if (index >= size)
        throw std::runtime_error
        ("Index is outside the bounds of the vector");

    return data[index];
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
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
        data = new T[capacity];

        for (std::size_t i{ 0 }; i < size; ++i)
            data[i] = other.data[i];
    }

    return *this;
}

#endif //Vector_H