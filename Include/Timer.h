#ifndef _TIMER_H
#define _TIMER_H

#include "SGUtil.h"
#include <GLFW/glfw3.h>

namespace SGEngine
{
class SGTimer
{
  public:
    static SGTimer& instance();
    ~SGTimer();
    //Call Each Frame
    void Tick();

    float GetDeltaTime() const
    {
        return _deltaTime;
    }

    float GetTotalTime() const
    {
        return _totalTime;
    }

    float GetFPS() const
    {
        return _fps;
    }

  private:
    SGTimer();
    float _deltaTime;
    float _totalTime;
    float _fps, _timeElapsed, _frameCount;
    float _secsPerCnt;
    __int64_t _prevCnts;
};
} // namespace SGEngine

#endif