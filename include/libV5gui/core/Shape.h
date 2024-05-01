#ifndef SHAPE_H
#define SHAPE_H

#include "libv5gui/core/ScreenElement.h"



namespace libv5gui
{
  class Shape : public ScreenElement
  {
    private:
      virtual void drawShape(void) = 0;

    protected:
      virtual int _sizeX(void) = 0;

      void uniqueDraw(void) override;

    public:
      const int posX;
      const int posY;



      Shape(int posX, int posY, const vex::color &penColor, const vex::color &fillColor);



      virtual bool contains(int x, int y) = 0;



      friend class ButtonElement;
  };
}



#endif