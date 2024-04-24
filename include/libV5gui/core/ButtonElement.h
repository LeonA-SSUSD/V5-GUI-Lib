#ifndef BUTTON_ELEMENT_H
#define BUTTON_ELEMENT_H

#include "libV5gui/core/Text.h"
#include "libV5gui/core/Shape.h"



namespace libv5gui
{
  class ButtonElement : public ScreenElement
  {
    private:
      /// @brief Internal variable for tracking new button presses
      mutable bool buttonDown = false;

      /// @brief Used to align the text whenever it is changed
      const int _sizeX;



      int maxTextLength(void) const { return floor(_sizeX / 10) - 2; }

    public:
      Shape *shape = 0;

      Text text;



      ButtonElement(int posX, int posY, int sizeX, int sizeY,
                    const std::string &text,
                    const vex::color &penColor, const vex::color &fillColor);

      ButtonElement(int posX, int posY, int sizeX, int sizeY,
                    const vex::color &penColor, const vex::color &fillColor);



      bool setText(const char * format, ...) const;

      bool isPressed(void) const;
      bool getNewPress(void) const;

      void draw(void) override;
  };
}



#endif