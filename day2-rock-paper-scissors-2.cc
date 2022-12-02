#include <iostream>
#include <string_view>
#include "day2-helper.hh"
#include "helper.hh"

int main(const int argc, const char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    auto fileStream = ReadFile(argv[1]);
    if (!fileStream)
    {
        std::cerr << "Failed to open or read file \'" << argv[1] << "\'\n";
        return 1;
    }

    static auto PrintPlan = [](Action opponent, Strategy strategy)
    {
        std::cout << std::setw(4) << strategyStrings[strategy] << " against " << actionStrings[opponent] << ": ";
    };

    int roundResultLookup[3][3] = {};
    for (int opponent = Rock; opponent <= Scissors; ++opponent)
    {
        for (int strategy = Lose; strategy <= Win; ++strategy)
        {
            const int response = (opponent + strategy + 2) % 3;
            const int roundScore = 1 + response + strategy * 3;
            roundResultLookup[opponent][strategy] = roundScore;
            PrintPlan(ActionCast(opponent), StrategyCast(strategy));
            std::cout << actionStrings[response] << ' ' << roundScore << '\n';
        }
        std::cout << '\n';
    }

    int scoreTotal = 0;
    std::string line;
    while (std::getline(*fileStream, line) && !line.empty())
    {
        const Action opponent = ActionCast(line.front() - 'A');
        const Strategy strategy = StrategyCast(line.back() - 'X');
        const int &roundScore = roundResultLookup[opponent][strategy];
        PrintPlan(opponent, strategy);
        std::cout << roundScore << '\n';
        scoreTotal += roundScore;
    }
    std::cout << scoreTotal << '\n';
}
