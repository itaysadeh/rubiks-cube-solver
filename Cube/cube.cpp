#include "cube.h"

Rubiks::Rubiks()
{
    resetCube();
}

bool Rubiks::operator==(const Rubiks& lhs)
{
    return
        getFace(EFACE::U) == lhs.getFace(EFACE::U) &&
        getFace(EFACE::L) == lhs.getFace(EFACE::L) &&
        getFace(EFACE::F) == lhs.getFace(EFACE::F) &&
        getFace(EFACE::R) == lhs.getFace(EFACE::R) &&
        getFace(EFACE::B) == lhs.getFace(EFACE::B) &&
        getFace(EFACE::D) == lhs.getFace(EFACE::D);
}

Rubiks& Rubiks::operator=(const Rubiks& lhs)
{
    // copies in 6 chunks of 64 bits
    memcpy(&m_cube[0], &lhs.m_cube[0], sizeof(uint64_t) * 6);
    return *this;
}

void Rubiks::resetCube()
{
    setFace(EFACE::U, 0x0000000000000000);
    setFace(EFACE::L, 0x0101010101010101);
    setFace(EFACE::F, 0x0202020202020202);
    setFace(EFACE::R, 0x0303030303030303);
    setFace(EFACE::B, 0x0404040404040404);
    setFace(EFACE::D, 0x0505050505050505);
}

bool Rubiks::isSovled() const
{
    return
        getFace(EFACE::U) == 0x0000000000000000 &&
        getFace(EFACE::L) == 0x0101010101010101 &&
        getFace(EFACE::F) == 0x0202020202020202 &&
        getFace(EFACE::R) == 0x0303030303030303 &&
        getFace(EFACE::B) == 0x0404040404040404 &&
        getFace(EFACE::D) == 0x0505050505050505;
}

void Rubiks::rotateFaceCW(EFACE face)
{
    // requires C++20
    setFace(face, std::rotl(getFace(face), 16));
}

void Rubiks::rotateFaceCCW(EFACE face)
{
    // requires C++20
    setFace(face, std::rotr(getFace(face), 16));
}

void Rubiks::rotateFace180(EFACE face)
{
    // requires C++20, 
    setFace(face, std::rotl(getFace(face), 32));
}

void Rubiks::rotateAdjacents(const adjacentIndices_t& adj)
{
    // rotates 16 bits (2 facelets) in 1 operation
    uint16_t tmpi0;
    memcpy(&tmpi0,          &m_cube[adj[0]], sizeof(uint16_t));
    memcpy(&m_cube[adj[0]], &m_cube[adj[1]], sizeof(uint16_t));
    memcpy(&m_cube[adj[1]], &m_cube[adj[2]], sizeof(uint16_t));
    memcpy(&m_cube[adj[2]], &m_cube[adj[3]], sizeof(uint16_t));
    memcpy(&m_cube[adj[3]], &tmpi0,          sizeof(uint16_t));
    // 3rd facelet is coppied by itself in case it's not continious in memory
    // (i.e indices 6,7,0 are affected in a L face rotation)
    uint8_t tmpi4;
    memcpy(&tmpi4,          &m_cube[adj[4]], sizeof(uint8_t));
    memcpy(&m_cube[adj[4]], &m_cube[adj[5]], sizeof(uint8_t));
    memcpy(&m_cube[adj[5]], &m_cube[adj[6]], sizeof(uint8_t));
    memcpy(&m_cube[adj[6]], &m_cube[adj[7]], sizeof(uint8_t));
    memcpy(&m_cube[adj[7]], &tmpi4, sizeof(uint8_t));
}

void Rubiks::rotateAdjacents180(const adjacentIndices_t& adj)
{
    std::swap(*(uint16_t*)&m_cube[adj[0]], *(uint16_t*)&m_cube[adj[2]]);
    std::swap(*(uint16_t*)&m_cube[adj[1]], *(uint16_t*)&m_cube[adj[3]]);

    std::swap(m_cube[adj[4]], m_cube[adj[6]]);
    std::swap(m_cube[adj[5]], m_cube[adj[7]]);
}

