#include "nail/Log/ConsoleWriter.hpp"

#include <iostream>

namespace nail
{
    std::shared_ptr<ConsoleWriter> ConsoleWriter::out(new ConsoleWriter(std::cout));
    std::shared_ptr<ConsoleWriter> ConsoleWriter::err(new ConsoleWriter(std::cerr));

    ConsoleWriter::ConsoleWriter(std::ostream& os) noexcept
        : m_output(os) {}

    void ConsoleWriter::write(Logger::Level const level, std::string_view const line)
    {
        // TODO: Colours
        m_output << line << std::endl;
    }
}

