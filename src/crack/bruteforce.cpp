#include "crack/bruteforce.hpp"

#include <string>

namespace {

// Advance `key` to the next combination over `charset`, like a base-N odometer.
// Returns false when the space has been exhausted at the current length.
bool increment(std::string& key, const std::string& charset) {
    for (auto it = key.rbegin(); it != key.rend(); ++it) {
        auto pos = charset.find(*it);
        if (pos + 1 < charset.size()) {
            *it = charset[pos + 1];
            return true;
        }
        *it = charset.front();
    }
    return false;
}

} // namespace

std::optional<CrackResult> crackBruteforce(
    const Hasher& hasher,
    const std::string& targetHash,
    const std::string& charset,
    std::size_t maxLength) {

    if (charset.empty()) {
        return std::nullopt;
    }

    std::size_t attempts = 0;
    for (std::size_t len = 1; len <= maxLength; ++len) {
        std::string candidate(len, charset.front());
        do {
            ++attempts;
            if (hasher.hash(candidate) == targetHash) {
                return CrackResult{candidate, attempts};
            }
        } while (increment(candidate, charset));
    }
    return std::nullopt;
}
