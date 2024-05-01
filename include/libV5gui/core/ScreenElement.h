#ifndef SCREEN_ELEMENT_H
#define SCREEN_ELEMENT_H

#include "libV5gui/core/CoreFeatures.h"



namespace libv5gui
{
  class ScreenElement
  {
    private:
      inline bool setColor(vex::color &color, const vex::color& newColor);

    protected:
      vex::color penColor;
      vex::color fillColor;

      /// @brief The ScreenElement's "layer" when drawn on a Screen
      int zIndex;

      /// @brief Whether the ScreenElement should be redrawn
      bool refreshable = false;



      inline virtual void uniqueDraw(void) = 0;
      
    public:
      /// @brief Whether the ScreenElement should be drawn
      bool enabled = true;

      

      ScreenElement(const vex::color &penColor, const vex::color &fillColor);



      bool setPenColor(const vex::color &newColor);
      bool setFillColor(const vex::color &newColor);

      void draw(void);



      friend class Screen;
  };
}



#endif