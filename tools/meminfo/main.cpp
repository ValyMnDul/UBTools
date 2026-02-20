#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <sstream>

static void printHelp(){

    std::cout<<
R"(-- meminfo reads /proc/meminfo --

Usage:
  meminfo [--raw] [--human] [--json] [--help]

Flags:
  --raw     display values in kB (as they appear in /proc/meminfo)
  --human   display in MB/GB (easier to read)
  --json    output as JSON (for parsing)
  --help    show this message

If you encounter any bugs or issues, please open a pull request or submit an issue on GitHub.
(https://github.com/valymndul/ubtools)
)";
}

int main(){

    return 0;
}