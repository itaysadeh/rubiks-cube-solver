#ifndef CUBE_H
#define CUBE_H

#include <bit>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>
#include <array>
#include <ctime>

class Rubiks
{
public: 
    Rubiks();
    // colour of EFACE::X is ECOLOUR::X
    enum class EFACE   : uint8_t { U, L, F, R, B, D }; // up,    left,   front, right, back, down
    enum class ECOLOUR : uint8_t { W, O, G, R, B, Y }; // white, orange, green, red,   blue, yellow

    bool operator==(const Rubiks& lhs);
    Rubiks& operator=(const Rubiks& lhs);

    // indexing pieces with positions
    enum class EEDGE : uint8_t
    {
        UB = 1 ,    UR = 3 ,    UF = 5 ,    UL = 7,
        LU = 9 ,    LF = 11,    LD = 13,    LB = 15,
        FU = 17,    FR = 19,    FD = 21,    FL = 23,
        RU = 25,    RB = 27,    RD = 29,    RF = 31,
        BU = 33,    BL = 35,    BD = 37,    BR = 39,
        DF = 41,    DR = 43,    DB = 45,    DL = 47,
    };
    enum class ECORNER : uint8_t
    {
        ULB = 0 ,   URB = 2 ,   URF = 4 ,   ULF = 6 ,
        LUB = 8 ,   LUF = 10,   LDF = 12,   LDB = 14,
        FLU = 16,   FRU = 18,   FRD = 20,   FLD = 22,
        RUF = 24,   RUB = 26,   RDB = 28,   RDF = 30,
        BRU = 32,   BLU = 34,   BLD = 36,   BRD = 38,
        DLF = 40,   DRF = 42,   DRB = 44,   DLB = 46,
    };
    enum class EMOVE : uint8_t
    {
        NO_MOVE, // = NULL, when comparing moves with a root position (no move was made)
        U, Up, U2,
        L, Lp, L2,
        F, Fp, F2,
        R, Rp, R2,
        B, Bp, B2,
        D, Dp, D2,
    };

    // indices of ajacent facelets of the face when performing a face rotation
    struct AdjacentIndices
    {
        uint8_t i0, i1, i2, i3, i4, i5, i6, i7;
    };

    void resetCube();
    bool isSovled() const;

    // face rotations logic
    void rotateFaceCW(EFACE face);
    void rotateFaceCCW(EFACE face);
    void rotateFace180(EFACE face);
    void rotateAdjacents(const AdjacentIndices& adj);
    void rotateAdjacents180(const AdjacentIndices& adj);

    // updates a face (8 colours) from a 64bit integer
    void setFace(EFACE face, uint64_t newFace);

    ECOLOUR     getColour(uint8_t index) const;
    ECOLOUR     getColour(ECORNER index) const;
    ECOLOUR     getColour(EEDGE   index) const;
    uint64_t    getFace(EFACE face) const;
    std::string getColourName(ECOLOUR colour) const;
    std::string getMoveName(EMOVE move) const;
    EMOVE       getMoveFromStr(const std::string& name) const;

    using edge_t   = std::array<ECOLOUR, 2>;
    using corner_t = std::array<ECOLOUR, 3>;

    // first index is the facelet on the R/L face, or U/D for the M slice
    uint8_t getEdgeOrientation(const edge_t& edge) const;
    // first index is the facelet on the R/L face
    uint8_t getCornerOrientation(const corner_t& corner) const;

    // get the index of a piece based on it's colours
    uint8_t getEdgeInd(const edge_t& edge) const;
    uint8_t getCornerInd(const corner_t& edge) const;

    // display the cube state in ASCII
    void displayCube() const;

    void performMove(EMOVE move);
    void revertMove(EMOVE move);

    // face rotations
    void U();
    void Up();
    void U2();
    void L();
    void Lp();
    void L2();
    void F();
    void Fp();
    void F2();
    void R();
    void Rp();
    void R2();
    void B();
    void Bp();
    void B2();
    void D();
    void Dp();
    void D2();

private:
    std::array<ECOLOUR, 48> m_cube;
};

#endif // CUBE_H
