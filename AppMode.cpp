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
//-------------//

#include <vector>
#include <string>

AppMode::AppMode(const std::vector<std::string> &args) : test_{0}, generate_{0}, playerName_{}
{
  if (args.size() && args.at(0)[0] == '-')
  {
    switch (args.at(0)[1])
    {
    case 't':
    {
      this->test_ = true;
      if (int(args.size()) > 1)
        this->playerName_ = args.at(1);
    }
    break;
    case 'g':
    {
      if (int(args.size()) > 1)
      {
        this->generate_ = std::stoi(args.at(1));
      }
    }
    break;
    case 's':
    {
      // TODO support both full stats output and single player stats output
    }
    break;
    }
  }
  else
  {
    if (args.size())
      this->playerName_ = args.at(0);
  }
}
