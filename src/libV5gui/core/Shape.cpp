#include "libV5gui/core/Shape.h"



namespace libV5gui
{
  Shape::Shape(int posX, int posY, const vex::color &penColor, const vex::color &fillColor)
       : ColorElement(penColor, fillColor),
         posX(posX), posY(posY)
  {}

  void Shape::uniqueDraw()
  {
    Brain.Screen.setPenColor(penColor);

    drawShape();

    Brain.Screen.setPenColor(vex::white);
  }
}