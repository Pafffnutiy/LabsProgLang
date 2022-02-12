#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <algorithm>

template <typename T>
class List
{
private:
    struct Node
    {
        Node* next = nullptr;
        T value;

        Node(T val)
            :next{ nullptr }, value{ val }
        {}
    };

    Node* head;

public:
    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(Node* ptr) : m_ptr(ptr) {}
        Iterator(const Iterator& mit) : m_ptr(mit.m_ptr) {}

        const T& operator*() const { return m_ptr->value; }
        T& operator*() { return m_ptr->value; }
        pointer operator->() { return &m_ptr; }


        Iterator& operator++() {
            m_ptr = m_ptr->next;
            return *this;
        }
        Iterator operator++(int) 
        { Iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator== 
            (const Iterator& a, const Iterator& b) 
        { return a.m_ptr == b.m_ptr; };
        friend bool operator!= 
            (const Iterator& a, const Iterator& b) 
        { return a.m_ptr != b.m_ptr; };

    private:
        Node* m_ptr;
    };

    Iterator begin() const { return Iterator(head); }
    Iterator end()   const { return Iterator(nullptr); }

    List();
    List(const List& other) = default;
    ~List() = default;

    void erase(std::size_t index);
    void insert(std::size_t index, T val);
    void push_back(T val);
    void pop_back();
    void push_front(T val);
    void pop_front();

    std::size_t length() const;
    size_t size() const { return std::distance(begin(), end()); }

    Node*& operator[](std::size_t index);
    Node*& operator[](std::size_t index) const;
};

template <typename T>
List<T>::List()
    :head{ nullptr }
{}

template <typename T>
void List<T>::erase(std::size_t index)
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

template <typename T>
void List<T>::insert(std::size_t index, T val)
{
    if (index >= length())
        throw std::runtime_error
        ("index was outside the bounds of the list");

    if (index == 0) push_front(val);
    else {
        Node* tmp = new Node(val);

        tmp->next = (*this)[index];
        (*this)[index - 1]->next = tmp;
    }
}

template <typename T>
void List<T>::push_back(T val)
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

template <typename T>
void List<T>::pop_back()
{
    if (length() == 0)
        throw std::runtime_error
        ("List is empty");

    if (length() == 1)
        throw std::runtime_error
        ("Attempt to delete the head of the list");

    (*this)[length() - 2]->next = nullptr;
}

template <typename T>
void List<T>::push_front(T val)
{
    Node* tmp = new Node(val);
    tmp->next = head;
    head = tmp;
}

template <typename T>
void List<T>::pop_front()
{
    if (length() == 0)
        throw std::runtime_error
        ("List is empty");

    if (length() == 1)
        throw std::runtime_error
        ("Attempt to delete the head of the list");

    head = (*this)[1];
}

template <typename T>
std::size_t List<T>::length() const
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

template <typename T>
typename List<T>::Node*& List<T>::operator[](std::size_t index)
{
    if (index > length())
        throw std::runtime_error
        ("index was outside the bounds of the list");

    Node* current = head;

    for (std::size_t pos{ 0 }; pos < index; ++pos)
    {
        current = current->next;
    }

    return current;
}

template <typename T>
typename List<T>::Node*& List<T>::operator[](std::size_t index) const
{
    if (index >= length())
        throw std::runtime_error
        ("index was outside the bounds of the list");

    Node current = head;

    for (std::size_t pos{ 0 }; pos < index; ++pos)
    {
        current = current.next;
    }

    return current;
}
#endif //LIST_HPP