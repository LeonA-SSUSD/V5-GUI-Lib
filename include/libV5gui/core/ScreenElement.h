#ifndef SCREEN_ELEMENT_H
#define SCREEN_ELEMENT_H

#include "libV5gui/core/CoreFeatures.h"



namespace libv5gui
{
  class ScreenElement
  {
    friend class Screen;

    private:
      /// @brief The ScreenElement's "layer" when drawn on a Screen
      int zIndex;

    protected:
      /// @brief Whether the ScreenElement should be redrawn
      bool refreshable = false;



      virtual void uniqueDraw(void) = 0;
      
    public:
      /// @brief Whether the ScreenElement should be drawn
      bool enabled = true;

      

      ScreenElement() {}



      void draw(void);
  };
}



#endif