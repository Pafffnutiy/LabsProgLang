#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>

template <typename T>
class Queue
{
private:
	T* data;
	std::size_t size, count;
	int rear, front;

public:
	struct Iterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = value_type*;
		using reference = value_type&;

		Iterator(pointer ptr) : m_ptr(ptr) {}

		Iterator(pointer ptr, std::size_t size, 
			T* zero, std::size_t pos) 
			: m_ptr(ptr), size(size),
			zero(zero), pos(pos) {}

		Iterator(const Iterator& mit) 
			: m_ptr(mit.m_ptr), size(mit.size),
			zero(mit.zero), pos(mit.pos) {}

		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		Iterator& operator++() {
			++pos;

			if (m_ptr - zero == size - 1)
				m_ptr = zero;
			else 
				m_ptr++;

			return *this; 
		}

		Iterator operator++(int) 
		{ 
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		friend bool operator== 
			(const Iterator& a, const Iterator& b) 
		{ return a.pos == b.pos; }
		friend bool operator!= 
			(const Iterator& a, const Iterator& b)
		{ return a.pos != b.pos; }

		std::size_t size;
		T* zero;
		std::size_t pos;
	private:
		T* m_ptr;
	};

	Iterator begin() const 
	{ 
		Iterator i(&data[front], size, &data[0], 0);
		return i;
	}

	Iterator end() const 
	{ 
		Iterator i(&data[rear] + 1, size, &data[0], size);
		return i;
	}


	Queue();
	Queue(const Queue& other);
	Queue(std::size_t size);
	~Queue();

	void erase(std::size_t index);
	void insert(std::size_t index, T val);
	void pop_front();
	void push_back(T val);

	void Dump() const;

	std::size_t length() const;

	T& operator[](std::size_t index);
	T& operator[](std::size_t index) const;
};

template <typename T>
Queue<T>::Queue()
	:data{ nullptr }, size{1}, count{0}, rear{0}, front{-1}
{}

template <typename T>
Queue<T>::Queue(const Queue& other)
	: size{ other.size }, count{ other.count }, rear{ other.rear },
	front{ other.front }
{
	data = new T[size];

	std::copy(other.data, other.data + size, data);
}

template <typename T>
Queue<T>::Queue(std::size_t size)
	: size{ size }, count{ 0 }, rear{ 0 }, front{ -1 }
{
	data = new T[size];

	std::fill(data, data + size, 0);
}

template <typename T>
Queue<T>::~Queue()
{
	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}
}

template <typename T>
void Queue<T>::erase(std::size_t index)
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
			T temp = (*this)[i % size];
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

template <typename T>
void Queue<T>::insert(std::size_t index, T val)
{
	if (index >= size)
		throw std::runtime_error
		("Index is outside the bounds of the queue");

	if (index == rear + 1) push_back(val);

	if ((*this)[index] == 0/*nullptr*/)
		(*this)[index] = val;
	else {
		if (index != front)
		{
			std::size_t end = (index - rear > 0) ? 
				rear + size : rear;
			for (std::size_t i{ index + 1 }; i < end; ++i)
			{
				T temp = (*this)[i % size];
				(*this)[i % size] = 
					(*this)[(i - 1) % size];
				(*this)[(i - 1) % size] = temp;
			}
			std::swap((*this)[index], (*this)[rear]);
			(*this)[index] = val;
		}
	}
}

template <typename T>
void Queue<T>::pop_front()
{
	if (count == 0)
		throw std::runtime_error
		("Queue is empty");

	(*this)[front] = 0/*nullptr*/;

	for (std::size_t i = front; i < size + front; ++i)
	{
		T temp = (*this)[i % size];
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

template <typename T>
void Queue<T>::push_back(T val)
{
	if ((rear + 1) % size == front)
		front = (front + 1) % size;

	if (count == 0)
		++front;

	if (count < size)
		++count;

	if ((*this)[rear] != 0/*nullptr*/)
		rear = (rear + 1) % size;

	(*this)[rear] = val;
}

template <typename T>
std::size_t Queue<T>::length() const
{
	return size;
}

template <typename T>
T& Queue<T>::operator[](std::size_t index)
{
	if (index >= size)
		throw std::runtime_error
		("Index is outside the bounds of the queue");

	return data[index];
}

template <typename T>
T& Queue<T>::operator[](std::size_t index) const
{
	if (index >= size)
		throw std::runtime_error
		("Index is outside the bounds of the queue");

	return data[index];
}

template <typename T>
void Queue<T>::Dump() const
{
	for (std::size_t i{ 0 }; i < length(); ++i)
		std::cout << (*this)[i] << ' ';

	std::cout << '\n';

	std::cout << front << ' ' << rear << '\n';
}
#endif //QUEUE_HPP