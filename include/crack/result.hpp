#pragma once

#include <cstddef>
#include <string>

struct CrackResult {
    std::string plaintext;
    std::size_t attempts;
};
