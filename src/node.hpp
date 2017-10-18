#ifndef NODE_HPP
#define NODE_HPP

#include <memory>

struct Node
{
    char character;
    int frequency;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};

struct NodePtrComparison
{
    bool operator () (const std::shared_ptr<Node>, const std::shared_ptr<Node>) const;
};

#endif
