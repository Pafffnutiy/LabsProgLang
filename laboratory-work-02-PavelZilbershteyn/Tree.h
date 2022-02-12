#ifndef TREE_H
#define TREE_H

#include "ADT.h"

// Нумерация дерева начинается с 1
// Не с 0! Головной элемент имеет индекс 1
class Tree
{
private:
	struct Node {
		Node* left = nullptr;
		Node* right = nullptr;
		ADT* val;
	};

	Node* head;
	std::size_t steps = 0, size = 0;

public:
	Tree();
	Tree(const Tree& other);
	Tree(std::size_t steps);
   ~Tree() = default;

   //void Resize(std::size_t NewSteps);

   void erase(std::size_t index);
   //Deleting all children starting from index

   void insert(std::size_t index, ADT* val);

   std::size_t length() const;

   Node*& operator[](std::size_t index);
   Node*& operator[](std::size_t index) const;


};

#endif
