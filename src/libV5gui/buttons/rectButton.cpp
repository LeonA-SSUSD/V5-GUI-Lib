#include "libV5gui/buttons/rectButton.h"



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

  /// @brief Draws the RectButton, overrides ScreenElement::draw()
  void RectButton::draw()
  {
    if (!enabled) return;

    refreshable = false;

    Brain.Screen.setPenColor(penColor);
    Brain.Screen.setFillColor(fillColor);

    Brain.Screen.drawRectangle(posX, posY, sizeX, sizeY);

    cleanText();
    text.draw();

    Brain.Screen.setPenColor(vex::white);
    Brain.Screen.setFillColor(vex::transparent);
  }

  /// @brief Detects if the RectButton is pressed, overrides ButtonElement::isPressed()
  /// @return Whether the RectButton is currently pressed
  bool RectButton::isPressed()
  {
    if (!enabled || !Brain.Screen.pressing()) return false;

    int x = Brain.Screen.xPosition();
    int y = Brain.Screen.yPosition();

    // Absolute value version of a double-sided inequality: posX < x < (posX + sizeX)
    bool inX = abs((posX + sizeX / 2) - x) <= sizeX / 2;
    bool inY = abs((posY + sizeY / 2) - y) <= sizeY / 2;

    return (inX && inY);
  }
}