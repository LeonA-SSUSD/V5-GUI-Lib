#ifndef SHAPE_H
#define SHAPE_H

#include "libV5gui/core/ColorElement.h"



namespace libV5gui
{
  class Shape : public ColorElement
  {
    friend class ButtonElement;
    
    private:
      virtual void drawShape(void) = 0;

      virtual int _sizeX(void) = 0;

    protected:
      int posX;
      int posY;



      void uniqueDraw(void) override;

    public:
      Shape(int posX, int posY, const vex::color &penColor, const vex::color &fillColor);



      virtual bool contains(int x, int y) = 0;
  };
}



#endif