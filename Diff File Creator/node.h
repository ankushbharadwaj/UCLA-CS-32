//
//  Node.h
//  project 4 round 2
//
//  Created by Ankush Bharadwaj on 6/6/19.
//  Copyright © 2019 Ankush Bharadwaj. All rights reserved.
//

#ifndef Node_h
#define Node_h
struct Node
{
    Node(int offset, std::string data, Node* next) :offset(offset), data(data), next(next)
    {}
    int offset;
    std::string data;
    Node* next;
    bool used = false;
};
#endif /* Node_h */
