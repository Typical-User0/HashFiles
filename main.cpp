#include <iostream>
#include <fstream>
#include <filesystem>
#include "mathematics.h"
#include <deque>


void write_to_file(std::fstream &file, uint8_t data) {
    file.write((char*)&data, sizeof(uint8_t));
}


int main() {
    std::string input_filename;

    std::cout << "Enter input file name: ";
    std::cin >> input_filename;

    if (not std::filesystem::exists(input_filename)) {
        std::cerr << "\033[1;31m"<< "Error: file doesn't exist!" << std::endl;
        return -1;
    }

    std::string output_filename;

    std::cout << "Enter output file name: ";
    std::cin >> output_filename;

    std::ifstream input_stream;

    input_stream.open(input_filename, std::ios_base::binary);

    std::fstream output_stream;



    std::deque<uint8_t> bytes;

    uint8_t ch;

    while (input_stream.read((char*)&ch, sizeof(uint8_t))) {
        bytes.push_back(ch);
    }

    input_stream.close();


    while (bytes.size() > 2) {
        std::cout << std::endl;

        uint8_t a = bytes.front();
        bytes.pop_front();
        uint8_t b = bytes.front();
        bytes.pop_front();
        uint8_t c = bytes.front();
        bytes.pop_front();

        std::cout << (int) a << " " << (int) b << " " << (int) c << std::endl;

        if (c % 2 == 0) {
            bytes.push_back(modulo(discriminant(a, b, c), 256));
        } else {
            bytes.push_back((a * b + c) % 256);
        }
    }

    output_stream.open(output_filename, std::ios_base::binary | std::ios_base::out);

    if (bytes.size() == 2) {
        uint8_t a = bytes.front();
        bytes.pop_front();
        uint8_t b = bytes.front();
        bytes.pop_front();

        std::cout << (int)a << " " << (int)b << std::endl;

        write_to_file(output_stream, a);
        write_to_file(output_stream, b);
    }

    if (bytes.size() == 1) {
        uint8_t a = bytes.front();

        bytes.pop_front();

        std::cout << (int)a << std::endl;

        write_to_file(output_stream, a);
    }

    output_stream.close();
    return 0;
}
