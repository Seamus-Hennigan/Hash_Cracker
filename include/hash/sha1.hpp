#pragma once
#include "hash/hasher.hpp"
#include <string>

class Sha1 : public Hasher {
public:
    std::string hash(const std::string& input) const override;
    std::string name() const override;
};