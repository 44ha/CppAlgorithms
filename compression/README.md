# Lossless Data Compression in C++

Clean, modern C++17 implementations of fundamental lossless data compression algorithms.

## Algorithms

| Directory | Algorithm | Paradigm | Description |
|-----------|-----------|----------|-------------|
| [rle/](rle/) | Run-Length Encoding (RLE) | Statistical / Run-Length | Compresses runs of identical contiguous bytes into character-count pairs. |
| [lz77/](lz77/) | LZ77 Sliding Window | Dictionary-based | Replaces repetitive substrings with `(offset, length, nextChar)` back-references. |

## Quick Start

Navigate to any algorithm directory and compile:

```bash
cd rle
g++ -std=c++17 -O2 -o rle rle.cpp
./rle
```
