#ifndef TEXT_H
#define TEXT_H

#include "libV5gui/core/ScreenElement.h"



namespace libv5gui
{
  class Text : public ScreenElement
  {
    private:
      /// @brief The whitespaced, printed string
      mutable std::string printedText = "";



      /// @return The maximum length of a null-terminated character
      ///         array that would fit on the screen
      unsigned int maxChars(void) const { return floor(49 - x / xScale()); }
      
    public:
      /// @brief The stored string
      mutable std::string text = "";

      mutable int x;
      const int y;



      Text(const std::string &text,
          int rowOrX, int columnOrY, CoordType gridOrPx,
          const vex::color &penColor = vex::white, const vex::color &fillColor = vex::transparent);

      Text(int rowOrX, int columnOrY, CoordType gridOrPx,
          const vex::color &penColor = vex::white, const vex::color &fillColor = vex::transparent);



      bool setTextRaw(std::string newText) const;
      bool setText(const char *format, ...) const;

      void draw(void) override;
  };
}



#endif