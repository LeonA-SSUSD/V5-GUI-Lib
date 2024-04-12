#ifndef GENERICS_H
#define GENERICS_H

#include "vex.h"

#include<list>
#include<string>


/// @brief An external instance of the vex::brain
/// that all print/draw functions will call from
extern vex::brain Brain;



int getCenterRow(int posY, int sizeY);

int getCenterColumn(int posX, int sizeX,
                    const std::string & text = "");


class ScreenElement
{
  public:
    mutable vex::color penColor;
    mutable vex::color fillColor;

    const bool isText;

    /// @brief The ScreenElement's "layer" when drawn on a Screen
    int zIndex;

    /// @brief Whether the ScreenElement should be drawn
    bool enabled = true;

    /// @brief Whether the ScreenElement should be redrawn
    mutable bool refreshable = false;

    

    ScreenElement(const vex::color & penColor, const vex::color & fillColor,
                  bool isText = false);



    virtual void setPenColor(const vex::color & newColor);
    virtual void setFillColor(const vex::color & newColor);

    virtual void draw(void) = 0;
};



class Text : public ScreenElement
{
  private:
    /// @brief The whitespaced, printed string
    mutable std::string printedText = "";
    
  public:
    /// @brief The stored string
    mutable std::string text = "";

    int row;
    mutable int column;



    Text(const std::string & text,
         int row, int column,
         const vex::color & penColor = vex::white, const vex::color & fillColor = vex::transparent);

    Text(int row, int column,
         const vex::color & penColor = vex::white, const vex::color & fillColor = vex::transparent);



    bool setText(std::string newText, bool addWhitespaces = true) const;
    bool setTextFormat(const char * format, ...) const;

    void draw(void) override;
};



class ButtonElement : public ScreenElement
{
  private:
    /// @brief Internal variable for tracking new button presses
    mutable bool buttonDown = false;

    /// @brief How many columns of text need to be cleared when the text changes
    mutable int totalWhitespaces = 0;

    /// @brief Where the remaining text starts when the text changes
    mutable int lastColumn;

    /// @brief Used to align the text whenever it is changed
    const int sizeX;

  public:
    /// @brief All buttons will have a leftmost X-coordinate
    const int posX;

    /// @brief All buttons will have an uppermost y-coordinate
    const int posY;

    Text text;



    ButtonElement(int posX, int posY, int sizeX, int sizeY,
                  const std::string & text,
                  const vex::color & penColor, const vex::color & fillColor);

    ButtonElement(int posX, int posY, int sizeX, int sizeY,
                  const vex::color & penColor, const vex::color & fillColor);



    void setText(std::string newText) const;
    void setTextFormat(const char * format, ...) const;

    void cleanText(void) const;

    void setPenColor(const vex::color & newColor) override;
    void setFillColor(const vex::color & newColor) override;

    bool getNewPress(void);

    virtual bool isPressed(void) = 0;
};



class Screen
{
  private:
    /// @brief The screen's element list
    mutable std::list<ScreenElement*> elements;

    /// @brief The screen's main color
    mutable vex::color screenColor = vex::black;

    /// @brief Whether the next refresh() should just draw()
    /// due to the screen's color changing
    mutable bool screenChanged = false;

  public:
    /// @brief Initializes a screen with a black background
    Screen(void) {}

    Screen(const vex::color & screenColor);



    void setScreenColor(const vex::color & screenColor) const;

    void add(ScreenElement & element, int zIndex = -1) const;

    void draw(void) const;
    void refresh(void) const;
    void clear(void) const;

    void enable(void) const;
    void disable(void) const;
};



#endif