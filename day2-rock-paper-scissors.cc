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

    int roundResultLookup[3][3] = {};
    for (int player = Rock; player <= Scissors; ++player)
    {
        for (int opponent = Rock; opponent <= Scissors; ++opponent)
        {
            // points for choosing rock, paper, or scissors
            roundResultLookup[player][opponent] = player + 1;
            // draw
            if (player == opponent)
            {
                roundResultLookup[player][opponent] += 3;
            }
            // win
            else if ((opponent + 1) % 3 == player)
            {
                roundResultLookup[player][opponent] += 6;
            }
        }
    }

    int scoreTotal = 0;
    std::string line;
    while (std::getline(*fileStream, line) && !line.empty())
    {
        const Action opponent = ActionCast(line.front() - 'A');
        const Action player = ActionCast(line.back() - 'X');
        const int &roundScore = roundResultLookup[player][opponent];
        std::cout << actionStrings[player] << " against " << actionStrings[opponent] << ": " << roundScore << '\n';
        scoreTotal += roundScore;
    }
    std::cout << scoreTotal << '\n';
}
