template<typename Event>
inline void nail::EventQueue<Event>::push(Event&& event)
{
    m_queue.push_back(std::make_unique<Event>(std::move(event)));
}

template<typename Event>
inline void nail::EventQueue<Event>::process()
{
    for (auto& event : std::exchange(m_queue, {}))
        dispatch(event.get());
}

template<typename Event>
inline void nail::EventQueue<Event>::dispatch(Event* event)
{
    for (auto& subscriber : m_subscribers)
        std::invoke(*subscriber, *event);
}

template<typename Event>
inline void nail::EventQueue<Event>::subscribe(Subscriber& subscriber)
{
    m_subscribers.insert(&subscriber);
}

template<typename Event>
inline void nail::EventQueue<Event>::unsubscribe(Subscriber& subscriber)
{
    m_subscribers.erase(&subscriber);
}

