// Release: cl /EHsc /std:c++latest day7.cpp
// Debug  : cl /EHsc /std:c++latest /Zi /DDEBUG day7.cpp
#include <fstream>       // For std::ifstream
#include <iostream>      // For std::cout
#include <string>        // For std::string
#include <sstream>       // For std::istringstream
#include <cassert>       // For assert()
#include <map>           // For std::map<>
#include <numeric>       // For access to std::accumulate
#include <ranges>        // For std::ranges
#include <algorithm>     // For std::ranges::sort

int main()
{
  using Name = std::string;
  using Size = std::size_t;

  std::map<Name,Size> dirpaths;
  dirpaths["/"] = 0;

  Name currdirpath = "/";

  // ParentDir - p expected to be string (a directory path) ending with / 
  auto ParentDir = [](auto& p)
  {
    // Verify directory path
    assert(p.back() == '/');

    if( p != "/" )
    {
      p.pop_back();
      p.erase(p.find_last_of('/'));
      p += "/";
      return true;
    }
    return false;
  };

  // Load data
  std::string dummy;
  std::ifstream fin("input.txt");
  for( std::string line; std::getline(fin, line); )
  {
    if( line.empty() )
      continue;

    if( line == "$ ls" )
      continue; // do nothing

    std::istringstream istr(line);

    // Change directory command
    if( line.starts_with("$ cd") )
    {
      // Eat command, parse directory name
      Name dir;
      istr >> dummy >> dummy >> dir;

      if( dir == "/" )
        currdirpath = "/";
      else if( dir == ".." )
        ParentDir(currdirpath);
      else
        currdirpath += dir + "/";

      continue;
    }

    // dir <name>
    if( line.starts_with("dir") )
      continue;

    // Q: What if 'ls' already has been done once for current directory?
    //    - Potentially new files could have been added or deleted between these.
    //    - Even the file (same name) and its size could have changed!

    // otherwise line must begin with a filesize and filename
    Size fsize;
    Name fname;
    istr >> fsize >> fname;

    //std::cout << currdirpath << fname << " (" << fsize << ")" << std::endl;

    dirpaths[currdirpath] += fsize;
    
    // Update parent directories with that same file size
    auto p = currdirpath;
    while( ParentDir(p) )
      dirpaths[p] += fsize;
  }

  // * ls can in principle be done on the same directory multiple times
  // * a dir may be shown in ls that we do not necessary do a ls for (hence unknown content - at least wrt files)
  // * Q: can you have a directory and file with same name?

  const auto atmostsizesum = std::accumulate( std::begin(dirpaths), std::end(dirpaths), 0, [](const auto & sum, const auto & d2) {
    return d2.second <= 100000 ? sum+d2.second : sum; }
  );

  std::cout << atmostsizesum << std::endl; // 1490523

  // Part 2

  const std::size_t capacity = 70000000;
  const std::size_t used     = dirpaths["/"]; // size of root
  const std::size_t unused   = capacity - used;
  const std::size_t needed   = 30000000;

  // Convert map to vector (for sorting afterwards)
  std::vector<std::pair<Name, Size>> dirs;
  for( const auto& dir : dirpaths )
    dirs.push_back(std::make_pair(dir.first, dir.second));

  // Sort them by size (smallest first)
  std::ranges::sort(dirs, [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });

  // Find the fist one that added to unused gives what is needed
  auto it = std::ranges::find_if(dirs, [&unused, &needed](const auto& dir) { return unused + dir.second >= needed; });
  if( it != std::end(dirs) )
    std::cout << it->second << std::endl;   // 12390492
}
