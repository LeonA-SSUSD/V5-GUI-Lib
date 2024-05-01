#include "libV5gui/shapes/Circle.h"



namespace libv5gui
{
  Circle::Circle(int posX, int posY, unsigned int diameter,
                 const vex::color &penColor, const vex::color &fillColor)
        : Shape(posX, posY, penColor, fillColor),
          radius(floor(diameter / 2)), centerX(posX + radius), centerY(posY + radius)
  {}

  /// @brief Takes an (x, y) coordinate pair and calculates if it is inside the Circle
  /// @param x Potentially contained x-coordinate
  /// @param y Potentially contained y-coordinate
  /// @return Whether the point is in the Circle
  bool Circle::contains(int x, int y) { return (pow(x - centerX, 2) + pow(y - centerY, 2) < radius*radius); }
}