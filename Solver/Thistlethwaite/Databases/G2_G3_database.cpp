#include "G2_G3_database.h"

uint32_t G2_G3_Database::getIndex(const Rubiks& cube) const
{
    using EEDGE   = Rubiks::EEDGE;
    using ECORNER = Rubiks::ECORNER;
    using ECOLOUR = Rubiks::ECOLOUR;

    // store the location of all edges in the E and S slice
    std::array<uint8_t, 8> edgePosPerm = {
        cube.getEdgeInd({cube.getColour(EEDGE::UL), cube.getColour(EEDGE::LU)}),
        cube.getEdgeInd({cube.getColour(EEDGE::UR), cube.getColour(EEDGE::RU)}),
        cube.getEdgeInd({cube.getColour(EEDGE::DL), cube.getColour(EEDGE::LD)}),
        cube.getEdgeInd({cube.getColour(EEDGE::DR), cube.getColour(EEDGE::RD)}),
        cube.getEdgeInd({cube.getColour(EEDGE::RF), cube.getColour(EEDGE::FR)}),
        cube.getEdgeInd({cube.getColour(EEDGE::RB), cube.getColour(EEDGE::BR)}),
        cube.getEdgeInd({cube.getColour(EEDGE::LF), cube.getColour(EEDGE::FL)}),
        cube.getEdgeInd({cube.getColour(EEDGE::LB), cube.getColour(EEDGE::BL)}),
    };

    // store the location of all corners
    std::array<uint8_t, 8> a = {
        cube.getCornerInd({ cube.getColour(ECORNER::LUB), cube.getColour(ECORNER::ULB), cube.getColour(ECORNER::BLU) }), //ULB WBO 0
        cube.getCornerInd({ cube.getColour(ECORNER::LUF), cube.getColour(ECORNER::ULF), cube.getColour(ECORNER::FLU) }), //ULF WGO 1
        cube.getCornerInd({ cube.getColour(ECORNER::LDF), cube.getColour(ECORNER::DLF), cube.getColour(ECORNER::FLD) }), //DLF YGO 2
        cube.getCornerInd({ cube.getColour(ECORNER::LDB), cube.getColour(ECORNER::DLB), cube.getColour(ECORNER::BLD) }), //DLB YBO 3
        cube.getCornerInd({ cube.getColour(ECORNER::RDB), cube.getColour(ECORNER::DRB), cube.getColour(ECORNER::BRD) }), //DRB YBR 4
        cube.getCornerInd({ cube.getColour(ECORNER::RDF), cube.getColour(ECORNER::DRF), cube.getColour(ECORNER::FRD) }), //DRF YGR 5
        cube.getCornerInd({ cube.getColour(ECORNER::RUB), cube.getColour(ECORNER::URB), cube.getColour(ECORNER::BRU) }), //URB WBR 6
        cube.getCornerInd({ cube.getColour(ECORNER::RUF), cube.getColour(ECORNER::URF), cube.getColour(ECORNER::FRU) }), //URF WGR 7
    };

    std::array<uint8_t, 8> cornerPosPerm;

    for (uint8_t i = 0; i < 8; ++i)
    {
        cornerPosPerm[a[i]] = i;
    }

    // store the positions of the 4 edges that need to be brought back to the E-slice
    // a solved E-slice dictates a solved S-slice (vice versa), only 1 slice has to be considered
    std::array<uint8_t, 4> edgesPosComb;

    for (uint8_t i = 0, e = 0; i < 8 && e < 4; ++i)
    {
        // indices of the E-slice edges are 4, 5, 6, 7
        if (edgePosPerm[i] == 4 || edgePosPerm[i] == 5 ||
            edgePosPerm[i] == 6 || edgePosPerm[i] == 7)
        {
            edgesPosComb[e++] = i + 1;
        }
    }

    uint32_t eInd = indexer.getInd(edgesPosComb); // edge
    uint32_t cInd = 0;                            // corner
    uint32_t pInd = 0;                            // parity

    // check if parity is even or odd
    // this works like a bubble-sort, but instead 0 / 1 is switched based on
    // how many swaps were made from the root position
    for (uint8_t i = 0; i < 8; ++i)
    {
        for (uint8_t j = i + 1; j < 8; ++j)
        {
            pInd ^= cornerPosPerm[i] < cornerPosPerm[j];
        }
    }

    // pairRank[0] = 0..8C2, pairRank[1] = 0..6C2, pairRank[2] = 0..4C2
    uint8_t pairRank[3];
    bool    seen[8]{}; // {} default initialises to false

    // loop through the first 3 pairs (4th pair is forced by the first 3)
    for (uint8_t i = 0; i < 6; i += 2)
    {
        // order the pairs in ascending order
        if (cornerPosPerm[i] > cornerPosPerm[i + 1])
        {
            std::swap(cornerPosPerm[i], cornerPosPerm[i + 1]);
        }

        uint8_t rank = 0;
        uint8_t pair[8][8];

        // set the rank of each pair relative to former pairs
        for (uint8_t l = 0; l < 8; ++l)
        {
            if (seen[l]) continue;
            for (uint8_t r = l + 1; r < 8; ++r)
            {
                if (seen[r]) continue;
                pair[l][r] = rank++;
            }
        }

        // get the rank of the 3 pairs
        pairRank[i >> 1] = pair[cornerPosPerm[i]][cornerPosPerm[i + 1]];

        seen[cornerPosPerm[i]]     = true;
        seen[cornerPosPerm[i + 1]] = true;
    }

    // 0..8C2 - 1 * (6C2 * 4C2 * 2C2) + 0..6C2 - 1 * (4C2 * 2C2) + 0..4C2 - 1 = 0..2519
    cInd = pairRank[0] * 90 + pairRank[1] * 6 + pairRank[2];

    // (0..2519 * 70 + 0..69) * 2 + 0..1 = 0..352799
    return (cInd * 70 + eInd) * 2 + pInd;
}
