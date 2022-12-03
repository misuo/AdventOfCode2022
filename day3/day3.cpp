// Release: cl /EHsc /std:c++latest day3.cpp
// Debug  : cl /EHsc /std:c++latest /Zi /DDEBUG day3.cpp
#include <fstream>       // For std::ifstream
#include <iostream>      // For std::cout
#include <vector>        // For std::vector
#include <string>        // For std::string
#include <map>           // For std::map<>
#include <cassert>       // For assert()
#include <algorithm>     // For std::set_intersection().
#include <unordered_set> // For std::unordered_set<>
#include <ranges>

template <typename T>
void remove_duplicates(std::vector<T>& v)
{
  auto itr = v.begin();
  std::unordered_set<T> s;

  for( auto curr = v.begin(); curr != v.end(); ++curr )
  {
    if( s.insert(*curr).second )
      *itr++ = *curr;
  }

  v.erase(itr, v.end());
}


int main()
{
  using Rucksack = std::string;
  using Priority = std::size_t;

  std::vector<Rucksack> rucksacks;

  auto GetIntersect = [](std::string line)
  {
    // Verify even length
    assert(line.size() % 2 == 0);

    std::vector<char> intersection;

    // Note: Need to sort as this is a requirement for set_intersection.
    std::sort(std::begin(line), std::begin(line) + line.size() / 2);
    std::sort(std::begin(line) + line.size() / 2, std::end(line));

    std::set_intersection(
      std::begin(line), std::begin(line) + line.size() / 2,
      std::begin(line) + line.size() / 2, std::end(line),
      std::back_inserter(intersection));

    // Remove duplicates
    remove_duplicates(intersection);

    //assert(intersection.size() > 0 && "No intersected character found");
    assert(intersection.size() <= 1);

    return intersection;
  };

  auto GetPriority = [](const auto& elems)
  {
    Priority prio{0};
    for( const auto& elem : elems )
      prio += ((elem - 'a') < 0 ? (27 + elem - 'A') : (1 + elem - 'a'));

    return prio;
  };

  using Rucksack = std::string;

  // Tests
  const std::vector<Rucksack> rucksacks_test = {
    "vJrwpWtwJgWrhcsFMMfFFhFp",
    "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
    "PmmdzqPrVvPwwTWBwg",
    "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
    "ttgJtRGJQctTZtZT",
    "CrZsJsPPZsGzwwsLwLmpwMDw"
  };

  const std::vector<Priority> priority_test = { 16, 38, 42, 22, 20, 19 };
  auto test_resit = std::begin(priority_test);

  // Samples
  for( const auto& rucksack : rucksacks_test )
  {
    assert(GetPriority(GetIntersect(rucksack)) == *test_resit++ && "Unexpected test result");
  }

  // Extra
  assert(GetPriority(GetIntersect("TSchqLtTLFhgQbMMQMrr")) == 8);


  std::ifstream fin("input.txt");
  for( std::string line; std::getline(fin, line); )
    rucksacks.push_back(line);

  assert(rucksacks.size() == 300); // Verify number of rucksacks in input

  // Part 1
  std::size_t priosum{0};
  for( const auto & rucksack : rucksacks )
    priosum += GetPriority(GetIntersect(rucksack));

  std::cout << priosum << std::endl; // 8298

  // Part 2
  auto CommonItemType = [](std::ranges::viewable_range auto&& r)
  {
    assert(r.size() == 3);

    // Search each group/elems (because set_intersection requires that)
    for( auto& elems : r )
      std::ranges::sort(elems); // aks std::sort(std::begin(elems), std::end(elems));

    auto it = std::begin(r);

    std::vector<char> intersection;
    std::ranges::set_intersection(*it++, *it++,std::back_inserter(intersection));

    std::vector<char> intersection1;
    std::ranges::set_intersection(intersection, *it, std::back_inserter(intersection1));

    // Remove duplicates
    remove_duplicates(intersection1);

    //for( auto elem : intersection1 )
    //  std::cout << elem;
    //std::cout << std::endl;

    return intersection1;
  };

  std::size_t itemsum{0};
  for( const auto& chunks : rucksacks | std::views::chunk(3) )
    itemsum += GetPriority(CommonItemType(chunks));

  std::cout << itemsum << std::endl; // 2708

  return 0;
}

// Others:
// * https://github.com/TartanLlama/aoc-2022/blob/main/aoc-2022/day03/day03.cpp
