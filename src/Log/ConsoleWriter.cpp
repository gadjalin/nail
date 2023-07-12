#include "nail/Log/ConsoleWriter.hpp"

#include <iostream>

namespace nail
{
    ConsoleWriter ConsoleWriter::std(std::cout);
    ConsoleWriter ConsoleWriter::err(std::cerr);

    ConsoleWriter::ConsoleWriter(std::ostream& os) noexcept
        : m_output(os) {}

    void ConsoleWriter::write(Logger::Level const level, std::string_view const line)
    {
        // TODO: Colours
        m_output << line << std::endl;
    }
}

