// Release: cl /EHsc /std:c++20 day2.cpp
// Debug  : cl /EHsc /std:c++20 /Zi /DDEBUG day2.cpp
#include <fstream>       // For std::ifstream
#include <iostream>      // For std::cout
#include <vector>        // For std::vector
#include <string>        // For std::string
#include <map>           // For std::map<>
#include <cassert>       // For assert()

int main()
{
  std::ifstream fin("input.txt");

  using Score = int;

  const Score WinScore{6};
  const Score LostScore{0};
  const Score DrawScore{3};

  //                A     B      C
  //                X     Y      Z
  //                0     1      2
  enum class Hand { Rock, Paper, Scissors };

  using Play = std::pair<Hand, Hand>;

  // Get play score given an opponent hand and your play hand.
  auto GetPlayScore = [](Hand ophand,Hand playhand)
  {
    // Play Scores
    static const std::map<Play, Score> playscores = {
      //  Opponent      , Me            , Score
      { { Hand::Rock    , Hand::Rock    }, DrawScore },
      { { Hand::Rock    , Hand::Paper   }, WinScore },
      { { Hand::Rock    , Hand::Scissors}, LostScore },
      { { Hand::Paper   , Hand::Rock    }, LostScore },
      { { Hand::Paper   , Hand::Paper   }, DrawScore },
      { { Hand::Paper   , Hand::Scissors}, WinScore },
      { { Hand::Scissors, Hand::Rock    }, WinScore },
      { { Hand::Scissors, Hand::Paper   }, LostScore },
      { { Hand::Scissors, Hand::Scissors}, DrawScore }
    };

    auto it = playscores.find(std::make_pair(ophand,playhand));
    if( it != std::end(playscores) )
      return it->second;

    return 0;
  };

  // Get the shape score given the hand.
  auto GetShapeScore = [](const Hand& hand)
  {
    switch( hand )
    {
      case Hand::Rock: return 1;
      case Hand::Paper: return 2;
      case Hand::Scissors: return 3;
        //default:
          //assert(false);
    }
    return 0;
  };

  // Part 2:          X     Y     Z
  // X means you need to lose, Y means you need to end the round in a draw, and Z means you need to win.
  enum class NeedTo { Lose, Draw, Win };

  // Lookup the needed hand given opponent hand and need to (win,lose,draw)
  auto GetHandNeed = [](Hand ophand, NeedTo needto)
  {
    static const std::map<std::pair<Hand, NeedTo>, Hand> handneeds = {
      //  Opponent      , NeedTo         , HandNeed
      { { Hand::Rock    , NeedTo::Lose    }, Hand::Scissors },
      { { Hand::Rock    , NeedTo::Draw    }, Hand::Rock     },
      { { Hand::Rock    , NeedTo::Win     }, Hand::Paper    },
      { { Hand::Paper   , NeedTo::Lose    }, Hand::Rock     },
      { { Hand::Paper   , NeedTo::Draw    }, Hand::Paper    },
      { { Hand::Paper   , NeedTo::Win     }, Hand::Scissors },
      { { Hand::Scissors, NeedTo::Lose    }, Hand::Paper    },
      { { Hand::Scissors, NeedTo::Draw    }, Hand::Scissors },
      { { Hand::Scissors, NeedTo::Win     }, Hand::Rock     }
    };

    auto it = handneeds.find(std::make_pair(ophand, needto));
    if( it != std::end(handneeds) )
      return it->second;

    assert(false);
    return Hand::Rock;
  };


  //std::vector<Play> plays;

  Score mytotalscore{0};
  Score totalneedscore{0};

  while( !fin.eof() )
  {
    char opponentch, dummy, inch;
    fin.get(opponentch);
    fin.get(dummy); // eat ' '
    fin.get(inch);
    fin.get(dummy); // eat '\n'

    if( !fin.good() )
      break;

    const Hand ophand = static_cast<Hand>(opponentch-'A');

    // Part 1
    const Hand myhand = static_cast<Hand>(inch-'X');
    mytotalscore += GetPlayScore(ophand, myhand)+GetShapeScore(myhand);

    // Part 2
    const NeedTo needto = static_cast<NeedTo>(inch-'X');
    const auto needhand = GetHandNeed(ophand, needto);

    totalneedscore += GetPlayScore(ophand, needhand)+GetShapeScore(needhand);

    // If you want to collect the part1 "plays"
    //plays.push_back(std::make_pair(ophand,myhand));
  }

  // assert(plays.size()==2500); // Verify expected number of plays.

  std::cout << mytotalscore << "\n";   // With my input: 14163
  std::cout << totalneedscore << "\n"; // With my input: 12091 

  return 0;
}

// Others:
// * https://git.sr.ht/~bogdanb/aoc/tree/master/item/source/2022/02/solution.cpp // Elegant solution using a matrix (Eigen) taking the predefined results a step further.
// * https://old.reddit.com/r/adventofcode/comments/zac2v2/2022_day_2_solutions/iylmwb8/
// * https://github.com/MichaelCG8/aoc2022/blob/main/02/lib.cpp
