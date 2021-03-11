#include "G2_G3_goal.h"

bool G2_G3_Goal::contented(const Rubiks& cube) const
{
    using ECOLOUR = Rubiks::ECOLOUR;
    using ECORNER = Rubiks::ECORNER;
    using EEDGE   = Rubiks::EEDGE;

    // indices of all corners split to two tetrads (positions 0...3 and 4...7)
    std::array<uint8_t, 8> cornersPerm = {
        cube.getCornerInd({ cube.getColour(ECORNER::LUB), cube.getColour(ECORNER::ULB), cube.getColour(ECORNER::BLU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::LUF), cube.getColour(ECORNER::ULF), cube.getColour(ECORNER::FLU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::LDF), cube.getColour(ECORNER::DLF), cube.getColour(ECORNER::FLD) }),
        cube.getCornerInd({ cube.getColour(ECORNER::LDB), cube.getColour(ECORNER::DLB), cube.getColour(ECORNER::BLD) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RUF), cube.getColour(ECORNER::URF), cube.getColour(ECORNER::FRU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RUB), cube.getColour(ECORNER::URB), cube.getColour(ECORNER::BRU) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RDB), cube.getColour(ECORNER::DRB), cube.getColour(ECORNER::BRD) }),
        cube.getCornerInd({ cube.getColour(ECORNER::RDF), cube.getColour(ECORNER::DRF), cube.getColour(ECORNER::FRD) }),
    };

    using compareRanks = std::array< uint8_t, 8>;

    constexpr compareRanks unaffected      = { 0, 1, 2, 3, 4, 5, 6, 7 };
    constexpr compareRanks mirrored        = { 0, 1, 2, 3, 7, 6, 5, 4 };
    constexpr compareRanks mirroredOrdered = { 0, 1, 2, 3, 6, 7, 4, 5 };

    // tetrad comparators 
    auto comparePerm = [&](const compareRanks& ind)->bool {
        return
            cornersPerm[ind[0]] == cornersPerm[ind[4]] &&
            cornersPerm[ind[1]] == cornersPerm[ind[5]] &&
            cornersPerm[ind[2]] == cornersPerm[ind[6]] &&
            cornersPerm[ind[3]] == cornersPerm[ind[7]];
    };
    auto comparePermDiff = [&](const compareRanks& ind)->bool {
        return
            // this comparison is made when the tetrad's ranks are differnt
            cornersPerm[ind[1]] == cornersPerm[ind[5]] ||
            cornersPerm[ind[2]] == cornersPerm[ind[6]] ||
            cornersPerm[ind[3]] == cornersPerm[ind[7]];
    };

    // every corner gets a rank in relation to it's own tetrad (0..3)
    for (uint8_t i = 0; i < 8; ++i)
    {
        // the first tetrad contains all the corners with even indices
        if (i <= 3 && (cornersPerm[i] & 1))
        {
            return false;
        }
        cornersPerm[i] >>= 1;
    }

    // the tetrad's rank is determined by the rank of the first corner
    uint8_t l_tetradRank = cornersPerm[0];
    uint8_t r_tetradRank = cornersPerm[4];
    // pairs in good states are (0,1) and (2,3) without regard to order
    bool    pairsState   = (cornersPerm[0] & 2) == (cornersPerm[1] & 2);
    
    // if ((l_tetradRank ^ r_tetradRank) == 3)

    if (pairsState)
    {
        if (!comparePerm(unaffected))
        {
            if (l_tetradRank == r_tetradRank ||
                comparePermDiff(unaffected))
            {
                return false;
            }
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