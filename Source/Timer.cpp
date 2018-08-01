#include "Timer.h"

namespace SGEngine
{

SGTimer &SGTimer::instance()
{
    static SGTimer *_instance = new SGTimer();
    return *_instance;
}
SGTimer::SGTimer()
{
    _deltaTime = _fps = _frameCount = _timeElapsed = _totalTime = 0.0f;
    __int64_t cntsPerSec = glfwGetTimerFrequency();
    _secsPerCnt = (float)(1.0f / cntsPerSec);

    _prevCnts = glfwGetTimerValue();
}

void SGTimer::Tick()
{
    __int64_t currCnts = glfwGetTimerValue();
    __int64_t delta = currCnts - _prevCnts;
    _prevCnts = currCnts;
    _deltaTime = delta * _secsPerCnt;

    //Make sure that delta time does not become negative
    if (_deltaTime < 0.0f)
    {
        _deltaTime = 0.0f;
    }

    _totalTime += _deltaTime;

    _frameCount++;
    _timeElapsed += _deltaTime;
    if (_timeElapsed >= 1.0f)
    {
        _fps = _frameCount;
        _frameCount = _timeElapsed = 0.0f;
    }
}

SGTimer::~SGTimer()
{
}

} // namespace SGEngine