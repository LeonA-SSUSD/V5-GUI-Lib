#ifndef TEXT_H
#define TEXT_H

#include "libV5gui/core/ColorElement.h"



namespace libV5gui
{
  class Text : public ColorElement
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
      size_t maxLength(void) const { return floor(48 - x / xScale()); }

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