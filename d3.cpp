#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <assert.h>

struct Mul {
    int left;
    int right;

    int compute() { return left * right; }
};

void d3(std::string input) {
    const std::string three_digits = "\\d{1,3}";
    //                                 this looks like a buttcrack lol
    const std::string mul_pattern = "mul\\((" + three_digits + "),(" + three_digits + ")\\)"; 
    std::regex mul_regex(mul_pattern);
    std::vector<Mul> instrs;
    
    std::sregex_iterator iter = std::sregex_iterator(input.begin(), input.end(), mul_regex);
    auto iter_end = std::sregex_iterator();
    for (std::sregex_iterator i = iter; i != iter_end; ++i)
    {
        std::smatch m = *i;
        instrs.push_back(Mul {
            .left = std::stoi(m[1]),
            .right = std::stoi(m[2])});
    }
    int score = 0;
    for (Mul &m : instrs) {
        score += m.compute();
    }

    instrs.clear();
    std::regex enabler_and_mul("(don't\\(\\))|(do\\(\\))|("+ mul_pattern + ")");
    auto iter2 = std::sregex_iterator(input.begin(), input.end(), enabler_and_mul);
    std::sregex_iterator end2;
    bool can_add_mul = true;
    for (auto i = iter2; i != end2; ++i) {
        std::smatch m = *i;
        if (m[1].matched) {
            can_add_mul = false;
        } else if (m[2].matched) {
            can_add_mul = true;
        } else if (can_add_mul && m[3].matched) {
            instrs.push_back(Mul {
                .left = std::stoi(m[4].str()),
                .right = std::stoi(m[5].str())
            });
        }
    }

    int score2 = 0;
    for (Mul &m : instrs) {
        score2 += m.compute();
    }
    
    std::cout << "Day 3 part 1: " << score << 
    "\nDay 3 part 2: " << score2 << std::endl; 
}