#include <map>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
    std::map<char, int> table;

    std::ifstream inputFile("input.txt");
    char character;

    while (inputFile >> character) {
        ++table[character];
    }

    for (const auto& kv : table) {
        std::cout << kv.first << " has value " << kv.second << std::endl;
    }

    inputFile.close();
}
