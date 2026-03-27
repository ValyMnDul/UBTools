# UBTools

## A toolkit for developers and system administrators

This project includes a collection of terminal tools for **Debian-based Linux** distributions.

It is designed to be simple, lightweight, and practical. Each tool is designed to help with system inspection, process analysis, resource monitoring, and troubleshooting.

## 1. pstatus

Inspect detailed information about a running process using its PID.

### 1.1 Usage

| Command                                         | Description     |
|--------                                         | ------------    |
| `pstatus <pid> [--json] [--no-header] [--help]` | Run the program |

---

### 1.2 Arguments

| Argument | Description         |
|----------|------------         |
| `<pid>`  | Process ID (number) |

---

### 1.3 Flags

| Flag | Description |
| ------ | ------------ |
| `-j, --json` | Output as JSON (for parsing) |
| `-n, --no-header` | No title/header lines |
| `-h, --help` | Show this message |

---

### 1.4 Exit Codes

| Code | Meaning |
| ------ | -------- |
| `0` | Success |
| `1` | Usage error / invalid arguments |
| `2` | Cannot read `/proc/<pid>/status` (not found / process ended / permission denied) |

---

### 1.5 Data

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

## 2. meminfo

Display system memory statistics.

### 2.1 Usage

| Command                                   | Description     |
|--------                                   |------------     |
| `meminfo [--json] [--no-header] [--help]` | Run the program |

---

### 2.2 Flags

| Flag | Description |
| ------ | ------------ |
| `-j, --json` | Output as JSON (for parsing) |
| `-n, --no-header` | No title/header lines |
| `-h, --help` | Show this message |

---

### 2.3 Exit Codes

| Code | Meaning |
| ------ | -------- |
| `0` | Success |
| `1` | Usage error / invalid arguments |
| `2` | Cannot read `/proc/meminfo` (permission denied / unavailable) |

---

### 2.4 Data

meminfo reads data from `/proc/meminfo` and displays structured memory information, including:

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

### OR

Download the binary from the [releases page](https://github.com/valymndul/UBTools/releases)

## Find bugs and contribute

If you find any bugs or have suggestions for improvements, please feel free to open an issue or submit a pull request. Contributions are welcome!

## Open Source

UBTools is licensed under the [MIT License](LICENSE.md)
