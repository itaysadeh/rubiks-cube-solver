#include "G2_G3_goal.h"

bool G2_G3_Goal::contented(const Rubiks& cube) const
{
    using ECOLOUR = Rubiks::ECOLOUR;
    using ECORNER = Rubiks::ECORNER;
    using EEDGE   = Rubiks::EEDGE;

    // store the location of all corners
    std::array<std::array<uint8_t, 2>, 4> cPairPerm = {
        cube.getCornerInd({ cube.getColour(ECORNER::LUB), cube.getColour(ECORNER::ULB), cube.getColour(ECORNER::BLU) }), // ULB WBO 0
        cube.getCornerInd({ cube.getColour(ECORNER::LDF), cube.getColour(ECORNER::DLF), cube.getColour(ECORNER::FLD) }), // DLF YGO 2
        cube.getCornerInd({ cube.getColour(ECORNER::RDB), cube.getColour(ECORNER::DRB), cube.getColour(ECORNER::BRD) }), // DRB YBR 4
        cube.getCornerInd({ cube.getColour(ECORNER::RUB), cube.getColour(ECORNER::URB), cube.getColour(ECORNER::BRU) }), // URB WBR 6
        cube.getCornerInd({ cube.getColour(ECORNER::LUF), cube.getColour(ECORNER::ULF), cube.getColour(ECORNER::FLU) }), // ULF WGO 1
        cube.getCornerInd({ cube.getColour(ECORNER::LDB), cube.getColour(ECORNER::DLB), cube.getColour(ECORNER::BLD) }), // DLB YBO 3
        cube.getCornerInd({ cube.getColour(ECORNER::RDF), cube.getColour(ECORNER::DRF), cube.getColour(ECORNER::FRD) }), // DRF YGR 5
        cube.getCornerInd({ cube.getColour(ECORNER::RUF), cube.getColour(ECORNER::URF), cube.getColour(ECORNER::FRU) }), // URF WGR 7
    };

    std::array<uint8_t, 8> cPosPerm = {
        cube.getCornerInd({ cube.getColour(ECORNER::LUB), cube.getColour(ECORNER::ULB), cube.getColour(ECORNER::BLU) }), // ULB WBO 0
        cube.getCornerInd({ cube.getColour(ECORNER::LDF), cube.getColour(ECORNER::DLF), cube.getColour(ECORNER::FLD) }), // DLF YGO 2
        cube.getCornerInd({ cube.getColour(ECORNER::RDB), cube.getColour(ECORNER::DRB), cube.getColour(ECORNER::BRD) }), // DRB YBR 4
        cube.getCornerInd({ cube.getColour(ECORNER::RUB), cube.getColour(ECORNER::URB), cube.getColour(ECORNER::BRU) }), // URB WBR 6
        cube.getCornerInd({ cube.getColour(ECORNER::LUF), cube.getColour(ECORNER::ULF), cube.getColour(ECORNER::FLU) }), // ULF WGO 1
        cube.getCornerInd({ cube.getColour(ECORNER::LDB), cube.getColour(ECORNER::DLB), cube.getColour(ECORNER::BLD) }), // DLB YBO 3
        cube.getCornerInd({ cube.getColour(ECORNER::RDF), cube.getColour(ECORNER::DRF), cube.getColour(ECORNER::FRD) }), // DRF YGR 5
        cube.getCornerInd({ cube.getColour(ECORNER::RUF), cube.getColour(ECORNER::URF), cube.getColour(ECORNER::FRU) }), // URF WGR 7
    };

//    // convert 'perm[position] = piece;' to 'perm[piece] = position;'
//    std::array<uint8_t, 8> cPiecePerm;
//    for (uint8_t i = 0; i < 8; ++i)
//    {
//        cPiecePerm[cPosPerm[i]] = i;
//    }

    // check for even parity (0 = even, 1 = odd)
    uint8_t parity = 0;

    for (uint8_t i = 0; i < 8; ++i)
    {
        for (uint8_t j = i + 1; j < 8; ++j)
        {
            parity ^= cPosPerm[i] < cPosPerm[j];
        }
    }
    // return false if parity is odd
    if (parity == 1)
    {
        std::cout << "PARITY IS ODD:\n";
        for (uint8_t i = 0; i < 8; ++i)
        {
            std::cout << (int)cPosPerm[i] << " ";
        }
        return false;
    }

    // check that the 4 pairs are formed
    for (uint8_t i = 0; i < 4; ++i)
    {
        // order the pairs in ascending order
        if (cPairPerm[i][0] > cPairPerm[i][1])
        {
            std::swap(cPairPerm[i][0], cPairPerm[i][1]);
        }
        if ((cPairPerm[i][0] & 5) != (cPairPerm[i][1] & 5))
        {
            std::cout << "WRONG PAIRS:\n";
            for (uint8_t i = 0; i < 4; ++i)
            {
                std::cout << (int)cPairPerm[i][0] << (int)cPairPerm[i][1] << " ";
            }
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
