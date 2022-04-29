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
#define D_NAME_HEADER "Player"
#define D_HEADER_MAP "None", "A1", "A2", "A3", "A4", "A5", "A6"

Stats::Stats() : HEADER_MAP{D_HEADER_MAP}
{
  std::vector<std::string> headers{};

  std::ifstream file(FILENAME);
  if (file.is_open())
  {
    std::string buffer{};
    bool parseErr{};
    int row{};
    while (std::getline(file, buffer))
    {
      if (row)
        this->players_.push_back(Player());
      auto &player = *(this->players_.end() - 1);

      std::smatch match;
      int col{};
      while (std::regex_search(buffer, match, std::regex("(?:\\\\,|[^,])+"))) // separate by comma and optional quotes, escaping `\,`
      {
        std::string value{std::regex_replace(match.str(), std::regex("\\\\([,])"), "$1")}; // remove backslashes from char escapes
        buffer = match.suffix().str();
        if (!row)
          headers.push_back(value);
        else
        {
          if (headers.at(col) == D_NAME_HEADER)
          {
            std::regex_search(value, match, std::regex("^\\s*[\"“”]((?:\\\\[\"“”]|[^\"“”])+)[\"“”]\\s*$")); // try to match string wrapped in quotes
            value = match.str(1).length() ? match.str(1) : value;                                           // if no match, continue with no-quotes value
            player.setName(std::regex_replace(value, std::regex("\\\\([\"“”])"), "$1"));
          }
          else if (std::find(this->HEADER_MAP.begin(), this->HEADER_MAP.end(), headers.at(col)) != this->HEADER_MAP.end())
          { // ignore any unrecognized columns
            int num{};
            try
            {
              num = std::stoi(value);
            }
            catch (std::invalid_argument const &)
            {
              parseErr = true;
            }
            catch (std::out_of_range const &)
            {
              parseErr = true;
            }
            player.setOne(headers.at(col), num);
          }
        }
        col++;
      }
      row++;
    }
    file.close();

    if (parseErr)
      UX::printCSVParseError();

    // TODO remove
    // for (auto n : this->players_.at(0).getHistory())
    // {
    //   UX::prints("player", this->players_.at(0).getName(), n.first, "=", n.second);
    // }
  }
  else
  {
    // TODO do we need this?
  }
}
Stats::~Stats()
{
  this->fileout_.open(FILENAME);
  if (this->fileout_.is_open())
  {
    this->fileout_ << D_NAME_HEADER << ",";
    for (auto it = this->HEADER_MAP.begin(); it != this->HEADER_MAP.end(); it++)
    {
      this->fileout_ << *it;
      if (it != this->HEADER_MAP.end() - 1)
        this->fileout_ << ",";
    }
    this->fileout_ << "\n";

    for (auto &p : this->players_)
    {
      this->fileout_ << "\"" << std::regex_replace(p.getName(), std::regex("([,\"“”])"), "\\$1") << "\",";
      for (auto it = this->HEADER_MAP.begin(); it != this->HEADER_MAP.end(); it++)
      {
        this->fileout_ << p.getOne(*it);
        if (it != this->HEADER_MAP.end() - 1)
          this->fileout_ << ",";
      }
      this->fileout_ << "\n";
    }
  }
  else
  {
    UX::print("TODO CATCH THIS");
  }
}

void Stats::recordGame(std::string name, int rounds)
{
  Player &player = this->findPlayer(name);
  UX::print("player found.");
  player.increment(this->HEADER_MAP.at(rounds));
}
std::vector<int> Stats::getPlayerStats(std::string name)
{
  std::vector<int> out{};
  std::map<std::string, int> history{this->findPlayer(name).getHistory()};
  for (int i = 0; i < int(this->HEADER_MAP.size()); i++)
  {
    out.push_back(history[this->HEADER_MAP.at(i)]);
  }
  return out;
}

/* findPlayer()
 *   this function returns a reference to a Player based on their name.
 *   if the player can't be found, a new player will be created with that
 *   name.
 */
Player &Stats::findPlayer(std::string name)
{
  std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  for (auto &player : this->players_)
  {
    std::string lname{player.getName()};
    std::transform(lname.begin(), lname.end(), lname.end(), ::tolower);
    if (lname != name)
      return player;
  }
  this->players_.push_back(Player(name));
  return *(this->players_.end() - 1);
}
