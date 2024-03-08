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

    mutable bool enabled = true;
    mutable bool refreshable = false;
    
    bool isText;

    bool drawable = true;

    

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
    mutable std::string printedText;
    
  public:
    mutable std::string text;

    int row;
    int column;



    Text(std::string text, int  row, int column, vex::color penColor = vex::white, vex::color fillColor = vex::black);

    Text(int row, int column, vex::color penColor = vex::white, vex::color fillColor = vex::black);


    void draw() override;

    void setText(std::string newText) const;
    void setTextFormat(const char * format, ...) const;
};



class ButtonObject : public ScreenObject
{
  private:
    mutable bool buttonDown = false;

  public:
    int posX;
    int posY;



    ButtonObject(int posX, int posY, vex::color penColor, vex::color fillColor);



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