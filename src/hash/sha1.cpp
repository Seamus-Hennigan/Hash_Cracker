#include "hash/sha1.hpp"

std::string Sha1::name() const {
    return "SHA-1";
}

std::string Sha1::hash(const std::string& input) const {
    // TODO: implement SHA-1 (RFC 3174) and return the 40-char lowercase hex digest.
    (void)input;
    return {};
}
