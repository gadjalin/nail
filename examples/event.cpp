#include <iostream>
#include <map>
#include <nail/Event/EventQueue.hpp>
#include <nail/Event/EventSubscriber.hpp>

class TestEvent
{
public:
    using Type = int;

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

    nail::EventSubscriber<TestEvent> sub1 = [](TestEvent& event) -> void
        {
            std::cout << event.msg << std::endl;
        };

    test_queue.subscribe(sub1);

    test_queue.push({0, "foo"});
    test_queue.push({0, "bar"});
    test_queue.push({1, "baz"});
    test_queue.push({134, "hola"});

    std::cout << "Process..." << std::endl;
    test_queue.process();

    return 0;
}
