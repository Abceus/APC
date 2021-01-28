#pragma once
#include <functional>
#include <map>
#include <set>
#include <concepts>

namespace apc
{
    template <typename CallFunc, typename... Args>
    concept Caller = std::convertible_to<CallFunc, std::function<void(Args...)>>;

    template<typename... Args>
    class Signal {
        std::map<int, std::function<void(Args...)>> slots;
    public:
        template<Caller<Args...> CallType>
        int connect(CallType func);

        void disconnect(int id);

        void operator()(Args... args);

        using slot_id_type = typename decltype(slots)::key_type;
    private:
        slot_id_type currentId = 0;
        int callStarted = 0;
        std::set<slot_id_type> disconnectLater;
    };

    template<typename... Args>
    template<Caller<Args...> CallType>
    int Signal<Args...>::connect(CallType func) {
        slots.emplace(++currentId, static_cast<std::function<void(Args...)>>(func));
        return currentId;
    }

    template<typename... Args>
    void Signal<Args...>::disconnect(int id) {
        disconnectLater.emplace(id);
    }

    template<typename... Args>
    void Signal<Args...>::operator()(Args... args) {
        callStarted++;
        for(const auto& slot: slots) {
            const auto& foundDisconnected = std::find(std::begin(disconnectLater), std::end(disconnectLater), slot.first);
            if(foundDisconnected == std::end(disconnectLater)) {
                slot.second(args...);
            }
        }
        callStarted--;

        if(callStarted == 0) {
            for (const auto &disconnect: disconnectLater) {
                const auto &found = slots.find(disconnect);
                if (found != std::end(slots)) {
                    slots.erase(found);
                }
            }
            disconnectLater.clear();
        }
    }
}