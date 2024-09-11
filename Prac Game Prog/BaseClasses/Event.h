#pragma once
#include <functional>
#include <vector>

// Define an event type using a function signature
using EventListener = std::function<void()>;

class Event
{
public:
    // Register an event listener
    void AddListener(EventListener listener) {
        listeners.push_back(listener);
    }

    // Trigger all listeners
    void TriggerEvent() {
        for (const auto& listener : listeners) {
            listener();
        }
    }

private:
    std::vector<EventListener> listeners;
};
