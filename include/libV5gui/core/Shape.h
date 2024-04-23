#ifndef SHAPE_H
#define SHAPE_H

#include "libv5gui/core/ScreenElement.h"



namespace libv5gui
{
  class Shape : public ScreenElement
  {
    public:
      const int posX;
      const int posY;



      Shape(int posX, int posY, const vex::color &penColor, const vex::color &fillColor);
  };
}



#endif