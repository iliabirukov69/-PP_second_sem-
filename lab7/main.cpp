#include "functions.h"
#include <iostream>

int main() {
    ProcessorFacade processors_facade;
    try {
        processors_facade.Create({
            "input.txt",
            "input.bin",
            "input.json",
            "input.csv",
            "input.ini"
        });

        
        processors_facade.Write(42);

        
        std::vector<std::string> contents = processors_facade.ReadAll();
        std::vector<std::string> filenames = { "input.txt", "input.bin", "input.json", "input.csv", "input.ini" };

        std::cout << "=== FILE READ RESULTS ===" << std::endl;
        for (size_t i = 0; i < contents.size(); ++i) {
            std::cout << filenames[i] << ":\n" << contents[i] << "\n----------------------" << std::endl;
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception" << std::endl;
    }
    return 0;
}
