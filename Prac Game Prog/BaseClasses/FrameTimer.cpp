#include "FrameTimer.h"

void FrameTimer::Init(int requestedFPS)
{
    QueryPerformanceFrequency(&timerFreq);
    QueryPerformanceCounter(&timeNow);
    QueryPerformanceCounter(&timePrev);

    this->requestedFPS = requestedFPS;

    intervalsPerFrame = timerFreq.QuadPart / requestedFPS;
}

int FrameTimer::GetFramesToUpdate()
{
    int framesToUpdate = 0;
    QueryPerformanceCounter(&timeNow);

    deltaTime = timeNow.QuadPart - timePrev.QuadPart;

    framesToUpdate = (int)(deltaTime / intervalsPerFrame);

    if(framesToUpdate != 0)
        QueryPerformanceCounter(&timePrev);
    
    return framesToUpdate;
}
