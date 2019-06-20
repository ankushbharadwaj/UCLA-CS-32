//
//  Sequence.cpp
//  project 2 tester 1
//
//  Created by Ankush Bharadwaj on 4/23/19.
//  Copyright © 2019 Ankush Bharadwaj. All rights reserved.
//

#include "Sequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence()
: m_size(0)
{
    head = new Node;
    head->m_next = head;
    head->m_previous = head;
}

Sequence::~Sequence()
{
    while (head->m_previous != head)
    {
        Node* deleter = head->m_previous;
        deleter->m_previous->m_next= head;
        head->m_previous = deleter->m_previous;
        delete deleter;
    }
    delete head;
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

Sequence::Sequence(const Sequence& other)
: m_size(other.m_size)
{
    head = new Node;
    head->m_next = head;
    head->m_previous = head;
    
    for (Node* p = other.head->m_next; p != other.head; p = p->m_next)
    {
        Node* adder = new Node;
        adder->m_value = p->m_value;
        adder->m_next = head;
        adder->m_previous = head->m_previous;
        head->m_previous->m_next = adder;
        head->m_previous = adder;
    }
    
}

bool Sequence::empty() const
{
    if (m_size == 0)
        return true;
    return false;
}

int Sequence::size() const
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
{
    if (pos < 0 || pos > size())
        return -1;
    if (pos >= 0 && pos < size())
    {
        Node* p = head->m_next;
        for (int i = 0; i < size(); i++)
        {
            if (i == pos)
            {
                Node* new_guy = new Node;
                new_guy->m_value = value;
                new_guy->m_next = p;
                new_guy->m_previous = p->m_previous;
                p->m_previous->m_next = new_guy;
                p->m_previous = new_guy;
                m_size++;
                return pos;
            }
            p = p->m_next;
        }
    }
    else if (pos == size())
    {
        Node* p = head->m_previous;
        Node* new_guy = new Node;
        new_guy->m_value = value;
        new_guy->m_next = head;
        new_guy->m_previous = p;
        p->m_next = new_guy;
        head->m_previous = new_guy;
        m_size++;
        return pos;
    }
    return pos;
}

int Sequence::insert(const ItemType& value)
{
    if (empty())
    {
        Node* new_guy = new Node;
        new_guy->m_value = value;
        new_guy->m_next = head;
        new_guy->m_previous = head;
        head->m_next = new_guy;
        head->m_previous = new_guy;
        m_size++;
        return 0;
    }
    int pos = 0;
    Node* p = head;
    for (int i = 0; i < size(); i++)
    {
        p = p->m_next;
        if (p->m_value >= value)
        {
            pos = i;
            break;
        }
        else
            pos = size();
    }
    insert(pos, value);
    return pos;
}

bool Sequence::erase(int pos)
{
    if (pos >= 0 || pos < size())
    {
        Node* p = head;
        for (int i = 0; i < size(); i++)
        {
            p = p->m_next;
            if (i == pos)
            {
                Node* deleter = p;
                p->m_previous->m_next = deleter->m_next;
                p->m_next->m_previous = deleter->m_previous;
                delete deleter;
                m_size--;
                return true;
            }
        }
    }
    return false;
}


int Sequence::remove(const ItemType& value)
{
    int removed = 0;
    Node* p;
    for (p = head->m_next; p != head; p = p->m_next)
    {
        if (p->m_value == value)
        {
            Node* deleter = p;
            p->m_previous->m_next = deleter->m_next;
            p->m_next->m_previous = deleter->m_previous;
            delete deleter;
            removed++;
            m_size--;
        }
    }
    return removed;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos >= 0 || pos < size())
    {
        Node* p = head;
        for (int i = 0; i < size(); i++)
        {
            p = p->m_next;
            if (i == pos)
            {
                value = p->m_value;
                return true;
            }
        }
    }
    return false;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos >= 0 || pos < size())
    {
        Node* p = head;
        for (int i = 0; i < size(); i++)
        {
            p = p->m_next;
            if (i == pos)
            {
                p->m_value = value;
                return true;
            }
        }
    }
    return false;
}

int Sequence::find(const ItemType& value) const
{
    if (size() > 0)
    {
        Node* p = head;
        for (int i = 0; i < size(); i++)
        {
            p = p->m_next;
            if (p->m_value == value)
                return i;
        }
    }
    return -1;
}

void Sequence::swap(Sequence& other)
{
    Node* temp_head = other.head;
    other.head = head;
    head = temp_head;
    
    int temp_size = other.m_size;
    other.m_size = m_size;
    m_size = temp_size;
}

void Sequence::dump() const
{
    for (Node* p = head->m_next; p != head; p = p->m_next)
        cerr << p->m_value << " " ;
    cerr << endl;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if (seq2.empty() || seq2.size() > seq1.size())
        return -1;
    ItemType val_1, val_2;
    bool is_Sequence = false;
    int startPoint;
    for (int i  = 0; i < seq1.size(); i++)
    {   seq1.get(i, val_1);
        seq2.get(0, val_2);
        if (val_1 == val_2)
        {
            startPoint = i;
            for (int j = 0, iPos = i; j<seq2.size(); j++, iPos++)
            {
                is_Sequence = true;
                seq2.get(j, val_2);
                seq1.get(iPos, val_1);
                if(val_2 != val_1)
                {
                    is_Sequence = false;
                    break;
                }
            }
            if (is_Sequence)
                return startPoint;
        }
    }
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    Sequence temp_result(result);
    while (!temp_result.empty())
        temp_result.erase(0);
    if (seq1.empty())
        temp_result = seq2;
    else if (seq2.empty())
        temp_result = seq1;
    ItemType val_1, val_2;
    int q = 0, r = 0, p = 0;
    while (q < seq1.size() || r < seq2.size())
    {
        if (q < seq1.size())
        {
            seq1.get(q, val_1);
            temp_result.insert(p, val_1);
            q++;
            p++;
        }
        if (r < seq2.size())
        {
            seq2.get(r, val_2);
            temp_result.insert(p, val_2);
            r++;
            p++;
        }
    }
    result = temp_result;
}
