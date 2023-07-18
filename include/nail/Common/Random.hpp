// Random.hpp
// 4 Apr 2021
// Gaétan "Gad" Jalin
// See end of file for complete license description
#ifndef NAIL_RANDOM_HPP
#define NAIL_RANDOM_HPP

#include <random>
#include <limits>

#include "nail/platform.hpp"
#include "nail/defines.hpp"
#include "nail/Common/NonCopyable.hpp"

#if defined(NAIL_PLATFORM_WINDOWS)
    #undef min
    #undef max
#endif

namespace nail
{
    template<typename Generator = std::default_random_engine>
    class RandomGenerator : public NonCopyable, NonMovable
    {
    public:
        using SeedType = std::invoke_result_t<Generator&>;

        void setSeed(SeedType seed);

        template<typename IntType>
        auto next(IntType min = std::numeric_limits<IntType>::lowest(),
                  IntType max = std::numeric_limits<IntType>::max())
            -> std::enable_if_t<std::is_integral_v<IntType>, IntType>;

        template<typename RealType>
        auto next(RealType min = std::numeric_limits<RealType>::lowest(),
                  RealType max = std::numeric_limits<RealType>::max())
            -> std::enable_if_t<std::is_floating_point_v<RealType>, RealType>;

        RandomGenerator();
        explicit RandomGenerator(SeedType seed);

    private:
        static std::random_device s_rd;
        Generator m_rng;
    };

    NAIL_API RandomGenerator<std::default_random_engine>& GetDefaultRandomGenerator();

    template<typename T>
    T GenerateRandom(T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max());
}

#include "Random.inl"

#endif // NAIL_RANDOM_HPP
/**
 * Copyright (C) 2020-2023 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/

