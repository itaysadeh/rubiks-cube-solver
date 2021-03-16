#include "G2_G3_goal.h"

bool G2_G3_Goal::contented(const Rubiks& cube) const
{
    using ECOLOUR = Rubiks::ECOLOUR;
    using ECORNER = Rubiks::ECORNER;
    using EEDGE   = Rubiks::EEDGE;

    // store the indices of all the corners in relation to the pairs in G3 (0:1, 2:3, 4:5, 6:7 with no order within the pairs)
    std::array<uint8_t, 8> cornerPosPerm = {
        cube.getCornerInd({ cube.getColour(ECORNER::LUB), cube.getColour(ECORNER::ULB), cube.getColour(ECORNER::BLU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::LUF), cube.getColour(ECORNER::ULF), cube.getColour(ECORNER::FLU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::LDB), cube.getColour(ECORNER::DLB), cube.getColour(ECORNER::BLD) }),
        cube.getCornerInd({ cube.getColour(ECORNER::LDF), cube.getColour(ECORNER::DLF), cube.getColour(ECORNER::FLD) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RDB), cube.getColour(ECORNER::DRB), cube.getColour(ECORNER::BRD) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RDF), cube.getColour(ECORNER::DRF), cube.getColour(ECORNER::FRD) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RUF), cube.getColour(ECORNER::URF), cube.getColour(ECORNER::FRU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RUB), cube.getColour(ECORNER::URB), cube.getColour(ECORNER::BRU) }),
    };

    // check for even parity (0 = even, 1 = odd)
    uint8_t parity = 0;

    for (uint8_t i = 0; i < 8; ++i)
    {
        for (uint8_t j = i + 1; j < 8; ++j)
        {
            parity ^= cornerPosPerm[i] < cornerPosPerm[j];
        }
    }

    if (parity == 1) return false;

    // check that the corners are formed
    for (uint8_t i = 0; i < 6; i += 2)
    {
        // order the pairs in ascending order
        if (cornerPosPerm[i] > cornerPosPerm[i + 1])
        {
            std::swap(cornerPosPerm[i], cornerPosPerm[i + 1]);
        }
        if (cornerPosPerm[i] != cornerPosPerm[i + 1] - 1)
        {
            return false;
        }
    }

    // check if all the edges are in their home slice (M-slice edges are already solved)
    return
        (cube.getColour(EEDGE::UR) == ECOLOUR::W || cube.getColour(EEDGE::UR) == ECOLOUR::Y) &&
        (cube.getColour(EEDGE::UL) == ECOLOUR::W || cube.getColour(EEDGE::UL) == ECOLOUR::Y) &&
        (cube.getColour(EEDGE::DR) == ECOLOUR::W || cube.getColour(EEDGE::DR) == ECOLOUR::Y) &&
        (cube.getColour(EEDGE::DL) == ECOLOUR::W || cube.getColour(EEDGE::DL) == ECOLOUR::Y) &&

        (cube.getColour(EEDGE::FR) == ECOLOUR::G || cube.getColour(EEDGE::FR) == ECOLOUR::B) &&
        (cube.getColour(EEDGE::FL) == ECOLOUR::G || cube.getColour(EEDGE::FL) == ECOLOUR::B) &&
        (cube.getColour(EEDGE::BR) == ECOLOUR::G || cube.getColour(EEDGE::BR) == ECOLOUR::B) &&
        (cube.getColour(EEDGE::BL) == ECOLOUR::G || cube.getColour(EEDGE::BL) == ECOLOUR::B);
}
