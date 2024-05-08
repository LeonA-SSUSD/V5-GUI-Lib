#ifndef EVENT_THREADER_H
#define EVENT_THREADER_H

#include "libV5gui/core/Event.h"



namespace libV5gui
{
  class EventThreader
  {
    inline static vex::thread *eventThread = 0;

    inline static bool   polling  = false;
    inline static size_t pollRate =    10;

    inline static auto mutex = vex::mutex();

    inline static auto events = std::list<Event>();



    static void poll(void);

    static void startPolling(void);
    static void stopPolling (void);

    public:
      static void bindEvent(Event event);

      static void setPollRate(size_t ms);
  };
}



#endif