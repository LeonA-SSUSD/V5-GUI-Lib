#ifndef TEXT_H
#define TEXT_H

#include "libV5gui/core/ScreenElement.h"



namespace libv5gui
{
  class Text : public ScreenElement
  {
    friend class ButtonElement;
    
    private:
      /// @brief The stored string
      std::string text = "";

      /// @brief The whitespaced, printed string
      std::string printedText = "";

      int x;
      int y;



      void init(int rowOrX, int columnOrY, CoordType gridOrPx);



      bool setTextRaw(std::string newText);

      /// @return The maximum length of a null-terminated character
      ///         array that would fit on the screen
      unsigned int maxChars(void) const { return floor(49 - x / xScale()); }

    protected:
      void uniqueDraw(void) override;

    public:
      Text(const std::string &text,
          int rowOrX, int columnOrY, CoordType gridOrPx,
          const vex::color &penColor = vex::white, const vex::color &fillColor = vex::transparent);

      Text(int rowOrX, int columnOrY, CoordType gridOrPx,
          const vex::color &penColor = vex::white, const vex::color &fillColor = vex::transparent);



      bool setText(std::string format, ...);
  };
}



#endif