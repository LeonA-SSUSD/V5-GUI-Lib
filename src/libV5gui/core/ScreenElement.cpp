#include "libV5gui/core/ScreenElement.h"



namespace libV5gui
{
  /// @brief Draws the ScreenElement
  void ScreenElement::draw()
  {
    if (!enabled) return;

    refreshable = false;

    uniqueDraw();
  }
}