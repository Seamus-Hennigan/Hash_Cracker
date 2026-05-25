#pragma once
#include <string>

class Hasher {
public:
    virtual ~Hasher() = default;
    virtual std::string hash(const std::string& input) const = 0;
    virtual std::string name() const = 0;
};