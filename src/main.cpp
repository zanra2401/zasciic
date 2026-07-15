#include <vector>
#include "commandCenter.hpp"

int main(int argc, const char *argv[]) {
  CommandCenter commandCenter = CommandCenter(argc, argv);
  commandCenter.parseArguments();
  commandCenter.processCommand();
  return 0;
}
