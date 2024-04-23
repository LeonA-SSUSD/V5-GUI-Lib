#ifndef BUTTON_ELEMENT_H
#define BUTTON_ELEMENT_H

#include "libV5gui/core/Text.h"
#include "libV5gui/core/Shape.h"



namespace libv5gui
{
  class ButtonElement : public ScreenElement
  {
    private:
      /// @brief Internal variable for tracking new button presses
      mutable bool buttonDown = false;

      /// @brief How many columns of text need to be cleared when the text changes
      mutable int totalWhitespaces = 0;

      /// @brief Where the remaining text starts when the text changes
      mutable int lastColumn;

      /// @brief Used to align the text whenever it is changed
      const int _sizeX;



      bool setColor(vex::color &color, vex::color &shapeColor, vex::color &textColor,
                    const vex::color &newColor) const;

      virtual bool pressCondition(void) = 0;

    public:
      Shape *shape = 0;

      Text text;



      ButtonElement(int posX, int posY, int sizeX, int sizeY,
                    const std::string &text,
                    const vex::color &penColor, const vex::color &fillColor);

      ButtonElement(int posX, int posY, int sizeX, int sizeY,
                    const vex::color &penColor, const vex::color &fillColor);



      void setText(std::string newText) const;
      void setTextFormat(const char * format, ...) const;

      void cleanText(void) const;

      bool setPenColor(const vex::color &newColor) override;
      bool setFillColor(const vex::color &newColor) override;

      bool isPressed(void);
      bool getNewPress(void);

      void draw(void) override;
  };
}



#endif