# Keyword Cipher (C++)

A modern C++ implementation of polyalphabetic repeating-key substitution ciphers (Vigenère and modular ASCII).

## Features

- **Classical Alphabetic Mode**: Encrypts alphabetic letters `[A-Za-z]` using modular shift derived from a repeating keyword, preserving non-alphabetic characters.
- **7-Bit ASCII Mode**: Modular arithmetic over ASCII values `(message[i] + key[i]) % 128` for binary-safe reversible mapping.
- **Robust Error Handling**: Enforces non-empty keywords and validates string lengths.
- **Performance**: Zero heap reallocations using `reserve()` and `std::string_view`.

## How it works

1. Given a keyword of length $K$, character $i$ in the message is transformed by $key[i \pmod K]$.
2. In classical alphabetic mode, $shift = key[i] - 'A'$, and $c' = 'A' + (c - 'A' + shift) \pmod{26}$.
3. In modular ASCII mode, $c' = (c + key[i]) \pmod{128}$.
4. Decryption reverses the addition by subtracting the key character modulo 128 (or 26).

## Building and Running

```bash
g++ -std=c++17 -O2 -o keyword_cipher keyword_cipher.cpp
./keyword_cipher
```

On Windows:
```cmd
g++ -std=c++17 -O2 -o keyword_cipher.exe keyword_cipher.cpp
keyword_cipher.exe
```
