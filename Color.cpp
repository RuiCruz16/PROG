#include "Color.hpp"

namespace prog {
    Color::Color() {
        r_ = 0;
        g_ = 0;
        b_ = 0;
        // teste
    }
    Color::Color(const Color& other) {
        r_ = other.r_;
        g_ = other.g_;
        b_ = other.b_;
        // comentario
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        r_ = red;
        g_ = green;
        b_ = blue;
    }
    rgb_value& Color::red() {
        return r_;
    }
    rgb_value& Color::green() {
        return g_;
    }
    rgb_value& Color::blue() {
        return b_;
    }
    rgb_value Color::red() const {
        return r_;
    }
    rgb_value Color::green() const {
        return g_;
    }
    rgb_value Color::blue() const {
        return b_;
    }
    bool Color::compare_colors(Color c1, Color c2){
        if (c1.red() == c2.red() and c1.green() == c2.green() and c1.blue() == c2.blue())
            return true;
        else
            return false;
    }
    bool Color::operator<(const Color& other) const {
    if (r_ < other.red()){
        return true;
    }
    if (r_ == other.red() && g_ < other.green()){
        return true;
    }
    if (r_ == other.red() && g_ == other.green() && b_ < other.blue()){
        return true;
    }
    return false;
    }
}
