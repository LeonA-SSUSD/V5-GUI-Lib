#include "libV5gui/core/ButtonElement.h"



namespace libv5gui
{ 
  ButtonElement::ButtonElement(int posX, int posY, int sizeX, int sizeY,
                               const std::string &text,
                               const vex::color &penColor, const vex::color &fillColor)
               : ScreenElement(penColor, fillColor), _sizeX(sizeX), posX(posX), posY(posY),
                 text(text, getCenterRow(posY, sizeY), getCenterColumn(posX, sizeX, text), penColor, fillColor)
  {}

  ButtonElement::ButtonElement(int posX, int posY, int sizeX, int sizeY,
                               const vex::color &penColor, const vex::color &fillColor)
               : ScreenElement(penColor, fillColor), _sizeX(sizeX), posX(posX), posY(posY),
                 text(getCenterRow(posY, sizeY), getCenterColumn(posX, sizeX), penColor, fillColor)
  {}

  /// @brief Sets the ButtonElement's text to a std::string
  /// @param newText The new text
  void ButtonElement::setText(std::string newText) const
  {
    totalWhitespaces = text.text.length(); 

    lastColumn = text.column;

    if (text.setText(newText, false)) 
    {
      refreshable = true;
      
      text.column = getCenterColumn(posX, _sizeX, newText);
    }
  }

  /// @brief Uses printf() formatting and sets the ButtonElement's text to the result
  /// @param format Format string
  /// @param ... Arguments for the format string
  void ButtonElement::setTextFormat(const char * format, ...) const
  {
    __builtin_va_list args;

    __builtin_va_start(args, format);

    char buffer[256];
    
    vsnprintf(buffer, sizeof(buffer), format, args);

    __builtin_va_end(args);

    setText(buffer);
  }

  /// @brief Removes leftover text from edges realigning when the text is changed
  void ButtonElement::cleanText() const
  {
    if (!totalWhitespaces) return;

    for (int i = 0; i < totalWhitespaces; i++)
    {
      Brain.Screen.setCursor(text.row, lastColumn + i);

      Brain.Screen.print(" ");
    }

    totalWhitespaces = 0;
  }

  /// @brief Sets one of the ButtonElement and its text's colors and
  //         automatically determines refreshability
  /// @param color The color to change
  /// @param textColor The text color to change
  /// @param newColor The new color
  /// @return Whether the ScreenElement is refreshable
  bool ButtonElement::setColor(vex::color &color, vex::color &textColor, const vex::color &newColor) const
  {
    if (color == newColor && textColor == newColor) return false;

    refreshable = true;

    color = newColor;

    textColor = newColor;

    return true;
  }

  /// @brief Sets the ButtonElement and its text's pen color and
  ///        automatically determines refreshability, overrides
  ///        ScreenElement::setPenColor
  /// @param newColor The new pen color
  bool ButtonElement::setPenColor(const vex::color &newColor) { return setColor(penColor, text.penColor, newColor); }

  /// @brief Sets the ButtonElement and its text's fill color and
  ///        automatically determines refreshability, overrides
  ///        ScreenElement::setFillColor
  /// @param newColor The new fill color
  bool ButtonElement::setFillColor(const vex::color &newColor) { return setColor(fillColor, text.fillColor, newColor); }


  /// @brief Detects if the ButtonElement is pressed
  /// @return Whether the ButtonElement is currently pressed
  bool ButtonElement::isPressed() { return enabled && Brain.Screen.pressing() && pressCondition(); }

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

  void ButtonElement::draw()
  {
    if (!enabled) return;

    refreshable = false;

    Brain.Screen.setPenColor(penColor);
    Brain.Screen.setFillColor(fillColor);

    drawShape();

    cleanText();
    text.draw();

    Brain.Screen.setPenColor(vex::white);
    Brain.Screen.setFillColor(vex::transparent);
  }
}