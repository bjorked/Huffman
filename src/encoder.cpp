#include "encoder.hpp"

Encoder::Encoder()
{}

void Encoder::Encode(const std::string& fileName)
{
    readyFile(fileName);
    findFrequency();
    closeFile();
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
