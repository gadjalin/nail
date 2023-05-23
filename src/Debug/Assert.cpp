#include "nail/Debug/Assert.hpp"

#include <iostream>
#include "nail/crash.hpp"

namespace nail
{
    [[noreturn]]
    void EnabledAssertHandler::Handle(
        SourceLocation const& location,
        char const* expression,
        char const* message) noexcept
    {
        try
        {
            std::cerr
                << "Assertion has failed: " << message << "\n"
                << "\tIn " << location.file << "::" << location.function << ", line " << location.line << "\n"
                << "\t(" << expression << ")"
                << std::endl;
        } catch (...) {}

        nail::crash();
    }
}

