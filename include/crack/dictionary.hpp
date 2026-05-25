#pragma once

#include "crack/result.hpp"
#include "hash/hasher.hpp"

#include <filesystem>
#include <optional>
#include <string>

std::optional<CrackResult> crackDictionary(
    const Hasher& hasher,
    const std::string& targetHash,
    const std::filesystem::path& wordlist);
