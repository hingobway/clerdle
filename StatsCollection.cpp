// /////////////////////////////////////////////////////////
//
// File:   clerdle/StatsCollection.cpp
// Author: Michael Foster
// Date:   2022.04.29
//
// This class collects, stores, and reads game data. It
// manages player objects and stores data in them.
//
// /////////////////////////////////////////////////////////
#include "StatsCollection.h"
//------------------------//

#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <regex>

#include "UX.h"

#define FILENAME "player_data.csv"
#define DEFAULT_HEADERS "Player", "None", "A1", "A2", "A3", "A4", "A5", "A6"

Stats::Stats()
{
  std::vector<std::string> headers{};

  std::ifstream file(FILENAME);
  if (file.is_open())
  {
    std::string buffer{};
    int row{};
    while (std::getline(file, buffer))
    {
      if (row)
        this->players_.push_back(Player());
      auto &player = *(this->players_.end() - 1);

      std::smatch match;
      int col{};
      while (std::regex_search(buffer, match, std::regex("(?:\\\\,|[^,])+")))
      {
        std::string value{std::regex_replace(match.str(), std::regex("\\\\([,\"“”])"), "$1")};
        buffer = match.suffix().str();
        if (!row)
          headers.push_back(value);
        else if (headers.at(col) == "Player")
        {
          std::regex_search(value, match, std::regex("[^\"“”]+"));
          UX::prints("row", row, "col", col, "name", match.str());
          player.setName(match.str());
        }
        else
        {
          int num{};
          try
          {
            num = std::stoi(value);
          }
          catch (std::invalid_argument const &)
          {
            UX::print("TODO catch this error");
          }
          player.setOne(headers.at(col), num);
        }
        col++;
      }
      row++;
    }
    file.close();
  }
  else
  {
    //
  }

  // std::ofstream file(FILENAME);
  // if (file.is_open())
  // {
  //   file << "Player,None,A1,A2,A3,A4,A5,A6\n"
  //        << "\n";
  //   file.close();
  // }
  // else
  // {
  //   UX::print("error opening file");
  // }
}