void Rubiks::setFace(EFACE face, uint64_t new_face)
{
    // sets the 8 bytes (facelets) in a face from a 64-bit integer
    memcpy(&m_cube[(unsigned)face * 8], &new_face, sizeof(uint64_t));
}

uint64_t Rubiks::getFace(EFACE face) const
{
    return *(uint64_t*)&m_cube[(unsigned)face * 8];
}

Rubiks::ECOLOUR Rubiks::getColour(uint8_t index) const
{
    return m_cube[index];
}

Rubiks::ECOLOUR Rubiks::getColour(ECORNER index) const
{
    return m_cube[(unsigned)index];
}

Rubiks::ECOLOUR Rubiks::getColour(EEDGE index) const
{
    return m_cube[(unsigned)index];
}

uint8_t Rubiks::getEdgeOrientation(const edge_t& edge) const
{
    return
         ((edge[0] == ECOLOUR::G || edge[0] == ECOLOUR::B) ||
         ((edge[0] == ECOLOUR::W || edge[0] == ECOLOUR::Y) &&
          (edge[1] == ECOLOUR::R || edge[1] == ECOLOUR::O)));

    // checks if a facelet has one of the colours from the R/L axis, if not, checks if it's from the U/D axis and
    // that the adjacent edge facelet has a colour from the F/B axis
}

uint8_t Rubiks::getCornerOrientation(const corner_t& corner) const
{
    // www.ryanheise.com/cube/cube_laws.html
    // orientation is determined by the twist of the corner, but this follows
    // a differnet logic to avoid unnecessary extra code

    // retrun 0 / 1 / 2 based on which axis the L/R colour is on
    for (uint8_t i = 0; i < 3; ++i)
    {
        if (corner[i] == ECOLOUR::R || corner[i] == ECOLOUR::O)
        {
            return i;
        }
    }

    throw std::logic_error("Rubiks::getCornerOrientation unable to get orientation, corner must have a R / O facelet");
}

uint8_t Rubiks::getEdgeInd(const edge_t& edge) const
{ 
    // unique index based on colour combinations
    uint8_t result = ((1 << (uint8_t)edge[0]) + (1 << (uint8_t)edge[1]));

    switch (result)
    {
    case 3:
        return 0;
    case 34:
        return 1;
    case 40:
        return 2;
    case 9:
        return 3;
    case 6:
        return 4;
    case 18:
        return 5;
    case 12:
        return 6;
    case 24:
        return 7;
    case 5:
        return 8;
    case 36:
        return 9;
    case 48:
        return 10;
    case 17:
        return 11;
    default:
        std::string edgeComb = getColourName(edge[0]) + getColourName(edge[1]);
        throw std::logic_error("Rubiks::getCornerInd invalid combination of edge colours: " + edgeComb);
    }
}

uint8_t Rubiks::getCornerInd(const corner_t& corner) const
{
    // unique index based on colour combinations
    uint8_t result = ((1 << (uint8_t)corner[0]) + (1 << (uint8_t)corner[1]) + (1 << (uint8_t)corner[2]));

    // W = 0 = 1
    // O = 1 = 2
    // G = 2 = 4
    // R = 3 = 8
    // B = 4 = 16
    // Y = 5 = 32

    // ULB = WOB = 19 = 0
    // ULF = WOG = 7  = 1
    // DLF = YOG = 38 = 2
    // DLB =

    switch (result)
    {
    case 19:
        return 0;
    case 7:
        return 1;
    case 38:
        return 2;
    case 50:
        return 3;
    case 56:
        return 4;
    case 44:
        return 5;
    case 13:
        return 6;
    case 25:
        return 7;
    default:
        std::string colourComb = getColourName(corner[0]) + getColourName(corner[1]) + getColourName(corner[2]);
        throw std::logic_error("Rubiks::getCornerInd invalid combination of edge colours:" + colourComb);
    }
}

