
#include <sstream>
#include <filesystem>
#include <optional>
// read entire contents of a file into a string stream
std::optional<std::istringstream> ReadFile(std::filesystem::path path);