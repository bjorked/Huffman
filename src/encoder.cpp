#include "encoder.hpp"

Encoder::Encoder()
{}

void Encoder::Encode(const std::string& fileName)
{
    readyInputFile(fileName);
    findFrequency();
    createNodes();
    buildTree();
    createCodeTable(*(nodeQueue.top()), "");
    writeOutput();
}

void Encoder::readyInputFile(const std::string &fileName)
{
    inputFile.open(fileName);
}

void Encoder::resetInputFile(void)
{
    inputFile.clear();
    inputFile.seekg(0, inputFile.beg);
}

void Encoder::readyOutputFile(void)
{
    outputFile.open("output.bin", std::ios::binary | std::ios::out);
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

void Encoder::buildTree(void)
{
    while (nodeQueue.size() > 1) {
        std::shared_ptr<Node> first = nodeQueue.top();
        nodeQueue.pop();
        std::shared_ptr<Node> second = nodeQueue.top();
        nodeQueue.pop();

        std::shared_ptr<Node> newNode(new Node);
        newNode->character = '\0';
        newNode->frequency = first->frequency + second->frequency;
        newNode->left = first;
        newNode->right = second;

        nodeQueue.push(newNode);
    }
}

void Encoder::createCodeTable(const Node& node, const std::string &code)
{
    if (node.character == '\0') {
        createCodeTable(*(node.left), code + '0');
        createCodeTable(*(node.right), code + '1');
    } else {
        codeTable[node.character] = code;
    }
}

void Encoder::writeOutput(void)
{
    resetInputFile();
    readyOutputFile();

    char character;
    while (inputFile.get(character)) {
        outputFile << codeTable[character];
    }

    inputFile.close();
    outputFile.close();
}
