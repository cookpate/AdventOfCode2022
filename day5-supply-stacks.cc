#include "helper.hh"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <deque>
#include <iostream>
#include <regex>
#include <string_view>

using namespace std::string_view_literals;
static constexpr auto air = "   "sv;

static bool ParseLine(const std::string_view line,
                      std::vector<std::deque<char>> &stacks) {
  if (stacks.empty()) {
    stacks.resize((1u + line.length()) / 4u);
    std::cout << stacks.size() << " stacks\n";
  }

  if (std::isdigit(line[1])) {
    return false;
  }

  for (size_t i = 0, idx = 0; i != stacks.size(); ++i, idx += 4) {
    const auto container = line.substr(idx, 3);
    if (container != air) {
      stacks[i].push_front(container[1]);
    }
  }

  return true;
}

static const auto moveRegex = std::regex("^move (\\d+) from (\\d+) to (\\d+)$",
                                         std::regex_constants::ECMAScript |
                                             std::regex_constants::optimize);

int main(const int argc, const char *argv[]) {
  if (argc < 3) {
    return 1;
  }

  auto fileStream = ReadFile(argv[1]);
  if (!fileStream) {
    std::cerr << "Failed to open or read file \'" << argv[1] << "\'\n";
    return 1;
  }

  bool part1 = (*argv[2] == '0');

  std::vector<std::deque<char>> stacks;

  std::string line;
  std::string message;
  while (std::getline(*fileStream, line) && !line.empty()) {
    if (!ParseLine(line, stacks)) {
      break;
    }
  }

  size_t height = std::max_element(stacks.cbegin(), stacks.cend(),
                                   [](const auto &lhs, const auto &rhs) {
                                     return lhs.size() < rhs.size();
                                   })
                      ->size();
  for (size_t i = height; i != 0;) {
    --i;
    for (auto const &container : stacks) {
      if (container.size() > i) {
        std::cout << "[" << container[i] << ']' << ' ';
      } else {
        std::cout << air << ' ';
      }
    }
    std::cout << '\n';
  }
  for (size_t i = 0; i != stacks.size(); ++i) {
    std::cout << ' ' << i + 1 << "  ";
  }
  std::cout << '\n';

  (void)std::getline(*fileStream, line);

  while (std::getline(*fileStream, line) && !line.empty()) {
    std::smatch match;
    if (std::regex_search(line, match, moveRegex)) {
      std::cout << match[0] << '\n';
      std::cout << match[1] << ' ' << match[2] << ' ' << match[3] << '\n';

      size_t count, from, to;
      ::from_chars(match[1].str(), count, 10);
      ::from_chars(match[2].str(), from, 10);
      ::from_chars(match[3].str(), to, 10);

      auto &fromStack = stacks[from - 1];
      auto &toStack = stacks[to - 1];

      if (part1) {
        const auto begin = fromStack.rbegin();
        const auto end = fromStack.rbegin() + count;
        std::copy(begin, end, std::back_inserter(toStack));
        fromStack.erase(end.base(), begin.base());
      } else {
        const auto begin = fromStack.end() - count;
        const auto end = fromStack.end();
        std::copy(begin, end, std::back_inserter(toStack));
        fromStack.erase(begin, end);
      }
    }
  }

  for (const auto &container : stacks) {
    message += container.back();
  }

  std::cout << message << '\n';
}
