// /////////////////////////////////////////////////////////
//
// File:   clerdle/AppMode.cpp
// Author: Michael Foster
// Date:   2022.04.29
//
// This class processes command line arguments to determine
// the desired application mode.
//
// /////////////////////////////////////////////////////////
#include "AppMode.h"
//----------------//

#include <vector>
#include <string>

#include "StatsCollection.h"
#include "Puzzle.h"
#include "UX.h"

AppMode::AppMode(const std::vector<std::string> &args) : test_{0}, generate_{0}, stats_{0}, playerName_{}, quit_{0}
{
  if (args.size() && args.at(0)[0] == '-')
  {
    switch (args.at(0)[1])
    {
    case 't':
      this->test_ = true;
      if (int(args.size()) > 1)
        this->playerName_ = args.at(1);
      break;
    case 'g':
      if (int(args.size()) > 1)
      {
        try
        {
          this->generate_ = std::stoi(args.at(1));
        }
        catch (const std::invalid_argument &)
        {
          this->generate_ = -1;
        }
        catch (const std::out_of_range &)
        {
          this->generate_ = -1;
        }
      }
      else
        this->generate_ = -1;
      this->quit_ = true;
      break;
    case 's':
      this->stats_ = true;
      if (int(args.size()) > 1)
        this->playerName_ = args.at(1);
      break;
    }
  }
  else
  {
    if (args.size())
      this->playerName_ = args.at(0);
  }
}

bool AppMode::executeSimpleModes(Stats &stats)
{
  if (this->isGenerate())
  { // print a number of example puzzles
    this->quit_ = true;
    if (this->generate_ == -1)
    {
      UX::errorNoGenNumber();
      this->generate_ = 0;
    }

    for (int i = 0; i < this->generate_; i++)
      UX::prints(Puzzle().getAnswer(), '(', i + 1, ')');
  }
  else if (this->isStats())
  { // print user stats
    this->quit_ = true;
    if (this->playerName_.length())
    {
      std::vector<int> pstats{stats.getPlayerStats(this->playerName_, false)};
      if (!pstats.size())
        UX::errorUserNotFound();
      else
        UX::printHistogram(this->playerName_, pstats);
    }
    else
    {
      for (const auto &p : stats.getAllPlayerStats())
        UX::printHistogram(p.first, p.second);
    }
  }
  return this->quit_;
}
