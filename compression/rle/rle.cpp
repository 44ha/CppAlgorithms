#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <cassert>

/**
 * @brief Run-Length Encoding (RLE) lossless data compression in C++.
 *
 * Compresses contiguous runs of identical characters into (character, count) representations.
 */
class RunLengthEncoding {
public:
    struct Run {
        char character;
        size_t count;

        bool operator==(const Run& other) const noexcept {
            return character == other.character && count == other.count;
        }
    };

    /**
     * @brief Encodes input into structured vector of Runs.
     */
    [[nodiscard]] static std::vector<Run> encodeRuns(std::string_view input) {
        std::vector<Run> runs;
        if (input.empty()) {
            return runs;
        }

        const size_t n = input.size();
        for (size_t i = 0; i < n; ++i) {
            size_t count = 1;
            while (i + 1 < n && input[i] == input[i + 1]) {
                ++count;
                ++i;
            }
            runs.push_back({input[i], count});
        }
        return runs;
    }

    /**
     * @brief Reconstructs original string from structured vector of Runs.
     */
    [[nodiscard]] static std::string decodeRuns(const std::vector<Run>& runs) {
        std::string result;
        size_t totalLen = 0;
        for (const auto& r : runs) {
            totalLen += r.count;
        }
        result.reserve(totalLen);

        for (const auto& r : runs) {
            result.append(r.count, r.character);
        }
        return result;
    }

    /**
     * @brief Encodes input into a compact string representation.
     * Single chars are written as <char>. Runs of >1 are written as <char><count>~
     * where '~' acts as a unambiguous delimiter after the integer run length.
     */
    [[nodiscard]] static std::string encodeString(std::string_view input, char delimiter = '~') {
        std::string encoded;
        const size_t n = input.size();

        for (size_t i = 0; i < n; ++i) {
            size_t count = 1;
            while (i + 1 < n && input[i] == input[i + 1]) {
                ++count;
                ++i;
            }

            encoded += input[i];
            if (count > 1) {
                encoded += std::to_string(count);
                encoded += delimiter;
            }
        }
        return encoded;
    }

    /**
     * @brief Decodes a compact delimited string representation back to original text.
     */
    [[nodiscard]] static std::string decodeString(std::string_view encoded, char delimiter = '~') {
        std::string decoded;
        const size_t n = encoded.size();
        size_t i = 0;

        while (i < n) {
            char currentChar = encoded[i++];
            size_t count = 1;

            if (i < n && std::isdigit(static_cast<unsigned char>(encoded[i]))) {
                size_t numStart = i;
                while (i < n && std::isdigit(static_cast<unsigned char>(encoded[i]))) {
                    ++i;
                }
                std::string countStr(encoded.substr(numStart, i - numStart));
                count = std::stoul(countStr);

                if (i < n && encoded[i] == delimiter) {
                    ++i; // consume delimiter
                }
            }

            decoded.append(count, currentChar);
        }
        return decoded;
    }

    /**
     * @brief Calculates compression ratio: (compressedSize / originalSize) * 100%.
     */
    [[nodiscard]] static double compressionRatio(size_t originalSize, size_t compressedSize) noexcept {
        if (originalSize == 0) return 0.0;
        return (static_cast<double>(compressedSize) / static_cast<double>(originalSize)) * 100.0;
    }
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "        Run-Length Encoding Demo" << std::endl;
    std::cout << "========================================" << std::endl;

    std::string sample = "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWB";

    // 1. String-encoded RLE
    std::string encoded = RunLengthEncoding::encodeString(sample);
    std::string decoded = RunLengthEncoding::decodeString(encoded);

    std::cout << "\n[String Delimited Encoding]" << std::endl;
    std::cout << "Original:   " << sample << " (" << sample.size() << " bytes)" << std::endl;
    std::cout << "Encoded:    " << encoded << " (" << encoded.size() << " bytes)" << std::endl;
    std::cout << "Decoded:    " << decoded << std::endl;
    std::cout << "Ratio:      " << std::fixed << std::setprecision(1)
              << RunLengthEncoding::compressionRatio(sample.size(), encoded.size()) << "% of original size" << std::endl;

    assert(sample == decoded && "String RLE round-trip failed!");
    std::cout << "String verification: PASSED" << std::endl;

    // 2. Structured Token RLE
    auto runs = RunLengthEncoding::encodeRuns(sample);
    std::string decodedFromRuns = RunLengthEncoding::decodeRuns(runs);

    std::cout << "\n[Structured Run List (" << runs.size() << " runs)]" << std::endl;
    for (const auto& r : runs) {
        std::cout << "  ['" << r.character << "': " << r.count << "x] ";
    }
    std::cout << std::endl;

    assert(sample == decodedFromRuns && "Structured RLE round-trip failed!");
    std::cout << "Structured verification: PASSED" << std::endl;

    std::cout << "\nAll demonstrations completed successfully." << std::endl;
    return 0;
}
