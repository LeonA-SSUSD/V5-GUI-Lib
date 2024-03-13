#include "libV5gui/buttons.h"



int getCenterRow(int posY, int sizeY)
{
  return floor((posY + sizeY / 2) / 20);
}

int getCenterColumn(int posX, int sizeX, std::string text)
{
  return ceil((posX + sizeX / 2) / 10 - text.length() / 2);
}



RectButton::RectButton(int posX, int posY, int sizeX, int sizeY, std::string text, vex::color penColor, vex::color fillColor)
          : ButtonElement(posX, posY, penColor, fillColor),
            sizeX(sizeX), sizeY(sizeY),
            text(text, getCenterRow(posY, sizeY), getCenterColumn(posX, sizeX, text), penColor, fillColor)
{}

RectButton::RectButton(int posX, int posY, int sizeX, int sizeY, vex::color penColor, vex::color fillColor)
          : ButtonElement(posX, posY, penColor, fillColor),
            sizeX(sizeX), sizeY(sizeY),
            text("", getCenterRow(posY, sizeY), getCenterColumn(posX, sizeX, ""), penColor, fillColor)
{}

/// @brief Draws the RectButton, overrides ScreenElement::draw()
void RectButton::draw()
{
  if (!enabled) return;

  Brain.Screen.setPenColor(penColor);
  Brain.Screen.setFillColor(fillColor);

  Brain.Screen.drawRectangle(posX, posY, sizeX, sizeY);

  text.draw();
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



CircButton::CircButton(int posX, int posY, int radius, std::string text, vex::color penColor, vex::color fillColor)
          : ButtonElement(posX, posY, penColor, fillColor),
            radius(radius),
            centerX(posX + radius), centerY(posY + radius),
            text(text, getCenterRow(posY - radius, radius*2), getCenterColumn(posX - radius, radius*2, text), penColor, fillColor)
{}

CircButton::CircButton(int posX, int posY, int radius, vex::color penColor, vex::color fillColor)
          : ButtonElement(posX, posY, penColor, fillColor),
            radius(radius),
            centerX(posX + radius), centerY(posY + radius),
            text("", getCenterRow(posY - radius, radius*2), getCenterColumn(posX - radius, radius*2, ""), penColor, fillColor)
{}

/// @brief Draws the CircButton, overrides ScreenElement::draw()
void CircButton::draw()
{
  if (!enabled) return;

  Brain.Screen.setPenColor(penColor);
  Brain.Screen.setFillColor(fillColor);

  Brain.Screen.drawCircle(centerX, centerY, radius);

  text.draw();
}

/// @brief Detects if the CircButton is pressed, overrides ButtonElement::isPressed()
/// @return Whether the CircButton is currently pressed
bool CircButton::isPressed()
{
  if (!enabled || !Brain.Screen.pressing()) return false;

  int relativeX = Brain.Screen.xPosition() - centerX;
  int relativeY = Brain.Screen.yPosition() - centerY;

  bool inRadius = (pow(relativeX, 2) + pow(relativeY, 2) <= pow(radius, 2));

  return inRadius;
}