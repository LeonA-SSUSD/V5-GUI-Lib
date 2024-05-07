#include "libV5gui/shapes/Rectangle.h"



namespace libV5gui
{
  Rectangle::Rectangle(int posX, int posY, unsigned int sizeX, unsigned int sizeY,
                       const vex::color &penColor, const vex::color &fillColor)
           : Shape(posX, posY, penColor, fillColor),
             sizeX(sizeX), sizeY(sizeY)
  {}

  /// @brief Takes an (x, y) coordinate pair and calculates if it is inside the Rectangle
  /// @param x Potentially contained x-coordinate
  /// @param y Potentially contained y-coordinate
  /// @return Whether the point is in the Rectangle
  bool Rectangle::contains(int x, int y) { return (x > posX && x < sizeX) && (y > posY && y < sizeY); }
}