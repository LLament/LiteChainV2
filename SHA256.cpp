#include "SHA256.h"
#include <sstream>
#include <iomanip>
#include <cstring>

const std::array<uint32_t, 64> SHA256::k = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

const std::array<uint32_t, 8> SHA256::initialHashValues = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

std::string SHA256::hash(const std::string& input) {
    // Padding the input
    std::vector<uint8_t> paddedData(input.begin(), input.end());
    uint64_t bitLength = input.size() * 8;
    paddedData.push_back(0x80);
    while ((paddedData.size() % 64) != 56) {
        paddedData.push_back(0x00);
    }

    for (int i = 7; i >= 0; --i) {
        paddedData.push_back(static_cast<uint8_t>(bitLength >> (i * 8)));
    }

    // Initialize hash values
    uint32_t hashValues[8];
    std::copy(initialHashValues.begin(), initialHashValues.end(), hashValues);

    // Process each 512-bit chunk
    for (size_t i = 0; i < paddedData.size(); i += 64) {
        processChunk(&paddedData[i], hashValues);
    }

    // Produce final hash
    std::vector<uint8_t> digest;
    for (int i = 0; i < 8; ++i) {
        for (int j = 3; j >= 0; --j) {
            digest.push_back(static_cast<uint8_t>(hashValues[i] >> (j * 8)));
        }
    }
    return toHexString(digest);
}

uint32_t SHA256::rotateRight(uint32_t value, uint32_t count) {
    return (value >> count) | (value << (32 - count));
}

void SHA256::processChunk(const uint8_t* chunk, uint32_t* hashValues) {
    uint32_t w[64];
    for (int i = 0; i < 16; ++i) {
        w[i] = (chunk[i * 4] << 24) | (chunk[i * 4 + 1] << 16) | (chunk[i * 4 + 2] << 8) | chunk[i * 4 + 3];
    }
    for (int i = 16; i < 64; ++i) {
        uint32_t s0 = rotateRight(w[i - 15], 7) ^ rotateRight(w[i - 15], 18) ^ (w[i - 15] >> 3);
        uint32_t s1 = rotateRight(w[i - 2], 17) ^ rotateRight(w[i - 2], 19) ^ (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    uint32_t a = hashValues[0], b = hashValues[1], c = hashValues[2], d = hashValues[3];
    uint32_t e = hashValues[4], f = hashValues[5], g = hashValues[6], h = hashValues[7];

    for (int i = 0; i < 64; ++i) {
        uint32_t s1 = rotateRight(e, 6) ^ rotateRight(e, 11) ^ rotateRight(e, 25);
        uint32_t ch = (e & f) ^ (~e & g);
        uint32_t temp1 = h + s1 + ch + k[i] + w[i];
        uint32_t s0 = rotateRight(a, 2) ^ rotateRight(a, 13) ^ rotateRight(a, 22);
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        uint32_t temp2 = s0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    hashValues[0] += a;
    hashValues[1] += b;
    hashValues[2] += c;
    hashValues[3] += d;
    hashValues[4] += e;
    hashValues[5] += f;
    hashValues[6] += g;
    hashValues[7] += h;
}

std::string SHA256::toHexString(const std::vector<uint8_t>& digest) {
    std::stringstream ss;
    for (uint8_t byte : digest) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return ss.str();
}