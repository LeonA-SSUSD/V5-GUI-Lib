#include "libV5gui/buttons/RectButton.h"



namespace libv5gui
{
  RectButton::RectButton(int posX, int posY, int sizeX, int sizeY,
                         const std::string &text,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, sizeX, sizeY, text, penColor, fillColor),
              rectangle(posX, posY, sizeX, sizeY, penColor, fillColor)
  { shape = &rectangle; }

  RectButton::RectButton(int posX, int posY, int sizeX, int sizeY,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, sizeX, sizeY, penColor, fillColor),
              rectangle(posX, posY, sizeX, sizeY, penColor, fillColor)
  { shape = &rectangle; }
}