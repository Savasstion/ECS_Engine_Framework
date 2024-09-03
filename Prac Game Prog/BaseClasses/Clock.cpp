#include "Clock.h"
#include <chrono>
#include <cmath>

using namespace std::chrono;

Clock::Clock()
{
    this->centerPosX = DEFAULT_CENTER_POINT_X;
    this->centerPosY = DEFAULT_CENTER_POINT_Y;
}

Clock::Clock(int x, int y)
{
    this->centerPosX = x;
    this->centerPosY = y;
}

//double Clock::getInteriorAngle(){    return this->interiorAngle; }
//float Clock::getCentralAngle(){return this->centralAngle;}

std::tm Clock::GetSystemTime()
{
    // Get the current time as a time_point
    auto now = system_clock::now();

    // Convert the time_point to a time_t which is a C-style time representation
    std::time_t now_c = system_clock::to_time_t(now);

    // Convert the time_t to a tm structure to access individual components
    std::tm time;
    localtime_s(&time, &now_c);

    return time;
    
}

void Clock::UpdateClockTime()
{
    currentTime = GetSystemTime();
    SetHourVertices();
    SetMinVertices();
    SetSecVertices();
}

float Clock::GetCentralAngle()
{
    return this->centralAngle;
}

float Clock::GetXVertex(float radius, double angle, float posX)
{
return (float)(posX + (  radius * cos(angle - (PI/2)) ));
    
}

float Clock::GetYVertex(float radius, double angle, float posY)
{
    return (float)(posY + (  radius * sin(angle - (PI/2)) ));
    
}

void Clock::SetHourVertices()
{
    int hour = currentTime.tm_hour;
    int min = currentTime.tm_min;

    //  12 hour clock
    hour %= 12;

    // in radians
    double angle = hour * centralAngle;
    //  account for mins as well
    angle += (min / 60.0) * centralAngle;
    
    xHour = GetXVertex(hourRadius, angle, centerPosX);
    yHour = GetYVertex(hourRadius, angle, centerPosY);
    
}

void Clock::SetMinVertices()
{
    int min = currentTime.tm_min;
    
    double angle = (min / 60.0) * (2 * PI);

    xMin = GetXVertex(minRadius, angle, centerPosX);
    yMin = GetYVertex(minRadius, angle, centerPosY);
    
}

void Clock::SetSecVertices()
{
    int sec = this->currentTime.tm_sec;

    double angle = (sec / 60.0) * (2 * PI);

    xSec = GetXVertex(secRadius, angle, centerPosX);
    ySec = GetYVertex(secRadius, angle, centerPosY);
}

float Clock::GetXHour()
{
    return this->xHour;
}

float Clock::GetYHour()
{
    return this->yHour;
}

float Clock::GetXMin()
{
    return this->xMin;
}

float Clock::GetYMin()
{
    return this->yMin;
}

float Clock::GetXSec()
{
    return this->xSec;
}

float Clock::GetYSec()
{
    return this->ySec;
}

float Clock::GetClockRadius()
{
    return this->clockRadius;
}

float Clock::GetCenterPointX()
{
    return this->centerPosX;
}

float Clock::GetCenterPointY()
{
    return this->centerPosY;
}
