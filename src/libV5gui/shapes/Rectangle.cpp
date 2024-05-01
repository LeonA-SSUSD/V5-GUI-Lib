#include "libV5gui/shapes/Rectangle.h"



namespace libv5gui
{
  Rectangle::Rectangle(int posX, int posY, unsigned int sizeX, unsigned int sizeY,
                       const vex::color &penColor, const vex::color &fillColor)
           : Shape(posX, posY, penColor, fillColor),
             sizeX(sizeX), sizeY(sizeY)
  {}

  bool Rectangle::contains(int x, int y) { return (x > posX && x < sizeX) && (y > posY && y < sizeY); }
}