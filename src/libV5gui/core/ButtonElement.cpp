#include "libV5gui/core/ButtonElement.h"



namespace libV5gui
{ 
  ButtonElement::ButtonElement(int posX, int posY, int sizeX, int sizeY,
                               const std::string &text,
                               const vex::color &penColor, const vex::color &fillColor)
               : text(text.substr(0, maxLength()), getCenterX(posX, sizeX, text.substr(0, maxLength())),
                      getCenterY(posY, sizeY), px, penColor, fillColor)
  {}

  ButtonElement::ButtonElement(int posX, int posY, int sizeX, int sizeY,
                               const vex::color &penColor, const vex::color &fillColor)
               : text(getCenterX(posX, sizeX), getCenterY(posY, sizeY), px, penColor, fillColor)
  {}

  /// @brief Uses printf() formatting and sets the ButtonElement's text to the result
  /// @param format Format string
  /// @param ... Arguments for the format string
  /// @return Whether the ButtonElement is refreshable
  bool ButtonElement::setText(std::string format, ...)
  {
    __builtin_va_list args;
    __builtin_va_start(args, format);

    std::string newText = vnFormat(maxLength(), format, args);

    __builtin_va_end(args);

    if (!text.setTextRaw(newText)) return false;

    refreshable = true;

    text.x = getCenterX(shape() -> posX, shape() -> width(), newText);

    return true;
  }

  bool ButtonElement::setPenColor(const vex::color &newColor)
  {
    if (!(shape() -> setPenColor(newColor) || text.setPenColor(newColor))) return false;
    
    refreshable = true;

    return true;
  }

  bool ButtonElement::setFillColor(const vex::color &newColor)
  {
    if (!(shape() -> setFillColor(newColor) || text.setFillColor(newColor))) return false;

    refreshable = true;

    return true;
  }

  /// @brief Detects if the ButtonElement is pressed
  /// @return Whether the ButtonElement is currently pressed
  bool ButtonElement::isPressed()
  {
    return enabled && Brain.Screen.pressing() && shape() -> contains(Brain.Screen.xPosition(), Brain.Screen.yPosition());
  }

  /// @brief NOT thread safe: you should use this function in
  ///        the loop once and store its data in a variable
  ///        afterwards or it will not return the same value
  /// @return If a press has just started
  bool ButtonElement::getNewPress()
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

  void ButtonElement::uniqueDraw()
  {
    shape() -> uniqueDraw();

    text.uniqueDraw();
  }
}