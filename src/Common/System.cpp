#include "nail/Common/System.hpp"

#include <fstream>
#include <bitset>
#include <csignal>
#include <cstdlib>
#include <cstring>

#include "nail/platform.hpp"

#if defined(NAIL_PLATFORM_WINDOWS)
    #include <lmcons.h>
#elif defined(NAIL_PLATFORM_LINUX)
    #include <unistd.h>
    #include <sys/utsname.h>
#elif defined(NAIL_PLATFORM_MACOS)
    #include <unistd.h>
    #include <sys/utsname.h>
    #include <sys/sysctl.h>
    #include <sys/types.h>
    #include <mach/vm_statistics.h>
    #include <mach/mach.h>
#endif

// Inspired by https://github.com/ThePhD/infoware

namespace nail
{
    namespace
    {
        std::string getHostname()
        {
            std::string name;
 
        #if defined(NAIL_PLATFORM_WINDOWS)
            name.resize(MAX_COMPUTERNAME_LENGTH + 1);
            DWORD x = MAX_COMPUTERNAME_LENGTH;
            GetComputerNameA(&name[0], &x);
        #elif defined(NAIL_PLATFORM_LINUX) || defined(NAIL_PLATFORM_MACOS)
            const size_t hostnameSize = static_cast<size_t>(sysconf(_SC_HOST_NAME_MAX)) + 1;
            name.resize(hostnameSize);
            if (gethostname(&name[0], hostnameSize))
                return "";
        #else
            NAIL_MISSING_IMPLEMENTATION();
        #endif

            return name;
        }

        std::string getUsername()
        {
            std::string name;

        #if defined(NAIL_PLATFORM_WINDOWS)
            name.resize(UNLEN + 1); // TODO Not sure about this +1
            DWORD x = UNLEN;
            GetUserNameA(&name[0], &x);
        #elif defined(NAIL_PLATFORM_LINUX) || defined(NAIL_PLATFORM_MACOS)
            size_t loginNameSize = static_cast<size_t>(sysconf(_SC_LOGIN_NAME_MAX)) + 1;
            name.resize(loginNameSize);

            if (getlogin_r(&name[0], loginNameSize))
                return "";
        #else
            NAIL_MISSING_IMPLEMENTATION();
        #endif

            return name;
        }

        std::string getKernelName()
        {

        #if defined(NAIL_PLATFORM_WINDOWS)
            return "Windows";
        #elif defined(NAIL_PLATFORM_LINUX) || defined(NAIL_PLATFORM_MACOS)
            utsname sysInfo;
            uname(&sysInfo);

            return sysInfo.sysname;
        #else
            NAIL_MISSING_IMPLEMENTATION();
        #endif
        }

        System::OS::Version getKernelVersion()
        {
        #if defined(NAIL_PLATFORM_WINDOWS)
            // return "\"Windows is a mess to get the version (and you don't even care), gfy\"";

            std::string path;
            path.resize(GetSystemDirectoryA(nullptr, 0) - 1);
            GetSystemDirectoryA(&path[0], static_cast<uint32_t>(path.size() + 1));
            path += "\\kernel32.dll";

            uint32_t const verBufSize = GetFileVersionInfoSizeA(path.c_str(), nullptr);
            auto verBuf = std::make_unique<uint8_t[]>(verBufSize);
            GetFileVersionInfoA(path.c_str(), 0, verBufSize, verBuf.get());

            VS_FIXEDFILEINFO* version;
            uint32_t verSize;
            VerQueryValueA(verBuf.get(), "", reinterpret_cast<void**>(&version), &verSize);

            return { HIWORD(version->dwProductVersionMS), LOWORD(version->dwProductVersionMS), HIWORD(version->dwProductVersionLS), LOWORD(version->dwProductVersionLS) };
        #elif defined(NAIL_PLATFORM_LINUX) || defined(NAIL_PLATFORM_MACOS)
            utsname sysInfo;
            uname(&sysInfo);

            System::OS::Version version;
            char* cursor = sysInfo.release;
            version.major = static_cast<unsigned>(std::strtoul(cursor,     &cursor, 10));
            version.minor = static_cast<unsigned>(std::strtoul(cursor + 1, &cursor, 10));
            version.patch = static_cast<unsigned>(std::strtoul(cursor + 1, &cursor, 10));
            version.rev   = static_cast<unsigned>(std::strtoul(cursor + 1, nullptr, 10));

            return version;
        #else
            NAIL_MISSING_IMPLEMENTATION();
        #endif
        }

