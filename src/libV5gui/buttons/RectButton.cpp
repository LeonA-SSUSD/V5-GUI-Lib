#include "libV5gui/buttons/RectButton.h"



namespace libv5gui
{
  RectButton::RectButton(int posX, int posY, int sizeX, int sizeY,
                         const std::string &text,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, sizeX, sizeY, text, penColor, fillColor),
              sizeX(sizeX), sizeY(sizeY)
  {}

  RectButton::RectButton(int posX, int posY, int sizeX, int sizeY,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, sizeX, sizeY, penColor, fillColor),
              sizeX(sizeX), sizeY(sizeY)
  {}

  /// @brief Draws the RectButton's rectangle, overrides ButtonElement::drawShape()
  void RectButton::drawShape() { Brain.Screen.drawRectangle(posX, posY, sizeX, sizeY); }

  /// @brief The screen condition for RectButton, overrides ButtonElement::pressCondition()
  /// @return Whether the most recent screen coordinates are within the RectButton
  bool RectButton::pressCondition()
  {
    int relativeX = Brain.Screen.xPosition() - posX;
    int relativeY = Brain.Screen.yPosition() - posY;

    return (relativeX >= 0 && relativeX < sizeX) && (relativeY >= 0 && relativeY < sizeY);
  }
}