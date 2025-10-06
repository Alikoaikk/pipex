<div align="center">

![Pipex Banner](https://via.placeholder.com/800x200/0D1117/58A6FF?text=PIPEX)

### Recreation of shell pipe mechanism | 42 Project

</div>

---

## 🚀 Usage

```bash
./pipex infile "cmd1" "cmd2" outfile
```

**Equivalent to:**
```bash
< infile cmd1 | cmd2 > outfile
```

### Examples

```bash
./pipex infile "grep hello" "wc -l" outfile
./pipex input.txt "cat" "grep pattern" output.txt
./pipex file "ls -l" "wc -l" result.txt
```

## 🔧 Installation

```bash
make
```

## ⚙️ How It Works

1. **Fork** two child processes
2. Create a **pipe** between them
3. **Redirect** file descriptors:
   - Child 1: `infile` → `cmd1` → pipe
   - Child 2: pipe → `cmd2` → `outfile`
4. **Execute** commands using `execve()`

```
┌─────────┐    ┌─────────┐    ┌─────────┐    ┌──────────┐
│  infile │───>│  cmd1   │───>│  pipe   │───>│   cmd2   │───>│ outfile  │
└─────────┘    └─────────┘    └─────────┘    └──────────┘
```

---

<div align="center">

Made at 42 School

</div>
