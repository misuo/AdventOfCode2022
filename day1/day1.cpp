// Release: cl /EHsc /std:c++20 day1.cpp
// Debug  : cl /EHsc /std:c++20 /Zi /DDEBUG day1.cpp
#include <fstream>   // For std::ifstream
#include <iostream>  // For std::cout
#include <vector>    // For std::vector
#include <string>    // For std::string
#include <algorithm> // For std::sort()
#include <numeric>   // For std::accumulate()

int main()
{
  std::ifstream filein("input.txt");

  std::vector<int> calories;

  for( std::string line; std::getline(filein, line); )
  {
    if( calories.empty() || line.empty() )
      calories.push_back(0);

    if( !line.empty() )
      calories.back() += std::stoi(line); // Note: We do not handle exception if line do not contain number.
  }

  std::sort(std::begin(calories), std::end(calories), std::greater<>()); // or perhaps use std::max_element().

  // part 1
  std::cout << calories.front() << "\n";

  // part 2: using std::accumulate
  std::cout << std::accumulate(std::begin(calories), std::begin(calories)+3, 0); 

  return 0;
}
