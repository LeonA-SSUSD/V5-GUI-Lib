#ifndef CIRC_BUTTON_H
#define CIRC_BUTTON_H

#include "libV5gui/core/buttonElement.h"



namespace libv5gui
{
  class CircButton : public ButtonElement
  {
    private:
      const int diameter;
      const int radius;

      const int centerX;
      const int centerY;
    
    public:
      CircButton(int posX, int posY, int diameter,
                 const std::string &text,
                 const vex::color &penColor = vex::white, const vex::color &fillColor = vex::black);

      CircButton(int posX, int posY, int diameter,
                 const vex::color &penColor = vex::white, const vex::color &fillColor = vex::black);
      


      void draw(void) override;
      bool isPressed(void) override;
  };
}



#endif