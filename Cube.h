#pragma once

#include <cstdint>
#include <bit>
#include <bitset>
#include <iostream>
#include <vector>
#include <array>
#include <ctime>

class Rubiks
{
public: 
    Rubiks();

    // the EFACE and ECOLOUR enums correspond (up face is white, left face is orange....)
    enum class EFACE   : uint8_t { U, L, F, R, B, D }; // up,    left,   front, right, back, down
    enum class ECOLOUR : uint8_t { W, O, G, R, B, Y }; // white, orange, green, red,   blue, yellow

    // comparing two cubes
    bool operator==(const Rubiks& lhs);

    // copy asigment operator
    Rubiks& operator=(const Rubiks& lhs);

    // for indexing edges and corners using a readable name
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
        UBL = 0 ,   UBR = 2 ,   UFR = 4 ,   UFL = 6 ,
        LUB = 8 ,   LFU = 10,   LDF = 12,   LBD = 14,
        FUL = 16,   FRU = 18,   FDR = 20,   FLD = 22,
        RUF = 24,   RBU = 26,   RDB = 28,   RFD = 30,
        BUR = 32,   BLU = 34,   BDL = 36,   BRD = 38,
        DFL = 40,   DFR = 42,   DBR = 44,   DBL = 46,
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

    // indices of ajacent facelets of the face when performing a rotation
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

    // set a face with new colours from a 64bit integer
    void setFace(EFACE face, uint64_t newFace);

    typedef std::array<ECOLOUR, 2> Edge;
    typedef std::array<ECOLOUR, 3> Corner;

    uint64_t    getFace(EFACE face) const;
    ECOLOUR     getColour(std::size_t index) const;
    ECOLOUR     getColour(EEDGE edge) const;
    ECOLOUR     getColour(ECORNER corner) const;
    std::string getColourName(ECOLOUR colour) const;
    std::string getMoveName(EMOVE move) const;
    EMOVE       getMove(const std::string& name) const;

    // first index is the facelet on the R/L face, or U/D for the M slice
    uint8_t getEdgeOrientation(const Edge& edge) const;
    // first index is the facelet on the R/L face
    uint8_t getCornerOrientation(const Corner& corner) const;

    // unique ids for edges and corners, to assoicate them based on colours
    // regardless of where they are on the cube
    uint8_t getEdgeInd(const Edge& edge) const;
    uint8_t getCornerId(const Corner& edge) const;

    // run a face rotation function based on a move
    void performMove(EMOVE move);
    void revertMove(EMOVE move);

    // display cube in console
    void displayCube() const;

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
    // 6 faces * 8 facelets = 48, for easier indexing of colours
    std::array<ECOLOUR, 48> m_cube;
};

