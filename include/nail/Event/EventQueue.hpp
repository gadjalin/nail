// EventQueue.hpp
// Gaétan "Gad" Jalin
// 19 Apr 2023
// See end of file for complete licence description
#ifndef NAIL_EVENT_HPP
#define NAIL_EVENT_HPP

#include <unordered_set>
#include <memory>
#include <utility>
#include <vector>

#include "nail/Common/Observer.hpp"

namespace nail
{
    template<typename Event>
    class EventQueue
    {
        using Subscriber = Observer<void (Event&)>;

    public:
        void push(Event&& event);
        void processQueue();

        void subscribe(Subscriber& subscriber);
        void unsubscribe(Subscriber& subscriber);

        EventQueue() = default;

    private:
        void dispatch(Event* event);

        std::unordered_set<Subscriber*> m_subscribers;
        std::vector<std::unique_ptr<Event> > m_queue;
    };
}

#include "EventQueue.inl"

#endif // NAIL_EVENT_HPP
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

