#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"
#include "Color.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "xpm2_save") {
                string file;
                input >> file;
                saveToXPM2(file, image);
                continue;
            }
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            }
            if (command == "replace") {
                int r1, g1, b1, r2, g2, b2;
                input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
                Color c1, c2;
                c1.red() = r1, c1.green() = g1, c1.blue() = b1;
                c2.red() = r2, c2.green() = g2, c2.blue() = b2;
                replace(c1,c2);
                continue;
            }
            if (command == "invert") {
                invert();
                continue;
            }
            if (command == "to_gray_scale") {
                to_gray_scale();
                continue;
            }
            if (command == "fill") {
                int x,y,w,h,r, g, b;
                input >> x >> y >> w >> h >> r >> g >> b;
                Color c;
                c.red() = r, c.green() = g, c.blue() = b;
                fill(x,y,w,h,c);
                continue;
            }
            if (command == "h_mirror") {
                h_mirror();
                continue;
            }
            if (command == "v_mirror") {
                v_mirror();
                continue;
            }
            if (command == "add") {
                string filename;
                int r, g, b, x, y;
                input >> filename;
                input >> r >> g >> b >> x >> y;
                Color c;
                c.red() = r, c.green() = g, c.blue() = b; 
                add(filename,c,x,y);
                continue;
            }
            if (command == "crop") {
                int x, y, w, h;
                input >> x >> y >> w >> h;
                crop(x,y,w,h);
                continue;
            }
            if (command == "rotate_left") {
                rotate_left();
                continue;
            }
            if (command == "rotate_right") {
                rotate_right();
                continue;
            }
            if (command == "xpm2_open") {
                string file;
                input >> file;
                image = loadFromXPM2(file);
                continue;
            }
            if (command == "median_filter") {
                int ws;
                input >> ws;
                median_filter(ws);
                continue;
            }
        }
    }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }
    void Script::replace(Color c1, Color c2){
        for (int i = 0; i < image->width(); i++)
        {
            for (int j = 0; j < image->height(); j++)
            {
                if(Color::compare_colors(image->at(i,j), c1)){
                    image->at(i,j) = c2;
                }
            }
        }
    }
    void Script::invert(){
        for (int i = 0; i < image->width(); i++)
        {
            for (int j = 0; j < image->height(); j++)
            {
                image->at(i,j).red() = 255 - image->at(i,j).red();
                image->at(i,j).green() = 255 - image->at(i,j).green();
                image->at(i,j).blue() = 255 - image->at(i,j).blue();
            }
        }
    }
    void Script::to_gray_scale(){
        for (int i = 0; i < image->width(); i++)
        {
            for (int j = 0; j < image->height(); j++)
            {
                int aux;
                aux = image->at(i,j).red() + image->at(i,j).green() + image->at(i,j).blue();
                image->at(i,j).red() = aux / 3;
                image->at(i,j).green() = aux / 3;
                image->at(i,j).blue() = aux / 3;
            }
        }
    }
    void Script::fill(int x, int y, int w, int h, Color c){
        for (int i = x; i < x + w; i++)
        {
            for (int j = y; j < y + h; j++)
            {
                image->at(i,j).red() = c.red();
                image->at(i,j).green() = c.green();
                image->at(i,j).blue() = c.blue();
            }
        }
    }
    void Script::h_mirror(){
        for (int y = 0; y < image->height(); y++) // altura
        {
            for (int x = 0; x < image->width() / 2; x++) // largura
            {
                swap(image->at(x, y), image->at(image->width() - 1 - x, y));
            } 
        }
    }
    void Script::v_mirror(){
        for (int y = 0; y < image->height() / 2; y++) // altura
        {
            for (int x = 0; x < image->width(); x++) // largura
            {
                swap(image->at(x, y), image->at(x,image->height() -1 -y ));
            } 
        }
    }
    
    void Script::add(const std::string &filename, Color c, int x, int y){
        Image* aux = loadFromPNG(filename);
        for (int i = x; i < x + aux->width(); i++)
        {
            for (int j = y; j < y + aux->height(); j++) {
                if (Color::compare_colors(aux->at(i-x,j-y), c)){
                    continue;
                }
                else{
                    image->at(i,j) = aux->at(i-x,j-y);
                }
            }
        }
        delete aux;
    }

    void Script::crop(int x, int y, int w, int h) {
        Image* aux = new Image(w, h);
        for (int i = x; i < x + w; i++)
        {
            for (int j = y; j < y + h; j++) {
                aux->at(i - x, j - y) = image->at(i, j);
            }
        }
        delete image;
        image = aux;
    }

    void Script::rotate_left(){
        if (image->width() == image->height()) {
            Image* aux = new Image(image->width(), image->height()); // mesmas dimensões da original
            for (int i = 0; i < image->width(); i++) {
                for (int j = 0; j < image->height(); j++) {
                    aux->at(i,j) = image->at(i,j);
                }
            }
            for (int x = 0; x < image->width(); x++) {
                for (int y = 0; y < image->height(); y++) {
                    image->at(y,image->width() - x -1) = aux->at(x,y);
                }
            }
            delete aux;
        }
        else {
            Image* aux = new Image(image->height(), image->width());
            for (int j = 0; j < image->height(); j++) {
                for (int i = 0; i < image->width(); i++) {
                    aux->at(j, image->width() - i - 1) = image->at(i,j);
                }
            }
            delete image;
            image = aux;
        }
    }

    void Script::rotate_right(){
        if (image->width() == image->height()) {
            Image* aux = new Image(image->width(), image->height()); // mesmas dimensões da original
            for (int i = 0; i < image->width(); i++) {
                for (int j = 0; j < image->height(); j++) {
                    aux->at(i,j) = image->at(i,j);
                }
            }
            for (int x = 0; x < image->width(); x++) {
                for (int y = 0; y < image->height(); y++) {
                    image->at(image->width() - y - 1, x) = aux->at(x,y);
                }
            }
            delete aux;
        }
        else {
            Image* aux = new Image(image->height(), image->width());
            for (int i = 0; i < image->width(); i++) {
                for (int j = 0; j < image->height(); j++) {
                    aux->at(image->height() - j - 1,i) = image->at(i,j);
                }
            }
            delete image;
            image = aux;
        }
    }

    void Script::find_neighbours(int ws, int x, int y, Color& c) {
        int max_x, max_y, min_x, min_y;
        min_x = std::max(0, x - ws / 2);
        max_x = std::min(image->width() - 1, x + ws / 2);
        min_y = std::max(0, y - ws / 2);
        max_y = std::min(image->height() - 1, y + ws / 2);

        std::vector<unsigned char> red, green, blue;
        for (int i = min_x; i <= max_x; i++) {
            for (int j = min_y; j <= max_y; j++) {
                red.push_back(image->at(i, j).red());
                green.push_back(image->at(i, j).green());
                blue.push_back(image->at(i, j).blue());
            }
        }
        std::sort(red.begin(), red.end());
        std::sort(green.begin(), green.end());
        std::sort(blue.begin(), blue.end());

        unsigned char median_red = find_median(red);
        unsigned char median_green = find_median(green);
        unsigned char median_blue = find_median(blue);

        c.red() = median_red;
        c.green() = median_green;
        c.blue() = median_blue;
}

    unsigned char Script::find_median(std::vector<unsigned char> c) {
        int size = c.size();
        int mid = size / 2;
        if (size % 2 != 0)
            return c[mid];
        else
            return (c[mid - 1] + c[mid]) / 2;
    }

    void Script::median_filter(int ws) {
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height(); y++) {
                Color& c = image->at(x, y);
                find_neighbours(ws, x, y, c);
            }
        }
    }
}