#include "nail/Common/DynamicLibrary.hpp"

#include <stdexcept>

#include "nail/platform.hpp"

#if defined(NAIL_PLATFORM_WINDOWS)
    #define NOMINMAX
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#elif defined(NAIL_PLATFORM_LINUX) || defined(NAIL_PLATFORM_MACOS)
    #include <dlfcn.h>
#endif

namespace nail
{
    namespace details
    {
        std::string getFilename(std::string_view const libname)
        {
        #if defined(NAIL_PLATFORM_WINDOWS)
            return libname;
        #elif defined(NAIL_PLATFORM_LINUX)
            std::string filename;
            filename.reserve(libname.size() + 7);
            filename += "lib";
            filename += libname;
            filename += ".so";
            return filename;
        #elif defined(NAIL_PLATFORM_MACOS)
            std::string filename;
            filename.reserve(libname.size() + 10);
            filename += "lib";
            filename += libname;
            filename += ".dylib";
            return filename;
        #else
            NAIL_MISSING_IMPLEMENTATION();
        #endif
        }

        void* loadLib(std::string_view const libname)
        {
            std::string filename = getFilename(libname);

        #if defined(NAIL_PLATFORM_WINDOWS)
            return LoadLibraryA(filename.c_str());
        #elif defined(NAIL_PLATFORM_LINUX) || defined(NAIL_PLATFORM_MACOS)
            return dlopen(filename.c_str(), RTLD_NOW);
        #else
            NAIL_MISSING_IMPLEMENTATION();
        #endif
        }

        void* getSymbol(void* const handle, std::string_view const symbolName)
        {
        #if defined(NAIL_PLATFORM_WINDOWS)
            return GetProcAddress((HMODULE) handle, (LPCSTR) symbolName.data());
        #elif defined(NAIL_PLATFORM_LINUX) || defined(NAIL_PLATFORM_MACOS)
            return dlsym(handle, symbolName.data());
        #else
            NAIL_MISSING_IMPLEMENTATION();
        #endif
        }

        void freeLib(void* const handle)
        {
        #if defined(NAIL_PLATFORM_WINDOWS)
            FreeLibrary((HMODULE) handle);
        #elif defined(NAIL_PLATFORM_LINUX) || defined(NAIL_PLATFORM_MACOS)
            dlclose(handle);
        #else
            NAIL_MISSING_IMPLEMENTATION();
        #endif
        }

        std::string getErrorDescription()
        {
        #if defined(NAIL_PLATFORM_WINDOWS)
            DWORD errorCode = GetLastError();
            LPSTR errorMessage = nullptr;
            size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                         NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR) &errorMessage, 0, NULL);
            std::string errorDesc = errorMessage;
            LocalFree(errorMessage);

            return errorDesc;
        #elif defined(NAIL_PLATFORM_LINUX) || defined(NAIL_PLATFORM_MACOS)
            return dlerror();
        #else
            NAIL_MISSING_IMPLEMENTATION();
        #endif
        }
    }

    DynamicLibrary::DynamicLibrary(std::string_view const libname)
        : m_handle(nullptr)
    {
        this->load(libname);
    }

    DynamicLibrary::DynamicLibrary(DynamicLibrary&& other)
    {
        *this = std::move(other);
    }

    DynamicLibrary& DynamicLibrary::operator=(DynamicLibrary&& other)
    {
        m_handle = std::exchange(other.m_handle, nullptr);
        m_name = std::move(other.m_name);
        return *this;
    }

    void DynamicLibrary::load(std::string_view const libname)
    {
        m_handle = details::loadLib(libname);

        if (!m_handle)
            throw std::runtime_error(details::getErrorDescription());
        else
            m_name = libname;
    }

    void* DynamicLibrary::getSymbol(std::string_view const symbolName) const
    {
        if (!isLoaded()) return nullptr;

        void* symbol = details::getSymbol(m_handle, symbolName);
        if (!symbol)
            throw std::runtime_error(details::getErrorDescription());

        return symbol;
    }

    DynamicLibrary::~DynamicLibrary()
    {
        if (m_handle)
            details::freeLib(m_handle);
    }
}
