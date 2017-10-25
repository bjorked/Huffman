#ifndef NODE_HPP
#define NODE_HPP

#include <memory>

/*
 Represents a node on a Huffman tree.
 Each leaf node contains a symbol and its frequency in the text, while
 the non-leaf nodes posses an empty symbol and a sum of its left/right children's
 frequencies.
*/
struct Node
{
    char character;
    int frequency;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};

// Function needed to compare Nodes stored in a std::priority_queue
struct NodePtrComparison
{
    bool operator () (const std::shared_ptr<Node>&, const std::shared_ptr<Node>&) const;
};

#endif
