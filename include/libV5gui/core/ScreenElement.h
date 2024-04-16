#ifndef SCREEN_ELEMENT_H
#define SCREEN_ELEMENT_H

#include "vex.h"



/// @brief An external instance of the vex::brain
///        that all print/draw functions will call from
extern vex::brain Brain;



namespace libv5gui
{
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

      

      ScreenElement(const vex::color &penColor, const vex::color &fillColor,
                    bool isText = false);



      virtual void setPenColor(const vex::color &newColor);
      virtual void setFillColor(const vex::color &newColor);

      virtual void draw(void) = 0;
  };
}



#endif