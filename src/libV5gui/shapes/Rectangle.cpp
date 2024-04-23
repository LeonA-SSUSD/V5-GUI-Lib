#include "libV5gui/shapes/Rectangle.h"



namespace libv5gui
{
  Rectangle::Rectangle(int posX, int posY, int sizeX, int sizeY,
                       const vex::color &penColor, const vex::color &fillColor)
           : Shape(posX, posY, penColor, fillColor),
             sizeX(sizeX), sizeY(sizeY)
  {}

  void Rectangle::draw()
  {
    if (!enabled) return;

    refreshable = false;

    Brain.Screen.setPenColor(penColor);
    Brain.Screen.setFillColor(fillColor);

    Brain.Screen.drawRectangle(posX, posY, sizeX, sizeY);

    Brain.Screen.setPenColor(vex::white);
    Brain.Screen.setFillColor(vex::transparent);
  }
}