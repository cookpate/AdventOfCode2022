#include "helper.hh"

#include <fstream>

std::optional<std::istringstream> ReadFile(const std::filesystem::path path)
{
    std::ifstream file(path);
    if (!file)
    {
        return std::nullopt;
    }
    std::string buffer(static_cast<size_t>(std::filesystem::file_size(path)), '\0');
    file.read(&buffer.front(), buffer.size());
    buffer.resize(file.gcount());
    return std::istringstream(buffer);
}
