#ifndef SHAPE_H
#define SHAPE_H

#include "libv5gui/core/ColorElement.h"



namespace libv5gui
{
  class Shape : public ColorElement
  {
    friend class ButtonElement;
    
    private:
      virtual void drawShape(void) = 0;

      virtual int _sizeX(void) = 0;

    protected:
      void uniqueDraw(void) override;

      int posX;
      int posY;
      
    public:
      Shape(int posX, int posY, const vex::color &penColor, const vex::color &fillColor);



      virtual bool contains(int x, int y) = 0;
  };
}



#endif