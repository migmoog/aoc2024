#ifndef DAYS_H
#define DAYS_H
#include <string>

void d1(std::string input);

void (*day_functions[])(std::string) = {NULL, d1};
void run_day(int day_index, std::string input) {
    day_functions[day_index](input);
}

#endif