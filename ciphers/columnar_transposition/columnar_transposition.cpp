#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <stdexcept>
#include <cassert>

/**
 * @brief Columnar Transposition Cipher implementation in modern C++.
 *
 * Permutes plaintext by arranging characters into a grid of specified column width
 * and reading them column by column.
 */
class ColumnarTranspositionCipher {
public:
    explicit ColumnarTranspositionCipher(int columns, char padding = ' ')
        : columns_(columns), padding_(padding) {
        if (columns <= 0) {
            throw std::invalid_argument("Column key must be greater than zero.");
        }
    }

    void setColumns(int columns) {
        if (columns <= 0) {
            throw std::invalid_argument("Column key must be greater than zero.");
        }
        columns_ = columns;
    }

    [[nodiscard]] int getColumns() const noexcept {
        return columns_;
    }

    /**
     * @brief Encrypts plaintext by placing it in rows of size columns_
     * and reading out column by column.
     */
    [[nodiscard]] std::string encrypt(std::string_view text) const {
        if (text.empty()) {
            return {};
        }

        const size_t len = text.size();
        const size_t rows = (len + columns_ - 1) / columns_;

        // Use a flat std::vector<char> instead of non-standard VLAs
        std::vector<char> grid(rows * columns_, padding_);

        for (size_t i = 0; i < len; ++i) {
            grid[i] = text[i];
        }

        std::string ciphertext;
        ciphertext.reserve(rows * columns_);

        for (size_t col = 0; col < static_cast<size_t>(columns_); ++col) {
            for (size_t row = 0; row < rows; ++row) {
                ciphertext += grid[row * columns_ + col];
            }
        }

        return ciphertext;
    }

    /**
     * @brief Decrypts ciphertext by filling columns and reading out row by row.
     * @param ciphertext The encrypted string.
     * @param trimPadding Whether to strip trailing padding characters.
     */
    [[nodiscard]] std::string decrypt(std::string_view ciphertext, bool trimPadding = false) const {
        if (ciphertext.empty()) {
            return {};
        }

        const size_t len = ciphertext.size();
        const size_t rows = (len + columns_ - 1) / columns_;

        std::vector<char> grid(rows * columns_, padding_);

        size_t index = 0;
        for (size_t col = 0; col < static_cast<size_t>(columns_); ++col) {
            for (size_t row = 0; row < rows; ++row) {
                if (index < len) {
                    grid[row * columns_ + col] = ciphertext[index++];
                }
            }
        }

        std::string plaintext;
        plaintext.reserve(rows * columns_);

        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < static_cast<size_t>(columns_); ++col) {
                plaintext += grid[row * columns_ + col];
            }
        }

        if (trimPadding) {
            while (!plaintext.empty() && plaintext.back() == padding_) {
                plaintext.pop_back();
            }
        }

        return plaintext;
    }

private:
    int columns_;
    char padding_;
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "    Columnar Transposition Demo" << std::endl;
    std::cout << "========================================" << std::endl;

    int columns = 5;
    ColumnarTranspositionCipher cipher(columns, '_');

    std::string text = "DEFEND_THE_EAST_WALL";
    std::string ciphertext = cipher.encrypt(text);
    std::string decrypted = cipher.decrypt(ciphertext, false);

    std::cout << "\n[Transposition Matrix with " << columns << " columns]" << std::endl;
    std::cout << "Original:  \"" << text << "\"" << std::endl;
    std::cout << "Encrypted: \"" << ciphertext << "\"" << std::endl;
    std::cout << "Decrypted: \"" << decrypted << "\"" << std::endl;

    assert(decrypted.substr(0, text.size()) == text && "Transposition round-trip failed!");
    std::cout << "Verification: PASSED" << std::endl;

    std::cout << "\nAll demonstrations completed successfully." << std::endl;
    return 0;
}
