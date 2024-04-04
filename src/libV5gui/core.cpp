#include "libV5gui/core.h"



ScreenElement::ScreenElement(vex::color penColor, vex::color fillColor, bool isText)
            : penColor(penColor), fillColor(fillColor), enabled(true), refreshable(false), isText(isText)
{}

void ScreenElement::setPenColor(vex::color newColor)
{
  refreshable = true;

  penColor = newColor;
}

void ScreenElement::setFillColor(vex::color newColor)
{
  refreshable = true;

  fillColor = newColor;
}

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
  Brain.Screen.setFillColor(vex::transparent);

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
/// @param zIndex The "layer" that the screen element will be drawn on
void Screen::add(ScreenElement & element, int zIndex) const
{
  element.zIndex = (zIndex == -1) ? elements.size() : zIndex;

  if (element.isText) element.fillColor = vex::transparent;

  elements.push_back(&element);

  elements.sort([](const ScreenElement * A, const ScreenElement * B) { return A -> zIndex > B -> zIndex; });
}

/// @brief Draws the screen's background and all elements
void Screen::draw() const
{ 
  clear();

  for (const auto & element : elements) if (element -> enabled) element -> draw();
}

/// @brief Refreshes elements on the screen
void Screen::refresh() const
{
  int refreshZ = -1;

  for (const auto & element: elements) 
  {
    if (element -> enabled && element -> refreshable) refreshZ = element -> zIndex, element -> draw();

    else if (refreshZ > -1 && element -> zIndex > refreshZ) element -> draw();
  }
}

/// @brief Clears the screen to its background color
void Screen::clear() const { Brain.Screen.clearScreen(bgColor); }

/// @brief Enables all elements on the screen
void Screen::enable() const { for (const auto & element : elements) element -> enabled = true; }

/// @brief Disables all elements on the screen
void Screen::disable() const { for (const auto & element : elements) element -> enabled = false; }