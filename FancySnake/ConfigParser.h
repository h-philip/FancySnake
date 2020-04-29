#pragma once
#include <fstream>
#include <string>
#include <map>
#include <iostream>

class ConfigParser {
 public:
  static std::map<std::string, std::string> parse(std::string file);

  static std::string delimiter;
  static std::string comment;
};
