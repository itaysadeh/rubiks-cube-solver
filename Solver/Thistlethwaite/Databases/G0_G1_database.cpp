#include "G0_G1_database.h"

uint32_t G0_G1_Database::getIndex(const Rubiks& cube) const
{
    using EEDGE = Rubiks::EEDGE;

    // stores the orientation of all edges (by position, regardless of which edge is where)
    // the orientation of 11 edges dictates the orientation of the 12th edge (even orientation values)
    std::array<uint8_t, 11> eOrientationPerm = {
        cube.getEdgeOrientation({ cube.getColour(EEDGE::RB), cube.getColour(EEDGE::BR) }),
        cube.getEdgeOrientation({ cube.getColour(EEDGE::RF), cube.getColour(EEDGE::FR) }),
        cube.getEdgeOrientation({ cube.getColour(EEDGE::RU), cube.getColour(EEDGE::UR) }),
        cube.getEdgeOrientation({ cube.getColour(EEDGE::RD), cube.getColour(EEDGE::DR) }),
        cube.getEdgeOrientation({ cube.getColour(EEDGE::LB), cube.getColour(EEDGE::BL) }),
        cube.getEdgeOrientation({ cube.getColour(EEDGE::LF), cube.getColour(EEDGE::FL) }),
        cube.getEdgeOrientation({ cube.getColour(EEDGE::LU), cube.getColour(EEDGE::UL) }),
        cube.getEdgeOrientation({ cube.getColour(EEDGE::LD), cube.getColour(EEDGE::DL) }),
        cube.getEdgeOrientation({ cube.getColour(EEDGE::UB), cube.getColour(EEDGE::BU) }),
        cube.getEdgeOrientation({ cube.getColour(EEDGE::UF), cube.getColour(EEDGE::FU) }),
        cube.getEdgeOrientation({ cube.getColour(EEDGE::DB), cube.getColour(EEDGE::BD) }),
    };

    // converts to decimal

    // 0..2^11 - 1 = 0..2047
    return
       eOrientationPerm[0]  +
       eOrientationPerm[1]  * 2 +
       eOrientationPerm[2]  * 4 +
       eOrientationPerm[3]  * 8 +
       eOrientationPerm[4]  * 16 +
       eOrientationPerm[5]  * 32 +
       eOrientationPerm[6]  * 64 +
       eOrientationPerm[7]  * 128 +
       eOrientationPerm[8]  * 256 +
       eOrientationPerm[9]  * 512 +
       eOrientationPerm[10] * 1024;
}
