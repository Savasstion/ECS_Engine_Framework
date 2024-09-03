#pragma once
#include <ctime>
#define PI 3.14159
#define DEFAULT_CENTER_POINT_X 500
#define DEFAULT_CENTER_POINT_Y 500

class Clock
{
    const unsigned int vertices = 12;
    const float clockRadius = 200.0;
    float hourRadius = clockRadius - 150;
    float minRadius = clockRadius - 100;
    float secRadius = clockRadius - 50;
    //double interiorAngle = (vertices - 2) * PI / vertices;
    double centralAngle = 2 * PI / vertices;
    float centerPosX, centerPosY;
    float xHour, yHour, xMin, yMin, xSec, ySec;
    tm currentTime;
    
    //float getCentralAngle();
    tm GetSystemTime();
    void SetHourVertices();
    void SetMinVertices();
    void SetSecVertices();

public:
    //double getInteriorAngle();
    Clock();
    Clock(int x, int y);
    void UpdateClockTime();
    float GetCentralAngle();
    float GetCenterPointX();
    float GetCenterPointY();
    float GetXHour();
    float GetYHour();
    float GetXMin();
    float GetYMin();
    float GetXSec();
    float GetYSec();
    float GetClockRadius();
    float GetXVertex(float radius, double angle, float posX);
    float GetYVertex(float radius, double angle, float posY);
};
