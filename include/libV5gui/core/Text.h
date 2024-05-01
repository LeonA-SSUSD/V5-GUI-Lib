#ifndef TEXT_H
#define TEXT_H

#include "libV5gui/core/ScreenElement.h"



namespace libv5gui
{
  class Text : public ScreenElement
  {
    private:
      /// @brief The stored string
      std::string text = "";

      /// @brief The whitespaced, printed string
      std::string printedText = "";

      const int y;



      /// @return The maximum length of a null-terminated character
      ///         array that would fit on the screen
      unsigned int maxChars(void) const { return floor(49 - x / xScale()); }
      
    protected:
      int x;



      bool setTextRaw(std::string newText);

      void uniqueDraw(void) override;

    public:
      Text(const std::string &text,
          int rowOrX, int columnOrY, CoordType gridOrPx,
          const vex::color &penColor = vex::white, const vex::color &fillColor = vex::transparent);

      Text(int rowOrX, int columnOrY, CoordType gridOrPx,
          const vex::color &penColor = vex::white, const vex::color &fillColor = vex::transparent);



      bool setText(const char *format, ...);



      friend class ButtonElement;
  };
}



#endif