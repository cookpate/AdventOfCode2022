#ifndef AOC_2022_HELPER
#define AOC_2022_HELPER

#include <algorithm>
#include <charconv>
#include <filesystem>
#include <optional>
#include <sstream>
#include <type_traits>
#include <utility>

// read entire contents of a file into a string stream
std::optional<std::istringstream> ReadFile(std::filesystem::path path);

// casts int to enum, checking bad values
template <typename Enum, Enum min, Enum max>
constexpr inline std::optional<Enum> EnumCast(const int toCast) noexcept {
  static_assert(min <= max, "Inverted bounds!");
  Enum casted = std::max(min, std::min(static_cast<Enum>(toCast), max));
  return casted == toCast ? std::make_optional(casted) : std::nullopt;
}

template <typename Integer>
std::from_chars_result from_chars(std::string_view string, Integer &result,
                                  int base = 10) {
  if constexpr (std::is_integral_v<Integer>) {
    return std::from_chars(
        string.data(), std::next(string.data(), string.size()), result, base);
  } else if constexpr (std::is_floating_point_v<Integer>) {
    (void)base;
    return std::from_chars(string.data(),
                           std::next(string.data(), string.size()), result);
  }
}

std::pair<std::string_view, std::string_view> split(std::string_view input,
                                                    char splitChar);

#endif
