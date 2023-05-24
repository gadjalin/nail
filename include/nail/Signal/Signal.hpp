// Signal.hpp
// Gaétan "Gad" Jalin
// 6 Feb 2021
// See end of file for complete licence description
#ifndef NAIL_SIGNAL_HPP
#define NAIL_SIGNAL_HPP

#include <unordered_set>

#include "nail/Signal/Observer.hpp"

namespace nail
{
    template<typename Fn>
    class Signal;

    template<typename Return, typename... Args>
    class Signal<Return (Args...)>
    {
        using Listener = nail::Observer<Return (Args...)>;

    public:
        void listen(Listener& listener);
        void quit(Listener& listener);

        void emit(Args&&... args);

        virtual ~Signal() = default;

    private:
        std::unordered_set<Listener*> m_listeners;
    };
}

#include "Signal.inl"

#endif // NAIL_SIGNAL_HPP
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

