#ifndef __prog_XPM2_hpp__
#define __prog_XPM2_hpp__

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <cctype>
#include <sstream>
#include <iomanip>
#include "Image.hpp"

namespace prog {
    int hex_to_dec(string num_hex);

    string dec_to_hex(int num_dec);

    string to_upper(string a);
    
    Image* loadFromXPM2(const std::string &file);

    void saveToXPM2(const std::string& file, const Image* img);
}
#endif
