#include "libV5gui/buttons/circButton.h"



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

  /// @brief Draws the CircButton, overrides ScreenElement::draw()
  void CircButton::draw()
  {
    if (!enabled) return;

    refreshable = false;

    Brain.Screen.setPenColor(penColor);
    Brain.Screen.setFillColor(fillColor);

    Brain.Screen.drawCircle(centerX, centerY, radius);

    cleanText();
    text.draw();

    Brain.Screen.setPenColor(vex::white);
    Brain.Screen.setFillColor(vex::transparent);
  }

  /// @brief Detects if the CircButton is pressed, overrides ButtonElement::isPressed()
  /// @return Whether the CircButton is currently pressed
  bool CircButton::isPressed()
  {
    if (!enabled || !Brain.Screen.pressing()) return false;

    int relativeX = Brain.Screen.xPosition() - centerX;
    int relativeY = Brain.Screen.yPosition() - centerY;

    return (relativeX*relativeX + relativeY*relativeY <= radius*radius);
  }
}