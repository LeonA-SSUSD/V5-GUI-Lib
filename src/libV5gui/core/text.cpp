#include "libV5gui/core/text.h"



namespace libv5gui
{
  Text::Text(const std::string &text, int row, int column, const vex::color &penColor, const vex::color &fillColor)
      : ScreenElement(penColor, fillColor, true), printedText(text), text(text), row(row), column(column)
  {}

  Text::Text(int row, int column, const vex::color &penColor, const vex::color &fillColor)
      : ScreenElement(penColor, fillColor, true), row(row), column(column)
  {}

  /// @brief Sets the text to a std::string
  /// @param newText The new text
  /// @param addWhitespaces Whether the text deletes
  ///        characters it won't directly overwrite
  ///        (for internal purposes)
  /// @return Whether the text is refreshable
  bool Text::setText(std::string newText, bool addWhitespaces) const
  {
    if (newText == text) return false;

    refreshable = true;

    if (addWhitespaces && text.length() > newText.length())
    {
      int whitespaces = text.length() - newText.length();

      text = newText;

      printedText = newText.append(whitespaces, ' ');
    }

    else
    {
      text = newText;

      printedText = text;
    }

    return true;
  }

  /// @brief Uses printf() formatting and sets the text to the result
  /// @param format Format string
  /// @param ... Arguments for the format string
  /// @return Whether the text is refreshable
  bool Text::setTextFormat(const char * format, ...) const
  {
    __builtin_va_list args;

    __builtin_va_start(args, format);

    char buffer[256];
    
    vsnprintf(buffer, sizeof(buffer), format, args);

    __builtin_va_end(args);

    return setText(buffer);
  }

  /// @brief Draws the text, overrides ScreenElement::draw()
  void Text::draw()
  {
    if (!enabled || !printedText.length()) return;

    refreshable = false;

    Brain.Screen.setPenColor(penColor);
    Brain.Screen.setFillColor(fillColor);

    Brain.Screen.setCursor(row, column);
    Brain.Screen.print(printedText.c_str());

    Brain.Screen.setPenColor(vex::white);
    Brain.Screen.setFillColor(vex::transparent);

    printedText = text;
  }
}
