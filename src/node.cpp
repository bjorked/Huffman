#include "node.hpp"

// Nodes with lowest frequency have the highest priority
bool NodePtrComparison::operator () (const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs) const
{
    return lhs->frequency > rhs->frequency;
}
