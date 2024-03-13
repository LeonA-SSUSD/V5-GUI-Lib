#ifndef GUI_LIB_H
#define GUI_LIB_H

#include "libV5gui/core.h"



class RectButton : public ButtonElement
{
  private:
    int sizeX;
    int sizeY;

    Text text;
  
  public:
    RectButton(int posX, int posY, int sizeX, int sizeY, std::string text, vex::color penColor = vex::white, vex::color fillColor = vex::black);

    

    void draw() override;
    bool isPressed() override;
};

class CircButton : public ButtonElement
{
  private:
    int sizeX;
    int sizeY;

    int radius;

    int centerX;
    int centerY;

    Text text;
  
  public:
    CircButton(int posX, int posY, int radius, std::string text, vex::color penColor = vex::white, vex::color fillColor = vex::black);

    

    void draw() override;
    bool isPressed() override;
};



#endif