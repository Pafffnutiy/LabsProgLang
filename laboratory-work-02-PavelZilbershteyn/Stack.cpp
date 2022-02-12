#include "Stack.h"

Stack::Stack() 
	:size{ 0 }, capacity{ 0 }, data{ nullptr }
{}

Stack::Stack(const Stack& other)
	: size{ other.size }, capacity{ other.capacity }
{
	data = new ADT * [capacity];

	for (std::size_t i{ 0 }; i < size; ++i)
		data[i] = other.data[i];
}

Stack::Stack(std::size_t s)
	: size{ s }, capacity{ 2 * s }
{
	data = new ADT * [2 * s];
}

Stack::~Stack()
{
	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}
}

void Stack::Resize(std::size_t NewSize)
{
	data = new ADT * [2 * NewSize];

	capacity = 2 * NewSize;
	size = NewSize;
}

void Stack::push_back(ADT* val)
{
	if (size + 1 > capacity)
	{
		Stack res(*this);

		this->Resize(size + 1);

		for (std::size_t i{ 0 }; i < size-1; ++i)
			(*this)[i] = res[i];
	}
	else
	{
		++size;
	}

	(*this)[size - 1] = val;
}

void Stack::pop_back()
{
	if (size == 0) throw std::runtime_error("Stack is empty");

	--size;
}

void Stack::push_up(ADT* val)
{
	if (size + 1 > capacity)
	{
		Stack temp(*this);
		this->Resize(size + 1);
		for (std::size_t i{ 1 }; i < size; ++i)
		{
			(*this)[i] = temp[i-1];
		}
	}
	else
	{
		++size;

		for (std::size_t i{ size - 1 }; i > 0; --i)
		{
			ADT* temp = (*this)[i];
			(*this)[i] = (*this)[i - 1];
			(*this)[i - 1] = temp;
		}
	}

	(*this)[0] = val;
}

void Stack::pop_up()
{
	if (size == 0) throw std::runtime_error("Stack is empty");

	for (std::size_t i{ 0 }; i < size - 1; ++i)
		(*this)[i] = (*this)[i + 1];

	--size;
}

std::size_t Stack::length() const
{
	return size;
}

/*ADT*& Stack::operator[](std::size_t index)
{
	if (index >= size) 
		throw std::runtime_error
			("Index is outside the bounds of the vector");

	return data[index];
}*/

ADT*& Stack::operator[](std::size_t index) const
{
	if (index >= size) 
		throw std::runtime_error
			("Index is outside the bounds of the vector");

	return data[index];
}
