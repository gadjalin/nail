/**
 * C++ 17
 * Header-only tee debugging tool.
 *
 * Based on the "tee" unix command, this debugging tool is used
 * to display object values at run-time in a simple and readable way, based on expressiveness.
 *
 *           []================[]
 *          -->    ------>    --->
 *           []=====| | |======[]
 *                  | v |
 *                  |   |   ___   ___
 *                  |   |  |     |
 *                  |   |  |==   |==
 *                  |   |  |___  |___
 *                 || | ||
 *                    v
 *
 **/
// Tee.hpp
// 31 Aug 2020
// Gaétan "Gad" Jalin
// See end of file for complete licence description
#ifndef NAIL_TEEDEBUG_HPP
#define NAIL_TEEDEBUG_HPP

#include <iostream>
#include <fstream>
#include <type_traits>
#include <filesystem>

#include "nail/defines.hpp"

template<typename Fn, typename T = void>
using if_is_invocable = std::enable_if_t<std::is_invocable_v<Fn>, T>;

template<typename Stream, typename T = void>
using if_is_stream = std::enable_if_t<std::is_base_of_v<std::ios_base, Stream>, T>;

// Primary specialisable template
template<typename T, typename Enable = void>
class Tee {};

// Generic Customisable tee
template<typename PrintFn>
class Tee<PrintFn, if_is_invocable<PrintFn> >
{
public:
   template<typename V>
   decltype(auto) operator()(V&& value);

   explicit Tee(PrintFn func) noexcept;

private:
   PrintFn m_print;
};

// File output specialisation
template<>
class Tee<std::filesystem::path>
{
public:
   template<typename V>
   decltype(auto) operator()(V&& value);

   explicit Tee(std::filesystem::path const& filePath, std::ios_base::openmode mode = std::ios_base::out | std::ios_base::app) noexcept;

private:
   std::filesystem::path m_file;
   std::ios_base::openmode m_mode;
};

// Stream output specialisation
template<typename Stream>
class Tee<Stream, if_is_stream<Stream> >
{
public:
   template<typename V>
   decltype(auto) operator()(V&& value);

   explicit Tee(Stream& output) noexcept;

private:
   std::ostream& m_output;
};

// Deduction guides
Tee(char const*) -> Tee<std::filesystem::path>;
Tee(std::string const&) -> Tee<std::filesystem::path>;

template<typename PrintFunc, if_is_invocable<PrintFunc, int> = 0>
Tee<PrintFunc> make_tee(PrintFunc func) noexcept;

template<typename Stream, if_is_stream<Stream, int> = 0>
Tee<Stream> make_tee(Stream& stream) noexcept;

template<typename V, typename TeeType>
decltype(auto) operator|(V&& value, Tee<TeeType> tee);

// Default tee
inline Tee<std::ostream> ctee = make_tee(std::cout);

//
// Low Level Functions
//

// Simplest form
template<typename V, typename CharType>
decltype(auto) stee(V&& value, std::basic_ostream<CharType>& output);

// TODO Open a file at each call is performance heavy
template<typename V>
decltype(auto) ftee(V&& value, std::filesystem::path const& outputFile, std::ios_base::openmode mode = std::ios_base::out);

#include "Tee.inl"

#endif // NAIL_TEEDEBUG_HPP
/*
 * Copyright (C) 2020-2023 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

