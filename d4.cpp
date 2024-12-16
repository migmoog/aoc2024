#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>


using std::vector, std::cout, std::endl;

// global vars
const std::string XMAS = "XMAS";
int width;
int height;
std::string str;
vector<vector<char>> crossword;
vector<vector<char>> mas_crosses;

// vector 2
struct v2 {
    int x;
    int y;

    v2 operator*(const int factor) {
        return v2 { x * factor, y * factor };
    }

    void operator+=(const v2 &vec) {
        x += vec.x;
        y += vec.y;
    }

    bool is_on_screen() {
        return 0 <= x && x < width
            && 0 <= y && y < height;
    }
};

char at(v2 pos) {
    return str[pos.x + pos.y * width];
}

void mark_crossword(vector<v2> &path, vector<vector<char>> &cw, std::string cmp) {
    int xi = 0;
    for (v2 &v : path) {
        cw[v.y][v.x] = cmp[xi++];
    }
}

bool path_search(v2 pos, v2 dir, std::string cmp, vector<vector<char>> &cw) {
    vector<v2> path = vector(cmp.length(), pos);
    int xi = 0;
    for (v2 &v : path) {
        v += dir * xi;
        if (!v.is_on_screen() || at(v) != cmp[xi]) 
            return false;
        xi++;
    }

    mark_crossword(path, cw, cmp);

    return true;
}

bool xmas_search(v2 pos, v2 dir) {
    return path_search(pos, dir, XMAS, crossword);
}

int splash_xmas(v2 origin) {
    if (at(origin) != 'X') {
        return 0;
    }

    return xmas_search(origin, v2 {-1, -1}) + xmas_search(origin, v2 {0, -1}) + xmas_search(origin, v2 {1, -1})
        + xmas_search(origin, v2 {-1, 0}) + xmas_search(origin, v2 {1, 0})
        + xmas_search(origin, v2 {-1, 1}) + xmas_search(origin, v2 {0, 1}) + xmas_search(origin, v2 {1, 1});
}

bool mas_search(v2 pos, v2 dir) {
    return path_search(pos, dir, XMAS.substr(1), mas_crosses);
}

bool mas_cross(v2 origin) {
    if (at(origin) != 'A') {
        return false; 
    }
    
    v2 tl = v2 { origin.x - 1, origin.y - 1};
    v2 bl = v2 { origin.x - 1, origin.y + 1};
    v2 tr = v2 { origin.x + 1, origin.y - 1};
    v2 br = v2 { origin.x + 1, origin.y + 1};

    // can match top left to bottom right OR bottom right to top
    return (mas_search(tl, v2 {1,1}) || mas_search(br, v2 {-1,-1})) 
    // can match top right to bottom left OR bottom left to top right
        && (mas_search(tr, v2 {-1, 1}) || mas_search(bl, v2 {1, -1}));
}

void print_cw(vector<vector<char>> cw) {
    for (auto &row : cw) {
        cout << std::string(row.begin(), row.end()) << "\n";
    }
}

void d4(std::string input) {
	str = input;
    assert(str == input);
    width = str.find('\n');
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    height = str.length() / width;

    if ((size_t)width < XMAS.length() || (size_t)height < XMAS.length()) {
        cout << "Unsatisfactory dimensions: (" << width << ", " << height << ")" <<  endl;
        return;
    }

    crossword = vector(height, vector(width, '.'));
    mas_crosses = crossword;

    int score = 0;
    int score2 = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++) 
        {
            score += splash_xmas(v2 { x, y });
            score2 += mas_cross(v2 { x, y });
        }
    }
    
    print_cw(crossword);
    cout << "Day 2 part 1: " << score << "\n";
    print_cw(mas_crosses);
    cout << "Day 2 part 2: " << score2 << endl;
}