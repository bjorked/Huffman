#include "encoder.hpp"

Encoder::Encoder()
{}

void Encoder::Encode(const std::string& fileName)
{
    readyFile(fileName);
    findFrequency();
    closeFile();
    createNodes();
}

void Encoder::readyFile(const std::string &fileName)
{
    inputFile.open(fileName);
}

void Encoder::closeFile(void)
{
    inputFile.close();
}

void Encoder::findFrequency(void)
{
    char character;
    while (inputFile.get(character))
        ++frequencyTable[character];
}

void Encoder::createNodes(void)
{
    for (const auto& pair : frequencyTable) {
        std::shared_ptr<Node> node(new Node);
        node->character = pair.first;
        node->frequency = pair.second;
        node->left = nullptr;
        node->right = nullptr;
        nodeQueue.push(node);
    }
}
