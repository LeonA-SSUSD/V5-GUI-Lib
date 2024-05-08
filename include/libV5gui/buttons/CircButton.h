#ifndef CIRC_BUTTON_H
#define CIRC_BUTTON_H

#include "libV5gui/core/ButtonElement.h"
#include "libV5gui/shapes/Circle.h"



namespace libV5gui
{
  class CircButton : public ButtonElement
  {
    Circle circle;



    Shape *shape(void) override { return &circle; }
      
    static bool _circNewPress(CircButton &button) { return button.getNewPress(); }
      
    public:
      CircButton(int posX, int posY, int diameter,
                 const std::string &text,
                 const vex::color &penColor = vex::white, const vex::color &fillColor = vex::black);

      CircButton(int posX, int posY, int diameter,
                 const vex::color &penColor = vex::white, const vex::color &fillColor = vex::black);



      void addCallback(std::function<void (void)> callback) override;
  };
}



#endif