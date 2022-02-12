#ifndef Vector_H
#define Vector_H

#include "ADT.h"

class Vector
{
private:
	ADT** data;
	std::size_t size, capacity;

public:
	Vector();
	Vector(std::size_t s);
	Vector(const Vector& other);
   ~Vector();

   void erase(std::size_t pos);
   void insert(std::size_t pos, ADT* val);
   void push_back(ADT* value);
   void Resize(std::size_t NewSize); // with losing data
   std::size_t length() const;

   ADT*& operator[](std::size_t index);
   ADT*& operator[](std::size_t index) const;
   Vector& operator=(const Vector& other);
};

#endif //Vector_H
