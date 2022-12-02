#ifndef AOC_2022_DAY2_HELPER
#define AOC_2022_DAY2_HELPER

#include <string_view>
#include "helper.hh"

enum Action
{
    Rock = 0,
    Paper = 1,
    Scissors = 2,
};

static constexpr std::string_view actionStrings[3]{"Rock", "Paper", "Scissors"};

Action ActionCast(int toCast)
{
    return *EnumCast<Action, Rock, Scissors>(toCast);
}

enum Strategy
{
    Lose = 0,
    Draw = 1,
    Win = 2,
};

static constexpr std::string_view strategyStrings[3]{"Lose", "Draw", "Win"};

Strategy StrategyCast(int toCast)
{
    return *EnumCast<Strategy, Lose, Win>(toCast);
};

#endif
