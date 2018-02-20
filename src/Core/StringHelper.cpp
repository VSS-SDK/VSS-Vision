//
// Created by johnathan on 04/02/18.
//

#include "StringHelper.h"

std::vector<std::string> explode(std::string const & s, char delim)
{
  std::vector<std::string> result;
  std::istringstream iss(s);

  for (std::string token; std::getline(iss, token, delim); )
  {
    result.push_back(std::move(token));
  }

  return result;
}