uint8_t Rubiks::getPieceInd(EPIECE piece) const
{
    // same as getCorner/EedgeInd, only requires the position of the edge / corner piece
    // instead of all the colours
    switch (piece)
    {
    case EPIECE::UL:
        return getEdgeInd({ getColour(EEDGE::UL), getColour(EEDGE::LU) });
    case EPIECE::DL:
        return getEdgeInd({ getColour(EEDGE::DL), getColour(EEDGE::LD) });
    case EPIECE::DR:
        return getEdgeInd({ getColour(EEDGE::DR), getColour(EEDGE::RD) });
    case EPIECE::UR:
        return getEdgeInd({ getColour(EEDGE::UR), getColour(EEDGE::RU) });
    case EPIECE::LF:
        return getEdgeInd({ getColour(EEDGE::LF), getColour(EEDGE::FL) });
    case EPIECE::LB:
        return getEdgeInd({ getColour(EEDGE::LB), getColour(EEDGE::BL) });
    case EPIECE::RF:
        return getEdgeInd({ getColour(EEDGE::RF), getColour(EEDGE::FR) });
    case EPIECE::RB:
        return getEdgeInd({ getColour(EEDGE::RB), getColour(EEDGE::BR) });
    case EPIECE::UF:
        return getEdgeInd({ getColour(EEDGE::UF), getColour(EEDGE::FU) });
    case EPIECE::DF:
        return getEdgeInd({ getColour(EEDGE::DF), getColour(EEDGE::FD) });
    case EPIECE::DB:
        return getEdgeInd({ getColour(EEDGE::DB), getColour(EEDGE::BD) });
    case EPIECE::UB:
        return getEdgeInd({ getColour(EEDGE::UB), getColour(EEDGE::BU) });
    case EPIECE::ULB:
        return getCornerInd({ getColour(ECORNER::LUB), getColour(ECORNER::ULB), getColour(ECORNER::BLU) });
    case EPIECE::ULF:
        return getCornerInd({ getColour(ECORNER::LUF), getColour(ECORNER::ULF), getColour(ECORNER::FLU) });
    case EPIECE::DLF:
        return getCornerInd({ getColour(ECORNER::LDF), getColour(ECORNER::DLF), getColour(ECORNER::FLD) });
    case EPIECE::DLB:
        return getCornerInd({ getColour(ECORNER::LDB), getColour(ECORNER::DLB), getColour(ECORNER::BLD) });
    case EPIECE::DRB:
        return getCornerInd({ getColour(ECORNER::RDB), getColour(ECORNER::DRB), getColour(ECORNER::BRD) });
    case EPIECE::DRF:
        return getCornerInd({ getColour(ECORNER::RDF), getColour(ECORNER::DRF), getColour(ECORNER::FRD) });
    case EPIECE::URF:
        return getCornerInd({ getColour(ECORNER::RUF), getColour(ECORNER::URF), getColour(ECORNER::FRU) });
    case EPIECE::URB:
        return getCornerInd({ getColour(ECORNER::RUB), getColour(ECORNER::URB), getColour(ECORNER::BRU) });
    default:
        std::string value = std::to_string((int)piece);
        throw std::logic_error("Rubiks::getPieceInd invalid enum value: " + value);
    }
}

Rubiks::edge_t Rubiks::getEdge(EPIECE piece) const
{
    // same as getCorner/EedgeInd, only requires the position of the edge / corner piece
    // instead of all the colours
    switch (piece)
    {
    case EPIECE::UL:
        return { getColour(EEDGE::LU), getColour(EEDGE::UL) };
    case EPIECE::DL:
        return { getColour(EEDGE::LD), getColour(EEDGE::DL) };
    case EPIECE::DR:
        return { getColour(EEDGE::RD), getColour(EEDGE::DR) };
    case EPIECE::UR:
        return { getColour(EEDGE::RU), getColour(EEDGE::UR) };
    case EPIECE::LF:
        return { getColour(EEDGE::LF), getColour(EEDGE::FL) };
    case EPIECE::LB:
        return { getColour(EEDGE::LB), getColour(EEDGE::BL) };
    case EPIECE::RF:
        return { getColour(EEDGE::RF), getColour(EEDGE::FR) };
    case EPIECE::RB:
        return { getColour(EEDGE::RB), getColour(EEDGE::BR) };
    case EPIECE::UF:
        return { getColour(EEDGE::UF), getColour(EEDGE::FU) };
    case EPIECE::DF:
        return { getColour(EEDGE::DF), getColour(EEDGE::FD) };
    case EPIECE::DB:
        return { getColour(EEDGE::DB), getColour(EEDGE::BD) };
    case EPIECE::UB:
        return { getColour(EEDGE::UB), getColour(EEDGE::BU) };
    default:
        std::string value = std::to_string((int)piece);
        throw std::logic_error("Rubiks::getPieceInd invalid enum value: " + value);
    }
}

