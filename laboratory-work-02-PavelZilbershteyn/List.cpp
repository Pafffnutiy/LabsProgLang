#include <iostream>
#include "List.h"

List::List()
	:head{ nullptr }
{}

void List::erase(std::size_t index)
{
	if (index >= length()) 
		throw std::runtime_error
			("index was outside the bounds of the list");
	if (length() == 1)
		throw std::runtime_error
			("Attempt to delete the head of the list");

	if (index == length() - 1) pop_back();
	else if (index == 0) pop_front();
	else (*this)[index - 1]->next = (*this)[index]->next;
}

void List::insert(std::size_t index, ADT* val)
{
	if (index >= length()) 
		throw std::runtime_error
			("index was outside the bounds of the list");

	if (index == 0) push_front(val);
	else {
		Node* tmp = new Node(val);

		tmp->next = (*this)[index];
		(*this)[index-1]->next = tmp;
	}
}

void List::push_back(ADT* val)
{
	Node* tmp = new Node(val);
	if (head == nullptr)
		head = tmp;
	else {
		Node* current = head;

		while (current->next != nullptr)
			current = current->next;

		current->next = tmp;
	}
}

void List::pop_back()
{
	if (length() == 0)
		throw std::runtime_error
			("List is empty");

	if (length() == 1) 
		throw std::runtime_error
			("Attempt to delete the head of the list");

	(*this)[length() - 2]->next = nullptr;
}

void List::push_front(ADT* val)
{
	Node* tmp = new Node(val);
	tmp->next = head;
	head = tmp;
}

void List::pop_front()
{
	if (length() == 0) 
		throw std::runtime_error
			("List is empty");

	if (length() == 1) 
		throw std::runtime_error
			("Attempt to delete the head of the list");
	
	head = (*this)[1];
}

std::size_t List::length() const
{
	if (head == nullptr) return 0;

	std::size_t size{ 1 };
	Node* current = head;

	while (current->next != nullptr)
	{
		current = current->next;
		++size;
	}

	return size;
}

List::Node*& List::operator[](std::size_t index)
{
	if (index>=length())
		throw std::runtime_error
			("index was outside the bounds of the list");

	Node* current = head;

	for (std::size_t pos{ 0 }; pos < index; ++pos)
	{
		current = current->next;
	}

	return current;
}

List::Node*& List::operator[](std::size_t index) const
{
	if (index >= length()) 
		throw std::runtime_error
			("index was outside the bounds of the list");

	Node* current = head;

	for (std::size_t pos{ 0 }; pos < index; ++pos)
	{
		current = current->next;
	}

	return current;
}
