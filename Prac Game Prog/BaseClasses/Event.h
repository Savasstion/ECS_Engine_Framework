#pragma once
#include <functional>
#include <vector>

// Define an event type using a function signature
using EventListener = std::function<void()>;

class Event
{
public:
    static long id;

    
    // Register an event listener
    void AddListener(long listenerID, EventListener listener) {
        listeners.emplace_back(listenerID, listener);
    }

    // Trigger all listeners
    void TriggerEvent() {
        for (const auto& pair : listeners)
        {
            pair.second(); // 'pair' is a std::pair<int, CollisionEvent>
        }
    }

    void RemoveListener(long id) {
        listeners.erase(
            std::remove_if(listeners.begin(), listeners.end(),
                           [id](const auto& pair) { return pair.first == id; }),
            listeners.end());
    }

    static long GetNewEventListenerID()
    {
        id++;
        return id;
    }

private:
    std::vector<std::pair<long, EventListener>> listeners;
};
