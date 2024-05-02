#ifndef BUTTON_ELEMENT_H
#define BUTTON_ELEMENT_H

#include "libV5gui/core/Text.h"
#include "libV5gui/core/Shape.h"



namespace libv5gui
{
  class ButtonElement : public ScreenElement
  {
    private:
      Text text;

      /// @brief Internal variable for tracking new button presses
      mutable bool buttonDown = false;



      virtual Shape *shape(void) = 0;

      /// @return The maximum amount of text that
      ///         cleanly fits on the ButtonElement
      size_t maxLength(void) { return floor(shape() -> _sizeX() / xScale()) - 1; }
    
    protected:
      void uniqueDraw(void) override;

    public:
      ButtonElement(int posX, int posY, int sizeX, int sizeY,
                    const std::string &text,
                    const vex::color &penColor, const vex::color &fillColor);

      ButtonElement(int posX, int posY, int sizeX, int sizeY,
                    const vex::color &penColor, const vex::color &fillColor);



      bool setText(std::string format, ...);

      bool isPressed(void);
      bool getNewPress(void);
  };
}



#endif