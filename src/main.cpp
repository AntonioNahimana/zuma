#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

void populate_vector(std::vector<int>& vec)
{
    std::string input;

    std::cout << "Introduceti secventa de numere separate prin spatii: ";
    std::getline(std::cin, input);

    std::istringstream iss(input);

    int num;
    while (iss >> num)
    {
        vec.push_back(num);
    }
}

void print_vector(const std::vector<int>& vec)
{
    std::cout << "Vector: ";
    if (vec.empty())
    {
        std::cout << "Gol";
    }
    else
    {
        for (const auto& num : vec)
        {
            std::cout << num << " ";
        }
    }
    std::cout << "\n";
}

int count_sequences(const std::vector<int>& vec)
{
    int count = 0;

    int consecutive = 1;
    for (std::size_t i = 1; i < vec.size(); ++i)
    {
        if (vec[i] == vec[i - 1])
        {
            ++consecutive;
        }
        else
        {
            if (consecutive >= 3)
            {
                ++count;
            }
            consecutive = 1;
        }
    }

    if (consecutive >= 3)
    {
        ++count;
    }

    return count;
}

void eliminate_sequences(std::vector<int>& vec)
{
    int consecutive = 1;
    for (std::size_t i = 1; i < vec.size(); ++i)
    {
        if (vec[i] == vec[i - 1])
        {
            ++consecutive;
        }
        else
        {
            if (consecutive >= 3)
            {
                vec.erase(vec.begin() + (i - consecutive), vec.begin() + i);
                i -= consecutive;
            }
            consecutive = 1;
        }
    }

    if (consecutive >= 3)
    {
        vec.erase(vec.end() - consecutive, vec.end());
    }
}

void eliminate_adjacent_sequences(std::vector<int>& vec)
{
    std::size_t i = 1;
    while (i < vec.size() - 1)
    {
        std::size_t j = i - 1;
        while (j > 0 && vec[j] == vec[i])
        {
            --j;
        }

        std::size_t k = i + 1;
        while (k < vec.size() && vec[k] == vec[i])
        {
            ++k;
        }

        if (k - j >= 3)
        {
            vec.erase(vec.begin() + j + 1, vec.begin() + k);
            i -= (k - j - 1);
        }
        else
        {
            ++i;
        }
    }
}

void play()
{
    std::vector<int> zuma;
    populate_vector(zuma);

    int round_count = 0;
    int sequence_count = count_sequences(zuma);

    std::cout << "Vector initial:\n";
    print_vector(zuma);

    while (sequence_count > 0)
    {
        ++round_count;

        eliminate_sequences(zuma);
        print_vector(zuma);

        eliminate_adjacent_sequences(zuma);
        print_vector(zuma);

        sequence_count = count_sequences(zuma);
    }

    std::cout << "Vector final:\n";
    print_vector(zuma);
    std::cout << "Runde jucate: " << round_count << '\n';
}

int main()
{
    play();
    return 0;
}
