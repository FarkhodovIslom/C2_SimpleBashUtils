# Simple Bash Utils

Development of Bash text utilities: cat, grep.

## Overview

This project implements two classic Unix command-line utilities in C:
- **s21_cat**: A reimplementation of the `cat` utility for concatenating and displaying files
- **s21_grep**: A reimplementation of the `grep` utility for searching text using regular expressions

Both utilities are developed following the principles of structured programming and follow POSIX compliance where applicable.

## Project Structure

```
C2_SimpleBashUtils/
├── src/
│   ├── cat/
│   │   ├── s21_cat.c        # Main cat implementation
│   │   ├── s21_cat.h        # Cat header file
│   │   ├── Makefile         # Build configuration for cat
│   │   ├── test_cat.sh      # Cat test script
│   │   └── test.txt         # Test data
│   └── grep/
│       ├── s21_grep.c       # Main grep implementation
│       ├── s21_grep.h       # Grep header file
│       ├── Makefile         # Build configuration for grep
│       ├── test_grep.sh     # Grep test script
│       ├── test.txt         # Test data
│       └── patterns.txt     # Test patterns
├── materials/
│   ├── build/               # Docker build configuration
│   ├── linters/             # Code style configuration
│   ├── instructions_for_testing.md
│   └── topics-list.md
├── data-samples/            # Sample data files
└── code-samples/            # Code examples
```

## s21_cat

A reimplementation of the Unix `cat` utility that reads files sequentially and writes them to standard output.

### Supported Flags

| Flag | Description |
|------|-------------|
| `-b` (--number-nonblank) | Number non-empty output lines |
| `-e` | Display `$` at the end of each line, show non-printing characters |
| `-E` (--show-ends) | Display `$` at the end of each line |
| `-n` (--number) | Number all output lines |
| `-s` (--squeeze-blank) | Squeeze multiple adjacent empty lines |
| `-t` | Display tabs as `^I`, show non-printing characters |
| `-T` (--show-tabs) | Display tabs as `^I` |
| `-v` (--show-nonprinting) | Show non-printing characters |

### Building s21_cat

```bash
cd src/cat
make
```

### Running s21_cat

```bash
# Display a single file
./s21_cat file.txt

# Display multiple files
./s21_cat file1.txt file2.txt

# Number all lines
./s21_cat -n file.txt

# Number non-blank lines only
./s21_cat -b file.txt

# Show line endings with $
./s21_cat -E file.txt

# Squeeze multiple blank lines
./s21_cat -s file.txt

# Read from stdin
cat file.txt | ./s21_cat
```

## s21_grep

A reimplementation of the Unix `grep` utility that searches input files for lines matching a pattern.

### Supported Flags

| Flag | Description |
|------|-------------|
| `-e` | Specify pattern (can be used multiple times) |
| `-i` (--ignore-case) | Ignore case distinctions |
| `-v` (--invert-match) | Invert the sense of matching |
| `-c` (--count) | Output only a count of matching lines |
| `-l` (--files-with-matches) | Output only names of files with matches |
| `-n` (--line-number) | Prefix output with line numbers |
| `-h` (--no-filename) | Suppress prefixing filenames on output |
| `-s` (--no-messages) | Suppress error messages |
| `-f` (--file) | Obtain patterns from a file |
| `-o` (--only-matching) | Show only matching parts of lines |

### Building s21_grep

```bash
cd src/grep
make
```

### Running s21_grep

```bash
# Search for a pattern in a file
./s21_grep "pattern" file.txt

# Search case-insensitively
./s21_grep -i "pattern" file.txt

# Show line numbers
./s21_grep -n "pattern" file.txt

# Invert match (show non-matching lines)
./s21_grep -v "pattern" file.txt

# Count matching lines
./s21_grep -c "pattern" file.txt

# Get only filenames with matches
./s21_grep -l "pattern" file.txt

# Use patterns from file
./s21_grep -f patterns.txt file.txt

# Search in multiple files
./s21_grep "pattern" file1.txt file2.txt

# Show only matching parts
./s21_grep -o "pattern" file.txt
```

## Building All Utilities

To build both utilities:

```bash
# Build cat
cd src/cat && make

# Build grep
cd src/grep && make
```

## Testing

### Style Tests

The project uses clang-format for code style checking. Style configuration is in `materials/linters/.clang-format`.

```bash
# Copy style config to src directory
cp materials/linters/.clang-format src/

# Check style for a file
clang-format -n src/cat/s21_cat.c
clang-format -n src/grep/s21_grep.c
```

### Unit Tests

Each utility has a test script:

```bash
# Test cat
cd src/cat && ./test_cat.sh

# Test grep
cd src/grep && ./test_grep.sh
```

### Memory Tests

On macOS, use `leaks` to check for memory leaks:

```bash
leaks -atExit -- ./s21_cat file.txt | grep LEAK:
```

On Linux, use `valgrind`:

```bash
valgrind --tool=memcheck --leak-check=yes ./s21_cat file.txt
```

### Docker Build Test

Test the build in a Docker environment:

```bash
cd materials/build && ./run.sh
```

## Implementation Details

### Key Concepts Covered

- Command-line argument parsing using `getopt_long()`
- Regular expression matching using POSIX regex library
- File I/O operations
- Dynamic memory management
- Error handling
- Code decomposition and modular design

### Technical Specifications

- **Language**: C (C11 standard)
- **Compiler Flags**: `-Wall -Wextra -Werror`
- **Build System**: Make

## License

This project is developed for educational purposes as part of the School 21 curriculum.

## Contributing

This is an educational project, but if you'd like to contribute, feel free to submit pull requests or issues.

## References

- [GNU coreutils cat](https://www.gnu.org/software/coreutils/manual/html_node/cat-invocation.html)
- [GNU grep](https://www.gnu.org/software/grep/manual/grep.html)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
