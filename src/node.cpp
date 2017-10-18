#include "node.hpp"

bool compareNodes(const Node &lhs, const Node &rhs)
{
    return lhs.frequency < rhs.frequency;
}
