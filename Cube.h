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

    // set a face (8 colours) from a 64bit integer
    void setFace(EFACE face, uint64_t newFace);

    using Edge   = std::array<ECOLOUR, 2>;
    using Corner = std::array<ECOLOUR, 3>;

    uint64_t    getFace(EFACE face) const;
    ECOLOUR     getColour(std::size_t index) const;
    ECOLOUR     getColour(EEDGE edge) const;
    ECOLOUR     getColour(ECORNER corner) const;
    std::string getColourName(ECOLOUR colour) const;
    std::string getMoveName(EMOVE move) const;
    EMOVE       getMoveFromStr(const std::string& name) const;

    // first index is the facelet on the R/L face, or U/D for the M slice
    uint8_t getEdgeOrientation(const Edge& edge) const;
    // first index is the facelet on the R/L face
    uint8_t getCornerOrientation(const Corner& corner) const;

    // unique ids for edges and corners, to assoicate them based on colours
    // regardless of where they are on the cube
    uint8_t getEdgeInd(const Edge& edge) const;
    uint8_t getCornerInd(const Corner& edge) const;

    // run a face rotation function based on a move
    void performMove(EMOVE move);
    // make a move that cancels the given move (L => L')
    void revertMove(EMOVE move);

    // display the cube state in ASCII
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
    // 6 faces * 8 facelets = 48, for easier indexing of colours (doesn't store centre facelets)
    std::array<ECOLOUR, 48> m_cube;
};

#endif // CUBE_H
