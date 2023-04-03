#include <iostream>

#include <nail/Signal/Signal.hpp>
#include <nail/Signal/Listener.hpp>

class Hammer
{
    using SwingSignal = nail::Signal<void (std::string const&)>;
public:
    void swing()
    {
        std::cout << "Hammer was swung !" << std::endl;
        m_swingSignal.emit("I'm coming for you !");
    }

    SwingSignal& swingSignal() noexcept
    {
        return m_swingSignal;
    }

private:
    SwingSignal m_swingSignal;
};

class Nail
{
    using SwingListener = nail::Listener<void (std::string const&)>;
public:
    void fear()
    {
        std::cout << "Nail has panicked !" << std::endl;
    }

    void observeNearbyHammer(Hammer* hammer)
    {
        hammer->swingSignal().listen(m_swingListener);
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

