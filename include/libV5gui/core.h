#ifndef GENERICS_H
#define GENERICS_H

#include "vex.h"

#include<list>
#include<string>



extern vex::brain Brain;

class ScreenObject
{
  public:
    mutable vex::color penColor;
    mutable vex::color fillColor;

    /// @brief Whether the ScreenObject should be drawn
    mutable bool enabled = true;

    /// @brief Whether the ScreenObject should be redrawn
    mutable bool refreshable = false;
    
    bool isText;

    

    ScreenObject(vex::color penColor, vex::color fillColor, bool isText = false);



    void setPenColor(vex::color newColor) const;
    void setFillColor(vex::color newColor) const;

    void enable() const;
    
    void disable() const;

    virtual void draw();
};



class Text : public ScreenObject
{
  private:
    /// @brief The whitespaced, printed string
    mutable std::string printedText;
    
  public:
    /// @brief The stored string
    mutable std::string text;

    int row;
    int column;



    Text(std::string text, int  row, int column, vex::color penColor = vex::white, vex::color fillColor = vex::black);

    Text(int row, int column, vex::color penColor = vex::white, vex::color fillColor = vex::black);


    void draw() override;

    void setText(std::string newText) const;
    void setTextFormat(const char * format, ...) const;
};



class ButtonElement : public ScreenObject
{
  private:
    /// @brief Internal variable for tracking new button presses
    mutable bool buttonDown = false;

  public:
    int posX;
    int posY;



    ButtonElement(int posX, int posY, vex::color penColor, vex::color fillColor);



    bool getNewPress();

    virtual bool isPressed();
};



class Screen
{
  private:
    /// @brief The screen's element list
    mutable std::list<ScreenObject*> elements;

    /// @brief The screen's main color
    vex::color bgColor;

  public:
    Screen();

    Screen(vex::color screenColor);



    void add(ScreenObject & element) const;

    void draw() const;

    void refresh() const;

    void clear() const;

    void enable() const;

    void disable() const;
};



#endif