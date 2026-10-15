#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: main.exe <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        std::cout << "Error opening file\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string text = buffer.str();

    file.close();

    int n = 0;
    int io = 0;
    while (n < text.length()) {
        if (static_cast<unsigned char>(text[n]) == 32) {
            if (io == 0) {
                std::cout << "Found ASCII 20 at position " << n << '\n';
                n += 2;
                std::cout << static_cast<int>(static_cast<unsigned char>(text[n]));
                n += 3;
            } else {
                std::cout << "Found ASCII 20 at position " << n << '\n';
                n += 2;
                std::cout << static_cast<unsigned char>(text[n]);
                n += 3;
            }
        }
    }

    return 0;
}