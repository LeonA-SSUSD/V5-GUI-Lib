#include "libV5gui/buttons.h"



int getCenterRow(int posY, int sizeY) { return floorf((posY + sizeY / 2) / 20) + 1; }

int getCenterColumn(int posX, int sizeX, std::string text) { return ceilf((posX + sizeX / 2) / 10 - text.length() / 2) + 1; }

RectButton::RectButton(int posX, int posY, int sizeX, int sizeY, std::string text, vex::color penColor, vex::color fillColor)
          : ButtonObject(posX, posY, penColor, fillColor),
            sizeX(sizeX), sizeY(sizeY),
            text(text, getCenterRow(posY, sizeY), getCenterColumn(posX, sizeX, text), penColor, fillColor)
{}

void RectButton::draw()
{
  if (!enabled) return;

  Brain.Screen.setPenColor(penColor);
  Brain.Screen.setFillColor(fillColor);

  Brain.Screen.drawRectangle(posX, posY, sizeX, sizeY);

  text.draw();
}

bool RectButton::isPressed()
{
  if (!enabled || !Brain.Screen.pressing()) return false;

  int x = Brain.Screen.xPosition();
  int y = Brain.Screen.yPosition();

  bool inX = (x >= posX && x <= (posX + sizeX));
  bool inY = (y >= posY && y <= (posY + sizeY));

  return (inX && inY);
}

CircButton::CircButton(int posX, int posY, int radius, std::string text, vex::color penColor, vex::color fillColor)
            : ButtonObject(posX, posY, penColor, fillColor),
              radius(radius),
              text(text, getCenterRow(posY, radius*2), getCenterColumn(posX, radius*2, text), penColor, fillColor),
              centerX(posX + radius), centerY(posY + radius)
{}

void CircButton::draw()
{
  if (!enabled) return;

  Brain.Screen.setPenColor(penColor);
  Brain.Screen.setFillColor(fillColor);

  Brain.Screen.drawCircle(centerX, centerY, radius);

  text.draw();
}

bool CircButton::isPressed()
{
  if (!enabled || !Brain.Screen.pressing()) return false;

  int relativeX = Brain.Screen.xPosition() - centerX;
  int relativeY = Brain.Screen.yPosition() - centerY;

  bool inRadius = (pow(relativeX, 2) + pow(relativeY, 2) <= pow(radius, 2));

  return inRadius;
}