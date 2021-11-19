//
// Created by balin on 10/25/2021.
//

#ifndef BINARY_NODE_H
#define BINARY_NODE_H


struct BinaryNode {
    BinaryNode *parent,*left,*right;
    long int value;
    BinaryNode(long int v, BinaryNode* p): value(v), parent(p), left(nullptr), right(nullptr){};
};


#endif //BINARY_NODE_H
