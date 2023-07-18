// EventSubscriber.hpp
// Gaétan "Gad" Jalin
// 2 May 2023
// See end of file for complete license description
#ifndef NAIL_EVENTSUBSCRIBER_HPP
#define NAIL_EVENTSUBSCRIBER_HPP

#include <functional>

#include "nail/Common/Observer.hpp"

namespace nail
{
    // When you want to listen to a specific type of event
    template<typename Event, typename Type = typename Event::Type>
    class EventSubscriber : public Observer<void (Event&)>
    {
    public:
        // TODO: Find lighter alternative to std::function
        using Callback = std::function<void (Event&)>;

    public:
        virtual void update(Event& event) override;

        template<typename Fn>
        void setCallback(Fn callback);
        void setType(Type type);

        template<typename Fn = std::nullptr_t>
        explicit EventSubscriber(Type type, Fn callback = nullptr);
        EventSubscriber() noexcept = default;

    private:
        Type m_eventType;
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

