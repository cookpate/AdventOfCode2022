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
    for (int item = 'A'; item <= 'Z'; ++item)
    {
        priorityLookup[item] = 27 + item - 'A';
    }

    for (int item = 'a'; item <= 'z'; ++item)
    {
        priorityLookup[item] = 1 + item - 'a';
    }

    while (std::getline(*fileStream, line) && !line.empty())
    {
        const auto compartmentSize = line.length() / 2;
        const std::string_view compartments[2]{
            {line.data(), compartmentSize},
            {line.data() + compartmentSize, compartmentSize}};
        bool itemSeen[127]{};
        for (int item : compartments[0])
        {
            itemSeen[item] = true;
        }

        for (char item : compartments[1])
        {
            int itemIdx = item;
            if (itemSeen[itemIdx])
            {
                std::cout << "Comparments share " << item << " with priority " << priorityLookup[itemIdx] << '\n';
                priorities += priorityLookup[itemIdx];
                break;
            }
        }
    }
    std::cout << priorities << '\n';
}
