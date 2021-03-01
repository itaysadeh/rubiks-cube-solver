#include "G2_G3_goal.h"

bool G2_G3_Goal::contented(const Rubiks& cube) const
{
    using ECOLOUR = Rubiks::ECOLOUR;

    for (std::size_t i = 0; i < 8; i++)
    {
        if (cube.getColour(0x00 + i) != ECOLOUR::W && cube.getColour(0x00 + i) != ECOLOUR::Y ||
            cube.getColour(0x08 + i) != ECOLOUR::O && cube.getColour(0x08 + i) != ECOLOUR::R ||
            cube.getColour(0x10 + i) != ECOLOUR::G && cube.getColour(0x10 + i) != ECOLOUR::B ||
            cube.getColour(0x18 + i) != ECOLOUR::R && cube.getColour(0x18 + i) != ECOLOUR::O ||
            cube.getColour(0x20 + i) != ECOLOUR::B && cube.getColour(0x20 + i) != ECOLOUR::G ||
            cube.getColour(0x28 + i) != ECOLOUR::Y && cube.getColour(0x28 + i) != ECOLOUR::W)
        {
            return false;
        }
    }
    return true;
}
