#include "Image.hpp"
using namespace std;

namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    width_ = w; 
    height_ = h; 
    img = vector<vector<Color>>(w,vector<Color>(h,fill)); // creates a two-dimensional vector with "w" columns and "h" rows, filled with the color "fill"
  }
  Image::~Image()
  {

  }
  int Image::width() const
  {
    return width_; // returns the width of the image
  }
  int Image::height() const
  {
    return height_; // returns the height of the image
  }
  Color& Image::at(int x, int y)
  {
    return img[x][y]; // returns the color of the pixel at position (x,y)
  }
  const Color& Image::at(int x, int y) const
  {
    return img[x][y];
  }
}
