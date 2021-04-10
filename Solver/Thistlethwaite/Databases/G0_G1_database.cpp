#include "G0_G1_database.h"

uint32_t G0_G1_Database::getInd(const Rubiks& cube) const
{
    using EPIECE = Rubiks::EPIECE;

    // stores the orientation of all edges (by position, regardless of which edge is where)
    // the orientation of 11 edges dictates the orientation of the 12th edge (even orientation values)
    std::array<uint8_t, 11> E_orientationPerm = {
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
       E_orientationPerm[0]  +
       E_orientationPerm[1]  * 2 +
       E_orientationPerm[2]  * 4 +
       E_orientationPerm[3]  * 8 +
       E_orientationPerm[4]  * 16 +
       E_orientationPerm[5]  * 32 +
       E_orientationPerm[6]  * 64 +
       E_orientationPerm[7]  * 128 +
       E_orientationPerm[8]  * 256 +
       E_orientationPerm[9]  * 512 +
       E_orientationPerm[10] * 1024;
}
