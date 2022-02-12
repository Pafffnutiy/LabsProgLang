#ifndef QUEUE_H
#define QUEUE_H

#include "ADT.h"

class Queue
{
private:
	ADT** data;
	std::size_t size, count;
	int rear, front;


public:
	Queue();
	Queue(const Queue& other);
	Queue(std::size_t size);
   ~Queue();

    void erase(std::size_t index);
    void insert(std::size_t index, ADT* val);
	void pop_front();
	void push_back(ADT* val);

	std::size_t length() const;

	ADT*& operator[](std::size_t index);
	ADT*& operator[](std::size_t index) const;    
};

#endif //QUEUE_H