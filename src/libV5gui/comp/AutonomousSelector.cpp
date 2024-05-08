#include "libV5gui/comp/AutonomousSelector.h"



namespace libV5gui
{
  std::function<void ()> AutonomousSelector::setAuton(std::function<void ()> auton)
  {
    return std::bind([=]{ selectedAutonomous = auton; });
  }

  void AutonomousSelector::bindAuton1(std::function<void ()> auton)
  {
    auton1.addCallback(setAuton(auton));

    screen.draw();
  }

  void AutonomousSelector::bindAuton2(std::function<void ()> auton)
  {
    auton2.addCallback(setAuton(auton));

    screen.draw();
  }

  void AutonomousSelector::bindAuton3(std::function<void ()> auton)
  {
    auton3.addCallback(setAuton(auton));

    screen.draw();
  }

  void AutonomousSelector::bindAuton4(std::function<void ()> auton)
  {
    auton4.addCallback(setAuton(auton));

    screen.draw();
  }

  void AutonomousSelector::runAutonomous()
  {
    screen.disable();
    screen.clear();
    
    selectedAutonomous();
    
    screen.draw();
    screen.enable();
  }
}