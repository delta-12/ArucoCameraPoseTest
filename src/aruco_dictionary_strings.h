#ifndef __ARUCO_DICTIONARY_STRINGS_H__
#define __ARUCO_DICTIONARY_STRINGS_H__

#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> ARUCO_DICTIONARY_STRINGS = {
    {"DICT_4X4_50", 0},
    {"DICT_4X4_100", 1},
    {"DICT_4X4_250", 2},
    {"DICT_4X4_1000", 3},
    {"DICT_5X5_50", 4},
    {"DICT_5X5_100", 5},
    {"DICT_5X5_250", 6},
    {"DICT_5X5_1000", 7},
    {"DICT_6X6_50", 8},
    {"DICT_6X6_100", 9},
    {"DICT_6X6_250", 10},
    {"DICT_6X6_1000", 11},
    {"DICT_7X7_50", 12},
    {"DICT_7X7_100", 13},
    {"DICT_7X7_250", 14},
    {"DICT_7X7_1000", 15},
    {"DICT_ARUCO_ORIGINAL", 16},
    {"DICT_APRILTAG_16h5", 17},
    {"DICT_APRILTAG_25h9", 18},
    {"DICT_APRILTAG_36h10", 19},
    {"DICT_APRILTAG_36h11", 20}};

#endif