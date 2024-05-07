#include "libV5gui/core/Screen.h"



namespace libV5gui
{
  /// @brief Initializes a screen with a chosen color
  /// @param screenColor Screen background color
  Screen::Screen(const vex::color &screenColor) : screenColor(screenColor) {}

  /// @brief Sets the background color of the screen and
  ///        automatically determines refreshability
  /// @param newScreenColor The new screen color
  void Screen::setColor(const vex::color &newScreenColor)
  {
    if (screenColor == newScreenColor) return;

    screenChanged = true;

    screenColor = newScreenColor;
  }

  /// @brief Adds an element to the screen
  /// @param element The screen element to add
  /// @param zIndex The "layer" that the screen element will be drawn on
  void Screen::add(ScreenElement &element, int zIndex)
  {
    element.zIndex = (zIndex < 0) ? elements.size() : zIndex;
    
    ScreenElement *pElement = &element;

    Text *text = dynamic_cast<Text*>(pElement);

    if (text) text -> setFillColor(vex::transparent);

    elements.push_back(pElement);

    elements.sort([](const ScreenElement *A, const ScreenElement *B) { return A -> zIndex < B -> zIndex; });
  }

  /// @brief Draws the screen's background and all elements
  void Screen::draw() const
  { 
    screenChanged = false;

    clear();

    for (const auto &element : elements) if (element -> enabled) element -> draw();
  }

  /// @brief Refreshes elements on the screen
  void Screen::refresh() const
  {
    if (screenChanged) return draw();

    int refreshZ = -1;

    for (const auto &element : elements) 
    {
      if (element -> enabled && element -> refreshable) refreshZ = element -> zIndex, element -> draw();

      else if (refreshZ > -1 && element -> zIndex > refreshZ) element -> draw();
    }
  }

  /// @brief Clears the screen to its background color
  void Screen::clear() const { Brain.Screen.clearScreen(screenColor); }

  /// @brief Enables all elements on the screen
  void Screen::enable() { for (const auto &element : elements) element -> enabled = true; }

  /// @brief Disables all elements on the screen
  void Screen::disable() { for (const auto &element : elements) element -> enabled = false; }
}