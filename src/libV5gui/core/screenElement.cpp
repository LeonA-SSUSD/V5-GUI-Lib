#include "libV5gui/core/screenElement.h"



namespace libv5gui
{
  ScreenElement::ScreenElement(const vex::color &penColor, const vex::color &fillColor, bool isText)
               : penColor(penColor), fillColor(fillColor), isText(isText)
  {}

  /// @brief Sets the ScreenElement's pen color and automatically determines refreshability
  /// @param newColor The new pen color
  void ScreenElement::setPenColor(const vex::color &newColor)
  {
    if (penColor == newColor) return;

    refreshable = true;

    penColor = newColor;
  }

  /// @brief Sets the ScreenElement's fill color and automatically determines refreshability
  /// @param newColor The new fill color
  void ScreenElement::setFillColor(const vex::color &newColor)
  {
    if (fillColor == newColor) return;

    refreshable = true;

    fillColor = newColor;
  }
}