#include "libV5gui/core.h"



ScreenElement::ScreenElement(vex::color penColor, vex::color fillColor, bool isText)
            : penColor(penColor), fillColor(fillColor), enabled(true), refreshable(false), isText(isText)
{}

/// @brief Sets the ScreenElement's text/border color
/// @param newColor The new pen color
void ScreenElement::setPenColor(vex::color newColor) const { penColor = newColor; }

/// @brief Sets the ScreenElement's main color
/// @param newColor The new fill color
void ScreenElement::setFillColor(vex::color newColor) const { fillColor = newColor; }

/// @brief Enables the ScreenElement to be drawn
void ScreenElement::enable() const { enabled = true; }

/// @brief Disables drawing the ScreenElement
void ScreenElement::disable() const { enabled = false; }

/// @brief Draws the ScreenElement, overridden by derived classes
void ScreenElement::draw() {}



Text::Text(std::string text, int row, int column, vex::color penColor, vex::color fillColor)
    : ScreenElement(penColor, fillColor, true), printedText(text), text(text), row(row), column(column)
{}

Text::Text(int row, int column, vex::color penColor, vex::color fillColor)
    : ScreenElement(penColor, fillColor, true), printedText(""), text(""), row(row), column(column)
{}

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
  Brain.Screen.setFillColor(vex::black);

  printedText = text;
}

/// @brief Sets the text to a std::string
/// @param newText The new text
void Text::setText(std::string newText) const
{
  if (newText == text) return;

  refreshable = true;

  const int whitespaces = fmax(text.length() - newText.length(), 0);

  printedText = text.length() > newText.length() ? newText.append(whitespaces, ' ') : newText;

  text = newText;
}

/// @brief Uses printf() formatting and sets the text to the result
/// @param format Format string
/// @param ... Arguments for the format string
void Text::setTextFormat(const char * format, ...) const
{
  __builtin_va_list args;

  __builtin_va_start(args, format);

  char buffer[256];
  
  vsnprintf(buffer, sizeof(buffer), format, args);

  __builtin_va_end(args);

  setText(buffer);
}



ButtonElement::ButtonElement(int posX, int posY, vex::color penColor, vex::color fillColor)
            : ScreenElement(penColor, fillColor), posX(posX), posY(posY)
{}

/// @brief NOT thread safe: you should use this function once
///        and store its data in a variable afterwards or it
///        will not return the same value
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

/// @brief Detects if the ButtonElement is pressed, overridden by derived classes
/// @return false
bool ButtonElement::isPressed() { return false; }



/// @brief Initializes a screen with a black background
Screen::Screen() : bgColor(vex::black) {}

/// @brief Initializes a screen with a chosen color
/// @param bgColor Screen background color
Screen::Screen(vex::color bgColor) : bgColor(bgColor) {}

/// @brief Adds an element to the screen
/// @param element The screen element to add
void Screen::add(ScreenElement & element) const
{
  if (element.isText) element.setFillColor(bgColor);

  elements.push_back(&element);
}

/// @brief Draws the screen's background and all elements
void Screen::draw() const
{ 
  clear();

  for (auto & element : elements) if (element -> enabled) element -> draw();
}

/// @brief Refreshes elements on the screen
void Screen::refresh() const
{
  for (auto & element : elements) if (element -> enabled && element -> refreshable) element -> draw();
}

/// @brief Clears the screen to its background color
void Screen::clear() const { Brain.Screen.clearScreen(bgColor); }

/// @brief Enables all elements on the screen
void Screen::enable() const { for (auto & element : elements) element -> enabled = true; }

/// @brief Disables all elements on the screen
void Screen::disable() const { for (auto & element : elements) element -> enabled = false; }