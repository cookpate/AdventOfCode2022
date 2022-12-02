#include <iostream>
#include <charconv>
#include <set>
#include <numeric>
#include "helper.hh"

int main(const int argc, const char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }
    
    auto fileStream = ReadFile(argv[1]);
    if(!fileStream)
    {
        std::cerr << "Failed to open or read file \'" << argv[1] << "\'\n";
        return 1;
    }

    std::string line;
    int calories = 0;
    std::multiset<int> maxes;
    while (std::getline(*fileStream, line))
    {
        if (line.empty())
        {
            maxes.insert(std::exchange(calories, 0));
        }
        else
        {
            int value = 0;
            auto [_, errc] = std::from_chars(&line.front(), &line.back() + 1, value);
            if (errc != std::errc{})
            {
                std::cerr << "failed to parse \'" << line << "\'\n";
                std::cerr.flush();
                std::exit(1);
            }
            calories += value;
        }
    }
    maxes.insert(calories);
    const int total = std::accumulate(maxes.crbegin(), std::next(maxes.crbegin(), std::min(maxes.size(), size_t(3))), 0);
    std::cout << total << '\n';
}