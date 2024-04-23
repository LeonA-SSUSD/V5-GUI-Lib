#include "libV5gui/buttons/RectButton.h"



namespace libv5gui
{
  RectButton::RectButton(int posX, int posY, int sizeX, int sizeY,
                         const std::string &text,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, sizeX, sizeY, text, penColor, fillColor),
              rectangle(posX, posX, sizeX, sizeY, penColor, fillColor)
  { shape = &rectangle; }

  RectButton::RectButton(int posX, int posY, int sizeX, int sizeY,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, sizeX, sizeY, penColor, fillColor),
              rectangle(posX, posX, sizeX, sizeY, penColor, fillColor)
  { shape = &rectangle; }

  /// @brief The screen condition for RectButton, overrides ButtonElement::pressCondition()
  /// @return Whether the most recent screen coordinates are within the RectButton
  bool RectButton::pressCondition()
  {
    int relativeX = Brain.Screen.xPosition() - rectangle.posX;
    int relativeY = Brain.Screen.yPosition() - rectangle.posY;

    return (relativeX >= 0 && relativeX < rectangle.sizeX) && (relativeY >= 0 && relativeY < rectangle.sizeY);
  }
}