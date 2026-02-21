#include <iostream>
#include <fstream>
#include <string>


static void printHelp(){
    std::cout<<
R"(-- pstatus reads /proc/<pid>/status --

Usage:
  pstatus <pid> [--json] [--no-header] [--help]

Args:
  <pid>            Process id (number)

Flags:
  -j, --json       Output as JSON (for parsing)
  -n, --no-header  No title/header lines
  -h, --help       Show this message

Exit codes:
  0 Success
  1 Usage/incalid args
  2 Cannot read /proc/<pid>/status (not found/ended)
  3 Permission denied

If you encounter any bugs or issues, please open a pull request or submit an issue on GitHub.
(https://github.com/valymndul/ubtools)
)";
}

int main(){

    return 0;
}