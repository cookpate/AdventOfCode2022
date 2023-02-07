#include "helper.hh"

#include <charconv>
#include <iostream>
#include <string_view>

using CleaningRange = std::pair<int, int>;

static CleaningRange ParseRange(const std::string_view range) {
  const auto &&[first, second] = split(range, '-');

  CleaningRange result{};

  std::from_chars(first.data(), std::next(first.data(), first.size()),
                  result.first);
  std::from_chars(second.data(), std::next(second.data(), second.size()),
                  result.second);

  return result;
}

static std::pair<CleaningRange, CleaningRange>
ParseLine(const std::string_view line) {
  const auto &&[first, second] = split(line, ',');
  return {ParseRange(first), ParseRange(second)};
}

static bool Contains(const CleaningRange &container,
                     const CleaningRange &containee) {
  return container.first <= containee.first &&
         container.second >= containee.second;
}

static bool FullyOverlaps(const CleaningRange &lhs, const CleaningRange &rhs) {
  return Contains(lhs, rhs) || Contains(rhs, lhs);
}

static bool PartiallyOverlaps(CleaningRange lhs, CleaningRange rhs) {
  if (rhs.first < lhs.first) {
    std::swap(lhs.first, rhs.first);
  }

  if (rhs.second < lhs.second) {
    std::swap(lhs.second, rhs.second);
  }

  return lhs.second >= rhs.first && rhs.second >= lhs.first;
}

int main(const int argc, const char *argv[]) {
  if (argc < 2) {
    return 1;
  }

  auto fileStream = ReadFile(argv[1]);
  if (!fileStream) {
    std::cerr << "Failed to open or read file \'" << argv[1] << "\'\n";
    return 1;
  }

  std::string line;
  int overlaps[2]{};
  while (std::getline(*fileStream, line) && !line.empty()) {
    const auto &&[first, second] = ParseLine(line);
    if (FullyOverlaps(first, second)) {
      ++overlaps[0];
    }
    if (PartiallyOverlaps(first, second)) {
      ++overlaps[1];
    }
  }
  std::cout << "part1: " << overlaps[0] << '\n'
            << "part2: " << overlaps[1] << '\n';
}
