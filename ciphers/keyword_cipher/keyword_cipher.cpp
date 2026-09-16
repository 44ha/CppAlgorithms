#include <iostream>
#include <string>
#include <string_view>
#include <cctype>
#include <stdexcept>
#include <cassert>

/**
 * @brief Keyword / Polyalphabetic Repeating-Key Cipher in C++.
 *
 * Implements repeating-key substitution:
 * 1. 7-bit ASCII mode: (message[i] + key[i]) % 128 (original repository implementation)
 * 2. Classical Alphabetic (Vigenère) mode: Shifts letters A-Z / a-z according to the keyword letters.
 */
class KeywordCipher {
public:
    explicit KeywordCipher(std::string keyword) {
        setKeyword(keyword);
    }

    void setKeyword(std::string_view keyword) {
        if (keyword.empty()) {
            throw std::invalid_argument("Keyword cannot be empty.");
        }
        keyword_ = std::string(keyword);
    }

    [[nodiscard]] const std::string& getKeyword() const noexcept {
        return keyword_;
    }

    /**
     * @brief Encrypts message using 7-bit ASCII modular arithmetic (0-127).
     */
    [[nodiscard]] std::string encryptAscii(std::string_view message) const {
        std::string result;
        result.reserve(message.size());

        for (size_t i = 0; i < message.size(); ++i) {
            unsigned char m = static_cast<unsigned char>(message[i]);
            unsigned char k = static_cast<unsigned char>(keyword_[i % keyword_.size()]);
            result += static_cast<char>((m + k) % 128);
        }
        return result;
    }

    /**
     * @brief Decrypts message using 7-bit ASCII modular arithmetic (0-127).
     */
    [[nodiscard]] std::string decryptAscii(std::string_view encryptedMessage) const {
        std::string result;
        result.reserve(encryptedMessage.size());

        for (size_t i = 0; i < encryptedMessage.size(); ++i) {
            unsigned char c = static_cast<unsigned char>(encryptedMessage[i]);
            unsigned char k = static_cast<unsigned char>(keyword_[i % keyword_.size()]);
            result += static_cast<char>((c - k + 128) % 128);
        }
        return result;
    }

    /**
     * @brief Encrypts letters A-Z and a-z using classical Vigenère keyword shifting.
     * Preserves non-letter characters without advancing the keyword index.
     */
    [[nodiscard]] std::string encryptAlphabetic(std::string_view message) const {
        std::string result;
        result.reserve(message.size());

        size_t keyIndex = 0;
        for (char c : message) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                char k = keyword_[keyIndex % keyword_.size()];
                int shift = std::toupper(static_cast<unsigned char>(k)) - 'A';

                if (std::isupper(static_cast<unsigned char>(c))) {
                    result += static_cast<char>('A' + (c - 'A' + shift) % 26);
                } else {
                    result += static_cast<char>('a' + (c - 'a' + shift) % 26);
                }
                ++keyIndex;
            } else {
                result += c;
            }
        }
        return result;
    }

    /**
     * @brief Decrypts letters A-Z and a-z using classical Vigenère keyword shifting.
     */
    [[nodiscard]] std::string decryptAlphabetic(std::string_view encryptedMessage) const {
        std::string result;
        result.reserve(encryptedMessage.size());

        size_t keyIndex = 0;
        for (char c : encryptedMessage) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                char k = keyword_[keyIndex % keyword_.size()];
                int shift = std::toupper(static_cast<unsigned char>(k)) - 'A';

                if (std::isupper(static_cast<unsigned char>(c))) {
                    result += static_cast<char>('A' + (c - 'A' - shift + 26) % 26);
                } else {
                    result += static_cast<char>('a' + (c - 'a' - shift + 26) % 26);
                }
                ++keyIndex;
            } else {
                result += c;
            }
        }
        return result;
    }

private:
    std::string keyword_;
};

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "         Keyword Cipher Demo" << std::endl;
    std::cout << "========================================" << std::endl;

    KeywordCipher cipher("LEMON");

    // 1. Classical Alphabetic (Vigenère) Mode
    std::string message = "ATTACK AT DAWN";
    std::string encryptedAlpha = cipher.encryptAlphabetic(message);
    std::string decryptedAlpha = cipher.decryptAlphabetic(encryptedAlpha);

    std::cout << "\n[Alphabetic Mode with Keyword: \"" << cipher.getKeyword() << "\"]" << std::endl;
    std::cout << "Original:  " << message << std::endl;
    std::cout << "Encrypted: " << encryptedAlpha << std::endl;
    std::cout << "Decrypted: " << decryptedAlpha << std::endl;

    assert(message == decryptedAlpha && "Alphabetic round-trip failed!");
    std::cout << "Alphabetic verification: PASSED" << std::endl;

    // 2. ASCII Mode
    std::string secret = "Modern C++ Cryptography 2026!";
    cipher.setKeyword("SecretKey42");
    std::string encryptedAscii = cipher.encryptAscii(secret);
    std::string decryptedAscii = cipher.decryptAscii(encryptedAscii);

    std::cout << "\n[ASCII Mode with Keyword: \"" << cipher.getKeyword() << "\"]" << std::endl;
    std::cout << "Original:  " << secret << std::endl;
    std::cout << "Encrypted: (ASCII shifted string, len=" << encryptedAscii.size() << ")" << std::endl;
    std::cout << "Decrypted: " << decryptedAscii << std::endl;

    assert(secret == decryptedAscii && "ASCII round-trip failed!");
    std::cout << "ASCII verification: PASSED" << std::endl;

    std::cout << "\nAll demonstrations completed successfully." << std::endl;
    return 0;
}
