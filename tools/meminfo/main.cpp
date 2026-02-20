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

static bool readMeminfoFile(std::unordered_map<std::string,long long>& out){
    std::ifstream f("/proc/meminfo");
    if(!f.is_open()){
        return false;
    }

    std::string line;
    while(std::getline(f,line)){
        std::istringstream iss(line);

        std::string key;
        long long value;
        std::string unit;

        if(!(iss>>key>>value)){
            continue;
        }

        if(!key.empty() && key.back() == ':'){
            key.pop_back();
        }

        iss>>unit;

        out[key] = value;
    }

    return true;
}

static std::string getUnit(long long kB){
    double bytes = (double)kB * 1024.0;
    std::string units[]={"B","KB","MB","GB","TB"};
    int i=0;
    while(bytes>=1024.0 && i<4){
        bytes = bytes / 1024.0;
        i++;
    }

    std::ostringstream out;
    out<<std::fixed<<std::setprecision(2)<<bytes<<" "<<units[i];

    return out.str();
}

int main(){

    return 0;
}