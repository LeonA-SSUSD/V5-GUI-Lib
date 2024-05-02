#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "libv5gui/core/Shape.h"



namespace libv5gui
{
  class Rectangle : public Shape
  {
    private:
      int sizeX;
      int sizeY;



      void drawShape(void) override { Brain.Screen.drawRectangle(posX, posY, sizeX, sizeY, fillColor); }

      int _sizeX(void) override { return sizeX; }

    public:
      Rectangle(int posX, int posY, unsigned int sizeX, unsigned int sizeY,
                const vex::color &penColor = vex::white, const vex::color &fillColor = vex::black);



      bool contains(int x, int y) override;
  };
}



#endif