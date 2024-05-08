#include "libV5gui/buttons/CircButton.h"



namespace libV5gui
{
  CircButton::CircButton(int posX, int posY, int diameter,
                         const std::string &text,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, diameter, diameter, text, penColor, fillColor),
              circle(posX, posY, diameter, penColor, fillColor)
  {}

  CircButton::CircButton(int posX, int posY, int diameter,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, diameter, diameter, penColor, fillColor),
              circle(posX, posY, diameter, penColor, fillColor)
  {}

  void CircButton::addCallback(std::function<void ()> callback)
  {
    EventThreader::bindEvent({
                              (std::function<bool ()>) std::bind(_circNewPress, *this), callback
                            });
    
    _hasCallback = true;
  }
}