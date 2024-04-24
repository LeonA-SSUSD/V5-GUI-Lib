#include "libV5gui/core/ButtonElement.h"



namespace libv5gui
{ 
  ButtonElement::ButtonElement(int posX, int posY, int sizeX, int sizeY,
                               const std::string &text,
                               const vex::color &penColor, const vex::color &fillColor)
               : ScreenElement(penColor, fillColor), _sizeX(sizeX),
                 text(text.substr(0, maxTextLength()), getCenterRow(posY, sizeY),
                      getCenterColumn(posX, sizeX, text.substr(0, maxTextLength())), penColor, fillColor)
  {}

  ButtonElement::ButtonElement(int posX, int posY, int sizeX, int sizeY,
                               const vex::color &penColor, const vex::color &fillColor)
               : ScreenElement(penColor, fillColor), _sizeX(sizeX),
                 text(getCenterRow(posY, sizeY), getCenterColumn(posX, sizeX), penColor, fillColor)
  {}

  /// @brief Uses printf() formatting and sets the ButtonElement's text to the result
  /// @param format Format string
  /// @param ... Arguments for the format string
  /// @return Whether the ButtonElement is refreshable
  bool ButtonElement::setText(const char * format, ...) const
  {
    __builtin_va_list args;

    __builtin_va_start(args, format);

    char *buffer = new char[maxTextLength() + 1];
    
    vsnprintf(buffer, sizeof(buffer), format, args);

    __builtin_va_end(args);

    bool refresh = false;

    if (text.setTextRaw(buffer))
    {
      refresh = true;

      refreshable = true;

      text.column = getCenterColumn(shape -> posX, _sizeX, buffer);
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

    shape -> penColor = penColor;
    shape -> fillColor = fillColor;

    shape -> draw();

    text.penColor = penColor;
    text.fillColor = fillColor;

    text.draw();
  }
}