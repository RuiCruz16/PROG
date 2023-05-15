#include "XPM2.hpp"
#include <fstream>
#include <iostream>
#include <cctype>
using namespace std;

namespace prog {

    string to_upper(string a){
    string res;
    for (unsigned long i = 0; i < a.length(); i++)
    {
        res += toupper(a.at(i));
    }
    return res;
    }

    int hex_to_dec(string num_hex){ // usar mais tarde o substr para cada 2 do hexadecimal (r/g/b)
        int res = 0;
        char a = num_hex.at(0);
        char b = num_hex.at(1);
        if (b >= '0' and b <= '9'){
            res += b - '0';
        }
        else if(b >= 'A' and b <= 'F'){
            res += b - 'A' + 10;
        }
        if (a >= '0' and a <= '9'){
            res += 16 * (a - '0');
        }
        else if (a >= 'A' and b <= 'F'){
            res += 16 * (a - 'A' + 10);
        }
        return res;
    }

    string dec_to_hex(int num_dec){ // para cada cor (r/g/b)
        string res = "";
        while (num_dec != 0){
            int aux = num_dec % 16;
            char hex_digit;
            if (aux < 10) {
            hex_digit = aux + '0';
            } 
            else {
            hex_digit = aux - 10 + 'A';
            }
            res = hex_digit + res;
            num_dec /= 16;
        }
        return res;
    }

    Image* loadFromXPM2(const std::string& file) {
        ifstream inn(file);
        return nullptr;
    }

    void saveToXPM2(const std::string& file, const Image* image) {
        
    }
}
