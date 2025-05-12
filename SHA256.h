#pragma once
#include <array>
#include <string>
#include <vector>
#include <cstdint>

class SHA256 {
public:
    static std::string hash(const std::string& input);

private:
    static const std::array<uint32_t, 64> k;
    static const std::array<uint32_t, 8> initialHashValues;

    static std::string toHexString(const std::vector<uint8_t>& digest);
    static uint32_t rotateRight(uint32_t value, uint32_t count);
    static void processChunk(const uint8_t* chunk, uint32_t* hashValues);
};