#include "encoder.hpp"

Encoder::Encoder()
{}

void Encoder::Encode(const std::string& fileName)
{
    readyFile(fileName);
    findFrequency();
    closeFile();
    createNodes();
    printNodes();
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
        Node node = {pair.first, pair.second, nullptr, nullptr};
        nodeQueue.push(node);
    }
}

void Encoder::printNodes(void)
{
    for (int i = 0; i < nodeQueue.size(); ++i) {
        std::cout << nodeQueue.top().character << ' ' << nodeQueue.top().frequency << std::endl;
        nodeQueue.pop();
    }
}
