#include "nail/Log/FileWriter.hpp"

namespace nail
{
    FileWriter::FileWriter(std::string_view const filepath)
        : m_filepath(filepath), m_file(nullptr)
    {
        m_file = std::fopen(m_filepath.c_str(), "w");

        if (!m_file)
            std::perror("Unable to open file");
    }

    void FileWriter::write(Logger::Level const level, std::string_view const line)
    {
        if (!m_file) return;

        std::fprintf(m_file, "%s", line.data());
        std::fputc('\n', m_file);
        std::fflush(m_file);
    }

    FileWriter::~FileWriter()
    {
        if (m_file)
            std::fclose(m_file);
    }
}

