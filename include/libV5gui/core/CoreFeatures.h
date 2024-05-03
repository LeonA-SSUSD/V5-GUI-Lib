#ifndef CORE_FEATURES_H
#define CORE_FEATURES_H

#include "vex.h"

#include <string>



/// @brief An external instance of the vex::brain
///        that all print/draw functions will call from
extern vex::brain Brain;



namespace libv5gui
{
  enum CoordType { px, grid };



  int xScale(void);
  int yScale(void);

  int getCenterRow(int posY, int sizeY);
  int getCenterColumn(int posX, int sizeX, const std::string &text = "");

  int getCenterX(int posX, int sizeX, const std::string &text = "");
  int getCenterY(int posY, int sizeY);



  std::string vnFormat(size_t length, std::string format, __builtin_va_list args);
  std::string nFormat(size_t length, std::string format, ...);

  std::string vFormat(std::string format, __builtin_va_list args);
  std::string format(std::string format, ...);
}



#endif