#include "libV5gui/core/Text.h"



namespace libv5gui
{
  void Text::init(int rowOrX, int columnOrY, CoordType gridOrPx)
  {
    if (gridOrPx == px)
    {
      x = rowOrX;
      y = columnOrY;
    }

    else
    {
      x = xScale() * (columnOrY - 1);
      y = yScale() * rowOrX;
    }
  }

  Text::Text(const std::string &text,
             int rowOrX, int columnOrY, CoordType gridOrPx,
             const vex::color &penColor, const vex::color &fillColor)
      : ColorElement(penColor, fillColor), text(text), printedText(text)
  { init(rowOrX, columnOrY, gridOrPx); }

  Text::Text(int rowOrX, int columnOrY, CoordType gridOrPx,
             const vex::color &penColor, const vex::color &fillColor)
      : ColorElement(penColor, fillColor)
  { init(rowOrX, columnOrY, gridOrPx); }

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
  bool Text::setText(std::string format, ...)
  {
    __builtin_va_list args;
    __builtin_va_start(args, format);

    std::string newText = vnFormat(maxLength(), format, args);

    __builtin_va_end(args);

    if (text == newText) return false;

    refreshable = true;

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

    return true;
  }

  /// @brief Draws the text, overrides ScreenElement::draw()
  void Text::uniqueDraw()
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
