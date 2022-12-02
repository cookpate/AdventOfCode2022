#ifndef AOC_2022_HELPER
#define AOC_2022_HELPER

#include <sstream>
#include <filesystem>
#include <optional>
#include <algorithm>

// read entire contents of a file into a string stream
std::optional<std::istringstream> ReadFile(std::filesystem::path path);

// casts int to enum, checking bad values
template<typename Enum, Enum min, Enum max>
constexpr std::optional<Enum> EnumCast(const int toCast) noexcept
{
    static_assert(min <= max, "Inverted bounds!");
    Enum casted = std::max( min, std::min( static_cast<Enum>( toCast ), max ) );
    return casted == toCast ? std::make_optional(casted) : std::nullopt;
}

#endif