        std::string getSystemVersionName([[maybe_unused]] System::OS::Version version)
        {
        #if defined(NAIL_PLATFORM_WINDOWS)
            std::stringstream ss;
            ss << "v" << version.major << "." << version.minor << "." << version.patch << " rev" << version.rev;
            return ss.str();
        #elif defined(NAIL_PLATFORM_LINUX) || defined(NAIL_PLATFORM_MACOS)
            utsname sysInfo;
            uname(&sysInfo);

            return sysInfo.release;
        #else
            NAIL_MISSING_IMPLEMENTATION();
        #endif
        }

        Arch getArch()
        {
        #if defined(NAIL_PLATFORM_WINDOWS)
            SYSTEM_INFO sysInfo;
            GetSystemInfo(&sysInfo);

            switch (sysInfo.wProcessorArchitecture)
            {
               case PROCESSOR_ARCHITECTURE_INTEL:
                  return Arch::x86;
               case PROCESSOR_ARCHITECTURE_AMD64:
                  return Arch::x64;
               case PROCESSOR_ARCHITECTURE_ARM:
                  return Arch::ARM;
               case PROCESSOR_ARCHITECTURE_ARM64:
                  return Arch::ARM64;
               case PROCESSOR_ARCHITECTURE_IA64:
                  return Arch::IA64;
               default:
                  return Arch::Unknown;
            }
        #elif defined(NAIL_PLATFORM_LINUX) || defined(NAIL_PLATFORM_MACOS)
            utsname sysInfo;
            uname(&sysInfo);

            if (!strcmp(sysInfo.machine, "i686") ||
                !strcmp(sysInfo.machine, "i386"))
                return Arch::x86;
            else if (!strcmp(sysInfo.machine, "x86_64"))
                return Arch::x64;
            else if (!strcmp(sysInfo.machine, "arm") ||
                     !strcmp(sysInfo.machine, "armv7l"))
                return Arch::ARM;
            else if (!strcmp(sysInfo.machine, "aarch64") ||
                     !strcmp(sysInfo.machine, "armv8l") ||
                     !strcmp(sysInfo.machine, "arm64"))
                return Arch::ARM64;
            else if (!strcmp(sysInfo.machine, "ia64"))
                return Arch::IA64;
            else
                return Arch::Unknown;
        #else
            NAIL_MISSING_IMPLEMENTATION();
        #endif
        }

        Endian getEndianess()
        {
            union
            {
                uint32_t a;
                char b[4];
            } c = { 0x01020304 }; // I have absolutely no idea what names I could give to these things

            return c.b[0] == 1 ? Endian::Big : Endian::Little;
        }

        Processor::Cores getCPUCores()
        {
        #if defined(NAIL_PLATFORM_WINDOWS)
            std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION> infoList;
            DWORD size = 0;
            GetLogicalProcessorInformation(nullptr, &size);
            infoList.resize(size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION));
            GetLogicalProcessorInformation(infoList.data(), &size);

            uint32_t physic = 0;
            uint32_t logic = 0;

            for (auto&& info : infoList)
            {
                switch (info.Relationship)
                {
                    case RelationProcessorCore:
                        ++physic;
                        logic += static_cast<uint32_t>(std::bitset<sizeof(uint64_t) * 8>(info.ProcessorMask).count());
                        break;
                    default:
                        break;
                }
            }

            return { physic, logic };

         #elif defined(NAIL_PLATFORM_LINUX)
            std::ifstream cpuinfo("/proc/cpuinfo");
            if (!cpuinfo) return {};

            unsigned physic = 0;
            unsigned logic = static_cast<unsigned>(sysconf(_SC_NPROCESSORS_ONLN));

            for (std::string line; std::getline(cpuinfo, line);)
            {
                if (line.find("cpu cores") != std::string::npos) // TODO Test on other unix platforms
                {
                    physic = static_cast<unsigned>(std::strtoul(line.c_str() + line.find_first_of("0123456789"), nullptr, 10));
                    break;
                }
            }

            return { physic, logic };
        #elif defined(NAIL_PLATFORM_MACOS)
            int physic = 0, logic = 0;
            size_t length = sizeof(int);

            sysctlbyname("machdep.cpu.core_count", &physic, &length, nullptr, 0);
            sysctlbyname("machdep.cpu.thread_count", &logic, &length, nullptr, 0);

