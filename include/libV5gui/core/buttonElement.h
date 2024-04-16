#ifndef BUTTON_ELEMENT_H
#define BUTTON_ELEMENT_H

#include "libV5gui/core/text.h"



namespace libv5gui
{
  int getCenterRow(int posY, int sizeY);

  int getCenterColumn(int posX, int sizeX,
                      const std::string &text = "");



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
      const int sizeX;

    public:
      /// @brief All buttons will have a leftmost X-coordinate
      const int posX;

      /// @brief All buttons will have an uppermost y-coordinate
      const int posY;

      Text text;



      ButtonElement(int posX, int posY, int sizeX, int sizeY,
                    const std::string &text,
                    const vex::color &penColor, const vex::color &fillColor);

      ButtonElement(int posX, int posY, int sizeX, int sizeY,
                    const vex::color &penColor, const vex::color &fillColor);



      void setText(std::string newText) const;
      void setTextFormat(const char * format, ...) const;

      void cleanText(void) const;

      void setPenColor(const vex::color &newColor) override;
      void setFillColor(const vex::color &newColor) override;

      bool getNewPress(void);

      virtual bool isPressed(void) = 0;
  };
}



#endif