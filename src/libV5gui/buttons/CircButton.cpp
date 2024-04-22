#include "libV5gui/buttons/CircButton.h"



namespace libv5gui
{
  CircButton::CircButton(int posX, int posY, int diameter,
                         const std::string &text,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, diameter, diameter, text, penColor, fillColor),
              diameter(diameter),
              radius(floorf(diameter / 2)),
              centerX(posX + radius), centerY(posY + radius)
  {}

  CircButton::CircButton(int posX, int posY, int diameter,
                         const vex::color &penColor, const vex::color &fillColor)
            : ButtonElement(posX, posY, diameter, diameter, penColor, fillColor),
              diameter(diameter),
              radius(floorf(diameter / 2)),
              centerX(posX + radius), centerY(posY + radius)
  {}

  /// @brief Draws the CircButton's circle, overrides ButtonElement::drawShape()
  void CircButton::drawShape() { Brain.Screen.drawCircle(centerX, centerY, radius); }

  /// @brief The screen condition for CircButton, overrides ButtonElement::pressCondition()
  /// @return Whether the most recent screen coordinates are within the CircButton
  bool CircButton::pressCondition()
  {
    int relativeX = Brain.Screen.xPosition() - centerX;
    int relativeY = Brain.Screen.yPosition() - centerY;

    return (relativeX*relativeX + relativeY*relativeY <= radius*radius);
  }
}