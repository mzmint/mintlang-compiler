#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: main.exe <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Error opening file\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string text = buffer.str();

    file.close();

    int n = 0;
    std::uint8_t r[8] = {0};
    std::uint8_t io = 0;
    while (n + 4 < text.length()) {
        int op = static_cast<unsigned char>(text[n]);
        int t1 = static_cast<unsigned char>(text[n + 1]);
        int v1 = static_cast<unsigned char>(text[n + 2]);
        int t2 = static_cast<unsigned char>(text[n + 3]);
        int v2 = static_cast<unsigned char>(text[n + 4]);
        if (op == 0) {
            if (t1 == 1 && t2 == 1) {
                if (v1 < 8 && v2 < 8) {
                    r[v1] = r[v2];
                }
            } else if (t1 == 1 && t2 == 0){
                if (v1 < 8) {
                    r[v1] = v2;
                }
            }
        } else if (op == 16) {
            if (t1 == 1 && t2 == 1) {
                if (v1 < 8 && v2 < 8) {
                    r[v1] += r[v2];
                }
            } else if (t1 == 1 && t2 == 0){
                if (v1 < 8) {
                    r[v1] += v2;
                }
            }
        } else if (op == 17) {
            if (t1 == 1 && t2 == 1) {
                if (v1 < 8 && v2 < 8) {
                    r[v1] -= r[v2];
                }
            } else if (t1 == 1 && t2 == 0){
                if (v1 < 8) {
                    r[v1] -= v2;
                }
            }
        }
        n += 5;
    }

    std::cout << static_cast<int>(r[0]) << '\n';

    return 0;
}