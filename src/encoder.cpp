#include "encoder.hpp"
#include <bitset>

Encoder::Encoder()
{}

void Encoder::encode(const std::string& fileName)
{
    readyInputFile(fileName);
    findSymbolFrequency();
    createNodes();
    buildHuffmanTree();
    createCodeTable(*(nodeQueue.top()), "");
    writeCompressedOutput();
}

int Encoder::getInputSize(void) const
{
    return inputSize;
}

int Encoder::getOutputSize(void) const
{
    return outputSize;
}

void Encoder::readyInputFile(const std::string &fileName)
{
    inputFile.open(fileName, std::ifstream::ate);
    inputSize = inputFile.tellg();
    resetInputFile();
}

// Have to read the input file twice
void Encoder::resetInputFile(void)
{
    inputFile.clear();
    inputFile.seekg(0, inputFile.beg);
}

void Encoder::readyOutputFile(void)
{
    outputFile.open("output.bin", std::ios::binary | std::ios::out);
}

void Encoder::findSymbolFrequency(void)
{
    char character;
    while (inputFile.get(character))
        ++frequencyTable[character];
}

// Create a leaf node for each symbol and add it to the priority queue
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

/*
 * While there is more than one node in the queue:
 * 		1. Remove the two nodes of highest priority from the queue
 * 		2. Create a new node with these two nodes as children and with
 * 		frequency equal to the sum of the two nodes' frequencies
 * 		3. Add the new node to the queue
 * The remaining node is the root node and the tree is complete
*/
void Encoder::buildHuffmanTree(void)
{
    while (nodeQueue.size() > 1) {
        std::shared_ptr<Node> first = nodeQueue.top();
        nodeQueue.pop();
        std::shared_ptr<Node> second = nodeQueue.top();
        nodeQueue.pop();

        std::shared_ptr<Node> newNode(new Node);
        newNode->character = '\0';			// Represents a non-leaf node
        newNode->frequency = first->frequency + second->frequency;
        newNode->left = first;
        newNode->right = second;

        nodeQueue.push(newNode);
    }
}

/*
 * Recursively construct a code table
 * Adds 0 for left and 1 for right
*/
void Encoder::createCodeTable(const Node& node, const std::string &code)
{
    if (node.character == '\0') {
        createCodeTable(*(node.left), code + '0');
        createCodeTable(*(node.right), code + '1');
    } else {
        codeTable[node.character] = code;
    }
}

/*
 * Since you can't write single bits to file, this function packages
 * them into 8 bit chars
 * 1. Read a symbol from the input file
 * 2. Find appropriate code in the code table
 * 3. Set the bit to 0 or 1
 * 4. If the package has 8 bits, output it
*/
void Encoder::writeCompressedOutput(void)
{
    resetInputFile();
    readyOutputFile();

    char character;
    int packageLength = 0;
    std::bitset<8> code;

    while (inputFile.get(character)) {
        std::string codeStr = codeTable[character];

        for (const char& letter : codeStr) {
            if (letter == '0') {
                code.set(0, 0);
            } else if (letter == '1') {
                code.set(0, 1);
            }
            packageLength++;

            if (packageLength == 8) {
                unsigned long packageLong = code.to_ulong();
                unsigned char package = static_cast<unsigned char>(packageLong);
                outputFile << package;
                packageLength = 0;
            } else {
                code <<= 1;
            }
        }
    }

    outputSize = outputFile.tellp();

    inputFile.close();
    outputFile.close();
}
