# Columnar Transposition Cipher (C++)

A modern C++ implementation of the Columnar Transposition Cipher using standard dynamic buffers (replacing non-standard variable-length arrays).

## Features

- **Standard C++ Conformance**: Uses safe `std::vector<char>` buffers rather than compiler-specific C99 Variable Length Arrays (`char grid[rows][cols]`).
- **Configurable Matrix Width**: Set arbitrary number of columns (the key).
- **Configurable Padding**: Specify the character used to pad uneven trailing rows, with optional padding stripping on decryption.
- **Input Validation**: Rejects invalid column keys ($\le 0$) and handles empty strings gracefully.

## How it works

1. Let $N$ be the number of columns and $L$ be the plaintext length.
2. The number of rows is calculated as $R = \lceil L / N \rceil$.
3. **Encryption**: Characters are placed horizontally into an $R \times N$ matrix. The ciphertext is formed by reading columns vertically from left to right.
4. **Decryption**: Ciphertext characters populate the matrix column by column, and the original message is recovered by reading row by row.

## Building and Running

```bash
g++ -std=c++17 -O2 -o columnar_transposition columnar_transposition.cpp
./columnar_transposition
```

On Windows:
```cmd
g++ -std=c++17 -O2 -o columnar_transposition.exe columnar_transposition.cpp
columnar_transposition.exe
```
