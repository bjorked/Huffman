#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <map>
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

    std::ifstream inputFile;
    std::map<char, int> frequencyTable;
};

#endif
