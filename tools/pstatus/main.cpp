#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <sstream>

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
  1 Usage/invalid args
  2 Cannot read /proc/<pid>/status (not found/ended/permission denied)

If you encounter any bugs or issues, please open a pull request or submit an issue on GitHub.
(https://github.com/valymndul/ubtools)
)";
}

static bool isNumber(const std::string& s){
    if(s.empty()) return false;
    for(char c:s){
        if(c<'0'||c>'9') return false;
    }
    return true;
}

static std::string rmTabs(const std::string& s){
    std::string out = "";
    for(char c : s){
        if(c == '\t'){
            out += " ";
        }
        else {
            out += c;
        }
    }
    return out;
}

static std::string trimLeft(const std::string& s){
    size_t i = 0;
    int len = s.length();
    while(i<len && (s[i]=='\t'||s[i]==' ')){
        i++;
    }

    return s.substr(i);
}

static std::string getOrNA(const std::unordered_map<std::string,std::string>& m,const std::string& key){
    auto it = m.find(key);
    if(it == m.end()){
        return "N/A";
    }
    if((*it).second.empty()){
        return "N/A";
    }

    return (*it).second;
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
        std::string value = trimLeft(line.substr(i+1));

        m[key] = value;
    }

    return 0;
}

static std::string jsonFix(const std::string& value){
    std::string out;
    for(char c:value){
        switch (c){
            case '"':
                out += "\\\"";
                break;

            case '\\':
                out += "\\\\";
                break;

            case '\n':
                out += "\\n";
                break;

            case '\r':
                out += "\\r";
                break;

            case '\t':
                out += "\\t";
                break;
            
            default:
                if((unsigned char)c < 0x20){
                    out += '?';
                } else {
                    out += c;
                }
                break;
        }
    }

    return out;
}

static long long parse(const std::string& s,bool& ok){
    ok = false;
    std::istringstream iss(s);
    long long x;
    if(!(iss>>x)){
        return 0;
    }
    ok = true;
    return x;
}

static void printJson(const std::unordered_map<std::string,std::string>& m,const std::string& pid){
    auto emitString = [&](const std::string& key,const std::string& value,bool col){
        std::cout<<"  \""<<key<<"\": \""<< jsonFix(value) << "\"";
        std::cout<< (col ? ",\n":"\n");
    };

    auto emitNumOrStr = [&](const std::string& key, const std::string& value, bool col){
        bool ok = false;
        long long x = parse(value,ok);
        std::cout<< "  \"" << key << "\": ";
        if(ok){
            std::cout << x << (col ? ",\n" : "\n");
        } else {
            std::cout<< " \"" << jsonFix(value) << "\"" << (col ? ",\n" : "\n");
        }
    };

    std::cout << "{\n";
    emitString("pid", pid, true);
    emitString("Name", getOrNA(m, "Name"), true);
    emitString("State" ,getOrNA(m, "State"), true);

    emitNumOrStr("Pid", getOrNA(m, "Pid"), true);
    emitNumOrStr("PPid", getOrNA(m, "PPid"), true);
    emitNumOrStr("Tgid", getOrNA(m, "Tgid"), true);
    emitNumOrStr("Threads", getOrNA(m, "Threads"), true);

    emitString("Uid", rmTabs(getOrNA(m, "Uid")), true);
    emitString("Gid", rmTabs(getOrNA(m, "Gid")), true);
    emitString("VmRSS", getOrNA(m, "VmRSS"), true);
    emitString("VmSize", getOrNA(m, "VmSize"), true);
    emitString("VmData", getOrNA(m, "VmData"), true);
    emitString("VmStk", getOrNA(m, "VmStk"), true);
    emitString("VmExe", getOrNA(m, "VmExe"), true);
    emitString("VmLib", getOrNA(m, "VmLib"), true);
    emitString("voluntary_ctxt_switches", getOrNA(m, "voluntary_ctxt_switches"), true);
    emitString("nonvoluntary_ctxt_switches", getOrNA(m, "nonvoluntary_ctxt_switches"), false);
    std::cout << "}\n";
}

static void printNormal(const std::unordered_map<std::string,std::string>& m, const std::string& pid, const bool& noHeader){
    if(!noHeader){
        std::cout<< "pstatus PID " << pid << "\n";
        std::cout<< "-----------------------------\n";
    }

    struct Row {
        const char* label;
        const char* key;
    };

    Row rows[] = {
        {"Name", "Name"},
        {"State", "State"},
        {"PID", "Pid"},
        {"PPID", "PPid"},
        {"Tgid", "Tgid"},
        {"Threads", "Threads"},
        {"Uid", "Uid"},
        {"Gid", "Gid"},
        {"VmRSS", "VmRSS"},
        {"VmSize", "VmSize"},
        {"VmData", "VmData"},
        {"VmStk", "VmStk"},
        {"VmExe", "VmExe"},
        {"VmLib", "VmLib"},
        {"VCS", "voluntary_ctxt_switches"},
        {"NVCS", "nonvoluntary_ctxt_switches"},
    };

    for(const auto& row:rows){
        std::cout << std::left << std::setw(24) << row.label << getOrNA(m,row.key) << "\n";
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
                std::cerr<<"Try: pstatus --help\n";
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
    if(code != 0){
        std::cerr<<"Error: failed to read /proc/"<<pid<<"/status\n";
        std::cerr<<"Cause: process ended | not found | permission denied\n";
        return 2;
    }

    if(json){
        printJson(m,pid);
    } else {
        printNormal(m,pid,noHeader);
    }

    return 0;
}