#include "libV5gui/core/ScreenElement.h"



namespace libv5gui
{
  ScreenElement::ScreenElement(const vex::color &penColor, const vex::color &fillColor, bool isText)
               : penColor(penColor), fillColor(fillColor), isText(isText)
  {}

  /// @brief Logic for ScreenElement color changing and refreshability
  /// @param color The color to change
  /// @param newColor The new color
  /// @return Whether the ScreenElement is refreshable
  bool ScreenElement::setColor(vex::color &color, const vex::color &newColor)
  {
    if (color == newColor) return false;

    refreshable = true;

    color = newColor;

    return true;
  }

  /// @brief Sets the ScreenElement's pen color and automatically determines refreshability
  /// @param newColor The new pen color
  /// @return Whether the ScreenElement is refreshable
  bool ScreenElement::setPenColor(const vex::color &newColor) { return setColor(penColor, newColor); }

  /// @brief Sets the ScreenElement's fill color and automatically determines refreshability
  /// @param newColor The new fill color
  /// @return Whether the ScreenElement is refreshable
  bool ScreenElement::setFillColor(const vex::color &newColor) { return setColor(fillColor, newColor); }
}