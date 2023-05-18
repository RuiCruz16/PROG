#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Image.hpp"

namespace prog
{
  class Script
  {
  public: 
    Script(const std::string &filename);
    ~Script();
    void run();
    void invert();
    void to_gray_scale();
    void replace(Color c1, Color c2);
    void fill(int x, int y, int w, int h, Color c);
    void h_mirror();
    void v_mirror();
    void add(const std::string &filename,Color c, int x, int y);
    void crop(int x, int y, int w, int h);
    void rotate_left();
    void rotate_right();
    Color find_color(int ws, int x, int y);
    unsigned char find_median(vector<unsigned char> c);
    void median_filter(int ws);

  private:
    // Current image.
    Image *image;
    // Input stream for reading script commands.
    std::ifstream input;
  private:
    // Private functions
    void clear_image_if_any();
    void open();
    void blank();
    void save();
  };
}
#endif
