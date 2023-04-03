#ifndef NAIL_DEFINES_HPP
#define NAIL_DEFINES_HPP

#include <string>
#include <filesystem>
#include <fmt/format.h>

#include "platform.hpp"

#define NAIL_VERSION_MAJOR 0
#define NAIL_VERSION_MINOR 0
#define NAIL_VERSION_REV 1
#define NAIL_VERSION_STAGE "pre"

#define FLAG(shift) (1 << shift)
#define MACRO_TO_STRING(x) TO_STRING(x)
#define TO_STRING(str) #str

#ifdef NAIL_PLATFORM_WINDOWS
    #define NAIL_FILEPATHSEPARATOR_DOS
#else
    #define NAIL_FILEPATHSEPARATOR_UNIX
#endif

#ifdef NAIL_FILEPATHSEPARATOR_DOS
    #define __FILENAME__ \
        (std::string_view(__FILE__).find_last_of('\\') != std::string_view::npos ? \
        (char const*) __FILE__ + std::string_view(__FILE__).find_last_of('\\') + 1 : __FILE__)
#else
    #define __FILENAME__ \
        (std::string_view(__FILE__).find_last_of('/') != std::string_view::npos ? \
        (char const*) __FILE__ + std::string_view(__FILE__).find_last_of('/') + 1 : __FILE__)
#endif

#define CURRENT_SOURCE_LOCATION SourceLocation{__FILENAME__, static_cast<unsigned int>(__LINE__), __func__ }

typedef struct
{
    char const* file;
    unsigned int line;
    char const* function;
} SourceLocation;

template <>
struct fmt::formatter<std::filesystem::path>
{
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
    {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it != '}')
            throw format_error("invalid format");
        return it;
    }
 
    template<typename FormatContext>
    auto format(std::filesystem::path const& path, FormatContext& ctx) -> decltype(ctx.out())
    {
        return format_to(ctx.out(), "{}", path.string());
    }
};

#endif // NAIL_DEFINES_HPP

