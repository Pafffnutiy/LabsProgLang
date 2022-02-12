#include <iostream>
#include "Tree.h"
#include <cmath>
#include <vector>

static 
std::vector<bool> Dec2Bin(std::size_t param)
{
    std::vector<bool> bits;

    while (param)
    {
        bits.push_back(param % 2);
        param >>= 1;
    }

    std::reverse(bits.begin(), bits.end());

    return bits;
}

Tree::Tree()
    :head{ nullptr }
{}

Tree::Tree(const Tree& other)
    : steps{ other.steps }, size{ other.size }
{
    head = new Node;
    head = other.head;
}
Tree::Tree(std::size_t steps)
    : steps{ steps }
{
    head = new Node;
    size = std::pow(2, steps) - 1;

    for (std::size_t i{ 2 }; i <= size / 2; ++i)
    {
        (*this)[i] = new Node;
        (*this)[i]->val = nullptr;
        /*if (i % 2)
            (*this)[i / 2]->right = (*this)[i];
        else
            (*this)[i / 2]->left = (*this)[i];*/
    }
}

void Tree::erase(std::size_t index)
{
    if (index > size || index == 0)
        throw std::runtime_error
            ("Index is outside the bounds of the vector");

    (*this)[index]->val = nullptr;
    (*this)[index]->left = nullptr;
    (*this)[index]->right = nullptr;
}

void Tree::insert(std::size_t index, ADT* val)
{
    if (index > size || index == 0)
        throw std::runtime_error
            ("Index is outside the bounds of the vector");

    double step = std::log2(index);
    std::size_t delta = steps - static_cast<int>(step) - 1;

    steps += delta;

    size = std::pow(2, steps) - 1;

    Node* cur = new Node;

    cur->left = (*this)[index];
    cur->right = nullptr;
    cur->val = val;

    (index % 2) ? ((*this)[index / 2]->right = cur) 
        : ((*this)[index / 2]->left = cur);
}

std::size_t Tree::length() const
{
    return size;
}

Tree::Node*& Tree::operator[](std::size_t index)
{
    /*if (head == nullptr)
        throw std::runtime_error
            ("Tree is empty");*/

    if (index > size || index == 0)
        throw std::runtime_error
            ("Index is outside the bounds of the vector");

    if (index == 1) return head;

    std::vector<bool> bits = Dec2Bin(index);
    bits.erase(bits.begin());

    Node* current = head;

    for (bool elem : bits)
        if (elem)
            current = current->right;
        else
            current = current->left;

    if (current == nullptr)
        current = new Node;

    (index % 2) ? ((*this)[index / 2]->right = current) 
        : ((*this)[index / 2]->left = current);

    return current;
}

Tree::Node*& Tree::operator[](std::size_t index) const
{
    if (head == nullptr)
        throw std::runtime_error
            ("Tree is empty");

    if (index >= size || index == 0)
        throw std::runtime_error
            ("Index is outside the bounds of the vector");

    std::vector<bool> bits = Dec2Bin(index);
    bits.erase(bits.begin());

    Node* current = head;

    for (bool elem : bits)
        if (elem)
            current = current->right;
        else
            current = current->left;

    if (current == nullptr)
        throw std::runtime_error
            ("Element doesn't exist");

    return current;
}
