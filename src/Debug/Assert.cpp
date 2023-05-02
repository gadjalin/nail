#include "nail/Debug/Assert.hpp"

[[noreturn]] void nail::AssertHandler::handle(SourceLocation const& location, char const* expression, char const* message) noexcept
{
    //TODO fix this
//   Console::Trace("{0}::{1} ({2}) : Assertion failed \"{3}\" : {4}",
//                  location.file, location.function, location.line, expression, (message ? message : "No more information"));
   std::abort();
}

