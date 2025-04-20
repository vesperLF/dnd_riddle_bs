#include <array>
#include <fstream>
#include <iostream>
#include <string>

bool rainbow_condition(const std::string& str) {
    static const std::array<std::string, 7> rainbow {
        "red",
        "orange",
        "yellow",
        "green",
        "blue",
        "indigo",
        "violet"
    };
    for (size_t i = 0; i < 7; i++) {
        for (size_t j = i + 1; j < 7; j++) {
            std::string two_colors = rainbow[i];
            two_colors += rainbow[j];
            std::string str_copy = str;
            for (char c : two_colors) {
                for (size_t k = 0; k < str_copy.length(); k++) {
                    if (c == str_copy[k]) {
                        str_copy.erase(k, 1);
                        goto found_single_char;
                    }
                }
                goto failed_combo;
            found_single_char:;
            }
            if (str_copy.length() == 2 && str[0] >= 'a' && str[1] >= 'a' && str[0] <= 'z' && str[1] <= 'z') {
                return true;
            }
        failed_combo:;
        }
    }
    return false;
}

bool vowel_condition(const std::string& str) {
    static const std::string vowels = "aeiou";
    uint32_t vowel_count = 0;
    for (char vowel : vowels) {
        for (char c : str) {
            if (vowel == c) {
                vowel_count++;
                break;
            }
        }
    }
    return vowel_count == 4;
}

bool prime_condition(const std::string& str) {
    static const std::array<size_t, 22> primes { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79 };
    for (size_t prime_0 : primes) {
        for (size_t prime_1 : primes) {
            size_t len = str.length();
            if (len == prime_0 + 1 && len == prime_1 * 2) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    std::ifstream ifs("words_alpha.txt");
    if (!ifs.good()) {
        std::cout << "failed to open words_alpha.txt\n";
        return 'file';
    }
    std::string current;
    do {
        std::getline(ifs, current);
        if (prime_condition(current) && vowel_condition(current) && rainbow_condition(current)) {
            std::cout << current << '\n';
        }
    } while (ifs.good());
    return 0;
}
