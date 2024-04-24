#include "libV5gui/shapes/Rectangle.h"



namespace libv5gui
{
  Rectangle::Rectangle(int posX, int posY, int sizeX, int sizeY,
                       const vex::color &penColor, const vex::color &fillColor)
           : Shape(posX, posY, penColor, fillColor),
             sizeX(sizeX), sizeY(sizeY)
  {}

  bool Rectangle::contains(int x, int y)
  {
    int relativeX = x - posX;
    int relativeY = y - posY;

    return (relativeX >= 0 && relativeX < sizeX) && (relativeY >= 0 && relativeY < sizeY);
  }

  void Rectangle::draw()
  {
    if (!enabled) return;

    refreshable = false;

    Brain.Screen.setPenColor(penColor);

    Brain.Screen.drawRectangle(posX, posY, sizeX, sizeY, fillColor);

    Brain.Screen.setPenColor(vex::white);
  }
}