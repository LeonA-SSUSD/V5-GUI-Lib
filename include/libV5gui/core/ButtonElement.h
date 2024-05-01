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



      /// @return The maximum length of a null-terminated character
      ///         array that would fit on the button
      unsigned int maxChars(void) const { return floor(shape -> _sizeX() / xScale()); }

      /// @return The maximum amount of text, minus null-termination,
      ///         that would fit on a button
      unsigned int maxText(void) const { return maxChars() - 1; }
    
    protected:
      void uniqueDraw(void) override;

    public:
      Shape *shape = 0;

      Text text;



      ButtonElement(int posX, int posY, int sizeX, int sizeY,
                    const std::string &text,
                    const vex::color &penColor, const vex::color &fillColor);

      ButtonElement(int posX, int posY, int sizeX, int sizeY,
                    const vex::color &penColor, const vex::color &fillColor);



      bool setText(const char *format, ...);

      bool isPressed(void) const;
      bool getNewPress(void) const;
  };
}



#endif