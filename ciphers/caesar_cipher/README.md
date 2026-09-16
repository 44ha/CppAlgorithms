# Caesar Cipher (C++)

A robust, modern C++ implementation of the classical Caesar shift cipher supporting both standard 26-letter alphabetic rotation and full printable ASCII substitution.

## Features

- **Classical Alphabetic Mode**: Encrypts `A-Z` and `a-z` with wrap-around while preserving character case, spaces, digits, and punctuation.
- **Printable ASCII Mode**: Shifts all 95 printable ASCII characters (`[32, 126]`) with clean wrap-around.
- **Negative and Arbitrary Shifts**: Handles any integer shift value (positive, negative, and multiples of the alphabet length) using normalized modulo arithmetic.
- **Modern C++ API**: Employs `std::string_view` for efficient read-only string parameter passing and class encapsulation.

## How it works

- **Alphabet Shift**:
  - Upper: `c' = 'A' + (c - 'A' + shift) mod 26`
  - Lower: `c' = 'a' + (c - 'a' + shift) mod 26`
- **Decryption**: Inverts the shift: `decrypt(text, shift) == encrypt(text, -shift)`.

## Building and Running

```bash
g++ -std=c++17 -O2 -o caesar_cipher caesar_cipher.cpp
./caesar_cipher
```

On Windows:
```cmd
g++ -std=c++17 -O2 -o caesar_cipher.exe caesar_cipher.cpp
caesar_cipher.exe
```
