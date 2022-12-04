// Release: cl /EHsc /std:c++latest day3.cpp
// Debug  : cl /EHsc /std:c++latest /Zi /DDEBUG day3.cpp
#include <fstream>       // For std::ifstream
#include <iostream>      // For std::cout
#include <sstream>       // For std::istringstream
#include <vector>        // For std::vector
#include <string>        // For std::string
#include <cassert>       // For assert()
#include <algorithm>     // For std::count_if()

using ID = int;
using Section = std::pair<ID, ID>;
using ElfPair = std::pair<Section, Section>;

std::ostream& operator<<(std::ostream& os, const Section& s)
{
  return os << s.first << "-" << s.second;
}

std::ostream& operator<<(std::ostream& os, const ElfPair& ep)
{
  return os << ep.first << "," << ep.second;
}

int main()
{
  Section elf1;
  Section elf2;

  using ElfPairs = std::vector<ElfPair>;
  ElfPairs elfpairs;

  // Load data
  char d; // dummy
  std::ifstream fin("input.txt");
  for( std::string line; std::getline(fin, line); )
  {
    ElfPair ep;

    // <int>-<int>,<int>-<int>
    std::istringstream istr(line);
    istr >> ep.first.first >> d >> ep.first.second >> d >> ep.second.first >> d >> ep.second.second;

    elfpairs.push_back(ep);
  }

  assert(elfpairs.size() == 1000); // Verify correct number of lines/elspairs loaded.

  // Test data
  ElfPairs test_data = {
    { {2,4}, {6,8} },
    { {2,3}, {4,5} },
    { {5,7}, {7,9} }, //                                overlaps 7
    { {2,8}, {3,7} }, // second is contained in first   overlaps 34567
    { {6,6}, {4,6} }, // first is contained in second   overlaps 6
    { {2,6}, {4,8} }  //                                overlaps 456
  };

  // Part1
  auto Contains = [](const auto& ep)
  {
    return ep.first.first>=ep.second.first && ep.first.second<=ep.second.second || // first is contained in second
           ep.second.first>=ep.first.first && ep.second.second<=ep.first.second;   // second is contained in first
  };

  // Check test data result
  for( const auto& ep : test_data )
    std::cout << ep << " contains? " << Contains(ep) << std::endl;

  auto containscount = std::count_if(std::begin(elfpairs), std::end(elfpairs), Contains);
  std::cout << containscount << std::endl;

  // Part2 (overlaps is the same as not outside)
  auto Outside = [](const auto& ep)
  {
    return ep.first.second < ep.second.first ||
           ep.first.first > ep.second.second;
  };

  auto Overlap = [](const auto& ep)
  {
    return !(ep.first.second < ep.second.first ||
             ep.first.first > ep.second.second);
  };

  // Check test data result
  for( const auto& ep : test_data )
    std::cout << ep << " overlaps? " << Overlap(ep) << std::endl;

  auto overlapcount = std::count_if(std::begin(elfpairs), std::end(elfpairs), Overlap);
  std::cout << overlapcount << std::endl;

  return 0;
}
