#include "G1_G2_database.h"

uint32_t G1_G2_Database::getIndex(const Rubiks& cube) const
{
    using EEDGE   = Rubiks::EEDGE;
    using ECORNER = Rubiks::ECORNER;
    using ECOLOUR = Rubiks::ECOLOUR;

    // 0!.....12!
    constexpr std::array<uint32_t, 13> factorial = { 1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600 };

    // calculate nCk = n! / (k!(n - k)!)
    auto nCk = [&](uint8_t n, uint8_t k)->uint32_t {
        if (n < k)  return 0;
        if (n == k) return 1;
        return factorial[n] / (factorial[k] * factorial[n - k]);
    };

    // store the orientation of the corners
    std::array<uint8_t, 7> cornerOrientations = {
        //  face:                 {               L/R                          U/D                            F/B            }
        cube.getCornerOrientation({ cube.getColour(ECORNER::LUB), cube.getColour(ECORNER::ULB), cube.getColour(ECORNER::BLU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::LUF), cube.getColour(ECORNER::ULF), cube.getColour(ECORNER::FLU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::LDF), cube.getColour(ECORNER::DLF), cube.getColour(ECORNER::FLD) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::LDB), cube.getColour(ECORNER::DLB), cube.getColour(ECORNER::BLD) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::RUF), cube.getColour(ECORNER::URF), cube.getColour(ECORNER::FRU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::RUB), cube.getColour(ECORNER::URB), cube.getColour(ECORNER::BRU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::RDB), cube.getColour(ECORNER::DRB), cube.getColour(ECORNER::BRD) })
    };

    // the first 4 edges positions are the M-slice edge positions (a solved combination is the lowest combination)
    std::array<uint8_t, 12> edgeIndices = {
        cube.getEdgeInd({ cube.getColour(EEDGE::UB), cube.getColour(EEDGE::BU) }),
        cube.getEdgeInd({ cube.getColour(EEDGE::UF), cube.getColour(EEDGE::FU) }),
        cube.getEdgeInd({ cube.getColour(EEDGE::DB), cube.getColour(EEDGE::BD) }),
        cube.getEdgeInd({ cube.getColour(EEDGE::DF), cube.getColour(EEDGE::FD) }),
        cube.getEdgeInd({ cube.getColour(EEDGE::UR), cube.getColour(EEDGE::RU) }),
        cube.getEdgeInd({ cube.getColour(EEDGE::UL), cube.getColour(EEDGE::LU) }),
        cube.getEdgeInd({ cube.getColour(EEDGE::DR), cube.getColour(EEDGE::RD) }),
        cube.getEdgeInd({ cube.getColour(EEDGE::DL), cube.getColour(EEDGE::LD) }),
        cube.getEdgeInd({ cube.getColour(EEDGE::FR), cube.getColour(EEDGE::RF) }),
        cube.getEdgeInd({ cube.getColour(EEDGE::FL), cube.getColour(EEDGE::LF) }),
        cube.getEdgeInd({ cube.getColour(EEDGE::BR), cube.getColour(EEDGE::RB) }),
        cube.getEdgeInd({ cube.getColour(EEDGE::BL), cube.getColour(EEDGE::LB) })
    };

    // store the positions of the 4 edges that need to be brought back to the M-slice
    std::array<uint8_t, 4> edgePositionsComb;

    for (uint8_t i = 0, c = 0; i < 12 && c < 4; ++i)
    {
        // indices of the M-slice edges are 1, 2, 9 and 10
        if (edgeIndices[i] == 1 || edgeIndices[i] == 2 ||
            edgeIndices[i] == 9 || edgeIndices[i] == 10)
        {
            edgePositionsComb[c++] = i + 1;
        }
    }

    // www.jaapsch.net/puzzles/compindx.htm                                                                                                    
    // an edge combination is ranked based on the amount of possible smaller edge combinations
    // because there is no repetition or regard to order, nCk is used assuming the positions
    // permutations are always in a decending order (p = position: p[0]> p[1] > p[2] > p[3])
    // index = p[0]-1C4 + p[1]-1C3 + p[2]-1C2 + p[3]-1C1

    uint32_t edgesInd   = 0;

    for (uint8_t n = 4, k = 4; n > 0; --n, --k)
    {
        edgesInd += nCk(edgePositionsComb[n - 1] - 1, k);
    }

    uint32_t cornersInd = 0;

    // treat corner orientations as ternary numbers and convert it to decimal
    cornersInd += 
        (cornerOrientations[0]) +
        (cornerOrientations[1] * 3) +
        (cornerOrientations[2] * 3 * 3) +
        (cornerOrientations[3] * 3 * 3 * 3) +
        (cornerOrientations[4] * 3 * 3 * 3 * 3) +
        (cornerOrientations[5] * 3 * 3 * 3 * 3 * 3) +
        (cornerOrientations[6] * 3 * 3 * 3 * 3 * 3 * 3);

    //     0.....2186 * 495 + 0....494 = 0....1082565
    return cornersInd * 495 + edgesInd;
}
