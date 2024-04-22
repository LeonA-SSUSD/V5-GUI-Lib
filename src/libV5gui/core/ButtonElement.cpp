#include "libV5gui/core/ButtonElement.h"



namespace libv5gui
{
  /// @brief Gets the central row from a pixel-coordinate position and length
  /// @param posY The uppermost pixel coordinate
  /// @param sizeY The distance from the uppermost to the lowermost pixel coordinate
  /// @return The central row
  int getCenterRow(int posY, int sizeY) { return ceil((posY + sizeY / 2) / 20) + 1; }

  /// @brief Gets the central column from a pixel-coordinate position and length
  ///        as well a text string's character length
  /// @param posX The leftmost pixel coordinate
  /// @param sizeX The distance from the leftmost to the rightmost pixel coordinate
  /// @param text A text string in which the character length is accounted for in this function
  /// @return The central column number adjusted to center text
  int getCenterColumn(int posX, int sizeX, const std::string &text)
  {
    return ceil((posX + sizeX / 2) / 10 - text.length() / 2) + 1;
  }


  
  ButtonElement::ButtonElement(int posX, int posY, int sizeX, int sizeY,
                               const std::string &text,
                               const vex::color &penColor, const vex::color &fillColor)
               : ScreenElement(penColor, fillColor), sizeX(sizeX), posX(posX), posY(posY),
                 text(text, getCenterRow(posY, sizeY), getCenterColumn(posX, sizeX, text), penColor, fillColor)
  {}

  ButtonElement::ButtonElement(int posX, int posY, int sizeX, int sizeY,
                               const vex::color &penColor, const vex::color &fillColor)
               : ScreenElement(penColor, fillColor), sizeX(sizeX), posX(posX), posY(posY),
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
      
      text.column = getCenterColumn(posX, sizeX, newText);
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

  /// @brief Sets the ButtonElement and its text's pen color and
  ///        automatically determines refreshability, overrides
  ///        ScreenElement::setPenColor
  /// @param newColor The new pen color
  void ButtonElement::setPenColor(const vex::color &newColor)
  {
    if (penColor == newColor && text.penColor == newColor) return;

    refreshable = true;

    penColor = newColor;

    text.setPenColor(penColor);
  }

  /// @brief Sets the ButtonElement and its text's fill color and
  ///        automatically determines refreshability, overrides
  ///        ScreenElement::setFillColor
  /// @param newColor The new fill color
  void ButtonElement::setFillColor(const vex::color &newColor)
  {
    if (fillColor == newColor && text.fillColor == newColor) return;

    refreshable = true;

    fillColor = newColor;

    text.setFillColor(fillColor);
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
}