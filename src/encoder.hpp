#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <map>
#include <queue>
#include <string>
#include <fstream>
#include <iostream>
#include <src/node.hpp>

class Encoder
{
public:
    Encoder();

    void Encode(const std::string& fileName);
private:
    void readyFile(const std::string& fileName);
    void closeFile(void);

    void findFrequency(void);

    void createNodes(void);
    void buildTree(void);

    void createCodeTable(const Node &node, const std::string& code);

    std::ifstream inputFile;
    std::map<char, int> frequencyTable;
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodePtrComparison> nodeQueue;
    std::map<char, std::string> codeTable;
};

#endif
