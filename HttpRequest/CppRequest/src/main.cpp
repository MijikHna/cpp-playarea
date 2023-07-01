#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "cpr/cpr.h"
#include "json/json.h"

int main(void)
{

  // read from file
  std::ifstream datesFileRead("docs/Dates.txt");

  if (!datesFileRead)
  {
    std::cout << "Couldn't not open the file" << std::endl;
    return EXIT_FAILURE;
  }

  std::string lastCountry;
  std::string fileLine;

  while (datesFileRead)
  {
    std::getline(datesFileRead, fileLine);
    if (fileLine.size() > 1)
    {
      lastCountry = fileLine;
    }
  }

  std::cout << lastCountry << std::endl;

  datesFileRead.close();

  // send request
  cpr::Response r = cpr::Get(cpr::Url{"https://restcountries.com/v3.1/all"},
                             cpr::Header{{"Content-Type", "application/json"}, {"Accept", "application/json"}});

  Json::Reader jsonReader;
  Json::Value jsonValue;
  jsonReader.parse(r.text, jsonValue);

  u_int countriesLength = {jsonValue.size()};

  std::vector<std::string> countriesName = {};

  for (auto &&entry : jsonValue)
  {
    countriesName.push_back(entry["name"]["common"].asString());
  }

  std::srand(std::time(0));
  int randomIndex = std::rand() % countriesLength;

  std::string theCountry = countriesName.at(randomIndex);
  std::transform(theCountry.begin(), theCountry.end(), theCountry.begin(), ::tolower);

  // build new HTTP Message
  r = cpr::Get(cpr::Url{"https://restcountries.com/v3.1/name/" + theCountry},
               cpr::Header{{"Content-Type", "application/json"}, {"Accept", "application/json"}});

  jsonReader.parse(r.text, jsonValue);
  std::cout << jsonValue << std::endl;

  // add new line to file
  std::ofstream datesFileWrite{"docs/Dates.txt", std::ios::app};

  if (!datesFileWrite)
  {
    std::cout << "Couldn't open the file" << std::endl;
    return EXIT_FAILURE;
  }

  datesFileWrite << jsonValue[0]["name"]["common"].asString() << std::endl;

  datesFileWrite.close();

  return EXIT_SUCCESS;
}