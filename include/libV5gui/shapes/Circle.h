#ifndef CIRCLE_H
#define CIRCLE_H

#include "libv5gui/core/Shape.h"



namespace libv5gui
{
  class Circle : public Shape
  {
    private:
      unsigned int radius;

      int centerX;
      int centerY;


      
      void drawShape(void) override { Brain.Screen.drawCircle(centerX, centerY, radius, fillColor); }

    protected:
      int _sizeX(void) override { return 2 * radius; }

    public:
      Circle(int posX, int posY, unsigned int diameter,
             const vex::color &penColor = vex::white, const vex::color &fillColor = vex::black);



      bool contains(int x, int y) override;
  };
}



#endif