#include "Component.h"

Component::Component()
{
    this->isActive = true;
}

Component::Component(ComponentEnum componentType)
{
    this->componentType = componentType;
    this->isActive = true;
}

void Component::Start()
{
}

void Component::Update()
{
}

void Component::Destroy()
{
    this->isActive = false;
}
