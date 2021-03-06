#include "G2_G3_database.h"

#include "../../../Util/PermutationIndexer.h"

uint32_t G2_G3_Database::getIndex(const Rubiks& cube) const
{
    using EEDGE   = Rubiks::EEDGE;
    using ECORNER = Rubiks::ECORNER;
    using ECOLOUR = Rubiks::ECOLOUR;

    // first tertrad positions
    // cube.getCornerInd({ cube.getColour(ECORNER::ULF), cube.getColour(ECORNER::LUF), cube.getColour(ECORNER::FLU) }),
    // cube.getCornerInd({ cube.getColour(ECORNER::URB), cube.getColour(ECORNER::RUB), cube.getColour(ECORNER::BRU) }),
    // cube.getCornerInd({ cube.getColour(ECORNER::DLB), cube.getColour(ECORNER::LDB), cube.getColour(ECORNER::BLD) }),
    // cube.getCornerInd({ cube.getColour(ECORNER::DRF), cube.getColour(ECORNER::RDF), cube.getColour(ECORNER::FRD) }),

    // 70 combinations of the
    std::array<uint8_t, 8> cornersPerm = {
        cube.getCornerInd({ cube.getColour(ECORNER::LUB), cube.getColour(ECORNER::ULB), cube.getColour(ECORNER::BLU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::LUF), cube.getColour(ECORNER::ULF), cube.getColour(ECORNER::FLU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::LDF), cube.getColour(ECORNER::DLF), cube.getColour(ECORNER::FLD) }),
        cube.getCornerInd({ cube.getColour(ECORNER::LDB), cube.getColour(ECORNER::DLB), cube.getColour(ECORNER::BLD) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RUF), cube.getColour(ECORNER::URF), cube.getColour(ECORNER::FRU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RUB), cube.getColour(ECORNER::URB), cube.getColour(ECORNER::BRU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RDB), cube.getColour(ECORNER::DRB), cube.getColour(ECORNER::BRD) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RDF), cube.getColour(ECORNER::DRF), cube.getColour(ECORNER::FRD) }),
    };
    
    constexpr std::array<size_t, 13> factorial = { 1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600 };

    // calculate nCk = n! / (k!(n - k)!)
    auto nCk = [&](uint8_t n, uint8_t k)->uint32_t {
        if (n < k)  return 0;
        if (n == k) return 1;
        return factorial[n] / (factorial[k] * factorial[n - k]);
    };

    std::array<uint8_t, 4> tetradCornersPos;

    uint8_t c = 0;
    for (uint8_t i = 0; i < 8; ++i)
    {
        if (cornersPerm[i] & 1)
        {
            tetradCornersPos[c++] = i + 1;
        }
    }

    uint32_t ind = 0;

    uint8_t  k = 4;
    // reverse iterator to go from highest position to lowest position
    for (auto n = tetradCornersPos.begin(); n != tetradCornersPos.end(); ++n)
    {
        ind += nCk(*n - 1, k--);
    }

    //for (auto p : tetradCornersPos)
    //{
    //    std::cout << (int)p << " ";
    //}
    //std::cout << "\n";
    return ind;

}
