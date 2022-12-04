#include <iostream>
#include <string_view>
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

    int priorities = 0;
    std::string line;

    int priorityLookup[127]{};
    for (int badge = 'A'; badge <= 'Z'; ++badge)
    {
        priorityLookup[badge] = 27 + badge - 'A';
    }

    for (int badge = 'a'; badge <= 'z'; ++badge)
    {
        priorityLookup[badge] = 1 + badge - 'a';
    }

    std::string group[3];

    auto GetGroup = [&group, &fileStream]() -> bool
    {
        for (int i = 0; i < 3; ++i)
        {
            std::getline(*fileStream, group[i]);
        };

        return *fileStream && std::all_of(std::begin(group), std::end(group), [](std::string_view s)
                                          { return !s.empty(); });
    };

    while (GetGroup())
    {
        int groupBadgeShared[127]{};
        for (int i = 0; i < 2; ++i)
        {
            bool badgeSeen[127]{};
            for (int badgeIdx : group[i])
            {
                if (!badgeSeen[badgeIdx])
                {
                    badgeSeen[badgeIdx] = true;
                    groupBadgeShared[badgeIdx]++;
                }
            }
        }

        for (char badge : group[2])
        {
            int badgeIdx = badge;
            if (groupBadgeShared[badgeIdx] == 2)
            {
                std::cout << "Groups share " << badge << " with priority " << priorityLookup[badgeIdx] << '\n';
                priorities += priorityLookup[badgeIdx];
                break;
            }
        }
    }
    std::cout << priorities << '\n';
}