Rubiks::corner_t Rubiks::getCorner(EPIECE piece) const
{
    // same as getCorner/EedgeInd, only requires the position of the edge / corner piece
    // instead of all the colours
    switch (piece)
    {
    case EPIECE::ULB:
        return { getColour(ECORNER::LUB), getColour(ECORNER::ULB), getColour(ECORNER::BLU) };
    case EPIECE::ULF:
        return { getColour(ECORNER::LUF), getColour(ECORNER::ULF), getColour(ECORNER::FLU) };
    case EPIECE::DLF:
        return { getColour(ECORNER::LDF), getColour(ECORNER::DLF), getColour(ECORNER::FLD) };
    case EPIECE::DLB:
        return { getColour(ECORNER::LDB), getColour(ECORNER::DLB), getColour(ECORNER::BLD) };
    case EPIECE::DRB:
        return { getColour(ECORNER::RDB), getColour(ECORNER::DRB), getColour(ECORNER::BRD) };
    case EPIECE::DRF:
        return { getColour(ECORNER::RDF), getColour(ECORNER::DRF), getColour(ECORNER::FRD) };
    case EPIECE::URF:
        return { getColour(ECORNER::RUF), getColour(ECORNER::URF), getColour(ECORNER::FRU) };
    case EPIECE::URB:
        return { getColour(ECORNER::RUB), getColour(ECORNER::URB), getColour(ECORNER::BRU) };
    default:
        std::string value = std::to_string((int)piece);
        throw std::logic_error("Rubiks::getPieceInd invalid enum value: " + value);
    }
}

std::string Rubiks::getColourName(ECOLOUR colour) const
{
    switch (colour)
    {
    case ECOLOUR::W:
        return "W";
    case ECOLOUR::O:
        return "O";
    case ECOLOUR::G:
        return "G";
    case ECOLOUR::R:
        return "R";
    case ECOLOUR::B:
        return "B";
    case ECOLOUR::Y:
        return "Y";
    default:
        std::string value = std::to_string((int)colour);
        throw std::logic_error("Rubiks::getColourName invalid enum value: " + value);
    }
}

Rubiks::EMOVE Rubiks::getMoveFromStr(const std::string& name) const
{
    if (name == "U")  return EMOVE::U;
    if (name == "U'") return EMOVE::Up;
    if (name == "U2") return EMOVE::U2;
    if (name == "L")  return EMOVE::L;
    if (name == "L'") return EMOVE::Lp;
    if (name == "L2") return EMOVE::L2;
    if (name == "F")  return EMOVE::F;
    if (name == "F'") return EMOVE::Fp;
    if (name == "F2") return EMOVE::F2;
    if (name == "R")  return EMOVE::R;
    if (name == "R'") return EMOVE::Rp;
    if (name == "R2") return EMOVE::R2;
    if (name == "B")  return EMOVE::B;
    if (name == "B'") return EMOVE::Bp;
    if (name == "B2") return EMOVE::B2;
    if (name == "D")  return EMOVE::D;
    if (name == "D'") return EMOVE::Dp;
    if (name == "D2") return EMOVE::D2;
    if (name == "")   return EMOVE::NO_MOVE;
    if (name == " ")  return EMOVE::NO_MOVE;
    
    throw std::logic_error("Rubiks::getMove invalid move name" + name);
}

std::string Rubiks::getMoveName(EMOVE move) const
{
    switch (move)
    {
    case EMOVE::U:
        return "U";
    case EMOVE::Up:
        return "U'";
    case EMOVE::U2:
        return "U2";
    case EMOVE::L:
        return "L";
    case EMOVE::Lp:
        return "L'";
    case EMOVE::L2:
        return "L2";
    case EMOVE::F:
        return "F";
    case EMOVE::Fp:
        return "F'";
    case EMOVE::F2:
        return "F2";
    case EMOVE::R:
        return "R";
    case EMOVE::Rp:
        return "R'";
    case EMOVE::R2:
        return "R2";
    case EMOVE::B:
        return "B";
    case EMOVE::Bp:
        return "B'";
    case EMOVE::B2:
        return "B2";
    case EMOVE::D:
        return "D";
    case EMOVE::Dp:
        return "D'";
    case EMOVE::D2:
        return "D2";
    case EMOVE::NO_MOVE:
        return "";
    default:
        std::string value = std::to_string((int)move);
        throw std::logic_error("Rubiks::getMoveName invalid enum value: " + value);
    }
}

