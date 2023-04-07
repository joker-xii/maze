#ifndef GAME_DS_MAZE_H
#define GAME_DS_MAZE_H

#include <vector>
#include <utility>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <array>
#include <cstdlib>
#include <algorithm>
#include <random>
#include "disjoint_set.h"

using position = std::pair<int, int>;
typedef unsigned int uint;

position operator+(position const &x, position const &y) {
    return {x.first + y.first, x.second + y.second};
}

struct maze {
    disjoint_set s;
    int N, M;
    std::set<std::pair<position, position>> erased;

    maze(int N, int M)
            : s(N * M), N(N), M(M) {
        std::vector<std::pair<position, int>> walls;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                for (int k = 0; k < 4; ++k) {
                    walls.push_back({{i, j}, k});
                }
            }
        }

        static const std::vector<position> neighbor_choices = {
                {0,  1},
                {0,  -1},
                {1,  0},
                {-1, 0}
        };
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(walls.begin(), walls.end(), g);
        for (auto[choice, dir]: walls) {
            position neighbor = choice + neighbor_choices[dir];
            if (block_exists(choice) && block_exists(neighbor) && erase_wall(choice, neighbor)) {
                if (s.find(0) == s.find(N * M - 1)) {
                    break;
                }
            }
        }
    }

    [[nodiscard]] int encode_position(position a) const {
        return a.first * M + a.second;
    }

    [[nodiscard]] bool block_exists(position p) const {
        auto[x, y] = p;
        return x < N && x >= 0 && y < M && y >= 0;
    }

    [[nodiscard]] bool has_wall(position a, position b) const {
        if (!block_exists(a) and !block_exists(b))return false;
        if (!block_exists(a) || !block_exists(b))return true;
        return erased.find({a, b}) == erased.end();
    }

    static bool is_neighbor(position a, position b) {
        auto[x, y] = a;
        auto[i, j] = b;
        return abs(x - i) + abs(y - j) == 1;
    }

    [[nodiscard]] std::string get_border(position ul) const {
        auto[x, y] = ul;
        position dl = {x + 1, y}, ur = {x, y + 1}, dr = {x + 1, y + 1};
        static const std::vector<std::string> possible_borders = {
                " ", "╴", "╵", "┘", "╶", "─", "└", "┴", "╷", "┐", "│", "┤", "┌", "┬", "├", "┼"
        };
        uint index = 0;
        index |= ((uint) has_wall(ul, dl)) << 0;
        index |= ((uint) has_wall(ul, ur)) << 1;
        index |= ((uint) has_wall(ur, dr)) << 2;
        index |= ((uint) has_wall(dl, dr)) << 3;

        return possible_borders[index];
    }

    bool erase_wall(position a, position b) {
        if (!is_neighbor(a, b) || !has_wall(a, b)) {
            return false;
        }
        erased.insert({a, b});
        erased.insert({b, a});
        s.union_set(encode_position(a), encode_position(b));
        return true;
    }

};


std::ostream &operator<<(std::ostream &os, maze const &m) {
    int N = m.N, M = m.M;
    for (int i = -1; i < N; ++i) {
        for (int j = -1; j < M; ++j) {
            os << m.get_border({i, j});
        }
        os << std::endl;
    }
    return os;
}

#endif //GAME_DS_MAZE_H
