#pragma once

#include "crack/result.hpp"
#include "hash/hasher.hpp"

#include <cstddef>
#include <optional>
#include <string>

std::optional<CrackResult> crackBruteforce(
    const Hasher& hasher,
    const std::string& targetHash,
    const std::string& charset,
    std::size_t maxLength);
