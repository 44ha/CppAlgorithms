# LZ77 Compression (C++)

Sliding window lossless dictionary compression and decompression algorithm implemented in modern C++.

## Features

- **Structured Token Model**: Uses a dedicated `Token { offset, length, nextChar }` struct instead of fragmented parallel arrays.
- **Overlap-Safe Decompression**: Supports run-length character propagation when `length > offset`.
- **Configurable Buffers**: Adjustable sliding history window size and lookahead buffer size.
- **Integrity**: Round-trip assert test guaranteeing zero data loss.

## How it works

1. A sliding history window tracks previously encoded text.
2. At the current cursor, the algorithm finds the longest prefix that matches anywhere in the history window.
3. It emits a token:
   - `offset`: Backward distance to the match start.
   - `length`: Number of matching characters.
   - `nextChar`: The literal character following the match.
4. If no match is found, it emits `(0, 0, currentChar)`.

## Complexity

| Operation | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Compression | $O(n \cdot W)$ where $W$ is the search window size | $O(n)$ |
| Decompression | $O(n)$ | $O(n)$ |

## Building and Running

```bash
g++ -std=c++17 -O2 -o lz77 lz77.cpp
./lz77
```

On Windows:
```cmd
g++ -std=c++17 -O2 -o lz77.exe lz77.cpp
lz77.exe
```
