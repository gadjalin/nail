#include <iostream>
#include <map>

#include <nail/Event/EventQueue.hpp>
#include <nail/Event/EventSubscriber.hpp>
#include <nail/Event/EventDispatcher.hpp>
#include <nail/Debug/Tee.hpp>

class TestEvent
{
public:
    using Type = int;

public:
    Type getType() const noexcept
    {
        return type;
    }

    Type type;
    std::string msg;
};

int main()
{
    nail::EventQueue<TestEvent> test_queue;

    // Subscribe to event type 0
    nail::EventSubscriber<TestEvent> sub0(0, [](TestEvent& event) -> void
        {
            ("(Listener) Type 0: " + event.msg) | stdtee;
        });

    // Subscribe to event type 1
    nail::EventSubscriber<TestEvent> sub1(1, [](TestEvent& event) -> void
        {
            ("(Listener) Type 1: " + event.msg) | stdtee;
        });

    nail::EventDispatcher<TestEvent> dispatcher([](TestEvent& event) -> void
        {
            ("(Dispatcher) Type " + std::to_string(event.getType()) + " " + event.msg) | stdtee;
        });

    test_queue.subscribe(sub0);
    test_queue.subscribe(sub1);
    test_queue.subscribe(dispatcher);

    test_queue.push({0, "foo"});
    test_queue.push({0, "bar"});
    test_queue.push({1, "baz"});
    test_queue.push({134, "hola"});

    "Processing Queue..." | stdtee;
    test_queue.processQueue();

    return 0;
}
