#ifndef SCREEN_H
#define SCREEN_H

#include "libV5gui/core/Text.h"

#include <vector>



namespace libV5gui
{
  class Screen
  {
    /// @brief The screen's element list
    std::list<ScreenElement*> elements;

    /// @brief The screen's main color
    vex::color screenColor = vex::black;

    /// @brief Whether the next refresh() should just draw()
    ///        due to the screen's color changing
    mutable bool screenChanged = false;

    public:
      /// @brief Initializes a screen with a black background
      Screen(void) {}

      Screen(std::vector<ScreenElement*> screenElements, const vex::color &screenColor = vex::black);

      Screen(const vex::color &screenColor);



      void setColor(const vex::color &screenColor);

      void add(ScreenElement &element, int zIndex = -1);
      void add(ScreenElement *element, int zIndex = -1);

      void draw(void) const;
      void refresh(void) const;
      void clear(void) const;

      void enable(void);
      void disable(void);
  };
}



#endif