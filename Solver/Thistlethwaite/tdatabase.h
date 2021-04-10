#ifndef TDATABASE_H
#define TDATABASE_H

#include <cstdint>
#include "../../Cube/cube.h"
#include "../database.h"

#include <array>

class TDatabase : public Database
{
public:

    enum class EGroupState { G0, G1, G2, G3, G4 };

    uint32_t getInd(const Rubiks& cube) const override;

private:
    const size_t m_sizeG0 = 2048;
    const size_t m_sizeG1 = 1082565;
    const size_t m_sizeG2 = 352800;
    const size_t m_sizeG3 = 663552;
};

#endif // TDATABASE_H
