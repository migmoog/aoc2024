#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int sign(int num)
{
    if (num < 0)
        return -1;
    else if (num > 0)
        return 1;

    return 0;
}

using namespace std;
class Report
{
private:
    vector<int> levels;
    Report(vector<int> levels)
    {
        this->levels = levels;
    }

    int unsafe_level_index(bool increasing)
    {
        int trend_sign = increasing ? 1 : -1;
        for (size_t i = 1; i < levels.size(); i++)
        {
            int dif = levels[i - 1] - levels[i];
            int adif = abs(dif);
            if (sign(dif) != trend_sign || (adif < 1 || 3 < adif))
                return i;
        }

        return -1;
    }

public:
    Report()
    {
        levels = vector<int>();
    }
    void add_level(int l) { levels.push_back(l); }
    bool is_safe()
    {
        if (levels.size() < 2)
            return false;
        return unsafe_level_index(true) == -1 || unsafe_level_index(false) == -1;
    }

    bool can_fix()
    {
        if (is_safe())
            throw runtime_error("Report is safe. No unsafe level to find.");
        // I AM DONE FUCKING OPTIMIZING
        for (int i = 0; i < (int)levels.size(); i++) {
            auto copy = levels;
            copy.erase(copy.begin() + i);
            if (Report(copy).is_safe()) return true;
        }

        return false;
    }
};

void d2(string input)
{
    vector<Report> reps = {};
    stringstream ip(input);
    string line;

    // parsing
    while (getline(ip, line))
    {
        Report r;
        string num = "";
        for (char c : line)
        {
            if (isdigit(c))
                num += c;
            else
            {
                int level = stoi(num);
                num.clear();
                r.add_level(level);
            }
        }
        int level = stoi(num);
        num.clear();
        r.add_level(level);
        reps.push_back(r);
    }

    // actual problem solving
    int safe = 0, fixables = 0;
    for (Report &r : reps)
    {
        if (r.is_safe())
            safe++;
        else if (r.can_fix())
            fixables++;
    }

    cout << "Day 2 part 1: " << safe
         << "\nDay 2 part 2: " << safe + fixables << endl;
}