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

    using compareIndices = std::array< uint8_t, 4>;

    constexpr compareIndices r_tetrad                = { 4, 5, 6, 7 };
    constexpr compareIndices r_tetradMirrored        = { 7, 6, 5, 4 };
    constexpr compareIndices r_tetradMirroredOrdered = { 6, 7, 4, 5 };

    // tetrad comparators 
    auto comparePerm = [&](const compareIndices& ind)->bool {
        return
            cornersPerm[0] == cornersPerm[ind[0]] &&
            cornersPerm[1] == cornersPerm[ind[1]] &&
            cornersPerm[2] == cornersPerm[ind[2]] &&
            cornersPerm[3] == cornersPerm[ind[3]];
    };
    auto comparePermDiff = [&](const compareIndices& ind, bool checkRank = true)->bool {
        if (checkRank && cornersPerm[0] == cornersPerm[ind[0]])
        {
            return true;
        }
        return
            cornersPerm[1] == cornersPerm[ind[1]] ||
            cornersPerm[2] == cornersPerm[ind[2]] ||
            cornersPerm[3] == cornersPerm[ind[3]];
    };

    // the tetrad's rank is determined by the rank of the first corner
    uint8_t l_tetradRank = cornersPerm[0];
    uint8_t r_tetradRank = cornersPerm[4];
    // pairs in good states are (0,1) and (2,3) without regard to order
    bool    pairsState   = cornersPerm[0] & 2 == cornersPerm[1] & 2;

    // both tetrads have the same rank
    if (l_tetradRank == r_tetradRank)
    {
        if (pairsState)
        {
            // if the pairs are good and the tetrads have the same rank, the permutation has to be the same
            if (!comparePerm(r_tetrad))
                return false;
        }
        else
        {
            // if the pairs are bad and the tetrads have the same rank, the 3 remaining corners can't match
            if (comparePermDiff(r_tetrad, false))
                return false;
        }
    }
    else
    {
        // if the ranks are (0,3) or (1,2) with no relation to order
        if ((l_tetradRank ^ r_tetradRank) == 3)
        {
            if (pairsState)
            {
                // if pairs are good, the permutation has to be mirrored
                if (!comparePerm(r_tetradMirrored))
                    return false;
            }
            else
            {
                // if pairs are bad, the permutation has to be mirrored
            }
        }
        else
        {
            // if the state of pairs is good, the permutations has to be
            // mirrored without changing the order of the pairs
            if (pairsState)
            {
                if (cornersPerm[0] != cornersPerm[6] ||
                    cornersPerm[1] != cornersPerm[7] ||
                    cornersPerm[2] != cornersPerm[4] ||
                    cornersPerm[3] != cornersPerm[5])
                {
                    return false;
                }
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