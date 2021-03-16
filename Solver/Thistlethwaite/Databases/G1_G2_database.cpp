#include "G1_G2_database.h"

uint32_t G1_G2_Database::getIndex(const Rubiks& cube) const
{
    using EEDGE   = Rubiks::EEDGE;
    using ECORNER = Rubiks::ECORNER;
    using ECOLOUR = Rubiks::ECOLOUR;

    // store the orientation of all corners (by position, regardless of which corner is where)
    std::array<uint8_t, 7> cOrientationPerm = {
        //  face:                 {               L/R                          U/D                            F/B            }
        cube.getCornerOrientation({ cube.getColour(ECORNER::LUB), cube.getColour(ECORNER::ULB), cube.getColour(ECORNER::BLU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::LUF), cube.getColour(ECORNER::ULF), cube.getColour(ECORNER::FLU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::LDF), cube.getColour(ECORNER::DLF), cube.getColour(ECORNER::FLD) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::LDB), cube.getColour(ECORNER::DLB), cube.getColour(ECORNER::BLD) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::RUF), cube.getColour(ECORNER::URF), cube.getColour(ECORNER::FRU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::RUB), cube.getColour(ECORNER::URB), cube.getColour(ECORNER::BRU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::RDB), cube.getColour(ECORNER::DRB), cube.getColour(ECORNER::BRD) })
    };

    // store the positions of all edges
    // the first 4 positions are in the M-slice in order to make a solved state the lowest combination: 0,1,2,3
    std::array<uint8_t, 12> ePosPerm = {
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
    std::array<uint8_t, 4> ePosComb;

    for (uint8_t i = 0, e = 0; i < 12 && e < 4; ++i)
    {
        // indices of the M-slice edges are 1, 2, 9 and 10
        if (ePosPerm[i] == 1 || ePosPerm[i] == 2 ||
            ePosPerm[i] == 9 || ePosPerm[i] == 10)
        {
            ePosComb[e++] = i + 1;
        }
    }

    uint32_t eInd = combIndexer.getInd(ePosComb); // edge
    uint32_t cInd = 0;                            // corner

    // treat corner orientations as ternary numbers and convert it to decimal
    cInd +=
        cOrientationPerm[0] +
        cOrientationPerm[1] * 3 +
        cOrientationPerm[2] * 9 +
        cOrientationPerm[3] * 27 +
        cOrientationPerm[4] * 81 +
        cOrientationPerm[5] * 243 +
        cOrientationPerm[6] * 729;

    // 0.....2186 * 495 + 0....494 = 0....1082565
    return cInd * 495 + eInd;
}
