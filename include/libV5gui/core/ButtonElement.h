#ifndef BUTTON_ELEMENT_H
#define BUTTON_ELEMENT_H

#include "libV5gui/core/Text.h"
#include "libV5gui/core/Shape.h"
#include "libV5gui/core/EventThreader.h"



namespace libV5gui
{
  class ButtonElement : public ScreenElement
  {
    Text text;

    /// @brief Internal variable for tracking new button presses
    mutable bool buttonDown = false;



    virtual Shape *shape(void) = 0;

    /// @return The maximum amount of text that
    ///         cleanly fits on the ButtonElement
    size_t maxLength(void) { return floor(shape() -> width() / xScale()) - 1; }
    
    protected:
      bool _hasCallback = false;



      void uniqueDraw(void) override;

    public:
      ButtonElement(int posX, int posY, int sizeX, int sizeY,
                    const std::string &text,
                    const vex::color &penColor, const vex::color &fillColor);

      ButtonElement(int posX, int posY, int sizeX, int sizeY,
                    const vex::color &penColor, const vex::color &fillColor);



      bool setText(std::string format, ...);

      bool setPenColor(const vex::color &newColor);
      bool setFillColor(const vex::color &newColor);

      bool isPressed(void);
      bool getNewPress(void);

      bool hasCallback(void) { return _hasCallback; }

      virtual void addCallback(std::function<void (void)> callback) = 0;
  };
}



#endif