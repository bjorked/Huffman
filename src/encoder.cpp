#include "encoder.hpp"

Encoder::Encoder()
{}

void Encoder::Encode(const std::string& fileName)
{
    readyFile(fileName);
    findFrequency();
    closeFile();
    createNodes();
    buildTree();
    createCodeTable(*(nodeQueue.top()), "");

    std::shared_ptr<Node> asd = nodeQueue.top();
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

void Encoder::printCodeTable(void) const
{
    for (const auto& pair : codeTable)
        std::cout << pair.first << ' ' << pair.second << std::endl;
}
