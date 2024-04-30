#include "libV5gui/core/ButtonElement.h"



namespace libv5gui
{ 
  ButtonElement::ButtonElement(int posX, int posY, int sizeX, int sizeY,
                               const std::string &text,
                               const vex::color &penColor, const vex::color &fillColor)
               : ScreenElement(penColor, fillColor), _sizeX(sizeX),
                 text(text.substr(0, maxText()), getCenterX(posX, sizeX, text.substr(0, maxText())),
                      getCenterY(posY, sizeY), px, penColor, fillColor)
  {}

  ButtonElement::ButtonElement(int posX, int posY, int sizeX, int sizeY,
                               const vex::color &penColor, const vex::color &fillColor)
               : ScreenElement(penColor, fillColor), _sizeX(sizeX),
                 text(getCenterX(posX, sizeX), getCenterY(posY, sizeY), px, penColor, fillColor)
  {}

  /// @brief Uses printf() formatting and sets the ButtonElement's text to the result
  /// @param format Format string
  /// @param ... Arguments for the format string
  /// @return Whether the ButtonElement is refreshable
  bool ButtonElement::setText(const char *format, ...) const
  {
    __builtin_va_list args;

    __builtin_va_start(args, format);

    int chars = maxChars();

    char *buffer = new char[chars];
    
    vsnprintf(buffer, chars, format, args);

    __builtin_va_end(args);

    bool refresh = false;

    if (text.setTextRaw(buffer))
    {
      refresh = true;

      refreshable = true;

      text.x = getCenterX(shape -> posX, _sizeX, buffer);
    }

    delete[] buffer;

    return refresh;
  }

  /// @brief Detects if the ButtonElement is pressed
  /// @return Whether the ButtonElement is currently pressed
  bool ButtonElement::isPressed() const
  { return enabled && Brain.Screen.pressing() && shape -> contains(Brain.Screen.xPosition(), Brain.Screen.yPosition()); }

  /// @brief NOT thread safe: you should use this function in
  ///        the loop once and store its data in a variable
  ///        afterwards or it will not return the same value
  /// @return If a press has just started
  bool ButtonElement::getNewPress() const
  {
    bool pressed = isPressed();

    if (pressed && !buttonDown)
    {
      buttonDown = true;

      return true;
    }

    buttonDown = pressed;

    return false;
  }

  void ButtonElement::draw()
  {
    if (!enabled) return;

    refreshable = false;

    shape -> setPenColor(penColor);
    shape -> setFillColor(fillColor);

    shape -> draw();

    text.setPenColor(penColor);
    text.setFillColor(fillColor);

    text.draw();
  }
}