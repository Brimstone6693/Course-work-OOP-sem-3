#ifndef CUSTOMCONTAINER_H
#define CUSTOMCONTAINER_H

#include "SoftwarePackage.h"
#include <QVector>
#include <QList>
#include <functional>
#include <algorithm>

// Custom iterator for our container
template<typename T>
class CustomIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    explicit CustomIterator(QVector<T>* container, int index = 0) : m_container(container), m_index(index) {}
    
    CustomIterator& operator++() { ++m_index; return *this; }  // Pre-increment
    CustomIterator operator++(int) { CustomIterator tmp = *this; ++(*this); return tmp; }  // Post-increment
    
    CustomIterator& operator--() { --m_index; return *this; }  // Pre-decrement
    CustomIterator operator--(int) { CustomIterator tmp = *this; --(*this); return tmp; }  // Post-decrement
    
    bool operator==(const CustomIterator& other) const { return m_index == other.m_index; }
    bool operator!=(const CustomIterator& other) const { return !(*this == other); }
    
    reference operator*() { return m_container->operator[](m_index); }
    const reference operator*() const { return m_container->operator[](m_index); }
    
    pointer operator->() { return &(m_container->operator[](m_index)); }
    const T* operator->() const { return &(m_container->operator[](m_index)); }

private:
    QVector<T>* m_container;
    int m_index;
};

// Custom container based on QVector
template<typename T>
class CustomContainer
{
public:
    using iterator = CustomIterator<T>;
    using const_iterator = const CustomIterator<T>;

    CustomContainer() = default;
    
    // Add element to container
    void push_back(const T& item);
    
    // Remove element by index
    void erase(int index);
    
    // Remove element by iterator
    void erase(iterator it);
    
    // Get element by index
    T& operator[](int index);
    const T& operator[](int index) const;
    
    // Get size
    int size() const;
    
    // Check if empty
    bool empty() const;
    
    // Get iterator to beginning
    iterator begin();
    
    // Get iterator to end
    iterator end();
    
    // Find elements by condition
    template<typename Predicate>
    QList<T> find(Predicate pred);
    
    // Remove elements by condition
    template<typename Predicate>
    void remove_if(Predicate pred);
    
    // Clear all elements
    void clear();
    
    // Get all elements
    QVector<T> getAll() const;
    
    // Merge with another container
    void merge(const CustomContainer<T>& other);

private:
    QVector<T> m_data;
};

// Implementation of template methods
template<typename T>
void CustomContainer<T>::push_back(const T& item)
{
    m_data.push_back(item);
}

template<typename T>
void CustomContainer<T>::erase(int index)
{
    if (index >= 0 && index < m_data.size()) {
        m_data.remove(index);
    }
}

template<typename T>
void CustomContainer<T>::erase(iterator it)
{
    int index = it.m_index;
    if (index >= 0 && index < m_data.size()) {
        m_data.remove(index);
    }
}

template<typename T>
T& CustomContainer<T>::operator[](int index)
{
    return m_data[index];
}

template<typename T>
const T& CustomContainer<T>::operator[](int index) const
{
    return m_data[index];
}

template<typename T>
int CustomContainer<T>::size() const
{
    return m_data.size();
}

template<typename T>
bool CustomContainer<T>::empty() const
{
    return m_data.isEmpty();
}

template<typename T>
typename CustomContainer<T>::iterator CustomContainer<T>::begin()
{
    return iterator(&m_data, 0);
}

template<typename T>
typename CustomContainer<T>::iterator CustomContainer<T>::end()
{
    return iterator(&m_data, m_data.size());
}

template<typename T>
template<typename Predicate>
QList<T> CustomContainer<T>::find(Predicate pred)
{
    QList<T> result;
    for (const auto& item : m_data) {
        if (pred(item)) {
            result.append(item);
        }
    }
    return result;
}

template<typename T>
template<typename Predicate>
void CustomContainer<T>::remove_if(Predicate pred)
{
    for (int i = m_data.size() - 1; i >= 0; --i) {
        if (pred(m_data[i])) {
            m_data.remove(i);
        }
    }
}

template<typename T>
void CustomContainer<T>::clear()
{
    m_data.clear();
}

template<typename T>
QVector<T> CustomContainer<T>::getAll() const
{
    return m_data;
}

template<typename T>
void CustomContainer<T>::merge(const CustomContainer<T>& other)
{
    for (const auto& item : other.m_data) {
        m_data.push_back(item);
    }
}

#endif // CUSTOMCONTAINER_H