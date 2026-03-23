//
// Created by yashwanth on 3/15/26.
//

#include <fstream>

#include "Utils.h"

void Utils::load_wavefront(const std::string &filename) {
    std::ifstream ifile(std::string("assets/")+filename+"/obj");
}