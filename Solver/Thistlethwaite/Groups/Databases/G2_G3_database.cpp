#include "G2_G3_database.h"

uint32_t G2_G3_Database::getIndex(const Rubiks& cube) const
{
    using EEDGE   = Rubiks::EEDGE;
    using ECORNER = Rubiks::ECORNER;
    using ECOLOUR = Rubiks::ECOLOUR;

    // orientation of the corners is already solved, so corners are treated as if
    // the R/L facelet doesn't exist, and each corner only has an U/D or F/B facelet

    // F/B adjacents always correspond to these
    std::array<ECOLOUR, 8> cornersPerm = {
        cube.getColour(ECORNER::UBL),
        cube.getColour(ECORNER::UBR),
        cube.getColour(ECORNER::UFR),
        cube.getColour(ECORNER::UFL),
        cube.getColour(ECORNER::DBL),
        cube.getColour(ECORNER::DBR),
        cube.getColour(ECORNER::DFR),
        cube.getColour(ECORNER::DFL),
    };

    std::bitset<8> orientationsPerm;

    for (uint8_t i = 0; i < 8; ++i)
    {
        uint8_t o = (cornersPerm[i] == ECOLOUR::W || cornersPerm[i] == ECOLOUR::Y) ? 0 : 1;
        orientationsPerm.set(i, o);
    }

    return orientationsPerm.to_ulong();
}
