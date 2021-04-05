#include "G0_G1_database.h"

uint32_t G0_G1_Database::getIndex(const Rubiks& cube) const
{
    using EPIECE = Rubiks::EPIECE;

    // stores the orientation of all edges (by position, regardless of which edge is where)
    // the orientation of 11 edges dictates the orientation of the 12th edge (even orientation values)
    std::array<uint8_t, 11> eOrientationPerm = {
        cube.getEdgeOrientation(cube.getEdge(EPIECE::RB)),
        cube.getEdgeOrientation(cube.getEdge(EPIECE::RF)),
        cube.getEdgeOrientation(cube.getEdge(EPIECE::UR)),
        cube.getEdgeOrientation(cube.getEdge(EPIECE::DR)),
        cube.getEdgeOrientation(cube.getEdge(EPIECE::LB)),
        cube.getEdgeOrientation(cube.getEdge(EPIECE::LF)),
        cube.getEdgeOrientation(cube.getEdge(EPIECE::UL)),
        cube.getEdgeOrientation(cube.getEdge(EPIECE::DL)),
        cube.getEdgeOrientation(cube.getEdge(EPIECE::UB)),
        cube.getEdgeOrientation(cube.getEdge(EPIECE::UF)),
        cube.getEdgeOrientation(cube.getEdge(EPIECE::DB)),
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
