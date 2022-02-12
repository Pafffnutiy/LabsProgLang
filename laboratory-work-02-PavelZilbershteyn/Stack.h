/*#include "DateAndTime.h"
#include "BigNumber.h"
#include "YearFromAdam.h"
#include "Matrix.h"*/

#ifndef STACK_H
#define STACK_H

#include "ADT.h"

class Stack
{
private:
	std::size_t size, capacity;
	ADT** data;

public:
	Stack();
	Stack(const Stack& other);
	Stack(std::size_t s);
   ~Stack();
    
    void Resize(std::size_t NewSize); //with losing data
	void push_back(ADT* val);
	void pop_back();
	void push_up(ADT* val);
	void pop_up();
	std::size_t length() const;

	//ADT*& operator[](std::size_t index);
	//CAN WE CHANGE ELEMENTS IN STACK?

	ADT*& operator[](std::size_t index) const;
};

#endif //STACK_H
