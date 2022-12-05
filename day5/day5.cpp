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

  // Load data
  std::ifstream fin("input.txt");
  for( std::string line; std::getline(fin, line); )
  {
    if( line.empty() )
      continue;

    if( line.front() == '[' )
    {
      const StackNo stackscount = line.length()/4+1;
      if( stacks.empty() )
        stacks.resize(stackscount); // Create stacks

      for( StackNo n=0; n < stackscount; ++n )
      {
        if( CrateId ch = line[4*n+1]; ch != ' ' )
          stacks[n].push_back(ch);
      }
    }
    else if( line.front() == 'm' )
    {
      Move move;

      std::string word; // dummy
      std::istringstream istr(line);
      istr >> word >> std::get<0>(move) >> word >> std::get<1>(move) >> word >> std::get<2>(move);

      moves.push_back(move);
    }
  }

  assert(stacks.size() == 9); // Verify correct number of stacks loaded.
  assert(moves.size() == 502); // Verify correct number of moves loaded.

  Part1(stacks,moves);
  Part2(stacks,moves);

  return 0;
}

// Other
