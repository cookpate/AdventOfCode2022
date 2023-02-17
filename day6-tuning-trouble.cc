#include "helper.hh"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <type_traits>

static constexpr size_t signalLengthPart1 = 4U;
static constexpr size_t signalLengthPart2 = 14U;

int main(const int argc, const char *argv[]) {
  if (argc < 3) {
    return 1;
  }

  std::ifstream fileStream(argv[1], std::ios::in);
  if (!fileStream) {
    std::cerr << "Failed to open or read file \'" << argv[1] << "\'\n";
    return 1;
  }

  [[maybe_unused]] bool part1 = (*argv[2] == '0');
  const size_t signalLength =
      (part1) ? (signalLengthPart1) : (signalLengthPart2);

  std::string line;
  std::getline(fileStream, line);

  if (line.size() < signalLength) {
    return 1;
  }

  using Signal_t = unsigned char;

  std::array<int, std::numeric_limits<Signal_t>::max()> countInWindow{};

  auto left = line.cbegin();
  auto right = std::next(line.cbegin(), signalLength);
  std::for_each(left, right, [&countInWindow](const Signal_t signal) {
    countInWindow[signal]++;
  });

  const auto begin = line.cbegin();

  auto isWindowUnique = [&countInWindow, &left, &right]() -> bool {
    return find_if(left, right, [&countInWindow](const Signal_t signal) {
             return countInWindow[signal] > 1;
           }) == right;
  };

  auto printAnswer = [&left, &right, &begin] {
    std::copy(left, right, std::ostream_iterator<char>{std::cout});
    std::cout << '\n' << std::distance(begin, right) << std::endl;
  };

  auto slideWindow = [&left, &right, &countInWindow] {
    countInWindow[*left]--;
    ++left;
    countInWindow[*right]++;
    ++right;
  };

  for (const auto end = line.cend(); right != end; slideWindow()) {
    if (isWindowUnique()) {
      printAnswer();
      break;
    }
  }
}
