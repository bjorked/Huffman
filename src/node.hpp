#ifndef NODE_HPP
#define NODE_HPP


struct Node
{
    char character;
    int frequency;
    Node* left;
    Node* right;
};

#endif

bool operator< (const Node&, const Node&);
