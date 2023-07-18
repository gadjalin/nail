// DynamicLibrary.hpp
// 9 Oct 2021
// Gaétan "Gad" Jalin
// See end of file for complete license description
#ifndef NAIL_DYNAMICLIBRARY_HPP
#define NAIL_DYNAMICLIBRARY_HPP

#include <string>
#include <string_view>

#include "nail/defines.hpp"

namespace nail
{
    class NAIL_API DynamicLibrary
    {
    public:
        void load(std::string_view libname);

        bool isLoaded() const noexcept;
        explicit operator bool() const noexcept;

        void* getSymbol(std::string_view symbol) const;
        void* getHandle() const noexcept;
        std::string const& getName() const noexcept;

        explicit DynamicLibrary(std::string_view libname);
        DynamicLibrary(DynamicLibrary&& other);
        DynamicLibrary& operator=(DynamicLibrary&& other);
        DynamicLibrary() = default;

        DynamicLibrary(DynamicLibrary const&) = delete;
        DynamicLibrary& operator=(DynamicLibrary const&) = delete;

        ~DynamicLibrary();

    private:
        std::string m_name;
        void* m_handle;
    };
}

#include "DynamicLibrary.inl"

#endif // NAIL_DYNAMICLIBRARY_HPP
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

