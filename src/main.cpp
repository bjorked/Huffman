#include "src/encoder.hpp"

int main(int argc, char *argv[])
{
    Encoder huffmanEncoder;

    if (argc == 1) {
        std::cout << "No file specified, exiting" << std::endl;
        return 1;
    } else {
        std::string fileName = argv[1];
        std::cout << "Encoding " << fileName << "..." << std::endl;
        huffmanEncoder.encode(fileName);
        std::cout << "Done. Encoded into output.bin" << std::endl;
    }
}
