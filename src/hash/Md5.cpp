#include "hash/Md5_constants.hpp"
#include "hash/Md5.hpp"

#include <vector>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <cstring>

std::vector<uint8_t> padMessage(const uint8_t* data, uint64_t byteLength) {
    uint64_t bitLength = byteLength * 8;


    uint64_t paddedLength = byteLength + 1;
    while (paddedLength % 64 != 56) paddedLength++;
    paddedLength += 8;

    std::vector<uint8_t> padded(paddedLength, 0x00);
    std::memcpy(padded.data(), data, byteLength);
    padded[byteLength] = 0x80;

    for (int i = 0; i < 8; ++i) {
        padded[paddedLength - 8 + i] = (bitLength >> (i * 8)) & 0xFF;
    }

    return padded;
}

static void processBlock(const uint8_t* block, uint32_t& A, uint32_t& B, uint32_t& C, uint32_t& D) {
    // Step 1: Break the 64-byte block into 16 little-endian 32-bit words.
    uint32_t M[16];
    for (int i = 0; i < 16; ++i) {
        M[i] = static_cast<uint32_t>(block[i * 4 + 0])
             | (static_cast<uint32_t>(block[i * 4 + 1]) << 8)
             | (static_cast<uint32_t>(block[i * 4 + 2]) << 16)
             | (static_cast<uint32_t>(block[i * 4 + 3]) << 24);
    }

    // Step 2: Save the current state for the final addition.
    uint32_t AA = A, BB = B, CC = C, DD = D;

    // Single helper that performs one of the 64 operations.
    auto op = [](uint32_t& a, uint32_t b, uint32_t funcResult,
                 uint32_t Mk, uint32_t Ti, uint32_t s) {
        a = b + leftRotate(a + funcResult + Mk + Ti, s);
    };

    // Step 3: Run the 64 operations, in four rounds of 16.

    // Round 1 (operations 0–15): uses F. k = i.
    op(A, B, F(B, C, D), M[ 0], T[ 0], S[ 0]);
    op(D, A, F(A, B, C), M[ 1], T[ 1], S[ 1]);
    op(C, D, F(D, A, B), M[ 2], T[ 2], S[ 2]);
    op(B, C, F(C, D, A), M[ 3], T[ 3], S[ 3]);
    op(A, B, F(B, C, D), M[ 4], T[ 4], S[ 4]);
    op(D, A, F(A, B, C), M[ 5], T[ 5], S[ 5]);
    op(C, D, F(D, A, B), M[ 6], T[ 6], S[ 6]);
    op(B, C, F(C, D, A), M[ 7], T[ 7], S[ 7]);
    op(A, B, F(B, C, D), M[ 8], T[ 8], S[ 8]);
    op(D, A, F(A, B, C), M[ 9], T[ 9], S[ 9]);
    op(C, D, F(D, A, B), M[10], T[10], S[10]);
    op(B, C, F(C, D, A), M[11], T[11], S[11]);
    op(A, B, F(B, C, D), M[12], T[12], S[12]);
    op(D, A, F(A, B, C), M[13], T[13], S[13]);
    op(C, D, F(D, A, B), M[14], T[14], S[14]);
    op(B, C, F(C, D, A), M[15], T[15], S[15]);

    // Round 2 (operations 16–31): uses G. k = (5i + 1) mod 16.
    op(A, B, G(B, C, D), M[ 1], T[16], S[16]);
    op(D, A, G(A, B, C), M[ 6], T[17], S[17]);
    op(C, D, G(D, A, B), M[11], T[18], S[18]);
    op(B, C, G(C, D, A), M[ 0], T[19], S[19]);
    op(A, B, G(B, C, D), M[ 5], T[20], S[20]);
    op(D, A, G(A, B, C), M[10], T[21], S[21]);
    op(C, D, G(D, A, B), M[15], T[22], S[22]);
    op(B, C, G(C, D, A), M[ 4], T[23], S[23]);
    op(A, B, G(B, C, D), M[ 9], T[24], S[24]);
    op(D, A, G(A, B, C), M[14], T[25], S[25]);
    op(C, D, G(D, A, B), M[ 3], T[26], S[26]);
    op(B, C, G(C, D, A), M[ 8], T[27], S[27]);
    op(A, B, G(B, C, D), M[13], T[28], S[28]);
    op(D, A, G(A, B, C), M[ 2], T[29], S[29]);
    op(C, D, G(D, A, B), M[ 7], T[30], S[30]);
    op(B, C, G(C, D, A), M[12], T[31], S[31]);

    // Round 3 (operations 32–47): uses H. k = (3i + 5) mod 16.
    op(A, B, H(B, C, D), M[ 5], T[32], S[32]);
    op(D, A, H(A, B, C), M[ 8], T[33], S[33]);
    op(C, D, H(D, A, B), M[11], T[34], S[34]);
    op(B, C, H(C, D, A), M[14], T[35], S[35]);
    op(A, B, H(B, C, D), M[ 1], T[36], S[36]);
    op(D, A, H(A, B, C), M[ 4], T[37], S[37]);
    op(C, D, H(D, A, B), M[ 7], T[38], S[38]);
    op(B, C, H(C, D, A), M[10], T[39], S[39]);
    op(A, B, H(B, C, D), M[13], T[40], S[40]);
    op(D, A, H(A, B, C), M[ 0], T[41], S[41]);
    op(C, D, H(D, A, B), M[ 3], T[42], S[42]);
    op(B, C, H(C, D, A), M[ 6], T[43], S[43]);
    op(A, B, H(B, C, D), M[ 9], T[44], S[44]);
    op(D, A, H(A, B, C), M[12], T[45], S[45]);
    op(C, D, H(D, A, B), M[15], T[46], S[46]);
    op(B, C, H(C, D, A), M[ 2], T[47], S[47]);

    // Round 4 (operations 48–63): uses I. k = (7i) mod 16.
    op(A, B, I(B, C, D), M[ 0], T[48], S[48]);
    op(D, A, I(A, B, C), M[ 7], T[49], S[49]);
    op(C, D, I(D, A, B), M[14], T[50], S[50]);
    op(B, C, I(C, D, A), M[ 5], T[51], S[51]);
    op(A, B, I(B, C, D), M[12], T[52], S[52]);
    op(D, A, I(A, B, C), M[ 3], T[53], S[53]);
    op(C, D, I(D, A, B), M[10], T[54], S[54]);
    op(B, C, I(C, D, A), M[ 1], T[55], S[55]);
    op(A, B, I(B, C, D), M[ 8], T[56], S[56]);
    op(D, A, I(A, B, C), M[15], T[57], S[57]);
    op(C, D, I(D, A, B), M[ 6], T[58], S[58]);
    op(B, C, I(C, D, A), M[13], T[59], S[59]);
    op(A, B, I(B, C, D), M[ 4], T[60], S[60]);
    op(D, A, I(A, B, C), M[11], T[61], S[61]);
    op(C, D, I(D, A, B), M[ 2], T[62], S[62]);
    op(B, C, I(C, D, A), M[ 9], T[63], S[63]);

    // Step 4: Add the saved state back.
    A += AA;
    B += BB;
    C += CC;
    D += DD;
}

std::string Md5::name() const {
    return "MD5";
}


std::string Md5::hash(const std::string& input) const {
    // 1. Pad the input.
    auto padded = padMessage(
        reinterpret_cast<const uint8_t*>(input.data()),
        input.size()
    );

    // 2. Initialize state.
    uint32_t A = INIT_A, B = INIT_B, C = INIT_C, D = INIT_D;

    // 3. Process each 64-byte block.
    for (size_t i = 0; i < padded.size(); i += 64) {
        processBlock(padded.data() + i, A, B, C, D);
    }

    // 4. Assemble the 16-byte digest (little-endian for each word).
    uint8_t digest[16];
    auto writeWord = [](uint8_t* out, uint32_t word) {
        out[0] =  word        & 0xFF;
        out[1] = (word >>  8) & 0xFF;
        out[2] = (word >> 16) & 0xFF;
        out[3] = (word >> 24) & 0xFF;
    };
    writeWord(digest + 0,  A);
    writeWord(digest + 4,  B);
    writeWord(digest + 8,  C);
    writeWord(digest + 12, D);

    // 5. Convert to lowercase hex string.
    std::ostringstream oss;
    for (int i = 0; i < 16; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(digest[i]);
    }
    return oss.str();
}
