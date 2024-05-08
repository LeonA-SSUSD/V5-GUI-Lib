#ifndef AUTONOMOUS_SELECTOR_H
#define AUTONOMOUS_SELECTOR_H

#include "libV5gui/core/Screen.h"
#include "libV5gui/buttons/RectButton.h"



namespace libV5gui
{
  class AutonomousSelector
  {
    static inline auto auton1 = RectButton(0,     0, 240, 120, "AUTON 1");
    static inline auto auton2 = RectButton(240,   0, 240, 120, "AUTON 2");
    static inline auto auton3 = RectButton(0,   120, 240, 120, "AUTON 3");
    static inline auto auton4 = RectButton(240, 120, 240, 120, "AUTON 4");

    static inline auto screen = Screen({ &auton1, &auton2, &auton3, &auton4 });

    static std::function<void (void)> selectedAutonomous;

    

    static std::function<void (void)> setAuton(std::function<void (void)> auton);

    public:
      static void bindAuton1(std::function<void (void)> auton);
      static void bindAuton2(std::function<void (void)> auton);
      static void bindAuton3(std::function<void (void)> auton);
      static void bindAuton4(std::function<void (void)> auton);

      static void runAutonomous(void);
  };
}



#endif