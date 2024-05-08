#ifndef EVENT_H
#define EVENT_H

#include "libV5gui/core/CoreFeatures.h"

#include <functional>



namespace libV5gui
{
  struct Event
  {
    std::function<bool (void)> condition;
    std::function<void (void)>  callback;
  };
}



#endif