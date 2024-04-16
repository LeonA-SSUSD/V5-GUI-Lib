#ifndef RECT_BUTTON_H
#define RECT_BUTTON_H

#include "libV5gui/core/buttonElement.h"



namespace libv5gui
{
  class RectButton : public ButtonElement
  {
    private:
      const int sizeX;
      const int sizeY;
    
    public:
      RectButton(int posX, int posY, int sizeX, int sizeY,
                const std::string &text,
                const vex::color &penColor = vex::white, const vex::color &fillColor = vex::black);

      RectButton(int posX, int posY, int sizeX, int sizeY,
                const vex::color &penColor = vex::white, const vex::color &fillColor = vex::black);

      

      void draw(void) override;
      bool isPressed(void) override;
  };
}



#endif