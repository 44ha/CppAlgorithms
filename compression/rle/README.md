# Run-Length Encoding (RLE) Compression (C++)

A modern C++ implementation of the Run-Length Encoding lossless data compression algorithm.

## Features

- **Structured Run API**: Extracts explicit `(character, count)` tuples into `std::vector<Run>`.
- **String Delimited Encoding**: Encodes text into compact alphanumeric strings with configurable delimiter flags to prevent digit ambiguity.
- **Metrics**: Computes compression ratio percentages.
- **Round-Trip Integrity**: Clean assertions verifying exact decompression.

## Complexity

| Operation | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Compression | $O(n)$ | $O(n)$ |
| Decompression | $O(n)$ | $O(n)$ |

## Building and Running

```bash
g++ -std=c++17 -O2 -o rle rle.cpp
./rle
```

On Windows:
```cmd
g++ -std=c++17 -O2 -o rle.exe rle.cpp
rle.exe
```
