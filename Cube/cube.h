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
    enum class EFACE   : uint8_t { U, L, F, R, B, D };
    enum class ECOLOUR : uint8_t { W, O, G, R, B, Y };

    bool operator==(const Rubiks& lhs);
    Rubiks& operator=(const Rubiks& lhs);

    // piece indexing
    enum class EPIECE : uint8_t { UL,  DL,  DR,  UR,  LF,  LB,  RF,  RB,  UF,  DF,  DB,  UB,
                                  ULB, ULF, DLF, DLB, DRB, DRF, URF, URB };
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
    // move indexing
    enum class EMOVE : uint8_t
    {
        NO_MOVE,
        U, Up, U2,
        L, Lp, L2,
        F, Fp, F2,
        R, Rp, R2,
        B, Bp, B2,
        D, Dp, D2,
    };

    // indices of affected facelets in a face rotation (ajacents)
    using adjacentIndices_t = std::array<uint8_t, 8>; 

    void resetCube();
    bool isSovled() const;

    void rotateFaceCW(EFACE face);
    void rotateFaceCCW(EFACE face);
    void rotateFace180(EFACE face);
    void rotateAdjacents(const adjacentIndices_t& adj);
    void rotateAdjacents180(const adjacentIndices_t& adj);

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

    // unique indices of pieces derived from their colours
    uint8_t getEdgeInd(const edge_t& edge) const;
    uint8_t getCornerInd(const corner_t& edge) const;
    uint8_t getPieceInd(EPIECE piece) const;

    corner_t getCorner(EPIECE piece) const;
    edge_t getEdge(EPIECE piece) const;

    // prints cube states in ASCII
    void displayCube() const;

    void performMove(EMOVE move);
    void revertMove(EMOVE move);

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
