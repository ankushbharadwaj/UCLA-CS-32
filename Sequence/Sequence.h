//
//  Sequence.h
//  project 2
//
//  Created by Ankush Bharadwaj on 4/22/19.
//  Copyright © 2019 Ankush Bharadwaj. All rights reserved.
//

#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED
#include <string>
using namespace std;

using ItemType = unsigned long;

class Sequence
{
public:
    Sequence();
    ~Sequence();
    Sequence& operator=(const Sequence& value);
    Sequence(const Sequence& other);
    bool empty() const; //good
    int size() const; //good
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump() const;
private:
    struct Node
    {
        ItemType m_value;
        Node* m_next;       // Connects Nodes forward.
        Node* m_previous; 
    };
    Node* head;
    int m_size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);
#endif //SEQUENCE_INCLUDED
