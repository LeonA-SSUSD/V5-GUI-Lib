#ifndef CIRC_BUTTON_H
#define CIRC_BUTTON_H

#include "libV5gui/core/ButtonElement.h"



namespace libv5gui
{
  class CircButton : public ButtonElement
  {
    public:
      const int diameter;
      const int radius;

      const int centerX;
      const int centerY;



      CircButton(int posX, int posY, int diameter,
                 const std::string &text,
                 const vex::color &penColor = vex::white, const vex::color &fillColor = vex::black);

      CircButton(int posX, int posY, int diameter,
                 const vex::color &penColor = vex::white, const vex::color &fillColor = vex::black);
      


      void drawShape(void) override;
      
      bool pressCondition(void) override;
  };
}



#endif