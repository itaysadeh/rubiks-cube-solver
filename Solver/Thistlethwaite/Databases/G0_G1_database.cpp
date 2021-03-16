#include "G0_G1_database.h"

uint32_t G0_G1_Database::getIndex(const Rubiks& cube) const
{
    using EEDGE = Rubiks::EEDGE;

    // for each of the 11 edges (12th can be assumed www.ryanheise.com/cube/cube_laws.html)
    // get the orientation (0/1) and convert the binary permutation to a decimal number

    // store the orientation of all edges (by position, regardless of which edge is where)
    std::array<uint8_t, 11> edgeOrientationPerm = {
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

    // convert to decimal: 0...2^11 - 1 = 0...2047
    return
       edgeOrientationPerm[0]  +
       edgeOrientationPerm[1]  * 2 +
       edgeOrientationPerm[2]  * 4 +
       edgeOrientationPerm[3]  * 8 +
       edgeOrientationPerm[4]  * 16 +
       edgeOrientationPerm[5]  * 32 +
       edgeOrientationPerm[6]  * 64 +
       edgeOrientationPerm[7]  * 128 +
       edgeOrientationPerm[8]  * 256 +
       edgeOrientationPerm[9]  * 512 +
       edgeOrientationPerm[10] * 1024;
}
