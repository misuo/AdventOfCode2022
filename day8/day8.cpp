// Release: cl /EHsc /std:c++latest day8.cpp
// Debug  : cl /EHsc /std:c++latest /Zi /DDEBUG day8.cpp
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm> // For std::ranges::count

using Forest = std::vector<std::string>;

bool Load(Forest &forest)
{
  forest.clear();

  std::ifstream fin("input.txt");
  for( std::string line; std::getline(fin, line); )
  {
    forest.push_back(line);
    assert(forest.back().length() == line.length()); // Verify equal length
  }

  return true;
}

std::size_t CountVisible(const Forest& forest)
{
  const std::size_t rows = forest.size();
  const std::size_t cols = forest.front().size();

  const std::string visiblerow(cols, '1');
  const std::string emptyrow(cols, '0');
  Forest result(rows, emptyrow);

  // Initialize edges - all setting to '1'
  result.front() = visiblerow;
  result.back() = visiblerow;
  for( auto& rows : result )
  {
    rows.front() = '1';
    rows.back() = '1';
  }

  // Look horizontally
  for( std::size_t rowno = 1; rowno<rows-1; ++rowno )
  {
    // rows: leftwards (from left-to-right)
    auto max = forest[rowno].front();
    for( std::size_t colno = 1; colno<cols-1; ++colno )
      if( forest[rowno][colno] > max )
      {
        result[rowno][colno] = '1';
        max = forest[rowno][colno];
      }

    // rows: rightwards (from right to left)
    max = forest[rowno].back();
    for( std::size_t colno = cols-1; colno>0; --colno )
      if( forest[rowno][colno] > max)
      {
        result[rowno][colno] = '1';
        max = forest[rowno][colno];
      }
  }

  std::cout << "Horizontally processed\n";
  for( const auto& row : result )
    std::cout << row << std::endl;
  std::cout << "-----\n";

  // Look vertically
  for( std::size_t colno = 1; colno<cols-1; ++colno )
  {
    // cols: top-down 
    auto max = forest[0][colno];
    for( std::size_t rowno = 1; rowno<rows-2; ++rowno )
      if( forest[rowno][colno] > max )
      {
        result[rowno][colno] = '1';
        max = forest[rowno][colno];
      }

    // cols: bottom-up
    max = forest[rows-1][colno];
    for( std::size_t rowno = rows - 2; rowno > 0; --rowno )
      if( forest[rowno][colno] > max )
      {
        result[rowno][colno] = '1';
        max = forest[rowno][colno];
      }
  }

  std::size_t visible{0};

  for( const auto& row : result )
  {
    std::cout << row << std::endl;
    visible += std::ranges::count(row, '1');
  }

  return visible;
}

std::size_t ScenicScore(const Forest& forest, std::size_t row, std::size_t col)
{
  const std::size_t rows = forest.size();
  const std::size_t cols = forest.front().size();

  std::size_t up{0};
  std::size_t down{0};
  std::size_t left{0};
  std::size_t right{0};

  const auto max = forest[row][col];

  // stop if you reach an edge or at the first tree that is the same height 
  // or taller than the tree under consideration

  // up
  auto r = row-1;
  while( r<rows )
  {
    up++;
    if( forest[r][col] >= max )
      break;
    r--;
  }

  // left
  auto c = col-1;
  while( c<cols  )
  {
    left++;
    if( forest[row][c] >= max )
      break;
    c--;
  }

  // down
  r = row+1;
  while( r<rows )
  {
    down++;
    if( forest[r][col] >= max )
      break;
    r++;
  }

  // right
  c = col+1;
  while( c<cols )
  {
    right++;
    if( forest[row][c] >= max )
      break;
    c++;
  }

  return up * down * left * right;
}

int main()
{
  Forest forest{
    "30373",  // 0
    "25512",  // 1
    "65332",  // 2
    "33549",  // 3
    "35390"   // 4
  };
 
  // Verify part-1 algorithm on test data
  assert(CountVisible(forest) == 21);

  // Verify part-2 algorithm on test data
  assert(ScenicScore(forest, 1, 2) == 4);
  assert(ScenicScore(forest, 3, 2) == 8);

  Load(forest);

  // Part 1

  std::cout << CountVisible(forest) << std::endl;

  // Part 2

  const std::size_t rows = forest.size();
  const std::size_t cols = forest.front().size();

  std::size_t max{0};
  for( std::size_t row = 0; row < rows; ++row )
    for( std::size_t col = 0; col < cols; ++col )
      max = std::max(max, ScenicScore(forest, row, col));

  std::cout << max << std::endl;

  return 0;
}
