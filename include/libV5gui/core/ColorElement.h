#ifndef COLOR_ELEMENT_H
#define COLOR_ELEMENT_H

#include "libV5gui/core/ScreenElement.h"



namespace libv5gui
{
  class ColorElement : public ScreenElement
  {
    private:
      bool setColor(vex::color &color, const vex::color& newColor);

    protected:
      vex::color penColor;
      vex::color fillColor;

    public:
      ColorElement(const vex::color &penColor, const vex::color &fillColor);



      bool setPenColor(const vex::color &newColor);
      bool setFillColor(const vex::color &newColor);
  };
}



#endif