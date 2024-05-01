#include "libV5gui/core/CoreFeatures.h"



namespace libv5gui
{
  /// @brief Acts as the base unit for all pixel x-coordinate
  ///        to grid conversions
  /// @return The width of one column in pixels
  int xScale() { return Brain.Screen.getStringWidth(" "); }

  /// @brief Acts as the base unit for all pixel y-coordinate
  ///        to grid conversions
  /// @return The height of one row in pixels
  int yScale() { return Brain.Screen.getStringHeight(" "); }

  /// @brief Gets the central row from a pixel-coordinate position and length
  /// @param posY The uppermost pixel coordinate
  /// @param sizeY The distance from the uppermost to the lowermost pixel coordinate
  /// @return The central row
  int getCenterRow(int posY, int sizeY)
  {
    // (posY + sizeY/2) / yScale
    return ceil((posY + 0.5 * sizeY) / yScale()) + 1;
  }

  /// @brief Gets the central column from a pixel-coordinate position and length
  ///        as well a text string's character length
  /// @param posX The leftmost pixel coordinate
  /// @param sizeX The distance from the leftmost to the rightmost pixel coordinate
  /// @param text A text string in which the character length is accounted for in this function
  /// @return The central column number adjusted to center text
  int getCenterColumn(int posX, int sizeX, const std::string &text)
  {
    // (posX + sizeX/2) / xScale - text.length()/2
    return ceil((posX + 0.5 * sizeX) / xScale() - 0.5 * text.length()) + 1;
  }

  /// @brief Gets the central pixel x-coordinate from a position and length
  ///        as well a text string's character length
  /// @param posX The leftmost pixel coordinate
  /// @param sizeX The distance from the leftmost to the rightmost pixel coordinate
  /// @param text A text string in which the character length is accounted for in this function
  /// @return The central pixel x-coordinate adjusted to center text
  int getCenterX(int posX, int sizeX, const std::string &text)
  {
    // posX + (sizeX - text.pixelWidth())/2
    return ceil(posX + 0.5 * (sizeX - xScale() * text.length()));
  }

  /// @brief Gets the central pixel y-coordinate from a position and length
  /// @param posY The uppermost pixel coordinate
  /// @param sizeY The distance from the uppermost to the lowermost pixel coordinate
  /// @return The central pixel y-coordinate
  int getCenterY(int posY, int sizeY)
  {
    // posY + sizeY/2
    return ceil(posY + 0.5 * sizeY);
  }
}