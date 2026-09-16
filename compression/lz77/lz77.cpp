#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <iomanip>
#include <cassert>

/**
 * @brief LZ77 Sliding Window Dictionary Compression in C++.
 *
 * Implements LZ77 compression and decompression using (offset, length, nextChar) tokens.
 */
class LZ77 {
public:
    struct Token {
        int offset{0};       // Backward distance into sliding history window
        int length{0};       // Length of matched sequence
        char nextChar{'\0'}; // Literal following the match (or '\0' if end of stream)

        bool operator==(const Token& other) const noexcept {
            return offset == other.offset && length == other.length && nextChar == other.nextChar;
        }
    };

    explicit LZ77(int windowSize = 2048, int lookaheadSize = 32)
        : windowSize_(windowSize), lookaheadSize_(lookaheadSize) {}

    /**
     * @brief Compresses an input string into a sequence of LZ77 Tokens.
     */
    [[nodiscard]] std::vector<Token> compress(std::string_view input) const {
        std::vector<Token> tokens;
        const int n = static_cast<int>(input.size());
        int cursor = 0;

        while (cursor < n) {
            int matchOffset = 0;
            int matchLength = 0;

            int windowStart = std::max(0, cursor - windowSize_);
            int maxLookahead = std::min(lookaheadSize_, n - cursor);

            // Search history window for the longest matching sequence
            for (int j = windowStart; j < cursor; ++j) {
                int k = 0;
                while (k < maxLookahead && input[j + k] == input[cursor + k]) {
                    ++k;
                }
                if (k > matchLength) {
                    matchOffset = cursor - j;
                    matchLength = k;
                }
            }

            char nextChar = (cursor + matchLength < n) ? input[cursor + matchLength] : '\0';
            tokens.push_back({matchOffset, matchLength, nextChar});

            cursor += matchLength + 1;
        }

        return tokens;
    }

    /**
     * @brief Decompresses a sequence of LZ77 Tokens back to the original text.
     */
    [[nodiscard]] std::string decompress(const std::vector<Token>& tokens) const {
        std::string result;

        for (const auto& token : tokens) {
            // Copy matched characters from back-offset (handles overlapping runs)
            if (token.length > 0 && token.offset > 0) {
                const size_t startIdx = result.size() - static_cast<size_t>(token.offset);
                for (int i = 0; i < token.length; ++i) {
                    result.push_back(result[startIdx + static_cast<size_t>(i)]);
                }
            }

            // Append literal character if not terminal null
            if (token.nextChar != '\0') {
                result.push_back(token.nextChar);
            }
        }

        return result;
    }

private:
    int windowSize_;
    int lookaheadSize_;
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "         LZ77 Compression Demo" << std::endl;
    std::cout << "========================================" << std::endl;

    LZ77 compressor(32, 16);

    std::string text = "abracadabra_abracadabra_abc";
    auto tokens = compressor.compress(text);
    std::string decompressed = compressor.decompress(tokens);

    std::cout << "\nInput: \"" << text << "\" (" << text.size() << " bytes)" << std::endl;
    std::cout << "\nEmitted LZ77 Tokens (" << tokens.size() << " tokens):" << std::endl;
    std::cout << "  [Idx] (Offset, Length, NextChar)" << std::endl;
    for (size_t i = 0; i < tokens.size(); ++i) {
        std::cout << "  [" << std::setw(2) << i << "] ("
                  << std::setw(2) << tokens[i].offset << ", "
                  << std::setw(2) << tokens[i].length << ", ";
        if (tokens[i].nextChar == '\0') {
            std::cout << "\\0";
        } else {
            std::cout << '\'' << tokens[i].nextChar << '\'';
        }
        std::cout << ")\n";
    }

    std::cout << "\nDecompressed: \"" << decompressed << "\"" << std::endl;

    assert(text == decompressed && "LZ77 round-trip verification failed!");
    std::cout << "Verification: PASSED" << std::endl;

    std::cout << "\nAll demonstrations completed successfully." << std::endl;
    return 0;
}
