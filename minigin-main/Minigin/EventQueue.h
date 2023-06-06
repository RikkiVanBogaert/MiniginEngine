//#pragma once
//#include <queue>
//#include <functional>
//#include <type_traits>
//#include <memory>
//#include "Event.h"
//
//template<typename EventType, typename TimeType>
//class EventQueue {
//public:
//    static_assert(std::is_default_constructible_v<EventType>, "EventType must be default constructible");
//
//    static EventQueue& GetInstance() {
//        static EventQueue instance;
//        return instance;
//    }
//
//    template<typename DerivedEventType>
//    void schedule(const DerivedEventType& event, TimeType time) {
//        static_assert(std::is_base_of_v<Event, DerivedEventType>, "DerivedEventType must derive from Event");
//        std::shared_ptr<Event> sharedEvent = std::make_shared<DerivedEventType>(event);
//        queue.push(std::make_pair(time, sharedEvent));
//    }
//
//    void process() {
//        while (!queue.empty()) {
//            auto [time, sharedEvent] = queue.top();
//            if (time > current_time) {
//                current_time = time;
//            }
//            queue.pop();
//            sharedEvent->execute();
//        }
//    }
//
//    bool has_events() const {
//        return !queue.empty();
//    }
//
//    TimeType getCurrent_time() const
//	{
//        return current_time;
//    }
//
//    TimeType next_time() const
//	{
//        if (queue.empty()) {
//            return current_time;
//        }
//        return queue.top().first;
//    }
//
//    void process_next()
//	{
//        if (!queue.empty()) {
//            auto [time, sharedEvent] = queue.top();
//            current_time = time;
//            queue.pop();
//            sharedEvent->execute();
//        }
//    }
//
//private:
//    EventQueue() = default;
//    EventQueue(const EventQueue&) = delete;
//    EventQueue(EventQueue&&) = delete;
//    EventQueue& operator=(const EventQueue&) = delete;
//    EventQueue& operator=(EventQueue&&) = delete;
//
//    TimeType current_time{};
//
//    struct EventComparator
//	{
//        bool operator()(const std::pair<TimeType, std::shared_ptr<Event>>& lhs, const std::pair<TimeType, std::shared_ptr<Event>>& rhs) const {
//            return lhs.first > rhs.first;
//        }
//    };
//
//    std::priority_queue<std::pair<TimeType, std::shared_ptr<Event>>, std::vector<std::pair<TimeType, std::shared_ptr<Event>>>, EventComparator> queue;
//};
//
//
//
//
