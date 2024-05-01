#include "libV5gui/core/Text.h"



namespace libv5gui
{
  Text::Text(const std::string &text,
             int rowOrX, int columnOrY, CoordType gridOrPx,
             const vex::color &penColor, const vex::color &fillColor)
      : ScreenElement(penColor, fillColor), text(text), printedText(text),
        y(gridOrPx == px ? columnOrY : xScale() * rowOrX), x(gridOrPx == px ? rowOrX : yScale() * (columnOrY - 1))
  {}

  Text::Text(int rowOrX, int columnOrY, CoordType gridOrPx,
             const vex::color &penColor, const vex::color &fillColor)
      : ScreenElement(penColor, fillColor),
        y(gridOrPx == px ? columnOrY : xScale() * rowOrX), x(gridOrPx == px ? rowOrX : yScale() * (columnOrY - 1))
  {}

  /// @brief Sets the text to a std::string with no alterations,
  ///        only use this if you have to
  /// @param newText The new text
  /// @return Whether the text is refreshable
  bool Text::setTextRaw(std::string newText)
  {
    if (text == newText) return false;

    refreshable = true;

    text = newText;

    printedText = text;

    return true;
  }

  /// @brief Uses printf() formatting and sets the text to the result
  /// @param format Format string
  /// @param ... Arguments for the format string
  /// @return Whether the text is refreshable
  bool Text::setText(const char *format, ...)
  {
    __builtin_va_list args;

    __builtin_va_start(args, format);

    int chars = maxChars();

    char *buffer = new char[chars];
    
    vsnprintf(buffer, chars, format, args);

    __builtin_va_end(args);

    bool refresh = false;

    if (text != buffer)
    {
      refresh = true;

      refreshable = true;

      std::string newText = buffer;

      if (text.length() > newText.length())
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
    }

    delete[] buffer;

    return refresh;
  }

  /// @brief Draws the text, overrides ScreenElement::draw()
  inline void Text::uniqueDraw()
  {
    if (!printedText.length()) return;

    Brain.Screen.setPenColor(penColor);
    Brain.Screen.setFillColor(fillColor);

    Brain.Screen.printAt(x, y, printedText.c_str());

    Brain.Screen.setPenColor(vex::white);
    Brain.Screen.setFillColor(vex::transparent);

    printedText = text;
  }
}
