#include <iostream>
#include <string>
#include <string_view>
#include <cctype>
#include <cassert>

/**
 * @brief Caesar Cipher implementation.
 *
 * Supports both standard classical alphabetic shift (modulo 26, preserving case)
 * and full printable ASCII shift (ASCII 32 to 126).
 */
class CaesarCipher {
public:
    explicit CaesarCipher(int defaultShift = 3) : defaultShift_(defaultShift) {}

    /**
     * @brief Encrypts text using classical alphabetic shift (A-Z, a-z).
     * Non-alphabetic characters (spaces, punctuation, digits) remain unchanged.
     */
    std::string encryptAlphabet(std::string_view text, int shift) const {
        return shiftAlphabet(text, shift);
    }

    std::string encryptAlphabet(std::string_view text) const {
        return encryptAlphabet(text, defaultShift_);
    }

    /**
     * @brief Decrypts text by inverting the alphabetic shift.
     */
    std::string decryptAlphabet(std::string_view text, int shift) const {
        return shiftAlphabet(text, -shift);
    }

    std::string decryptAlphabet(std::string_view text) const {
        return decryptAlphabet(text, defaultShift_);
    }

    /**
     * @brief Encrypts all printable ASCII characters (range 32 to 126) with wrap-around.
     */
    std::string encryptAscii(std::string_view text, int shift) const {
        return shiftAscii(text, shift);
    }

    /**
     * @brief Decrypts printable ASCII characters.
     */
    std::string decryptAscii(std::string_view text, int shift) const {
        return shiftAscii(text, -shift);
    }

private:
    int defaultShift_;

    static std::string shiftAlphabet(std::string_view text, int shift) {
        std::string result;
        result.reserve(text.size());

        // Normalize shift into [0, 25] range
        int normalizedShift = (shift % 26 + 26) % 26;

        for (unsigned char c : text) {
            if (std::isupper(c)) {
                result += static_cast<char>('A' + (c - 'A' + normalizedShift) % 26);
            } else if (std::islower(c)) {
                result += static_cast<char>('a' + (c - 'a' + normalizedShift) % 26);
            } else {
                result += static_cast<char>(c);
            }
        }
        return result;
    }

    static std::string shiftAscii(std::string_view text, int shift) {
        constexpr int asciiStart = 32;
        constexpr int asciiCount = 95; // 32 to 126 inclusive

        int normalizedShift = (shift % asciiCount + asciiCount) % asciiCount;
        std::string result;
        result.reserve(text.size());

        for (unsigned char c : text) {
            if (c >= asciiStart && c < asciiStart + asciiCount) {
                result += static_cast<char>(asciiStart + (c - asciiStart + normalizedShift) % asciiCount);
            } else {
                result += static_cast<char>(c);
            }
        }
        return result;
    }
};

int main() {
    CaesarCipher cipher(3);

    std::cout << "========================================" << std::endl;
    std::cout << "         Caesar Cipher Demo" << std::endl;
    std::cout << "========================================" << std::endl;

    // 1. Classical Alphabet Shift Demo
    std::string plainText = "The quick brown fox jumps over the lazy dog!";
    int shift = 3;

    std::string encrypted = cipher.encryptAlphabet(plainText, shift);
    std::string decrypted = cipher.decryptAlphabet(encrypted, shift);

    std::cout << "\n[Classical Alphabet Mode (shift = " << shift << ")]" << std::endl;
    std::cout << "Original:  " << plainText << std::endl;
    std::cout << "Encrypted: " << encrypted << std::endl;
    std::cout << "Decrypted: " << decrypted << std::endl;

    assert(plainText == decrypted && "Classical round-trip check failed!");
    std::cout << "Classical verification: PASSED" << std::endl;

    // 2. Printable ASCII Shift Demo
    std::string asciiText = "Secret_Message_123 #Antigravity!";
    int asciiShift = 17;

    std::string asciiEnc = cipher.encryptAscii(asciiText, asciiShift);
    std::string asciiDec = cipher.decryptAscii(asciiEnc, asciiShift);

    std::cout << "\n[Printable ASCII Mode (shift = " << asciiShift << ")]" << std::endl;
    std::cout << "Original:  " << asciiText << std::endl;
    std::cout << "Encrypted: " << asciiEnc << std::endl;
    std::cout << "Decrypted: " << asciiDec << std::endl;

    assert(asciiText == asciiDec && "ASCII round-trip check failed!");
    std::cout << "ASCII verification: PASSED" << std::endl;

    std::cout << "\nAll demonstrations completed successfully." << std::endl;
    return 0;
}
