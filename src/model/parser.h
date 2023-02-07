#ifndef PARSER_H_
#define PARSER_H_

#include <string>

#include "data.h"

using std::string;

namespace s21 {

class Parser {
 private:
  static int countLines(const Data& data);
  static void addVertice(Data* data, const string& line);
  static void addFacet(Data* data, const string& line);

  static void fillLines(Data* data);

 public:
  // Паттерн Factory
  static Data* obtainData(const string& file_path);
};

}  //  namespace s21

#endif  // PARSER_H_
