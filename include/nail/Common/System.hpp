// System.hpp
// 3 Apr 2021
// Gaétan "Gad" Jalin
// See end of file for complete licence description
#ifndef NAIL_SYSTEM_HPP
#define NAIL_SYSTEM_HPP

#include <string>

#include "nail/defines.hpp"

namespace nail
{
    enum class Arch
    {
        x86, x64, ARM, ARM64, IA64, Unknown
    };

    // TODO: C++20 std::endian
    enum class Endian
    {
        Little, Big
    };

    struct System
    {
        std::string hostname;
        std::string username;

        struct OS
        {
            std::string name;
            std::string versionString;

            struct Version
            {
                unsigned major;
                unsigned minor;
                unsigned patch;
                unsigned rev;
            } version;
        } os;
    };

    struct Processor
    {
        std::string model;
        Arch arch;
        Endian endian;

        struct Cores
        {
            unsigned physical;
            unsigned logical;
        } cores;
    };

    struct Memory
    {
        uint64_t total;
        uint64_t available;
        uint64_t used;
    };

    NAIL_API System getSystemInfo();
    NAIL_API Processor getProcessorInfo();
    NAIL_API Memory getMemoryInfo();
}

#endif // NAIL_SYSTEM_HPP
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

