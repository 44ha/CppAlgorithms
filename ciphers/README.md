# Classical Ciphers & Cryptography in C++

Clean, modern C++17 implementations of classical cryptography and substitution/transposition ciphers.

## Algorithms

| Directory | Algorithm | Type | Description |
|-----------|-----------|------|-------------|
| [caesar_cipher/](caesar_cipher/) | Caesar Cipher | Substitution | Monoalphabetic shift cipher supporting 26-letter alphabetic rotation & printable ASCII. |
| [keyword_cipher/](keyword_cipher/) | Keyword Cipher | Polyalphabetic | Vigenère and modular 128 repeating-key substitution cipher. |
| [columnar_transposition/](columnar_transposition/) | Columnar Transposition | Transposition | Permutation cipher writing into an $N$-column matrix and reading by column. |

## Quick Start

Navigate to any cipher folder and compile with any C++17 compliant compiler:

```bash
cd caesar_cipher
g++ -std=c++17 -O2 -o caesar_cipher caesar_cipher.cpp
./caesar_cipher
```
