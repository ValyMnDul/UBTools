# UBTools

## A toolkit for developers and system administrators.

This project includes a collection of terminal tools for **Debian-based Linux** distributions.

It is designed to be simple, lightweight, and practical. Each tool is designed to help with system inspection, process analysis, resource monitoring, and troubleshooting.

## Tools

### 1. pstatus
Inspect detailed information about a running process using its PID.

pstatus reads data from /proc/&lt;pid>/status and displays structured process information, including:

- Name – Process name
- State – Current process state (e.g., running, sleeping, zombie)
- PID – Process ID
- PPID – Parent process ID
- Tgid – Thread group ID
- Threads – Number of threads used by the process
- Uid / Gid – User and group IDs
- VmRSS – Resident memory usage (physical RAM used)
- VmSize – Total virtual memory size
- VmData – Data segment size
- VmStk – Stack size
- VmExe – Executable memory size
- VmLib – Shared library memory usage
- VCS – Voluntary context switches
- NVCS – Non-voluntary context switches

### 2. meminfo
Display system memory statistics using data from /proc/meminfo.

It includes information such as:

- MemTotal – Total physical memory
- MemFree – Free memory
- MemAvailable – Estimated memory available for new applications
- Buffers – Memory used for kernel buffers
- Cached – Cached file data
- SwapTotal – Total swap space
- SwapFree – Free swap space

## How to Use

 Clone the repository:
```bash 
git clone https://github.com/valymndul/UBTools.git
``` 
Navigate to the tool directory:
```bash
cd UBTools/tools/<tool_name>
```
Make the executable:
```bash
g++ -o <tool_name> <tool_name>.cpp
```
Run the tool:
```bash
./<tool_name> <arguments> [--help]
``` 

## Find bugs and contribute
If you find any bugs or have suggestions for improvements, please feel free to open an issue or submit a pull request. Contributions are welcome!