void Rubiks::performMove(EMOVE move)
{
    switch (move)
    {
    case EMOVE::U:
        U();
        break;
    case EMOVE::Up:
        Up();
        break;
    case EMOVE::U2:
        U2();
        break;
    case EMOVE::L:
        L();
        break;
    case EMOVE::Lp:
        Lp();
        break;
    case EMOVE::L2:
        L2();
        break;
    case EMOVE::F:
        F();
        break;
    case EMOVE::Fp:
        Fp();
        break;
    case EMOVE::F2:
        F2();
        break;
    case EMOVE::R:
        R();
        break;
    case EMOVE::Rp:
        Rp();
        break;
    case EMOVE::R2:
        R2();
        break;
    case EMOVE::B:
        B();
        break;
    case EMOVE::Bp:
        Bp();
        break;
    case EMOVE::B2:
        B2();
        break;
    case EMOVE::D:
        D();
        break;
    case EMOVE::Dp:
        Dp();
        break;
    case EMOVE::D2:
        D2();
        break;
    case EMOVE::NO_MOVE:
        break;
    default:
        std::string value = std::to_string((int)move);
        throw std::logic_error("RubiksCube::performMove Invalid enum value: " + value);
    }
}

void Rubiks::revertMove(EMOVE move)
{
    switch (move)
    {
    case EMOVE::U:
        Up();
        break;
    case EMOVE::Up:
        U();
        break;
    case EMOVE::U2:
        U2();
        break;
    case EMOVE::L:
        Lp();
        break;
    case EMOVE::Lp:
        L();
        break;
    case EMOVE::L2:
        L2();
        break;
    case EMOVE::F:
        Fp();
        break;
    case EMOVE::Fp:
        F();
        break;
    case EMOVE::F2:
        F2();
        break;
    case EMOVE::R:
        Rp();
        break;
    case EMOVE::Rp:
        R();
        break;
    case EMOVE::R2:
        R2();
        break;
    case EMOVE::B:
        Bp();
        break;
    case EMOVE::Bp:
        B();
        break;
    case EMOVE::B2:
        B2();
        break;
    case EMOVE::D:
        Dp();
        break;
    case EMOVE::Dp:
        D();
        break;
    case EMOVE::D2:
        D2();
        break;
    default:
        std::string value = std::to_string((int)move);
        throw std::logic_error("RubiksCube::revertMove Invalid enum value: " + value);
    }
}

// rotations
void Rubiks::U()
{
    rotateFaceCW(EFACE::U);
    rotateAdjacents({ 8, 16, 24, 32, 10, 18, 26, 34 });
}

void Rubiks::Up()
{
    rotateFaceCCW(EFACE::U);
    rotateAdjacents({ 32, 24, 16, 8, 34, 26, 18, 10 });
}

void Rubiks::U2()
{
    rotateFace180(EFACE::U);
    rotateAdjacents180({ 32, 24, 16, 8, 34, 26, 18, 10 });
}

void Rubiks::L()
{
    rotateFaceCW(EFACE::L);
    rotateAdjacents({ 6, 34, 46, 22, 0, 36, 40, 16 });
}

void Rubiks::Lp()
{
    rotateFaceCCW(EFACE::L);
    rotateAdjacents({ 22, 46, 34, 6, 16, 40, 36, 0 });
}

void Rubiks::L2()
{
    rotateFace180(EFACE::L);
    rotateAdjacents180({ 22, 46, 34, 6, 16, 40, 36, 0 });
}

void Rubiks::F()
{
    rotateFaceCW(EFACE::F);

    rotateAdjacents({ 10, 40, 30, 4, 12, 42, 24 ,6 });
}

