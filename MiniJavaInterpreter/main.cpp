#include <iostream>
#include <driver.h>

int main(int argc, char** argv) {
    Driver driver;
    std::string filename;
    std::cin >> filename;
    driver.Parse(filename);
}