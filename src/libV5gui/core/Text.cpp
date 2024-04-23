#include "libV5gui/core/Text.h"



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
    std::string newTextSub = newText.substr(0, 48 - column);

    if (text == newTextSub) return false;

    refreshable = true;

    if (addWhitespaces && text.length() > newTextSub.length())
    {
      int whitespaces = text.length() - newTextSub.length();

      text = newTextSub;

      printedText = newTextSub.append(whitespaces, ' ');
    }

    else
    {
      text = newTextSub;

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

    char *buffer = new char[49 - column];
    
    vsnprintf(buffer, sizeof(buffer), format, args);

    __builtin_va_end(args);

    bool refreshable = setText(buffer);

    delete[] buffer;

    return refreshable;
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
