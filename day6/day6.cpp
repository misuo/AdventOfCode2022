// Release: cl /EHsc /std:c++latest day6.cpp
// Debug  : cl /EHsc /std:c++latest /Zi /DDEBUG day6.cpp
#include <fstream>       // For std::ifstream
#include <iostream>      // For std::cout
#include <string>        // For std::string
#include <cassert>       // For assert()
#include <map>           // For std::map<>

int main()
{
  auto GetMarkerPos = [](std::string_view str, std::size_t markersize = 4)
  {
    std::map<char,std::size_t> map; // aka like a bucket
    std::size_t pos{0};
    while( pos < str.size() )
    {
      if( pos > markersize-1 )
      {
        // Decrease count of the character at the position previous to marker size
        if( auto it = map.find(str[pos-markersize]); it != std::end(map) )
          if( it->second > 1 )
            it->second--;
          else
            map.erase(it);
      }

      // Increase count of character
      ++map[str[pos++]];              // Q: Is map value quaranteed to be initially zero?

      if( map.size() == markersize )
        break;
    }

    return pos;
  };

  // Load data
  std::ifstream fin("input.txt");
  std::string line;
  std::getline(fin, line); // TODO: Possible performance optimization: In principle no need to read entire line. Can e.g. read by character.

  // Part 1 - Test data verification
  assert(GetMarkerPos("mjqjpqmgbljsphdztnvjfqwrcgsmlb")    == 7);
  assert(GetMarkerPos("bvwbjplbgvbhsrlpgdmjqwftvncz")      == 5);  // first marker after character 5
  assert(GetMarkerPos("nppdvjthqldpwncqszvftbrmjlhg")      == 6);  // first marker after character 6
  assert(GetMarkerPos("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg") == 10); // first marker after character 10
  assert(GetMarkerPos("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw")  == 11); // first marker after character 11

  std::cout << GetMarkerPos(line) << std::endl;

  // Part 2 - test data verification
  assert(GetMarkerPos("mjqjpqmgbljsphdztnvjfqwrcgsmlb"   , 14) == 19); // first marker after character 19
  assert(GetMarkerPos("bvwbjplbgvbhsrlpgdmjqwftvncz"     , 14) == 23); // first marker after character 23
  assert(GetMarkerPos("nppdvjthqldpwncqszvftbrmjlhg"     , 14) == 23); // first marker after character 23
  assert(GetMarkerPos("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 14) == 29); // first marker after character 29
  assert(GetMarkerPos("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw" , 14) == 26); // first marker after character 26

  std::cout << GetMarkerPos(line,14) << std::endl;

  return 0;
}

// Other
// * https://github.com/MichaelCG8/aoc2022/blob/main/06/lib.cpp
// * https://github.com/mkinkela1/advent-of-code-2022/blob/master/day-6/day6.cpp
// * https://topaz.github.io/paste/#XQAAAQBwBAAAAAAAAAARmknGRw8TogB3Oxzri2QTFyHNmsUnNApHN7ntt1+q1pz6rRjBp5Ofi0acEhV0wFcu83LC7P/dQT64FQQbCvAJdNPkhgcwlb5yGUHZvkilQ9kKY+0vun0hy869C0PmhRdopcPOLjQUInt+z2+RtuLUo5UwUU+NPLw3hRLqB7B8xg6IDWmchbudXr6xKebMtP9E59FGGnCemuGzZob2UPZtTYa2Gq0+O4ocWMEkUtgLY5ScTHFrwO8yrkxUOXdKtcAP4PQdbfLM3dm79pmjhhpF35X6iTqWgPPxmxVErH1zxTND6xUe51yIitFxK/EThFH7R5/c3GAmLWb7cxB3Zn2NHbK9zOGeKRs+DAjBxoYv7e0CZiUujldjbEjOG0q20KpLfClrtl/nBmEfCvzYHIFyQ9F9EPi91S+5FIJ9zWpyxDNWhymzG6eW4X7psxnm6DaAAnfuPUtX1s8cOocB43XzEBhCBX784g7FcQw5S4fDCBkIY4X43LgXm/ZmwGnp1WnTZ9reBbhJoJU9E4+WJBk5V4c0NWQuL5pS0ubnOHT8h7kiOYM+E/P846KTNYQLG+n4rZ5ep8TM/pU90RWPOtDjdilEgGZzHgcROzkZCse/TdveVs0vhBZARzfKkB7ousz/+TYf+Q==
//   https://topaz.github.io/paste/#XQAAAQBwBAAAAAAAAAARmknGRw8TogB3Oxzri2QTFyHNmsUnNApHN7ntt1+q1pz6rRjBp5Ofi0acEhV0wFcu83LC7P/dQT64FQQbCvAJdNPkhgcwlb5yGUHZvkilQ9kKY+0vun0hy869C0PmhRdopcPOLjQUInt+z2+RtuLUo5UwUU+NPLw3hRLqB7B8xg6IDWmchbudXr6xKebMtP9E59FGGnCemuGzZob2UPZtTYa2Gq0+O4ocWMEkUtgLY5ScTHFrwO8yrkxUOXdKtcAP4PQdbfLM3dm79pmjhhpF35X6iTqWgPPxmxVErH1zxTND6xUe51yIitFxK/EThFH7R5/c3GAmLWb7cxB3Zn2NHbK9zOGeKRs+DAjBxoYv7e0CZiUujldjbEjOG0q20KpLfClrtl/nBmEfCvzYHIFyQ9F9EPi91S+5FIJ9zWpyxDNWhymzG6eW4X7psxnm6DaAAnfuPUtX1s8cOocB43XzEBhCBX784g7FcQw5S4fDCBkIY4X43LgXm/ZmwGnp1WnTZ9reBbhJoJU9E4+WJBk5V4c0NWQuL5pS0ubnOHT8h7kiOYM+E/P846KTNYQLG+n4rZ5ep8TM/pU90RWPOtDjdilEgGZzHgcROzkZCse/TdveVs0vhBZARzfKkB7ousz/+TYf+Q==
// * https://pastebin.com/e3RH6nje
//   
//   int part_two()
//   {
//     std::ifstream reader("data.txt");
//     for( auto [i, x] : std::views::zip(std::views::iota(0),
//       std::views::transform(std::views::slide(std::string{std::istreambuf_iterator<char>(reader),
//           std::istreambuf_iterator<char>()}, 14), [](auto&& x) {
//           return std::unordered_set(x.begin(), x.end());
//         })
//     ) ) if( x.size() == 14 ) return i + 14;
//   
//     return -1;
//   }
