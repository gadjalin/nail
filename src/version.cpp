#include "nail/version.hpp"

//using namespace std; lol jk

#define NAIL_MAKE_VERSION_STRING(major, minor, rev, stage) NAIL_CONCAT_VERSION_STRING(major, minor, rev, stage)
#define NAIL_CONCAT_VERSION_STRING(major, minor, rev, stage) #major "-" #minor "." #rev stage

namespace nail
{
    Version getLibraryVersion() noexcept
    {
        return {
            .major = NAIL_VERSION_MAJOR,
            .minor = NAIL_VERSION_MINOR,
            .rev = NAIL_VERSION_REV,
            .stage = NAIL_VERSION_STAGE
        };
    }

    char const* getLibraryVersionString() noexcept
    {
        return NAIL_MAKE_VERSION_STRING(NAIL_VERSION_MAJOR, NAIL_VERSION_MINOR, NAIL_VERSION_REV, NAIL_VERSION_STAGE);
    }
}

