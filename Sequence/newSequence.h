//
//  newSequence.hpp
//  test hwk 1 
//
//  Created by Ankush Bharadwaj on 4/15/19.
//  Copyright © 2019 Ankush Bharadwaj. All rights reserved.
//

#ifndef NEW_SEQUENCE_H
#define NEW_SEQUENCE_H

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

const int DEFAULT_MAX_ITEMS = 250;

using ItemType = unsigned long;

class Sequence
{
public:
    Sequence(int size = DEFAULT_MAX_ITEMS);    // Create a new Sequence of size, defaulted to DEFAULT_MAX_ITEMS
    Sequence(const Sequence& other);  // Copy constructor for the new Sequence.
    Sequence& operator=(const Sequence& rhs); // Assignment operator for = for the new Sequence.
    ~Sequence();     // Destructor for the new Sequence.
    bool empty() const;  // Return true if the Sequence is empty, otherwise false.
    int size() const;    // Return the number of items in the Sequence.

    int insert(int pos, const ItemType& value);
    // Insert value into the sequence so that it becomes the item at
    // position pos.  The original item at position pos and those that
    // follow it end up at positions one higher than they were at before.
    // Return pos if 0 <= pos <= size() and the value could be
    // inserted.  (It might not be, if the sequence has a fixed capacity,
    // e.g., because it's implemented using a fixed-size array.)  Otherwise,
    // leave the sequence unchanged and return -1.  Notice that
    // if pos is equal to size(), the value is inserted at the end.
    
    int insert(const ItemType& value);
    // Let p be the smallest integer such that value <= the item at
    // position p in the sequence; if no such item exists (i.e.,
    // value > all items in the sequence), let p be size().  Insert
    // value into the sequence so that it becomes the item at position
    // p.  The original item at position p and those that follow it end
    // up at positions one higher than before.  Return p if the value
    // was actually inserted.  Return -1 if the value was not inserted
    // (perhaps because the sequence has a fixed capacity and is full).
    
    bool erase(int pos);
    // If 0 <= pos < size(), remove the item at position pos from
    // the Sequence (so that all items that followed this item end up at
    // positions one lower than they were at before), and return true.
    // Otherwise, leave the Sequence unchanged and return false.
    
    int remove(const ItemType& value);
    // Erase all items from the Sequence that == value.  Return the
    // number of items removed (which will be 0 if no item == value).
    
    bool get(int pos, ItemType& value) const;
    // If 0 <= pos < size(), copy into value the item at position pos
    // in the Sequence and return true.  Otherwise, leave value unchanged
    // and return false.
    
    bool set(int pos, const ItemType& value);
    // If 0 <= pos < size(), replace the item at position pos in the
    // Sequence with value and return true.  Otherwise, leave the Sequence
    // unchanged and return false.
    
    int find(const ItemType& value) const;
    // Let p be the smallest integer such that value == the item at
    // position p in the Sequence; if no such item exists, let p be -1.
    // Return p.
    
    void swap(Sequence& other);
    // Exchange the contents of this Sequence with the other one.
    
    void dump() const;
    
private:
    int m_size;
    int max_size;
    ItemType* m_value;
};

#endif /* defined(NEW_SEQUENCE_H) */
