#ifndef STACK_H
#define STACK_H

#include <iostream>

template<typename T>
class Stack
{
private:
	std::size_t size, capacity;
	T* data;

public:
	struct Iterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		Iterator(pointer ptr)
			: m_ptr(ptr)
		{}

		Iterator(const Iterator& mit)
			: m_ptr(mit.m_ptr)
		{}

		bool operator< (const Iterator& tmp) const 
		{ return m_ptr < tmp.m_ptr; }
		difference_type operator-(const Iterator& rhs) const 
		{ return m_ptr - rhs.m_ptr; }

		reference operator*() const
		{
			return *m_ptr;
		}

		pointer operator->() {
			return m_ptr;
		}

		Iterator operator+(std::size_t x) const
		{
			return Iterator(m_ptr + x);
		}

		Iterator operator-(std::size_t x) const
		{
			return Iterator(m_ptr - x);
		}

		Iterator& operator++()
		{
			m_ptr++;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		Iterator& operator--()
		{
			--m_ptr;
			return *this;
		}

		Iterator operator--(int)
		{
			Iterator tmp(*this);
			--m_ptr;
			return tmp;
		}

		friend bool operator==
			(const Iterator& a, const Iterator& b)
		{
			return a.m_ptr == b.m_ptr;
		}

		friend bool operator!=
			(const Iterator& a, const Iterator& b)
		{
			return a.m_ptr != b.m_ptr;
		}

	private:
		pointer m_ptr;
	};

	Iterator begin() { return Iterator(&data[0]); }
	Iterator end() { return Iterator(&data[size]); }

	Stack();
	Stack(const Stack& other);
	Stack(std::size_t s);
	~Stack();

	void Resize(std::size_t NewSize); //with losing data
	void push_back(T val);
	void pop_back();
	void push_up(T val);
	void pop_up();
	std::size_t length() const;

	T& operator[](std::size_t index) const;
};

template<typename T>
Stack<T>::Stack()
	:size{ 0 }, capacity{ 0 }, data{ nullptr }
{}

template<typename T>
Stack<T>::Stack(const Stack<T>& other)
	: size{ other.size }, capacity{ other.capacity }
{
	data = new T[capacity];

	std::copy(other.data, other.data + size, data);
}

template<typename T>
Stack<T>::Stack(std::size_t s)
	: size{ s }, capacity{ 2 * s }
{
	data = new T[2 * s];
}

template<typename T>
Stack<T>::~Stack()
{
	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}
}

template<typename T>
void Stack<T>::Resize(std::size_t NewSize)
{
	data = new T[2 * NewSize];

	capacity = 2 * NewSize;
	size = NewSize;
}

template<typename T>
void Stack<T>::push_back(T val)
{
	if (size + 1 > capacity)
	{
		Stack res(*this);

		this->Resize(size + 1);

		for (std::size_t i{ 0 }; i < size - 1; ++i)
			(*this)[i] = res[i];
	}
	else
	{
		++size;
	}

	(*this)[size - 1] = val;
}

template<typename T>
void Stack<T>::pop_back()
{
	if (size == 0) throw std::runtime_error("Stack is empty");

	--size;
}

template<typename T>
void Stack<T>::push_up(T val)
{
	if (size + 1 > capacity)
	{
		Stack temp(*this);
		this->Resize(size + 1);
		for (std::size_t i{ 1 }; i < size; ++i)
		{
			(*this)[i] = temp[i - 1];
		}
	}
	else
	{
		++size;

		for (std::size_t i{ size - 1 }; i > 0; --i)
		{
			T temp = (*this)[i];
			(*this)[i] = (*this)[i - 1];
			(*this)[i - 1] = temp;
		}
	}

	(*this)[0] = val;
}

template<typename T>
void Stack<T>::pop_up()
{
	if (size == 0) throw std::runtime_error("Stack is empty");

	for (std::size_t i{ 0 }; i < size - 1; ++i)
		(*this)[i] = (*this)[i + 1];

	--size;
}

template<typename T>
std::size_t Stack<T>::length() const
{
	return size;
}

template<typename T>
T& Stack<T>::operator[](std::size_t index) const
{
	if (index >= size)
		throw std::runtime_error
		("Index is outside the bounds of the vector");

	return data[index];
}

#endif //STACK_H
