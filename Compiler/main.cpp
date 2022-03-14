#include "driver.h"

int main(int argc, char* argv[]) { 
  Driver driver;
  driver.Parse(argv[1]);
  for (int i = 2; i < argc; ++i) {
    if (std::string("-print") == argv[i]) {
      driver.EnablePrintingTree();
    }
  }
  for (int i = 2; i < argc; ++i) {
    if (std::string("-interpret") == argv[i]) {
      driver.EnableInterpreting();
    }
  }
  driver.Drive();
  std::cout << "==================================\n";
  std::cout << "All files are parsed\n";
  std::cout << "==================================\n";
  return 0; 
}