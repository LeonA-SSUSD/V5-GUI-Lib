#include "libV5gui/core.h"



int getCenterRow(int posY, int sizeY) { return ceil((posY + sizeY / 2) / 20) + 1; }

int getCenterColumn(int posX, int sizeX, std::string text)
{
  return ceil((posX + sizeX / 2) / 10 - text.length() / 2) + 1;
}



ScreenElement::ScreenElement(vex::color penColor, vex::color fillColor, bool isText)
             : penColor(penColor), fillColor(fillColor), enabled(true), refreshable(false), isText(isText)
{}

void ScreenElement::setPenColor(vex::color newColor)
{
  if (newColor == penColor) return;

  refreshable = true;

  penColor = newColor;
}

void ScreenElement::setFillColor(vex::color newColor)
{
  if (newColor == fillColor) return;

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
/// @return Whether the text is refreshable
bool Text::setText(std::string newText) const
{
  if (newText == text) return false;

  refreshable = true;

  const bool hasWhitespaces = text.length() > newText.length();

  const int whitespaces = fmax(text.length() - newText.length(), 0);

  text = newText;

  printedText = (hasWhitespaces) ? newText.append(whitespaces, ' ') : text;

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

  char buffer[256];
  
  vsnprintf(buffer, sizeof(buffer), format, args);

  __builtin_va_end(args);

  return setText(buffer);
}



ButtonElement::ButtonElement(int posX, int posY, int sizeX, int sizeY,
                              std::string text, vex::color penColor, vex::color fillColor)
             : ScreenElement(penColor, fillColor), posX(posX), posY(posY), sizeX(sizeX),
               text(text, getCenterRow(posY, sizeY), getCenterColumn(posX, sizeX, text), penColor, fillColor)
{}

ButtonElement::ButtonElement(int posX, int posY, int sizeX, int sizeY, vex::color penColor, vex::color fillColor)
             : ScreenElement(penColor, fillColor), posX(posX), posY(posY), sizeX(sizeX),
               text(getCenterRow(posY, sizeY), getCenterColumn(posX, sizeX), penColor, fillColor)
{}

/// @brief Sets the ButtonElement's text to a std::string
/// @param newText The new text
void ButtonElement::setText(std::string newText) const
{
  refreshable = text.setText(newText);

  if (refreshable) text.column = getCenterColumn(posX, sizeX, newText);
}

/// @brief Uses printf() formatting and sets the ButtonElement's text to the result
/// @param format Format string
/// @param ... Arguments for the format string
void ButtonElement::setTextFormat(const char * format, ...) const
{
  __builtin_va_list args;

  __builtin_va_start(args, format);

  char buffer[256];
  
  vsnprintf(buffer, sizeof(buffer), format, args);

  __builtin_va_end(args);

  setText(buffer);
}

void ButtonElement::setPenColor(vex:: color newColor)
{
  if (newColor == penColor) return;

  refreshable = true;

  penColor = newColor;

  text.setPenColor(newColor);
}

void ButtonElement::setFillColor(vex::color newColor)
{
  if (newColor == fillColor) return;

  refreshable = true;

  fillColor = newColor;

  text.setFillColor(newColor);
}

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