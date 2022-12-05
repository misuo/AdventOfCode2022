// Release: cl /EHsc /std:c++latest day5.cpp
// Debug  : cl /EHsc /std:c++latest /Zi /DDEBUG day5.cpp
#include <fstream>       // For std::ifstream
#include <iostream>      // For std::cout
#include <sstream>       // For std::istringstream
#include <vector>        // For std::vector
#include <string>        // For std::string
#include <cassert>       // For assert()
#include <algorithm>     // 
#include <ranges>        // For std::ranges::count_if()

using Stack    = std::string;
using Stacks   = std::vector<Stack>;
using CrateId  = char;
using CratesNo = std::size_t;
using StackNo  = std::size_t;
using Move     = std::tuple<CratesNo,StackNo,StackNo>;  // Number creates, from stack, to stack
using Moves    = std::vector<Move>;

// Outputs top crates on each stack
std::ostream& operator<<(std::ostream& os, const Stacks& stacks)
{
  for( const auto& stack : stacks )
    os << stack.front();
  return os;
}

void Load(Stacks& stacks, Moves& moves)
{
  std::ifstream fin("input.txt");
  for( std::string line; std::getline(fin, line); )
  {
    if( line.empty() )
      continue;

    if( line.front() == 'm' )
    {
      Move move;

      std::string word; // dummy
      std::istringstream istr(line);
      istr >> word >> std::get<0>(move) >> word >> std::get<1>(move) >> word >> std::get<2>(move);

      moves.push_back(move);
    }
    else if( line[1] != '1' )
    {
      const StackNo stackscount = line.length() / 4 + 1;
      if( stacks.empty() )
        stacks.resize(stackscount); // Create stacks

      for( StackNo n = 0; n < stackscount; ++n )
      {
        if( CrateId ch = line[4 * n + 1]; ch != ' ' )
          stacks[n].push_back(ch);
      }
    }
  }
}

void Part1(Stacks stacks,const Moves & moves)
{
  for( const auto& move : moves )
  {
    auto& fromstack = stacks[std::get<1>(move)-1];
    auto& tostack   = stacks[std::get<2>(move)-1];

    const auto cratecount = std::get<0>(move);

    auto crates = fromstack.substr(0, cratecount);
    std::ranges::reverse(crates);

    tostack.insert(0, crates);
    fromstack.erase(0, cratecount);
  }

  // Output top crates on each stack
  std::cout << stacks << std::endl;
}

void Part2(Stacks stacks, const Moves& moves)
{
  for( const auto& move : moves )
  {
    auto& fromstack = stacks[std::get<1>(move)-1];
    auto& tostack   = stacks[std::get<2>(move)-1];

    const auto cratecount = std::get<0>(move);

    auto crates = fromstack.substr(0, cratecount);

    tostack.insert(0, crates);
    fromstack.erase(0, cratecount);
  }

  // Output top crates on each stack
  std::cout << stacks << std::endl;
}

int main()
{
  Stacks stacks;
  Moves  moves;

  Load(stacks, moves);
  assert(stacks.size() == 9);  // Verify correct number of stacks loaded.
  assert(moves.size() == 502); // Verify correct number of moves loaded.

  Part1(stacks,moves);
  Part2(stacks,moves);

  return 0;
}

// Other
// * https://github.com/crzyhorse/AdventOfCode2022/blob/main/day5/Day5.cpp (https://old.reddit.com/r/adventofcode/comments/zcxid5/2022_day_5_solutions/iyz9g5c/)
// * https://github.com/bobolpwnz/AdventOfCode2022/blob/main/src/days/day05.cpp
// * https://github.com/RiotNu/advent-of-code-2022/commit/ccce490c55da9184c27e7d46218325738f9c0ce8
// * https://github.com/vss2sn/advent_of_code/blob/master/2022/cpp/day_05a.cpp
//   https://github.com/vss2sn/advent_of_code/blob/master/2022/cpp/day_05b.cpp
// * https://github.com/willkill07/AdventOfCode2022/blob/main/days/Day05.hpp (https://old.reddit.com/r/adventofcode/comments/zcxid5/2022_day_5_solutions/iyz38bl/)
//   https://github.com/willkill07/AdventOfCode2022/blob/main/days/Day05.cpp
// * https://topaz.github.io/paste/#XQAAAQA0DAAAAAAAAAARmknGRw8TogB3HRdqOZ3QvocKtDLIs+k1aQq8nn6y4JCwKflnTwe9r+kNPXlFg6+4xjpPuczrMADyj2VqC+7v8/ZisHzTxjKEES4vMr7ssA4595/csAs1cUlLQOf8RPPgX2OAGKmS0ZvByMvQLkVFso3YYdG8iwnSZAb950dqjpjEL8OjK6v1iUHU4sku3JXzMPRPo5B5gvFV1UZwYlv05uGDaSaGYL9MmHlTYQzD04hELk8BEHp2cSzGJKgQ4RXpIM2cRd6toeIUCBYalTzYOwml09MNDwe3EJrASDljvoBtp8blW4pXluuU1t3yGT2FBkBRzvwPgrz9YqwamAkxBBc5e4JXCjqFgrEfVHq5TQQmeUUrLoHZDzqjLASO7ycdEpcSUUS6HERW6zIxGPBqlQYM92/JMkGAe5n1YNzFofIUE6QwarrZa53TRUjMYMmu4lWL1+srl6AuS1D4DoKVZWo1bgu9B7OY4d/N7FcKYHdFNcxUI+nbsJVRAxLXnD2mEf4DlN/yzMcumoRsGRYXjmfK0BuLmE69hHjNPzapR1sQPRlmCTK9/ub7JgH1nkmz263GhhlW3EDNnBpZSD1fkcwes0IRryOdxSH85W4UB9CAZpNkLlZk2vo0ri8VlLBao21PSmYNiJ8y6asPf7ca1vdiVKPUt7dUyRL8qQdNql/6snx7Ov8AFonz64avlYe8JAP8/YdyPCh4SH2ggTl9Sf9iiHW9kJv4JsPIOhJ3W1ntFS6j5wXRrJa2x7HX/aPD2GQbpU4y+LQNjI1Rg+3r1Xfdg+/Wh8DFNDhk3VZLdlSp/VIG/CTYyBmaVeQZRHzMYdZjgV7lJWgmlUHyV5mnbyQDRVH7zqe3
