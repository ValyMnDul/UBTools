#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

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

static bool isNumber(std::string& s){
    if(s.empty()) return false;
    for(char c:s){
        if(c<'0'||c>'9') return false;
    }
    return true;
}

static int readStaticFile(std::string& pid,std::unordered_map<std::string,std::string>& m){
    std::string path = "/proc/"+pid+"/status";
    std::ifstream file(path);
    if(!file.is_open()){
        return 2;
    }

    std::string line;
    while(std::getline(file,line)){
        size_t i = line.find(':');
        if(i == std::string::npos){
            continue;
        }

        std::string key = line.substr(0,i);
        std::string value = line.substr(i+1);

        m[key] = value;
    }
}

int main(int argc,char* argv[]){

    bool json = false;
    bool noHeader = false;

    std::string pid;

    for(int i=1;i<argc;i++){
        std::string arg = argv[i];

        if(arg=="--help" || arg=="-h"){
            printHelp();
            return 0;
        } else if(arg == "--json" || arg == "-j"){
            json = true;
        } else if(arg == "--no-header" || arg == "-n"){
            noHeader = true;
        } else if(!arg.empty() && arg[0] == '-'){
            std::cerr<<"Unknown flag: "<< arg <<"\n";
            std::cerr<<"Try: pstatus --help\n";
            return 1;
        } else {
            if(!pid.empty()){
                std::cerr<<"Error: only one <pid> allowed\n";
                std::cerr<<"Try: pstatud --help\n";
                return 1;
            }
            pid = arg;
        }
    }

    if(pid.empty()){
        std::cerr<<"Error: missing <pid>\n";
        std::cerr<<"Try: pstatus --help\n";
        return 1;
    }

    if(!isNumber(pid)){
        std::cerr<<"Error: <pid> must be a number\n";
        std::cerr<<"Try: pstatus --help\n";
        return 1;
    }

    std::unordered_map<std::string,std::string> m;

    int code = readStaticFile(pid,m);

    return 0;
}