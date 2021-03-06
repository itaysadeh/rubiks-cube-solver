#include "G1_G2_database.h"

uint32_t G1_G2_Database::getIndex(const Rubiks& cube) const
{
    using EEDGE   = Rubiks::EEDGE;
    using ECORNER = Rubiks::ECORNER;
    using ECOLOUR = Rubiks::ECOLOUR;

    // store the orientation of all the corners (8th can be assumed based on the first 7)
    std::array<uint8_t, 7> cornerOrientations = {
        //                        {               L/R                          U/D                            F/B            }
        cube.getCornerOrientation({ cube.getColour(ECORNER::LUB), cube.getColour(ECORNER::ULB), cube.getColour(ECORNER::BLU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::LUF), cube.getColour(ECORNER::ULF), cube.getColour(ECORNER::FLU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::LDF), cube.getColour(ECORNER::DLF), cube.getColour(ECORNER::FLD) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::LDB), cube.getColour(ECORNER::DLB), cube.getColour(ECORNER::BLD) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::RUF), cube.getColour(ECORNER::URF), cube.getColour(ECORNER::FRU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::RUB), cube.getColour(ECORNER::URB), cube.getColour(ECORNER::BRU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::RDB), cube.getColour(ECORNER::DRB), cube.getColour(ECORNER::BRD) })
    };

    // the first 4 edges positions are in the M-slice (solved positions = 0;1;2;3 = lowest permutation)
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
    std::array<uint8_t, 4> edgePositionsPerm;

    uint8_t c = 0;
    for (uint8_t i = 0; i < 12 && c < 4; ++i)
    {
        // indices of the M-slice edges are 1, 2, 9 and 10
        if (edgeIndices[i] == 1 || edgeIndices[i] == 2 ||
            edgeIndices[i] == 9 || edgeIndices[i] == 10)
        {
            edgePositionsPerm[c++] = i + 1;
        }
    }

    // 0!.....12!
    constexpr std::array<size_t, 13> factorial = { 1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600 };

    // calculate nCk = n! / (k!(n - k)!)
    auto nCk = [&](uint8_t n, uint8_t k)->uint32_t {
        if (n < k)  return 0;
        if (n == k) return 1;
        return factorial[n] / (factorial[k] * factorial[n - k]);
    };

    // www.jaapsch.net/puzzles/compindx.htm                                                                                                    
    // edge index is calculated by getting the amount of possible smaller position combinations.
    // because there is no repetition or regard to order, nCk is used assuming the positions
    // perms are always in a decending order (p[0]> p[1] > p[2] > p[3])
    // index = p[0]-1C4 + p[1]-1C3 + p[2]-1C2 + p[3]-1C1

    uint32_t edgesInd   = 0;
    uint32_t cornersInd = 0;

    uint8_t  k = 4;
    // reverse iterator to go from highest position to lowest position
    for (auto n = edgePositionsPerm.rbegin(); n != edgePositionsPerm.rend(); ++n)
    {
        edgesInd += nCk(*n - 1, k--);
    }

    // treat corner orientations as ternary numbers and convert to decimal
    cornersInd += 
        (cornerOrientations[0]) +
        (cornerOrientations[1] * 3) +
        (cornerOrientations[2] * 3 * 3) +
        (cornerOrientations[3] * 3 * 3 * 3) +
        (cornerOrientations[4] * 3 * 3 * 3 * 3) +
        (cornerOrientations[5] * 3 * 3 * 3 * 3 * 3) +
        (cornerOrientations[6] * 3 * 3 * 3 * 3 * 3 * 3);

    //     0.....2186 * 495 + 0....495 = 0....1082565
    return cornersInd * 495 + edgesInd;
}
