#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <array>

using namespace std;

static bool is_all_digits(const std::string& s);
static bool is_valid_line(const std::string& s);
static std::array<string, 3> parse_line(std::string& s);
