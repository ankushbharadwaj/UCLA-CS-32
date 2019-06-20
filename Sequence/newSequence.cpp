//
//  newSequence.cpp
//  test hwk 1 
//
//  Created by Ankush Bharadwaj on 4/15/19.
//  Copyright © 2019 Ankush Bharadwaj. All rights reserved.
//

#include "newSequence.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Sequence::Sequence(int size)
{
    if (size < 0)
    {
        cerr << "Size must be non negative" << endl;
        exit(1);
    }
    else
    {
        m_size = 0;
        max_size = size;
        m_value = new ItemType[max_size];
    }
}

Sequence::Sequence(const Sequence& other)
{
    m_size = other.m_size;
    max_size = other.max_size;
    m_value = new ItemType[max_size];
    for (int i = 0; i < m_size; i++)
    {
        m_value[i] = other.m_value[i];
    }
}

Sequence& Sequence::operator=(const Sequence& rhs)
{
    if (this != &rhs)
    {
        Sequence temp(rhs);
        swap(temp);
    }
    return *this;
}

Sequence::~Sequence()
{
    delete [] m_value;
}

bool Sequence::empty() const
{
    if (m_size > 0)
    {
        return false;
    }
    return true;
}

int Sequence::size() const  
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
{
    if (pos >= 0 && pos <= size())
    {
        if (size() >= max_size)
        {
            return -1;
        }
        m_size++;
        if (pos == size())
        {
            m_value[size() - 1] = value;
        }
        for (int i = size() - 1; i >= pos; i--)
            m_value[i] = m_value[i-1];
        m_value[pos] = value;
        return pos;
    }
    return -1;   
}

int Sequence::insert(const ItemType& value)
{
    int p = 0;  // Default position is set as zero
    
    for (int i = 0; i < size(); i++)
    {
        if (m_value[i] >= value)
        {
            p = i;
            break;
        }
        else
        {
            p = size();
        }
    }
    if (p >= 0 && p <= size()) 
    {
        if (m_size < max_size)
        {
            m_size++;
            for (int i = size() - 1; i >= p; i--)
                m_value[i] = m_value[i-1];
            m_value[p] = value;
            return p;
        }
        else{
            return -1;
        }
    }
    
    return -1;
}

bool Sequence::erase(int pos)       // Erases the value at the position pos in the Sequence
{
    if (pos >= 0 && pos < size())
    {
        for (int i = pos; i < size(); i++)  // Loop through the Sequence and move all the items from pos to the end back by one, thus
            // effectively deleting the item at pos and then decrease the size by one
        {
            m_value[i] = m_value[i+1];
        }
        m_size--;
        return true;
    }
    return false;
}

int Sequence::remove(const ItemType& value) // Removes the value in the Sequence if it exists
{
    int removed = 0;
    
    for (int i = 0; i < size(); i++)        // Loop through the Sequence and check for whether value exists in the Sequence
    {
        if (m_value[i] == value)
        {
            for (int k = i; k < size(); k++)    // If the item exits, then move the items in the Sequence down by one and increase removed by 1
                m_value[k] = m_value[k+1];
            m_size--;
            removed++;
        }
    }
    return removed;
}

bool Sequence::get(int pos, ItemType& value) const      // Sets the value to the value in the Sequence at position pos
{
    if (pos >= 0 && pos < size())
    {
        value = m_value[pos];
        return true;
    }
    return false;
}

bool Sequence::set(int pos, const ItemType& value)      // Sets the value in the Sequence to the value paramenter at position pos
{
    if (pos >= 0 && pos < size())
    {
        m_value[pos] = value;
        return true;
    }
    return false;
}

int Sequence::find(const ItemType& value) const     // Finds the value passed within the Sequence if such an item exists
{
    int p = -1;
    if (size() > 0)
    {
        for (int i = 0; i < size(); i++)
        {
            if (m_value[i] == value)
            {
                p = i;
                return p;
            }
        }
    }
    return p;
}

void Sequence::swap(Sequence& other)        // Swaps the values in two Sequences, by creating a temporary assist array
{
    ItemType* temp_ptr;
    
    temp_ptr = m_value;
    m_value = other.m_value;
    other.m_value = temp_ptr;
    
    int temp_max_size;
    temp_max_size = max_size;
    max_size = other.max_size;
    other.max_size = temp_max_size;
    
    int temp_size;
    
    temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
}

void Sequence::dump() const {
    for(int i = 0; i < m_size; i++) {
        cerr << *(m_value+i) << " ";
    }
    cerr << endl;
}
