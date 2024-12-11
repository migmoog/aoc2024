#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "days.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./aoc <day index> \"<filename>\"\n"
            "Or: ./aoc <day index> < <filename>\n";
        return 1;
    }

    int day_index = std::stoi(argv[1]); 
    // C++ you are fucking evil this is garbo unreadable
    std::string input;
    std::string line;
    if (argc >= 3) {
        std::ifstream file(argv[2]);
        if (!file.is_open()) {
            std::cerr << "Could not find specified file";
            return 1;
        }
        
        while (std::getline(file, line)) {
            input += line + "\n";
        }
    } else {
       while (std::getline(std::cin, line)) {
            input += line + "\n";
       } 
    }

    run_day(day_index, input);
     
    return 0;
}