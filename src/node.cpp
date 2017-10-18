#include "node.hpp"

bool operator< (const Node &lhs, const Node &rhs)
{
    return lhs.frequency > rhs.frequency;
}
