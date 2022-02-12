#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <cmath>
#include <vector>

// Numeration of tree starts from 1
// Not from 0! Head element has index 1
template <typename T>
class Tree
{
private:
	struct Node {
		Node* left = nullptr;
		Node* right = nullptr;
		T val;
	};

	Node* head;
	std::size_t steps = 0, size = 0;

public:
    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(Node* ptr, std::size_t ind, Node* beg)
            : m_ptr(ptr), index(ind), beg (beg) {}
        Iterator(const Iterator& mit)
            : m_ptr(mit.m_ptr) {}

        const T& operator*() const { return m_ptr->val; }
        T& operator*() { return m_ptr->val; }
        pointer operator->() { return &m_ptr; }


        Iterator& operator++() {
            ++index;
            std::vector<bool> bits = Dec2Bin(index);
            bits.erase(bits.begin());

            Node* current = beg;

            for (bool elem : bits)
                if (elem)
                    current = current->right;
                else
                    current = current->left;

            m_ptr = current;
            return *this;
        }


        Iterator operator++(int)
        {
            Iterator tmp = *this; ++(*this); return tmp;
        }

        friend bool operator==
            (const Iterator& a, const Iterator& b)
        {
            return a.m_ptr == b.m_ptr;
        };
        friend bool operator!=
            (const Iterator& a, const Iterator& b)
        {
            return a.m_ptr != b.m_ptr;
        };

    private:
        Node* m_ptr;
        std::size_t index;
        Node* beg;
    };

    Iterator begin() const { return Iterator(head, 1, head); }
    Iterator end()   const { return Iterator(nullptr, size+1, head); }


	Tree();
	Tree(const Tree& other);
	Tree(std::size_t steps);
	~Tree() = default;

	//void Resize(std::size_t NewSteps);

	void erase(std::size_t index);
	//Deleting all children starting from index

	void insert(std::size_t index, T val);

	std::size_t length() const;

	Node*& operator[](std::size_t index);
	Node*& operator[](std::size_t index) const;

    static
    std::vector<bool> Dec2Bin(std::size_t param);
};


template<typename T>
std::vector<bool> Tree<T>::Dec2Bin(std::size_t param)
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

template <typename T>
Tree<T>::Tree()
    :head{ nullptr }
{}

template <typename T>
Tree<T>::Tree(const Tree<T>& other)
    : steps{ other.steps }, size{ other.size }
{
    head = new Node;
    head = other.head;
}

template <typename T>
Tree<T>::Tree(std::size_t steps)
    : steps{ steps }
{
    head = new Node;
    size = std::pow(2, steps) - 1;

    for (std::size_t i{ 2 }; i <= size / 2; ++i)
    {
        (*this)[i] = new Node;
        (*this)[i]->val = 0;
    }
}

template <typename T>
void Tree<T>::erase(std::size_t index)
{
    if (index > size || index == 0)
        throw std::runtime_error
        ("Index is outside the bounds of the vector");

    (*this)[index]->val = 0;
    (*this)[index]->left = nullptr;
    (*this)[index]->right = nullptr;
}

template <typename T>
void Tree<T>::insert(std::size_t index, T val)
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

template <typename T>
std::size_t Tree<T>::length() const
{
    return size;
}

template <typename T>
typename Tree<T>::Node*& Tree<T>::operator[](std::size_t index)
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

template <typename T>
typename Tree<T>::Node*& Tree<T>::operator[](std::size_t index) const
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

#endif //TREE_HPP