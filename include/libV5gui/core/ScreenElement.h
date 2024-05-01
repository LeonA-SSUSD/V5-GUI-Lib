#ifndef SCREEN_ELEMENT_H
#define SCREEN_ELEMENT_H

#include "libV5gui/core/CoreFeatures.h"



namespace libv5gui
{
  class ScreenElement
  {
    private:
      bool setColor(vex::color &color, const vex::color& newColor);

    protected:
      vex::color penColor;
      vex::color fillColor;

      /// @brief The ScreenElement's "layer" when drawn on a Screen
      int zIndex;

      /// @brief Whether the ScreenElement should be redrawn
      bool refreshable = false;



      virtual bool isText(void) { return false; }
      
    public:
      /// @brief Whether the ScreenElement should be drawn
      bool enabled = true;

      

      ScreenElement(const vex::color &penColor, const vex::color &fillColor);



      bool setPenColor(const vex::color &newColor);
      bool setFillColor(const vex::color &newColor);

      virtual void draw(void) = 0;



      friend class Screen;
  };
}



#endif