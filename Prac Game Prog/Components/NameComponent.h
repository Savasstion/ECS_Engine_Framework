#pragma once
#include <string>

#include "../BaseClasses/Component.h"


class NameComponent : public Component
{
    std::string name;
public:
    NameComponent();
    NameComponent(std::string name);
    std::string GetName(){return name;}
    void SetName(std::string newName){name = newName;}
};
