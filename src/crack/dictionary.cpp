#include "crack/dictionary.hpp"

#include <fstream>
#include <string>

std::optional<CrackResult> crackDictionary(
    const Hasher& hasher,
    const std::string& targetHash,
    const std::filesystem::path& wordlist) {

    std::ifstream in(wordlist);
    if (!in) {
        return std::nullopt;
    }

    std::size_t attempts = 0;
    std::string candidate;
    while (std::getline(in, candidate)) {
        ++attempts;
        if (hasher.hash(candidate) == targetHash) {
            return CrackResult{candidate, attempts};
        }
    }
    return std::nullopt;
}
