#include <iostream>

#include <nail/Signal/Signal.hpp>
#include <nail/Signal/Listener.hpp>
#include <nail/Debug/Tee.hpp>

class Hammer
{
public:
    using SwingSignal = nail::Signal<std::string const&>;

public:
    void swing()
    {
        "Hammer was swung !" | stdtee;
        swingSignal.emit("Hammer: I'm coming for you !");
    }

    SwingSignal swingSignal;
};

class Nail
{
public:
    using SwingListener = nail::Listener<std::string const&>;

public:
    void fear()
    {
        "Nail has panicked !" | stdtee;
    }

    void observeNearbyHammer(Hammer* hammer)
    {
        hammer->swingSignal.listen(m_swingListener);
    }

    Nail()
        : m_swingListener(
            [this](std::string const& threat)
            {
                this->fear();
            }) {}

private:
    SwingListener m_swingListener;
};

int main()
{
    Hammer fearsomeHammer;
    Nail fearfulNail;

    fearfulNail.observeNearbyHammer(&fearsomeHammer);
    fearsomeHammer.swing();

    return 0;
}

