#ifndef GUI_LIB_H
#define GUI_LIB_H

#include "libV5gui/core.h"



class RectButton : public ButtonElement
{
  private:
    int sizeX;
    int sizeY;
  
  public:
    RectButton(int posX, int posY, int sizeX, int sizeY,
               const std::string & text,
               const vex::color & penColor = vex::white, const vex::color & fillColor = vex::black);

    RectButton(int posX, int posY, int sizeX, int sizeY,
               const vex::color & penColor = vex::white, const vex::color & fillColor = vex::black);

    

    void draw(void) override;
    bool isPressed(void) override;
};

class CircButton : public ButtonElement
{
  private:
    int diameter;
    int radius;

    int centerX;
    int centerY;
  
  public:
    CircButton(int posX, int posY, int diameter,
               const std::string & text,
               const vex::color & penColor = vex::white, const vex::color & fillColor = vex::black);

    CircButton(int posX, int posY, int diameter,
               const vex::color & penColor = vex::white, const vex::color & fillColor = vex::black);
    


    void draw(void) override;
    bool isPressed(void) override;
};



#endif