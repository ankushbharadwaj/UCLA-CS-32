//
//  hash.hpp
//  project 4 round 2
//
//  Created by Ankush Bharadwaj on 6/6/19.
//  Copyright © 2019 Ankush Bharadwaj. All rights reserved.
//
#ifndef HASH_H
#define HASH_H
#include <string>
#include <list>
#include "node.h"

const int ARRAY_SIZE = 1000;
class Hash // my hash table implementation
{
public:
    Hash();
    ~Hash();
    void insert(const std::string& s, int offset);
    bool find(const std::string& s, int &offset, Node* &p);
private:
    Node* mLast;
    std::list <Node>* mArr[ARRAY_SIZE]; // an array of Node list pointers
    int hashVal(const std::string& s);
};
#endif
