#include "libV5gui/buttons/RectButton.h"



namespace libv5gui
{
  RectButton::RectButton(int posX, int posY, int sizeX, int sizeY,
                         const std::string &text,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, sizeX, sizeY, text, penColor, fillColor)
  {
    shape = new Rectangle(posX, posY, sizeX, sizeY, penColor, fillColor);
  }

  RectButton::RectButton(int posX, int posY, int sizeX, int sizeY,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, sizeX, sizeY, penColor, fillColor)
  {
    shape = new Rectangle(posX, posY, sizeX, sizeY, penColor, fillColor);
  }
}