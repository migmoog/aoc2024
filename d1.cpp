#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define IS_NUMC(c) ('0' <= c && c <= '9')

void get_mins(int mins[], vector<int> &nums)
{
    for (int i = 0; i < (int)nums.size(); i++)
    {
        if (mins[0] < nums[i])
        {
            mins[1] = mins[0];
            mins[0] = nums[i];
        }
    }
}

void d1(string input)
{
    int start = 0, end;
    vector<int> left_nums;
    vector<int> right_nums;

    // parsing inputs
    const int len = input.length();
    for (int i = 0; i < len; i++)
    {
        if (input[i] != '\n')
            continue;
        end = i - 1;

        if (!IS_NUMC(input[start]) || !IS_NUMC(input[end]))
        {
            cout << "Invalid Entry in list:\nLeft: " << input[start] << ", Right: " << input[end] << endl;
            return;
        }

        int l = input[start] - '0';
        int r = input[end] - '0';

        left_nums.push_back(l);
        right_nums.push_back(r);

        start = i+1;
    }

    if (left_nums.size() != right_nums.size())
    {
        cout << "List entries aren't parallel" << endl;
        return;
    }

    // doing the actual work (first is smallest, second is second smallest)
    int leftMins[2];
    get_mins(leftMins, left_nums);
    int rightMins[2];
    get_mins(rightMins, right_nums);

    int total_distance = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            total_distance += abs(leftMins[i] - rightMins[j]);       
        }
    }

    cout << "Day 1 part 1: " << total_distance << endl;
}