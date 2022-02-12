#ifndef LIST_H
#define LIST_H

#include "ADT.h"
class List
{
private:
	struct Node
	{
		Node* next = nullptr;
		ADT* value;

		Node(ADT* val)
			:next{ nullptr }, value{ val }
		{}
	};

	//std::size_t size = 0;
	Node* head;

public:
	List();
	List(const List& other) = default;
   ~List() = default;

   void erase(std::size_t index);
   void insert(std::size_t index, ADT* val);
   void push_back(ADT* val);
   void pop_back();
   void push_front(ADT* val);
   void pop_front();

   std::size_t length() const;

   Node*& operator[](std::size_t index);
   Node*& operator[](std::size_t index) const;

};

#endif //LIST_H