            return { static_cast<uint32_t>(physic), static_cast<uint32_t>(logic) };
        #else
            NAIL_MISSING_IMPLEMENTATION();
        #endif
        }

        std::string getCPUModel()
        {
        #if defined(NAIL_PLATFORM_WINDOWS)
            HKEY hkey;
            if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, R"(HARDWARE\DESCRIPTION\System\CentralProcessor\0)", 0, KEY_READ, &hkey))
                return {};

            char model[64];
            DWORD size = sizeof(model);
            if (RegQueryValueExA(hkey, "ProcessorNameString", nullptr, nullptr, static_cast<LPBYTE>(static_cast<void*>(&model[0])), &size))
                return {};

            return model;
        #elif defined(NAIL_PLATFORM_LINUX)
            std::ifstream cpuinfo("/proc/cpuinfo");
            if (!cpuinfo) return {};

            std::string model;
            for (std::string line; std::getline(cpuinfo, line);)
            {
                if (line.find("model name") != std::string::npos)
                {
                    model = line.substr(line.find(":") + 1); // TODO Test on other unix platforms
                    break;
                }
            }

            return model;
        #elif defined(NAIL_PLATFORM_MACOS)
            char name[64];
            size_t namelen = sizeof(name);

            sysctlbyname("machdep.cpu.brand_string", &name, &namelen, nullptr, 0);

            return name;
        #else
            NAIL_MISSING_IMPLEMENTATION();
        #endif
        }

        std::string archToString(Arch arch)
        {
            switch (arch)
            {
                case Arch::x64:
                    return "x64";
                case Arch::x86:
                    return "x86";
                case Arch::ARM:
                    return "ARM";
                case Arch::ARM64:
                    return "ARM64";
                case Arch::IA64:
                    return "IA64";
                case Arch::Unknown:
                default:
                    return "UNKNOWN";
            }
        }
    }

    System getSystemInfo()
    {
        System sysInfo{};

        sysInfo.hostname= getHostname();
        sysInfo.username = getUsername();
        sysInfo.os.name = getKernelName();
        sysInfo.os.version = getKernelVersion();
        sysInfo.os.versionString = getSystemVersionName(sysInfo.os.version);

        return sysInfo;
    }

   Processor getProcessorInfo()
   {
      Processor cpuInfo{};

      cpuInfo.arch = getArch();
      cpuInfo.endian = getEndianess();
      cpuInfo.cores = getCPUCores();
      cpuInfo.model = getCPUModel();

      return cpuInfo;
   }

    Memory getMemoryInfo()
    {
    #if defined(NAIL_PLATFORM_WINDOWS)
        Memory memoryInfo{};
 
        MEMORYSTATUSEX memStat;
        memStat.dwLength = sizeof(memStat);
        GlobalMemoryStatusEx(&memStat);

        memoryInfo.total = memStat.ullTotalPhys;
        memoryInfo.available = memStat.ullAvailPhys;
        memoryInfo.used = memStat.ullTotalPhys - memStat.ullAvailPhys;

        return memoryInfo;
    #elif defined(NAIL_PLATFORM_LINUX)
        Memory memoryInfo{};

        std::ifstream meminfo("/proc/meminfo");
        if (!meminfo) return {};

        for (std::string line; std::getline(meminfo, line);)
        {
           if (line.find("MemTotal") != std::string::npos)
              memoryInfo.total = std::strtoul(line.c_str() + line.find_first_of("0123456789"), nullptr, 10);
           if (line.find("MemAvailable") != std::string::npos)
              memoryInfo.available= std::strtoul(line.c_str() + line.find_first_of("0123456789"), nullptr, 10);
        }

        memoryInfo.used = memoryInfo.total - memoryInfo.available;

        return memoryInfo;
    #elif defined(NAIL_PLATFORM_MACOS)
        uint64_t total = 0, available = 0;
        size_t length = sizeof(uint64_t);

        vm_statistics64 stats;
        natural_t count = HOST_VM_INFO64_COUNT;
        mach_port_t host = mach_host_self();

        sysctlbyname("hw.memsize", &total, &length, nullptr, 0);
        host_statistics64(host, HOST_VM_INFO64, reinterpret_cast<host_info64_t>(&stats), &count);
        available = stats.free_count * static_cast<unsigned>(getpagesize());

        return { total, available, total - available };
    #else
        NAIL_MISSING_IMPLEMENTATION();
    #endif
    }
}

