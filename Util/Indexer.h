#ifndef INDEXER_H
#define INDEXER_H

#include <cstdint>
#include <array>
#include <bitset>

// all indexers require a permutation to be from 0 to N

// ranks combinations from 0 to nCk - 1
template<uint8_t K>
struct CombIndexer
{
    // 0!.....12! (longest possible combination has 12 values: 12 edges > 8 corners)
    const std::array<uint32_t, 13> factorial = { 1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600 };

    // calculate nCk = n! / (k!(n - k)!)
    uint32_t nCk(uint8_t n, uint8_t k) const
    {
        if (n < k)  return 0;
        if (n == k) return 1;
        return factorial[n] / (factorial[k] * factorial[n - k]);
    }

    // combinations are always assumed to be in a descending order
    uint32_t getInd(const std::array<uint8_t, K>& comb) const
    {
        // www.jaapsch.net/puzzles/compindx.htm
        // an edge combination is ranked based on the amount of possible smaller edge combinations
        // because there is no repetition or regard to order, nCk is used assuming the positions
        // permutations are always in a decending order (p = position: p[0]> p[1] > p[2] > p[3])
        // index = p[0]-1C4 + p[1]-1C3 + p[2]-1C2 + p[3]-1C1

        uint32_t index = 0;

        for (uint8_t n = K, k = K; k > 0; --n, --k)
        {
            index += nCk(comb[n - 1] - 1, k);
        }

        return index;
    }
};

// ranks permutations from 0 to N! - 1
template<uint8_t N>
struct PermIndexer
{
    // 0!.....12! (longest possible combination has 12 values: 12 edges > 8 corners)
    const std::array<uint32_t, 13> factorial = { 1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600 };

    uint32_t getInd(const std::array<uint8_t, N> perm) const
    {
        // calculates lehmer code
        std::array<uint8_t, N> lehmer = perm;

        for (uint8_t i = 1; i < N; ++i)
        {
            int j = i;
            while (j--)
            {
                if (perm[j] < perm[i])
                {
                    --lehmer[i];
                }
            }
        }

        uint32_t index = 0;

        for (uint8_t i = 0, j = N - 1; i < N && j >= 0; ++i, --j)
        {
            index += lehmer[i] * factorial[j];
        }

        return index;
    }
};

// ranks partial permutations from 0 to nPk - 1
template<uint8_t N, uint8_t K>
struct PermIndexerPartial
{
    // 0!.....12! (longest possible combination has 12 values: 12 edges > 8 corners)
    const std::array<uint32_t, 13> factorial = { 1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600 };

    // calculate nPk = n! / (n - k)!
    uint32_t nPk(uint8_t n, uint8_t k) const
    {
        if (n < k)  return 0;
        if (n == k) return 1;
        return factorial[n] / factorial[n - k];
    }

    uint32_t getInd(const std::array<uint8_t, K> perm) const
    {
        // calculates lehmer code
        std::array<uint8_t, K> lehmer = perm;

        for (uint8_t i = 1; i < K; ++i)
        {
            int j = i;
            while (j--)
            {
                if (perm[j] < perm[i])
                {
                    --lehmer[i];
                }
            }
        }

        uint32_t index = 0;

        for (uint8_t i = 0; i < K; ++i)
        {
            index += lehmer[i] * nPk(N - 1 - i, K - 1 - i);
        }

        return index;
    }
};

#endif // INDEXER_H
