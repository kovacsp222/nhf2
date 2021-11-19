//
// Created by balin on 10/25/2021.
//

#ifndef TERNARY_NODE_H
#define TERNARY_NODE_H


struct TernaryNode {
    TernaryNode *parent, *left, *middle, *right;
    long int value;

    TernaryNode(long int v, TernaryNode* p): value(v), parent(p), left(nullptr), middle(nullptr), right(nullptr){};
};



#endif //TERNARY_NODE_H
