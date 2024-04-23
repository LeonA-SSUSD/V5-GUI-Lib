#include "libV5gui/shapes/Circle.h"



namespace libv5gui
{
  Circle::Circle(int posX, int posY, int diameter,
                 const vex::color &penColor, const vex::color &fillColor)
        : Shape(posX, posY, penColor, fillColor),
          radius(floorf(diameter / 2)), centerX(posX + radius), centerY(posY + radius)
  {}

  bool Circle::contains(int x, int y)
  {
    int relativeX = x - centerX;
    int relativeY = y - centerY;

    return (relativeX*relativeX + relativeY*relativeY <= radius*radius);
  }

  void Circle::draw()
  {
    if (!enabled) return;

    refreshable = false;

    Brain.Screen.setPenColor(penColor);
    Brain.Screen.setFillColor(fillColor);

    Brain.Screen.drawCircle(centerX, centerY, radius);

    Brain.Screen.setPenColor(vex::white);
    Brain.Screen.setFillColor(vex::transparent);
  }
}