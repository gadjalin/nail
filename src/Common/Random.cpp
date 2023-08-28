#include "nail/Common/Random.hpp"

namespace nail
{
    RandomGenerator<std::default_random_engine>& GetDefaultRandomGenerator()
    {
        static RandomGenerator rng;
        return rng;
    }
}

