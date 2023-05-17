#include "XPM2.hpp"
#include <fstream>
#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <map>
#include <iomanip>
#include <vector>
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

    string dec_to_hex(int num_dec){
        string res = "";
        while (num_dec > 0){
            int aux = num_dec % 16;
            char hex_digit;
            if (aux < 10) {
            hex_digit = char(aux + '0');
            } 
            else {
            hex_digit = char(aux - 10 + 'A');
            }
            res = hex_digit + res;
            num_dec /= 16;
        }
        while(res.length() < 2){
            res += "0";
        }
        return res;
    }

    Image* loadFromXPM2(const std::string& file) {
        ifstream in(file);
        string aux, line;
        string temp, hex;
        char character;
        int w,h,num_colors,c;
        Color cor;
        map<char, Color> Colors;

        for (int i = 0; i < 2; i++)
        {
            getline(in,line);
            if (line == "! XPM2")
                continue;
            else {
                istringstream aux(line);
                aux >> w >> h >> num_colors >> c;
            }
        }

        Image* imagem_final = new Image(w,h); // criar nova imagem com as dimensões propostas

        for (int j = 0; j < num_colors; j++)
        {
            getline(in,line);
            istringstream aux(line);
            aux >> character >> temp >> hex;
            hex = to_upper(hex);
            cor.red() = hex_to_dec(hex.substr(1,2));
            cor.green() = hex_to_dec(hex.substr(3,2));
            cor.blue() = hex_to_dec(hex.substr(5,2));
            Colors.insert({character, cor});
        }

        for (int y = 0; y < h; y++)
        {
            getline(in,line);
            for (int x = 0; x < w; x++)
            {
                
                imagem_final->at(x,y) = Colors[line[x]];
            }
        }

        return imagem_final;
    }

    // image to xpm2
    void saveToXPM2(const std::string& file, const Image* image) {
        int num_aux = 0;
        ofstream out(file);
        out << "! XPM2" << "\n";
        int w, h;
        w = image->width();
        h = image->height();
        map<Color, char> Colors;
        for (int i = 0; i < image->width(); i++) {
            for (int j = 0; j < image->height(); j++) {
                if (Colors.find(image->at(i, j)) == Colors.end()) {
                    Colors.insert({image->at(i, j), char('!' + num_aux)});
                    num_aux++;
                }   
            }
        }
        out << w << " " << h << " " << num_aux << " 1" << "\n";
        for (auto& pair: Colors) {
            string hex = dec_to_hex(pair.first.red()) + dec_to_hex(pair.first.green()) + dec_to_hex(pair.first.blue());
            out << pair.second << " c" << " #" << hex << "\n";
        }
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                out << Colors[image->at(x,y)];
            }
            out << "\n";
        }
    }
}
