#ifndef RECT_BUTTON_H
#define RECT_BUTTON_H

#include "libV5gui/core/ButtonElement.h"
#include "libV5gui/shapes/Rectangle.h"



namespace libV5gui
{
  class RectButton : public ButtonElement
  {
    Rectangle rectangle;



    Shape *shape(void) override { return &rectangle; }
      
    static bool _rectNewPress(RectButton &button) { return button.getNewPress(); }
      
    public:
      RectButton(int posX, int posY, int sizeX, int sizeY,
                 const std::string &text,
                 const vex::color &penColor = vex::white, const vex::color &fillColor = vex::black);

      RectButton(int posX, int posY, int sizeX, int sizeY,
                 const vex::color &penColor = vex::white, const vex::color &fillColor = vex::black);


      
      void addCallback(std::function<void (void)> callback) override;
  };
}



#endif