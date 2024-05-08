#include "libV5gui/core/EventThreader.h"



namespace libV5gui
{
  void EventThreader::poll()
  {
    while (polling)
    {
      vex::this_thread::sleep_for(pollRate);

      mutex.lock();
      for (const auto &event : events) if (event.condition()) event.callback();
      mutex.unlock();
    }
  }

  void EventThreader::startPolling()
  {
    polling = true;

    if (eventThread) return;

    eventThread = new vex::thread(poll);

    eventThread -> detach();
  }

  void EventThreader::stopPolling()
  {
    polling = false;

    if (!eventThread) return;

    eventThread -> join();
    
    delete eventThread;
  }

  void EventThreader::bindEvent(Event event)
  {
    mutex.lock();
    events.push_back(event);
    mutex.unlock();

    startPolling();
  }

  void EventThreader::setPollRate(size_t ms)
  {
    mutex.lock();
    pollRate = ms;
    mutex.unlock();
  }
}