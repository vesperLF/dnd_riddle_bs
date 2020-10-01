#include <array>
#include <fstream>
#include <iostream>
#include <string>

void letter_increment(unsigned short& i) {
    unsigned short last_byte = i % 0x0100;
    if (last_byte == 'z') {
        i += 0x0100;
        i -= last_byte;
    } else {
        i++;
    }
}

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
            for (unsigned short suffix = 'aa'; suffix < 'zz'; letter_increment(suffix)) {
                std::string conglomerate = two_colors;
                char* suffix_ptr = (char*)&suffix;//NOOO you cant squeeze everything in a short!!! Follow the Sacred Object Oriented Way instead!!!
                conglomerate += suffix_ptr[0];//haha type pun go bloop bloop
                conglomerate += suffix_ptr[1];
                std::string str_copy = str;
                for (char c : conglomerate) {
                    for (size_t k = 0; k < str_copy.length(); k++) {
                        if (c == str_copy[k]) {
                            str_copy.erase(k, 1);
                            goto found_single_char;
                        }
                    }
                    goto failed_combo;
                found_single_char:;
                }
                if (str_copy.length() == 0) {
                    return true;
                }
            failed_combo:;
            }
        }
    }
    return false;
}

bool vowel_condition(const std::string& str) {
    static const std::string vowels = "aeiou";
    unsigned vowel_count = 0;
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
    static const std::array<unsigned, 22> primes { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79 };
    for (unsigned prime_0 : primes) {
        for (unsigned prime_1 : primes) {
            size_t len = str.length();
            if (len == (size_t)prime_0 + 1 && len == (size_t)prime_1 * 2) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    std::ifstream ifs("words_alpha.txt");
    std::string current;
    do {
        std::getline(ifs, current);
        if (rainbow_condition(current) && vowel_condition(current) && prime_condition(current)) {
            std::cout << current << '\n';
        }
    } while (ifs.good());
}
