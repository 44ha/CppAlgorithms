# Algorithms in C++

Clean implementations of fundamental classical ciphers and lossless data compression algorithms in modern C++ (C++17). Each project is self-contained with runnable examples, edge-case handling, and round-trip verification in `main()`.

## Directory Overview

```
CppAlgorithms/
├── ciphers/
│   ├── caesar_cipher/
│   │   ├── caesar_cipher.cpp
│   │   └── README.md
│   ├── keyword_cipher/
│   │   ├── keyword_cipher.cpp
│   │   └── README.md
│   ├── columnar_transposition/
│   │   ├── columnar_transposition.cpp
│   │   └── README.md
│   └── README.md
├── compression/
│   ├── rle/
│   │   ├── rle.cpp
│   │   └── README.md
│   ├── lz77/
│   │   ├── lz77.cpp
│   │   └── README.md
│   └── README.md
└── README.md
```

### Categorized Projects

| Category | Directory | Algorithm | Description |
|----------|-----------|-----------|-------------|
| **Cryptography** | [ciphers/caesar_cipher/](ciphers/caesar_cipher/) | Caesar Cipher | Classical shift cipher supporting 26-letter alphabetic rotation and printable ASCII |
| **Cryptography** | [ciphers/keyword_cipher/](ciphers/keyword_cipher/) | Keyword Cipher | Polyalphabetic repeating-key substitution (Vigenère and modular ASCII) |
| **Cryptography** | [ciphers/columnar_transposition/](ciphers/columnar_transposition/) | Columnar Transposition | Permutation cipher writing into an $N$-column matrix and reading by column |
| **Compression** | [compression/rle/](compression/rle/) | Run-Length Encoding (RLE) | Lossless run-length compression with structured runs and delimited string encoding |
| **Compression** | [compression/lz77/](compression/lz77/) | LZ77 Sliding Window | Dictionary-based sliding window algorithm using `(offset, length, nextChar)` tokens |

## Building and Running

Compile any source file directly with a C++17 compiler:

```bash
# Example: Building Caesar Cipher
g++ -std=c++17 -O2 -Wall ciphers/caesar_cipher/caesar_cipher.cpp -o caesar_cipher
./caesar_cipher
```

On Windows:
```cmd
g++ -std=c++17 -O2 -Wall ciphers\caesar_cipher\caesar_cipher.cpp -o caesar_cipher.exe
caesar_cipher.exe
```

## Overview & Reference

### Classical Ciphers
- **Caesar Cipher**: Shifts characters by a fixed numeric key. Preserves case in alphabetic mode and wraps cleanly over the 26-character Latin alphabet or printable ASCII range.
- **Keyword Cipher**: Extends single-shift substitution by repeating a secret keyword to create position-dependent shifts across the message.
- **Columnar Transposition**: Transposes characters by placing plaintext into an $N$-column grid and extracting characters along columns. Implemented using standard dynamic vectors, avoiding non-standard Variable Length Arrays.

### Lossless Compression
- **RLE (Run-Length Encoding)**: Compresses repeated contiguous runs of identical characters. Best for data with low entropy and frequent repeated runs.
- **LZ77**: Replaces repetitive substrings with backward references `(offset, length, nextChar)` inside a sliding history window. Provides overlap-safe decompression.
