//
// Created by R1perXNX on 7/1/2024.
//

#ifndef PACMANV2_GLOBAL_H
#define PACMANV2_GLOBAL_H
#include <iostream>
#include <vector>

constexpr size_t MAP_ROW_SIZE = 11; //65*11 = 715 px
constexpr size_t MAP_COLUM_SIZE = 20; //65*20 = 1300px
constexpr size_t MAP_SIZE = MAP_COLUM_SIZE * MAP_ROW_SIZE;

constexpr size_t SCREEN_MULT = 65;
constexpr size_t SCREEN_WIDTH = MAP_COLUM_SIZE * SCREEN_MULT;
constexpr size_t SCREEN_HEIGHT = MAP_ROW_SIZE * SCREEN_MULT;

using Map = std::vector<std::vector<int>>;

#endif //PACMANV2_GLOBAL_H
