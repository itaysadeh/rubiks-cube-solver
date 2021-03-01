#pragma once

#include <bitset>
#include <array>

#include <array>
using std::array;
#include <bitset>
using std::bitset;
#include <iostream>
using std::cout;
using std::endl;

// medium.com/@benjamin.botto/sequentially-indexing-permutations-a-linear-algorithm-for-computing-lexicographic-rank-a22220ffd6e3
// currently not in use

template <uint8_t N, uint8_t K = N>
class PermutationIndexer
{
    static array<std::size_t, (1 << N) - 1> onesCountLookup;

    static array<std::size_t, K> factorials;

public:
    PermutationIndexer()
    {
        for (std::size_t i = 0; i < (1 << N) - 1; ++i)
        {
            bitset<N> bits(i);
            this->onesCountLookup[i] = bits.count();
        }

        for (unsigned i = 0; i < K; ++i)
            this->factorials[i] = pick(N - 1 - i, K - 1 - i);
    }

    // Calculates n!.
    std::size_t factorial(std::size_t n)
    {
        return n <= 1 ? 1 : n * factorial(n - 1);
    }

    // Calculate nPk: n!/(n-k)!.
    std::size_t pick(std::size_t n, std::size_t k)
    {
        return factorial(n) / factorial(n - k);
    }

    uint32_t getInd(const array<uint8_t, K>& perm) const
    {
        array<std::size_t, K> lehmer;

        bitset<N> seen;
        lehmer[0] = perm[0];

        seen[N - 1 - perm[0]] = 1;

        for (std::size_t i = 1; i < K; ++i)
        {
            seen[N - 1 - perm[i]] = 1;
            std::size_t numOnes = this->onesCountLookup[seen.to_ulong() >> (N - perm[i])];

            lehmer[i] = perm[i] - numOnes;
        }

        std::size_t index = 0;

        for (std::size_t i = 0; i < K; ++i)
            index += lehmer[i] * this->factorials[i];

        return index;
    }
};


// Static member definitions.
template <uint8_t N, uint8_t K>
array<size_t, (1 << N) - 1> PermutationIndexer<N, K>::onesCountLookup;

template <uint8_t N, uint8_t K>
array<size_t, K> PermutationIndexer<N, K>::factorials;