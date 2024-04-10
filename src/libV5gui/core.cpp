#include "libV5gui/core.h"



/// @brief Gets the central row from a pixel-coordinate position and length
/// @param posY The uppermost pixel coordinate
/// @param sizeY The distance from the uppermost to the lowermost pixel coordinate
/// @return The central row
int getCenterRow(int posY, int sizeY) { return ceil((posY + sizeY / 2) / 20) + 1; }

/// @brief Gets the central column from a pixel-coordinate position and length as well a text string's character length
/// @param posX The leftmost pixel coordinate
/// @param sizeX The distance from the leftmost to the rightmost pixel coordinate
/// @param text A text string in which the character length is accounted for in this function
/// @return The central column number adjusted to center text
int getCenterColumn(int posX, int sizeX, const std::string & text)
{
  return ceil((posX + sizeX / 2) / 10 - text.length() / 2) + 1;
}



ScreenElement::ScreenElement(const vex::color & penColor, const vex::color & fillColor, bool isText)
             : penColor(penColor), fillColor(fillColor), isText(isText), enabled(true), refreshable(false)
{}

/// @brief Sets the ScreenElement's pen color and automatically determines refreshability
/// @param newColor The new pen color
void ScreenElement::setPenColor(const vex::color & newColor)
{
  if (penColor == newColor) return;

  refreshable = true;

  penColor = newColor;
}

/// @brief Sets the ScreenElement's fill color and automatically determines refreshability
/// @param newColor The new fill color
void ScreenElement::setFillColor(const vex::color & newColor)
{
  if (fillColor == newColor) return;

  refreshable = true;

  fillColor = newColor;
}



Text::Text(const std::string & text, int row, int column, const vex::color & penColor, const vex::color & fillColor)
    : ScreenElement(penColor, fillColor, true), printedText(text), text(text), row(row), column(column)
{}

Text::Text(int row, int column, const vex::color & penColor, const vex::color & fillColor)
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
/// @param addWhitespaces Whether the text deletes
/// characters it won't directly overwrite
/// (for internal purposes)
/// @return Whether the text is refreshable
bool Text::setText(std::string newText, bool addWhitespaces) const
{
  if (newText == text) return false;

  refreshable = true;

  if (addWhitespaces)
  {
    bool hasWhitespaces = text.length() > newText.length();

    int whitespaces = fmax(text.length() - newText.length(), 0);

    text = newText;

    printedText = (hasWhitespaces) ? newText.append(whitespaces, ' ') : text;
  }

  else
  {
    text = newText;

    printedText = text;
  }

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
                             const std::string & text,
                             const vex::color & penColor, const vex::color & fillColor)
             : ScreenElement(penColor, fillColor), sizeX(sizeX), posX(posX), posY(posY),
               text(text, getCenterRow(posY, sizeY), getCenterColumn(posX, sizeX, text), penColor, fillColor)
{}

ButtonElement::ButtonElement(int posX, int posY, int sizeX, int sizeY,
                             const vex::color & penColor, const vex::color & fillColor)
             : ScreenElement(penColor, fillColor), sizeX(sizeX), posX(posX), posY(posY),
               text(getCenterRow(posY, sizeY), getCenterColumn(posX, sizeX), penColor, fillColor)
{}

/// @brief Sets the ButtonElement's text to a std::string
/// @param newText The new text
void ButtonElement::setText(std::string newText) const
{
  if (text.setText(newText, false)) 
  {
    refreshable = true;

    lastColumn = text.column;
    
    int lastLength = text.text.length();
    
    text.column = getCenterColumn(posX, sizeX, newText);

    totalWhitespaces = fmax(lastLength + abs(lastColumn - text.column), 0);
  }
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

/// @brief Removes leftover text from edges realigning when the text is changed
void ButtonElement::cleanText() const
{
  if (!totalWhitespaces) return;

  std::string whitespaces;

  whitespaces.append(totalWhitespaces, ' ');

  Brain.Screen.setCursor(text.row, lastColumn);

  Brain.Screen.print(whitespaces.c_str());
}

/// @brief Sets the ButtonElement and its text's pen color and
/// automatically determines refreshability, overrides
/// ScreenElement::setPenColor
/// @param newColor The new pen color
void ButtonElement::setPenColor(const vex::color & newColor)
{
  if (penColor == newColor && text.penColor == newColor) return;

  refreshable = true;

  penColor = newColor;

  text.setPenColor(penColor);
}

/// @brief Sets the ButtonElement and its text's fill color and
/// automatically determines refreshability, overrides
/// ScreenElement::setFillColor
/// @param newColor The new fill color
void ButtonElement::setFillColor(const vex::color & newColor)
{
  if (fillColor == newColor && text.fillColor == newColor) return;

  refreshable = true;

  fillColor = newColor;

  text.setFillColor(fillColor);
}

/// @brief NOT thread safe: you should use this function in
///        the loop once and store its data in a variable
///        afterwards or it will not return the same value
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



/// @brief Initializes a screen with a black background
Screen::Screen() : bgColor(vex::black) {}

/// @brief Initializes a screen with a chosen color
/// @param bgColor Screen background color
Screen::Screen(const vex::color & bgColor) : bgColor(bgColor) {}

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

  for (const auto & element : elements) 
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