#include "G2_G3_database.h"

#include "../../../Util/PermutationIndexer.h"

uint32_t G2_G3_Database::getIndex(const Rubiks& cube) const
{
    using EEDGE   = Rubiks::EEDGE;
    using ECORNER = Rubiks::ECORNER;
    using ECOLOUR = Rubiks::ECOLOUR;

    // 0!.....12!
    constexpr std::array<size_t, 13> factorial = { 1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600 };

    // calculates nCk = n! / (k!(n - k)!)
    auto nCk = [&](uint8_t n, uint8_t k)->uint32_t {
        if (n < k)  return 0;
        if (n == k) return 1;
        return factorial[n] / (factorial[k] * factorial[n - k]);
    };

    // stores the location of all edges in the E and S slices
    std::array<uint8_t, 8> edgesPerm = {
        cube.getEdgeInd({cube.getColour(EEDGE::UL), cube.getColour(EEDGE::LU)}),
        cube.getEdgeInd({cube.getColour(EEDGE::UR), cube.getColour(EEDGE::RU)}),
        cube.getEdgeInd({cube.getColour(EEDGE::DL), cube.getColour(EEDGE::LD)}),
        cube.getEdgeInd({cube.getColour(EEDGE::DR), cube.getColour(EEDGE::RD)}),
        cube.getEdgeInd({cube.getColour(EEDGE::RF), cube.getColour(EEDGE::FR)}),
        cube.getEdgeInd({cube.getColour(EEDGE::RB), cube.getColour(EEDGE::BR)}),
        cube.getEdgeInd({cube.getColour(EEDGE::LF), cube.getColour(EEDGE::FL)}),
        cube.getEdgeInd({cube.getColour(EEDGE::LB), cube.getColour(EEDGE::BL)}),
    };

    // stores the location of all corners
    std::array<uint8_t, 8> cornersPerm = {
        cube.getCornerInd({ cube.getColour(ECORNER::LUB), cube.getColour(ECORNER::ULB), cube.getColour(ECORNER::BLU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RUF), cube.getColour(ECORNER::URF), cube.getColour(ECORNER::FRU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RDB), cube.getColour(ECORNER::DRB), cube.getColour(ECORNER::BRD) }),
        cube.getCornerInd({ cube.getColour(ECORNER::LDF), cube.getColour(ECORNER::DLF), cube.getColour(ECORNER::FLD) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RUB), cube.getColour(ECORNER::URB), cube.getColour(ECORNER::BRU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::LUF), cube.getColour(ECORNER::ULF), cube.getColour(ECORNER::FLU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::LDB), cube.getColour(ECORNER::DLB), cube.getColour(ECORNER::BLD) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RDF), cube.getColour(ECORNER::DRF), cube.getColour(ECORNER::FRD) }),
    };

    // stores the location of the edges of the E-slice
    std::array<uint8_t, 4> edgesPosComb;

    for (uint8_t i = 0, e = 0; i < 8 && e < 3; ++i)
    {
        // indices of the E-slice edges are 4, 5, 6, 7
        if (edgesPerm[i] == 4 || edgesPerm[i] == 5 ||
            edgesPerm[i] == 6 || edgesPerm[i] == 7)
        {
            edgesPosComb[e++] = i + 1;
        }
    }

    uint32_t cornersInd = 0;


    uint32_t edgesInd   = 0;

    for (uint8_t n = 4, k = 4; n > 0; --n, --k)
    {
        edgesInd   += nCk(edgesPosComb[n - 1]   - 1, k);
    }

    //     0.......69 * 70 + 0.....69 = 0......4899
    return cornersInd * 70 + edgesInd;
}
