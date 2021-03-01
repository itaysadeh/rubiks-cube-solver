#include "G0_G1_database.h"

uint32_t G0_G1_Database::getIndex(const Rubiks& cube) const
{
    using EEDGE = Rubiks::EEDGE;

    // for each of the 11 edges (12th can be assumed www.ryanheise.com/cube/cube_laws.html)
    // get the orientation (0/1) and convert the binary permutation to a decimal number

    std::bitset<11> orientationPerm;

    // permutation based on position on the cube, not edge indices
    orientationPerm.set(0,  cube.getEdgeOrientation({ cube.getColour(EEDGE::RB), cube.getColour(EEDGE::BR) }));
    orientationPerm.set(1,  cube.getEdgeOrientation({ cube.getColour(EEDGE::RF), cube.getColour(EEDGE::FR) }));
    orientationPerm.set(2,  cube.getEdgeOrientation({ cube.getColour(EEDGE::RU), cube.getColour(EEDGE::UR) }));
    orientationPerm.set(3,  cube.getEdgeOrientation({ cube.getColour(EEDGE::RD), cube.getColour(EEDGE::DR) }));
    orientationPerm.set(4,  cube.getEdgeOrientation({ cube.getColour(EEDGE::LB), cube.getColour(EEDGE::BL) }));
    orientationPerm.set(5,  cube.getEdgeOrientation({ cube.getColour(EEDGE::LF), cube.getColour(EEDGE::FL) }));
    orientationPerm.set(6,  cube.getEdgeOrientation({ cube.getColour(EEDGE::LU), cube.getColour(EEDGE::UL) }));
    orientationPerm.set(7,  cube.getEdgeOrientation({ cube.getColour(EEDGE::LD), cube.getColour(EEDGE::DL) }));
    orientationPerm.set(8,  cube.getEdgeOrientation({ cube.getColour(EEDGE::UB), cube.getColour(EEDGE::BU) }));
    orientationPerm.set(9,  cube.getEdgeOrientation({ cube.getColour(EEDGE::UF), cube.getColour(EEDGE::FU) }));
    orientationPerm.set(10, cube.getEdgeOrientation({ cube.getColour(EEDGE::DB), cube.getColour(EEDGE::BD) }));

    // convert to decimal
    return orientationPerm.to_ulong();
}
