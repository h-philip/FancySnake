#include "ConfigParser.h"

std::string ConfigParser::delimiter = "=";
std::string ConfigParser::comment = "#";

std::map<std::string, std::string> ConfigParser::parse(std::string file) {
  std::map<std::string, std::string> map;

  std::ifstream infile(file);
  if (infile.fail()) return map;

  std::string line;
  while (std::getline(infile, line)) {
    // Skip lines starting with comment string or ' ' or is empty
    if (line.rfind(comment, 0) == 0 || line.rfind(" ", 0) == 0 || line.length() == 0) continue;

    size_t index = line.find(delimiter);
    std::string key = line.substr(0, index),
                value = line.substr(index + 1, line.size() - 1);
#ifdef _DEBUG
    std::cout << key << " - " << value << std::endl;
#endif
    map.insert(std::pair<std::string, std::string>(key, value));
  }

  return map;
}
