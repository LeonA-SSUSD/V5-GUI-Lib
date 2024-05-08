#include "libV5gui/buttons/RectButton.h"



namespace libV5gui
{
  RectButton::RectButton(int posX, int posY, int sizeX, int sizeY,
                         const std::string &text,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, sizeX, sizeY, text, penColor, fillColor),
              rectangle(posX, posY, sizeX, sizeY, penColor, fillColor)
  {}

  RectButton::RectButton(int posX, int posY, int sizeX, int sizeY,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, sizeX, sizeY, penColor, fillColor),
              rectangle(posX, posY, sizeX, sizeY, penColor, fillColor)
  {}

  void RectButton::addCallback(std::function<void ()> callback)
  {
    EventThreader::bindEvent({
                              (std::function<bool ()>) std::bind(_rectNewPress, *this), callback
                            });
    
    _hasCallback = true;
  }
}