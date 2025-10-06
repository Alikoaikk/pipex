<div align="center">

# 🔗 PIPEX

### _A 42 School project that recreates the shell pipe mechanism_

![C](https://img.shields.io/badge/language-C-blue.svg)
![42](https://img.shields.io/badge/school-42-black.svg)
![Norminette](https://img.shields.io/badge/norminette-passing-success.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

```
┌─────────────────────────────────────────────────────┐
│                                                     │
│   < infile  cmd1  |  cmd2  > outfile               │
│                                                     │
│   ╔═══════╗    ╔═════╗    ╔═══════╗               │
│   ║ FILE  ║───>║PIPE ║───>║ FILE  ║               │
│   ╚═══════╝    ╚═════╝    ╚═══════╝               │
│                                                     │
└─────────────────────────────────────────────────────┘
```

[Features](#-features) • [Installation](#-installation) • [Usage](#-usage) • [How it Works](#-how-it-works) • [Examples](#-examples)

---

</div>

## 📖 About

**Pipex** is a 42 School project that implements the behavior of the shell pipe operator (`|`). It handles input/output redirection and creates a pipeline between two commands, mimicking the shell behavior:

```bash
./pipex infile "cmd1" "cmd2" outfile
```

This executes the equivalent of:
```bash
< infile cmd1 | cmd2 > outfile
```

## ✨ Features

- **Process Management**: Uses `fork()` to create child processes
- **Inter-Process Communication**: Implements pipes for communication between processes
- **File Descriptor Manipulation**: Uses `dup2()` for I/O redirection
- **Command Execution**: Searches for executables in `PATH` environment variable
- **Error Handling**: Comprehensive error management for files, pipes, and commands
- **Memory Safe**: No memory leaks, proper cleanup of allocated resources
- **Norminette Compliant**: Follows 42's strict coding standards

## 🛠️ Installation

### Prerequisites

- GCC or Clang compiler
- Make
- Unix-like operating system (Linux, macOS)

### Build

```bash
# Clone the repository
git clone <repository-url> pipex
cd pipex

# Compile the project
make

# Clean object files
make clean

# Full clean (including executable)
make fclean

# Recompile
make re
```

## 🚀 Usage

### Basic Syntax

```bash
./pipex <infile> <cmd1> <cmd2> <outfile>
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `infile`  | Input file to read from |
| `cmd1`    | First command with its arguments |
| `cmd2`    | Second command with its arguments |
| `outfile` | Output file to write to |

### Exit Codes

- `0`: Success
- `1`: General errors (file access, pipe creation, etc.)
- `127`: Command not found

## 📚 Examples

### Example 1: Word Count Pipeline
```bash
./pipex infile "grep hello" "wc -l" outfile
# Equivalent to: < infile grep hello | wc -l > outfile
```

### Example 2: Text Processing
```bash
./pipex input.txt "cat" "grep pattern" output.txt
# Equivalent to: < input.txt cat | grep pattern > output.txt
```

### Example 3: Using ls and grep
```bash
./pipex /dev/null "ls -l" "grep pipex" result.txt
# Equivalent to: < /dev/null ls -l | grep pipex > result.txt
```

## ⚙️ How It Works

### Architecture Overview

```
┌─────────────────────────────────────────────────────────────┐
│                      PIPEX EXECUTION FLOW                   │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. Parse arguments and validate input                      │
│  2. Open input file                                         │
│  3. Create pipe                                             │
│                                                             │
│  ┌───────────────┐         ┌───────────────┐              │
│  │  CHILD 1      │         │  CHILD 2      │              │
│  │               │         │               │              │
│  │  • dup2(in,0) │         │  • dup2(p[0]) │              │
│  │  • dup2(p[1]) │         │  • dup2(out)  │              │
│  │  • exec cmd1  │────────>│  • exec cmd2  │              │
│  │               │  pipe   │               │              │
│  └───────────────┘         └───────────────┘              │
│                                                             │
│  4. Parent waits for both children                          │
│  5. Return exit status of cmd2                              │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Core Functions

#### `main()` - pipex.c:80
Entry point that orchestrates the entire process:
- Validates arguments
- Opens input/output files
- Creates pipe
- Forks two child processes
- Waits for completion

#### `child1()` - pipex.c:42
First child process:
- Redirects input from `infile`
- Redirects output to pipe write end
- Executes first command

#### `child2()` - pipex.c:53
Second child process:
- Redirects input from pipe read end
- Redirects output to `outfile`
- Executes second command

#### `get_cmd_path()` - utils.c:32
Finds the full path of a command:
- Searches through `PATH` environment variable
- Checks executable permissions
- Returns full path or NULL if not found

#### `exec_cmd()` - pipex.c:16
Executes a command:
- Splits command string into arguments
- Finds command path
- Calls `execve()` to replace process

## 📁 Project Structure

```
pipex/
├── pipex.c           # Main program logic
├── utils.c           # Helper functions
├── includes/
│   └── pipex.h       # Header file with structures and prototypes
├── libft/            # Custom library functions
│   ├── ft_split.c    # String splitting
│   ├── ft_strjoin.c  # String concatenation
│   └── ft_strncmp.c  # String comparison
├── Makefile          # Build configuration
└── README.md         # This file
```

## 🔍 Technical Details

### System Calls Used

| System Call | Purpose |
|-------------|---------|
| `fork()`    | Create child processes |
| `pipe()`    | Create inter-process communication channel |
| `dup2()`    | Duplicate file descriptors for I/O redirection |
| `execve()`  | Execute commands |
| `waitpid()` | Wait for child processes to complete |
| `access()`  | Check file permissions |
| `open()`    | Open files for reading/writing |

### Error Handling

The program handles various error cases:

- **Invalid arguments**: Exits with usage message
- **File not found**: Uses `/dev/null` for input, creates output file
- **Command not found**: Returns exit code 127
- **Pipe creation failure**: Exits with error message
- **Fork failure**: Handled with appropriate error messages

## 🧪 Testing

### Test Cases

```bash
# Test 1: Basic functionality
echo "hello world" > infile
./pipex infile "cat" "wc -w" outfile
cat outfile  # Should output: 2

# Test 2: Command not found
./pipex infile "invalid_cmd" "wc -l" outfile
# Should print "command not found" and exit with 127

# Test 3: Missing input file
./pipex nonexistent "cat" "wc -l" outfile
# Should print error but continue execution

# Test 4: Complex pipeline
./pipex infile "grep pattern" "sort" outfile
```

### Comparison with Shell

You can verify the behavior matches the shell:

```bash
# Using pipex
./pipex infile "grep hello" "wc -l" outfile1

# Using shell
< infile grep hello | wc -l > outfile2

# Compare
diff outfile1 outfile2
```

## 📝 Learning Objectives

This project teaches:

- **Process creation and management** with `fork()`
- **Inter-process communication** using pipes
- **File descriptor manipulation** with `dup2()`
- **Understanding the shell** pipeline mechanism
- **Memory management** in C
- **Error handling** in system calls
- **Environment variables** usage

## 🤝 Contributing

This is a 42 School project, so direct contributions are not accepted. However, feel free to:

- Report bugs
- Suggest improvements
- Use as reference for your own learning

## 👤 Author

**akoaik**
- 42 Intra: akoaik
- GitHub: [@yourusername](https://github.com/yourusername)

## 📄 License

This project is part of the 42 School curriculum and is provided as-is for educational purposes.

---

<div align="center">

### ⭐ If you found this helpful, consider giving it a star!

**Made with ☕ at 42 School**

</div>
