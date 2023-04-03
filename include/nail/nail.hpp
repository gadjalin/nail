#ifndef NAIL_HPP
#define NAIL_HPP

#include <nail/defines.hpp>

// Backtrace
#include <nail/Backtrace/CallStack.hpp>
#include <nail/Backtrace/StackFrame.hpp>

// Logger
#include <nail/Log/Logger.hpp>
#include <nail/Log/Writer.hpp>
#include <nail/Log/ConsoleWriter.hpp>
#include <nail/Log/FileWriter.hpp>
#include <nail/Log/StreamWriter.hpp>

// Debug
#include <nail/Exception/Exception.hpp>
#include <nail/Debug/Assert.hpp>
#include <nail/Debug/Tee.hpp>
#include <nail/Debug/TodoBefore.hpp>

// Math
#include <nail/Math/Angle.hpp>
#include <nail/Math/RangedNumeric.hpp>
#include <nail/Math/Math.hpp>

// Event System
#include <nail/Event/Event.hpp>
#include <nail/Event/EventDispatcher.hpp>
#include <nail/Event/EventBus.hpp>
#include <nail/Event/EventSubscriber.hpp>

// Signal System
#include <nail/Signal/Signal.hpp>
#include <nail/Signal/Listener.hpp>

// Resource Management
#include <nail/Resource/ResourceManager.hpp>

// Memory Management
#include <nail/Memory/Allocator.hpp>
#include <nail/Memory/New.hpp>
#include <nail/Memory/StandardAllocator.hpp>

// Time management
#include <nail/Time/Chrono.hpp>
#include <nail/Time/Date.hpp>
#include <nail/Time/Time.hpp>

// Streams
#include "nail/Stream/OutputStream.hpp"
#include "nail/Stream/FileOutputStream.hpp"

// Common
#include <nail/Common/Arguments.hpp>
#include <nail/Common/Console.hpp>
#include <nail/Common/Functor.hpp>
#include <nail/Common/Observer.hpp>
#include <nail/Common/Random.hpp>
#include <nail/Common/System.hpp>
#include <nail/Common/NamedType.hpp>
#include <nail/Common/CRTP.hpp>

// Utils
#include <nail/Util/StringUtils.hpp>
#include <nail/Util/FileUtils.hpp>
#include <nail/Module/SharedObject.hpp>

#endif // NAIL_HPP
/**
 * nail.hpp
 * 27 Nov 2020
 * Gaétan "Gad" Jalin
 *
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

