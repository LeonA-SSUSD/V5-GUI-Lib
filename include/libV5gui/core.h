#ifndef GENERICS_H
#define GENERICS_H

#include "vex.h"

#include<list>
#include<string>



extern vex::brain Brain;



int getCenterRow(int posY, int sizeY);

int getCenterColumn(int posX, int sizeX,
                    const std::string & text = "");


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
    mutable std::string printedText;
    
  public:
    /// @brief The stored string
    mutable std::string text;

    int row;
    mutable int column;



    Text(const std::string & text,
         int row, int column,
         const vex::color & penColor = vex::white, const vex::color & fillColor = vex::transparent);

    Text(int row, int column,
         const vex::color & penColor = vex::white, const vex::color & fillColor = vex::transparent);



    bool setText(std::string newText) const;
    bool setTextFormat(const char * format, ...) const;

    void draw(void) override;
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



    ButtonElement(int posX, int posY, int sizeX, int sizeY,
                  const std::string & text,
                  const vex::color & penColor, const vex::color & fillColor);

    ButtonElement(int posX, int posY, int sizeX, int sizeY,
                  const vex::color & penColor, const vex::color & fillColor);



    void setText(std::string newText) const;
    void setTextFormat(const char * format, ...) const;

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
    vex::color bgColor;

  public:
    Screen(void);

    Screen(const vex::color & screenColor);



    void add(ScreenElement & element, int zIndex = -1) const;

    void draw(void) const;

    void refresh(void) const;

    void clear(void) const;

    void enable(void) const;

    void disable(void) const;
};



#endif