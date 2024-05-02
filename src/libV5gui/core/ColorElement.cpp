#include "libV5gui/core/ColorElement.h"



namespace libv5gui
{
  ColorElement::ColorElement(const vex::color &penColor, const vex::color &fillColor)
               : penColor(penColor), fillColor(fillColor)
  {}

  /// @brief Logic for ColorElement color changing and refreshability
  /// @param color The color to change
  /// @param newColor The new color
  /// @return Whether the ColorElement's color changed
  bool ColorElement::setColor(vex::color &color, const vex::color &newColor)
  {
    if (color == newColor) return false;

    refreshable = true;

    color = newColor;

    return true;
  }

  /// @brief Sets the ColorElement's pen color and automatically determines refreshability
  /// @param newColor The new pen color
  /// @return Whether the ColorElement's pen color changed
  bool ColorElement::setPenColor(const vex::color &newColor) { return setColor(penColor, newColor); }

  /// @brief Sets the ColorElement's fill color and automatically determines refreshability
  /// @param newColor The new fill color
  /// @return Whether the ColorElement's fill color changed
  bool ColorElement::setFillColor(const vex::color &newColor) { return setColor(fillColor, newColor); }
}