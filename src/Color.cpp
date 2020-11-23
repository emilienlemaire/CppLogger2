//
// Created by Emilien Lemaire on 16/03/2020.
//

#include <string>
#include "Color.h"

namespace CppLogger {
    std::string Color::red = "\033[31m";
    std::string Color::green = "\033[32m";
    std::string Color::yellow = "\033[33m";
    std::string Color::blue = "\033[34m";
    std::string Color::magenta = "\033[35m";
    std::string Color::cyan = "\033[36m";
    std::string Color::white = "\033[37m";
    std::string Color::reset = "\033[m";
}