// EventSubscriber.hpp
// Gaétan "Gad" Jalin
// 2 May 2023
// See end of file for complete licence description
#ifndef NAIL_EVENTSUBSCRIBER_HPP
#define NAIL_EVENTSUBSCRIBER_HPP

#include <functional>

namespace nail
{
    template<typename Event>
    class EventSubscriber
    {
        // TODO: Find lighter alternative to std::function
        using Callback = std::function<void (Event&)>;

    public:
        void operator()(Event& event) const;

        template<typename Fn>
        void setCallback(Fn callback) noexcept;

        template<typename Fn>
        EventSubscriber(Fn callback);
        EventSubscriber() = default;

    private:
        Callback m_callback;
    };
}

#include "EventSubscriber.inl"

#endif // NAIL_EVENTSUBSCRIBER_HPP
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

