#include <iomanip>
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

        double inputSizeMB = huffmanEncoder.getInputSize();
        double outputSizeMB = huffmanEncoder.getOutputSize();
        double decrease = 100.0 - (outputSizeMB / inputSizeMB) * 100;

        std::cout << std::fixed << std::setprecision(3);
        std::cout << "Input file size: " << inputSizeMB / 1000000 << " MB" << std::endl;
        std::cout << "Output file size: " << outputSizeMB / 1000000 << " MB" << std::endl;
        std::cout << "File size decreased by " << decrease << "%" << std::endl;
    }
}
