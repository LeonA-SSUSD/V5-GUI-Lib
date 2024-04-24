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
      
    public:
      /// @brief The stored string
      mutable std::string text = "";

      const int row;
      mutable int column;



      Text(const std::string &text,
          int row, int column,
          const vex::color &penColor = vex::white, const vex::color &fillColor = vex::transparent);

      Text(int row, int column,
          const vex::color &penColor = vex::white, const vex::color &fillColor = vex::transparent);



      bool setText(std::string newText) const;
      bool setTextRaw(std::string newText) const;
      bool setTextFormat(const char * format, ...) const;

      void draw(void) override;
  };
}



#endif