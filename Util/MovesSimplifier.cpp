#include "MovesSimplifier.h"

bool MovesSimplifier::isRedundant(EMOVE curr, EMOVE last) const
{
    // moves on the same face are redundant since:
    // L->L     is the same as L2
    // L->L'    cancels each other out
    // L->L2    is the same as L'

    // moves on opposite faces are redundant since:
    // R->L is the same as L->R
    // but since it's impossible to prune both of these, only check for one of the two combinations

    return (
        ((curr == EMOVE::U || curr == EMOVE::Up || curr == EMOVE::U2) &&
            ((last == EMOVE::U || last == EMOVE::Up || last == EMOVE::U2) ||
                (last == EMOVE::D || last == EMOVE::Dp || last == EMOVE::D2))) ||

        ((curr == EMOVE::L || curr == EMOVE::Lp || curr == EMOVE::L2) &&
            ((last == EMOVE::L || last == EMOVE::Lp || last == EMOVE::L2) ||
                (last == EMOVE::R || last == EMOVE::Rp || last == EMOVE::R2))) ||

        ((curr == EMOVE::F || curr == EMOVE::Fp || curr == EMOVE::F2) &&
            ((last == EMOVE::F || last == EMOVE::Fp || last == EMOVE::F2) ||
                (last == EMOVE::B || last == EMOVE::Bp || last == EMOVE::B2))) ||

        ((curr == EMOVE::R || curr == EMOVE::Rp || curr == EMOVE::R2) &&
            (last == EMOVE::R || last == EMOVE::Rp || last == EMOVE::R2)) ||

        ((curr == EMOVE::B || curr == EMOVE::Bp || curr == EMOVE::B2) &&
            (last == EMOVE::B || last == EMOVE::Bp || last == EMOVE::B2)) ||

        ((curr == EMOVE::D || curr == EMOVE::Dp || curr == EMOVE::D2) &&
            (last == EMOVE::D || last == EMOVE::Dp || last == EMOVE::D2)));
}
