#ifndef GENERICS_H
#define GENERICS_H

#include "vex.h"

#include<list>
#include<string>



extern vex::brain Brain;



int getCenterRow(int posY, int sizeY);

int getCenterColumn(int posX, int sizeX, std::string text = "");


class ScreenElement
{
  public:
    mutable vex::color penColor;
    mutable vex::color fillColor;

    /// @brief Whether the ScreenElement should be drawn
    bool enabled;

    /// @brief Whether the ScreenElement should be redrawn
    mutable bool refreshable;
    
    bool isText;

    bool zIndex;

    

    ScreenElement(vex::color penColor, vex::color fillColor, bool isText = false);



    void setPenColor(vex::color newColor);
    void setFillColor(vex::color newColor);

    virtual void draw() = 0;
};



class Text : public ScreenElement
{
  private:
    /// @brief The whitespaced, printed string
    mutable std::string printedText;
    
  public:
    /// @brief The stored string
    mutable std::string text;

    int row;
    mutable int column;



    Text(std::string text, int row, int column, vex::color penColor = vex::white, vex::color fillColor = vex::transparent);

    Text(int row, int column, vex::color penColor = vex::white, vex::color fillColor = vex::transparent);



    bool setText(std::string newText) const;
    bool setTextFormat(const char * format, ...) const;

    void draw() override;
};



class ButtonElement : public ScreenElement
{
  private:
    /// @brief Internal variable for tracking new button presses
    mutable bool buttonDown = false;

  public:
    int posX;
    int posY;

    int sizeX;

    Text text;



    ButtonElement(int posX, int posY, int sizeX, int sizeY, std::string text, vex::color penColor, vex::color fillColor);
    ButtonElement(int posX, int posY, int sizeX, int sizeY, vex::color penColor, vex::color fillColor);



    void setText(std::string newText) const;
    void setTextFormat(const char * format, ...) const;

    virtual void setPenColor(vex::color newColor);
    virtual void setFillColor(vex::color newColor);

    bool getNewPress();

    virtual bool isPressed() = 0;
};



class Screen
{
  private:
    /// @brief The screen's element list
    mutable std::list<ScreenElement*> elements;

    /// @brief The screen's main color
    vex::color bgColor;

  public:
    Screen();

    Screen(vex::color screenColor);



    void add(ScreenElement & element, int zIndex = -1) const;

    void draw() const;

    void refresh() const;

    void clear() const;

    void enable() const;

    void disable() const;
};



#endif