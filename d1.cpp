#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <map>
#include <set>

using namespace std;

#define IS_NUMC(c) ('0' <= c && c <= '9')

void tokenize(vector<int> &left, vector<int> &right,
              const bool addToLeft, const int off, const string input)
{
    if (input[off] == '\0')
        return;

    int bi = 0;
    char buf[30];
    int i = off;
    while (IS_NUMC(input[i]))
    {
        buf[bi++] = input[i];
        i++;
    }
    buf[bi] = '\0';

    int toknum = atoi(buf);
    if (addToLeft)
        left.push_back(toknum);
    else
        right.push_back(toknum);

    while (input[i] != '\0' && !IS_NUMC(input[i]))
        i++;

    tokenize(left, right, !addToLeft, i, input);
}

void d1(string input)
{
    vector<int> left_nums{};
    vector<int> right_nums{};
    tokenize(left_nums, right_nums, true, 0, input);

    if (left_nums.size() != right_nums.size())
    {
        cout << "List entries aren't parallel" << endl;
        return;
    }

    // doing the actual work (first is smallest, second is second smallest)
    long total_distance = 0;
    sort(left_nums.begin(), left_nums.end());
    sort(right_nums.begin(), right_nums.end());
    for (size_t i = 0; i < left_nums.size(); i++)
    {
        total_distance += abs(left_nums[i] - right_nums[i]);
    }

    // In C you'd have to actually write the utility.
    // Having a std library in C is WEEEEIIIIIRRRRRDDDDD....
    int shared_score = 0;
    map<int, int> appearances;
    set<int> lunique(left_nums.begin(), left_nums.end());
    for (int l : lunique) {
        for (int i = 0; i < (int)right_nums.size(); i++) {
            if (right_nums[i] == l) appearances[l]++;
        }
    }

    for (int l : left_nums) {
        shared_score += l * appearances[l];
    }

    cout << "Day 1 part 1: " << total_distance
         << "\nDay 1 part 2: " << shared_score << endl;
}