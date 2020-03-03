#include <string>

const char * concatString(const char * a, const char * b) {
  std::string buf(a);
  return buf.append(b).c_str();
}