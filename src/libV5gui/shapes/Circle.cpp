#include "libV5gui/shapes/Circle.h"



namespace libv5gui
{
  Circle::Circle(int posX, int posY, unsigned int diameter,
                 const vex::color &penColor, const vex::color &fillColor)
        : Shape(posX, posY, penColor, fillColor),
          radius(floor(diameter / 2)), centerX(posX + radius), centerY(posY + radius)
  {}

  bool Circle::contains(int x, int y)
  {
    x -= centerX;
    y -= centerY;

    return (x*x + y*y < radius*radius);
  }
}