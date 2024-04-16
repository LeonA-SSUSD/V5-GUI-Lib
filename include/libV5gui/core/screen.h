#ifndef SCREEN_H
#define SCREEN_H

#include "libv5gui/core/ScreenElement.h"

#include<list>



namespace libv5gui
{
  class Screen
  {
    private:
      /// @brief The screen's element list
      mutable std::list<ScreenElement*> elements;

      /// @brief The screen's main color
      mutable vex::color screenColor = vex::black;

      /// @brief Whether the next refresh() should just draw()
      ///        due to the screen's color changing
      mutable bool screenChanged = false;

    public:
      /// @brief Initializes a screen with a black background
      Screen(void) {}

      Screen(const vex::color &screenColor);



      void setScreenColor(const vex::color &screenColor) const;

      void add(ScreenElement &element, int zIndex = -1) const;

      void draw(void) const;
      void refresh(void) const;
      void clear(void) const;

      void enable(void) const;
      void disable(void) const;
  };
}



#endif