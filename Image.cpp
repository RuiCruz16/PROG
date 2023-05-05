#include "Image.hpp"
using namespace std;

namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    width_ = w; // nº de colunas
    height_ = h; // nº de linhas
    imagem = vector<vector<Color>>(w,vector<Color>(h,fill));
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
    return imagem[x][y];
  }
  const Color& Image::at(int x, int y) const
  {
    return imagem[x][y];
  }
}
