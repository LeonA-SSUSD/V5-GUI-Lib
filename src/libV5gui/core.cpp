#include "libV5gui/core.h"

#include<cstdarg>



ScreenObject::ScreenObject(vex::color penColor, vex::color fillColor, bool isText)
            : penColor(penColor), fillColor(fillColor), enabled(true), refreshable(false), isText(isText)
{}

void ScreenObject::setPenColor(vex::color newColor) const { penColor = newColor; }
void ScreenObject::setFillColor(vex::color newColor) const { fillColor = newColor; }

void ScreenObject::enable() const { enabled = true; }
void ScreenObject::disable() const { enabled = false; }

void ScreenObject::draw() {}



Text::Text(std::string text, int row, int column, vex::color penColor, vex::color fillColor)
    : ScreenObject(penColor, fillColor, true), printedText(text), text(text), row(row), column(column)
{}

void Text::draw()
{
  if (!enabled) return;

  refreshable = false;

  Brain.Screen.setPenColor(penColor);
  Brain.Screen.setFillColor(fillColor);

  Brain.Screen.setCursor(row, column);
  Brain.Screen.print(printedText.c_str());

  Brain.Screen.setPenColor(vex::white);
  Brain.Screen.setFillColor(vex::black);

  printedText = text;
}

void Text::setText(std::string newText) const
{
  if (newText == text) return;

  refreshable = true;

  const int whitespaces = fmax(text.length() - newText.length(), 0);

  printedText = text.length() > newText.length() ? newText.append(whitespaces, ' ') : newText;

  text = newText;
}

/// @brief Behaves like Text::setText() but with built-in formatting
/// @param format Format string
/// @param  ... Arguments for the format string
void Text::setTextFormat(const char * format, ...) const
{
  va_list args;

  va_start(args, format);

  char buffer[256];
  
  vsnprintf(buffer, sizeof(buffer), format, args);

  va_end(args);

  setText(buffer);
}



ButtonObject::ButtonObject(int posX, int posY, vex::color penColor, vex::color fillColor)
            : ScreenObject(penColor, fillColor), posX(posX), posY(posY)
{}

/// @brief NOT thread safe: you should use this function once
///        and store its data in a variable afterwards or it
///        will not return the same value
/// @return true if a press has just started
bool ButtonObject::getNewPress()
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

/// @brief True buttons override this function
/// @return If a button is currently pressed
bool ButtonObject::isPressed() { return false; }


/// @brief Initializes a screen with a black background
Screen::Screen() {}

/// @brief Initializes a screen with a chosen color
/// @param bgColor Screen background color
Screen::Screen(vex::color bgColor) : bgColor(bgColor) {}

/// @brief Adds an element to the screen
/// @param element The screen element to add
void Screen::add(ScreenObject & element) const
{
  if (element.isText) element.setFillColor(bgColor);

  elements.push_back(&element);
}

/// @brief Draws all elements on the screen after ensuring it has its background color
void Screen::draw() const
{ 
  if (firstDraw) 
  {
    firstDraw = false;

    clear();
  }

  for (auto & element : elements) if (element -> drawable) element -> draw();
}

/// @brief Refreshes elements on the screen
void Screen::refresh() const { for (auto & element : elements) if (element -> refreshable) element -> draw(); }

/// @brief Clears the screen to its background color
void Screen::clear() const { Brain.Screen.clearScreen(bgColor); }

/// @brief Enables all elements on the screen
void Screen::enable() const { for (auto & element : elements) element -> enabled = true; }

/// @brief Disables all elements on the screen
void Screen::disable() const { for (auto & element : elements) element -> enabled = false; }