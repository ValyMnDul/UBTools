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

static void printRow(const std::unordered_map<std::string,long long>& m){
    auto get = [&](const std::string& k) -> long long {
        auto it = m.find(k);
        return (it == m.end()) ? -1 : (*it).second;
    };

    std::cout<<"MemTotal:     "<<get("MemTotal")<<" KB\n";
    std::cout<<"MemFree:      "<<get("MemFree")<<" KB\n";
    std::cout<<"MemAvailable: "<<get("MemAvailable")<<" KB\n";
    std::cout<<"Buffers:      "<<get("Buffers")<<" KB\n";
    std::cout<<"Cached:       "<<get("Cached")<<" KB\n";
    std::cout<<"SwapTotal:    "<<get("SwapTotal")<<" KB\n";
    std::cout<<"SwapFree:     "<<get("SwapFree")<<" KB\n";
}

static void printHuman(const std::unordered_map<std::string,long long>& m){
    auto get = [&](const std::string& k) -> long long {
        auto it = m.find(k);
        return (it == m.end()) ? -1 : (*it).second;
    };

    std::cout<<"MemTotal:     "<<getUnit(get("MemTotal"))<<"\n";
    std::cout<<"MemFree:      "<<getUnit(get("MemFree"))<<"\n";
    std::cout<<"MemAvailable: "<<getUnit(get("MemAvailable"))<<"\n";
    std::cout<<"Buffers:      "<<getUnit(get("Buffers"))<<"\n";
    std::cout<<"Cached:       "<<getUnit(get("Cached"))<<"\n";
    std::cout<<"SwapTotal:    "<<getUnit(get("SwapTotal"))<<"\n";
    std::cout<<"SwapFree:     "<<getUnit(get("SwapFree"))<<"\n";
}

static void printJson(const std::unordered_map<std::string,long long>& m){
    auto get = [&](const std::string& k) -> long long {
        auto it = m.find(k);
        return (it==m.end()) ? -1 : (*it).second;
    };

    std::cout<<"{\n";
    std::cout<<"\"MemTotal_KB\": "<<get("MemTotal")<<",\n";
    std::cout<<"\"MemFree_KB\": "<<get("MemFree")<<",\n";
    std::cout<<"\"MemAvailable_KB\": "<<get("MemAvailable")<<",\n";
    std::cout<<"\"Buffers_KB\": "<<get("Buffers")<<",\n";
    std::cout<<"\"Cached_KB\": "<<get("Cached")<<",\n";
    std::cout<<"\"SwapTotal_KB\": "<<get("SwapTotal")<<",\n";
    std::cout<<"\"SwapFree_KB\": "<<get("SwapFree")<<"\n";
    std::cout<<"}\n";
}

int main(){
    
    return 0;
}