#include "tdatabase.h"

uint32_t TDatabase::getInd(const Rubiks& cube) const
{
    using EPIECE = Rubiks::EPIECE;

    // edge and corner orientation permutation (by position,
    // regardless of which piece is currently occupying each position)
    std::array<uint8_t, 12> E_orientationPerm = {
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
        cube.getEdgeOrientation(cube.getEdge(EPIECE::DF)),
    };
    std::array<uint8_t, 8> C_orientationPerm = {
        cube.getCornerOrientation(cube.getCorner(EPIECE::ULB)),
        cube.getCornerOrientation(cube.getCorner(EPIECE::ULF)),
        cube.getCornerOrientation(cube.getCorner(EPIECE::DLF)),
        cube.getCornerOrientation(cube.getCorner(EPIECE::DLB)),
        cube.getCornerOrientation(cube.getCorner(EPIECE::URF)),
        cube.getCornerOrientation(cube.getCorner(EPIECE::URB)),
        cube.getCornerOrientation(cube.getCorner(EPIECE::DRB)),
        cube.getCornerOrientation(cube.getCorner(EPIECE::DRF)),
    };

    return 1;
}
