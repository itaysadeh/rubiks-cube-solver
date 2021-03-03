#include "G3_G4_goal.h"

bool G3_G4_Goal::contented(const Rubiks& cube) const
{
    return cube.isSovled();
}
