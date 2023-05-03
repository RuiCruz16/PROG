#include "Image.hpp"
using namespace std;

namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    width_ = w; // nº de colunas
    height_ = h; // nº de linhas
    imagem = vector<vector<Color>>(h,vector<Color>(w,fill));
  }
  Image::~Image()
  {

  }
  int Image::width() const
  {
    return width_;
  }
  int Image::height() const
  {
    return height_;
  }
  Color& Image::at(int x, int y)
  {
    return imagem[y][x];
  }
  const Color& Image::at(int x, int y) const
  {
    return imagem[y][x];
  }
}
