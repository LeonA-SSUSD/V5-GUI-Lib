#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "libv5gui/core/Shape.h"



namespace libv5gui
{
  class Rectangle : public Shape
  {
    public:
      const int sizeX;
      const int sizeY;



      Rectangle(int posX, int posY, int sizeX, int sizeY,
                const vex::color &penColor = vex::white, const vex::color &fillColor = vex::black);




      void draw(void) override;
  };
}



#endif