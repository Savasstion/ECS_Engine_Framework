#pragma once

class Script
{
public:
    bool isInitialized = false;
    
    void Start(){isInitialized = true;} //pls override in child class whilst also calling parent Start()
    virtual void Update();
};
