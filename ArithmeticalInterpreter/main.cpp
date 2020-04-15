#include <iostream>
#include <driver.h>

int main(int argc, char** argv) {
    Driver driver;
    for (int i = 1; i < argc; ++i) {
        try {
          driver.Parse(argv[i]);
        } catch(std::exception& e) {
            std::cout << e.what() << '\n';
        }
        std::cout << '\n';
    }
    std::cout << "==================================\n";
    std::cout << "All files are parsed\n";
    std::cout << "==================================\n";
}