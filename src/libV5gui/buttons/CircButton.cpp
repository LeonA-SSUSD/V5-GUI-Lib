#include "libV5gui/buttons/CircButton.h"



namespace libv5gui
{
  CircButton::CircButton(int posX, int posY, int diameter,
                         const std::string &text,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, diameter, diameter, text, penColor, fillColor),
              circle(posX, posY, diameter, penColor, fillColor)
  { shape = &circle; }

  CircButton::CircButton(int posX, int posY, int diameter,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, diameter, diameter, penColor, fillColor),
              circle(posX, posY, diameter, penColor, fillColor)
  { shape = &circle; }

  /// @brief The screen condition for CircButton, overrides ButtonElement::pressCondition()
  /// @return Whether the most recent screen coordinates are within the CircButton
  bool CircButton::pressCondition()
  {
    int relativeX = Brain.Screen.xPosition() - circle.centerX;
    int relativeY = Brain.Screen.yPosition() - circle.centerY;

    return (relativeX*relativeX + relativeY*relativeY <= circle.radius*circle.radius);
  }
}