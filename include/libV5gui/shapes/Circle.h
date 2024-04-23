#ifndef CIRCLE_H
#define CIRCLE_H

#include "libv5gui/core/Shape.h"



namespace libv5gui
{
  class Circle : public Shape
  {
    public:
      const int radius;

      const int centerX;
      const int centerY;



      Circle(int posX, int posY, int diameter,
             const vex::color &penColor = vex::white, const vex::color &fillColor = vex::black);




      void draw(void) override;
  };
}



#endif