void Rubiks::Fp()
{
    rotateFaceCCW(EFACE::F);
    rotateAdjacents({ 4, 30, 40, 10, 6, 24, 42, 12 });
}

void Rubiks::F2()
{
    rotateFace180(EFACE::F);
    rotateAdjacents180({ 4, 30, 40, 10, 6, 24, 42, 12 });
}

void Rubiks::R()
{
    rotateFaceCW(EFACE::R);
    rotateAdjacents({ 2, 18, 42, 38, 4, 20, 44, 32 });
}

void Rubiks::Rp()
{
    rotateFaceCCW(EFACE::R);
    rotateAdjacents({ 38, 42, 18, 2, 32, 44, 20, 4 });
}

void Rubiks::R2()
{
    rotateFace180(EFACE::R);
    rotateAdjacents180({ 38, 42, 18, 2, 32, 44, 20, 4 });
}

void Rubiks::B()
{
    rotateFaceCW(EFACE::B);
    rotateAdjacents({ 0, 26, 44, 14, 2, 28, 46, 8 });
}

void Rubiks::Bp()
{
    rotateFaceCCW(EFACE::B);
    rotateAdjacents({ 14, 44, 26, 0, 8, 46, 28, 2 });
}

void Rubiks::B2()
{
    rotateFace180(EFACE::B);
    rotateAdjacents180({ 14, 44, 26, 0, 8, 46, 28, 2 });
}

void Rubiks::D()
{
    rotateFaceCW(EFACE::D);
    rotateAdjacents({ 36, 28, 20, 12, 38, 30, 22, 14 });
}

void Rubiks::Dp()
{
    rotateFaceCCW(EFACE::D);
    rotateAdjacents({ 12, 20, 28, 36, 14, 22, 30, 38 });
}

void Rubiks::D2()
{
    rotateFace180(EFACE::D);
    rotateAdjacents180({ 36, 28, 20, 12, 38, 30, 22, 14 });
}

void Rubiks::displayCube() const
{
    // TODO: find a better way to do this, obviously
    std::string buffer = "   ";

    std::cout << buffer << getColourName(m_cube[0]) << getColourName(m_cube[1]) << getColourName(m_cube[2]) << "\n";
    std::cout << buffer << getColourName(m_cube[7]) << "W" << getColourName(m_cube[3]) << "\n";
    std::cout << buffer << getColourName(m_cube[6]) << getColourName(m_cube[5]) << getColourName(m_cube[4]) << "\n";
    std::cout << getColourName(m_cube[8]) << getColourName(m_cube[9]) << getColourName(m_cube[10]) <<
        getColourName(m_cube[16]) << getColourName(m_cube[17]) << getColourName(m_cube[18]) <<
        getColourName(m_cube[24]) << getColourName(m_cube[25]) << getColourName(m_cube[26]) <<
        getColourName(m_cube[32]) << getColourName(m_cube[33]) << getColourName(m_cube[34]) << "\n";
    std::cout << getColourName(m_cube[15]) << "O" << getColourName(m_cube[11]) << getColourName(m_cube[23]) << "G" <<
        getColourName(m_cube[19]) << getColourName(m_cube[31]) << "R" << getColourName(m_cube[27]) <<
        getColourName(m_cube[39]) << "B" << getColourName(m_cube[35]) << "\n";
    std::cout << getColourName(m_cube[14]) << getColourName(m_cube[13]) << getColourName(m_cube[12]) <<
        getColourName(m_cube[22]) << getColourName(m_cube[21]) << getColourName(m_cube[20]) <<
        getColourName(m_cube[30]) << getColourName(m_cube[29]) << getColourName(m_cube[28]) <<
        getColourName(m_cube[38]) << getColourName(m_cube[37]) << getColourName(m_cube[36]) << "\n";
    std::cout << buffer << getColourName(m_cube[40]) << getColourName(m_cube[41]) << getColourName(m_cube[42]) << "\n";
    std::cout << buffer << getColourName(m_cube[47]) << "Y" << getColourName(m_cube[43]) << "\n";
    std::cout << buffer << getColourName(m_cube[46]) << getColourName(m_cube[45]) << getColourName(m_cube[44]) << "\n";

}
