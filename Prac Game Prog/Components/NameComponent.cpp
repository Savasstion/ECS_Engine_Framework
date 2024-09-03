#include "NameComponent.h"

NameComponent::NameComponent()
{
    Component(NAME);
}

NameComponent::NameComponent(std::string name)
{
    Component(NAME);
    this->name = name;
}
