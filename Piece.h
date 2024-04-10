#pragma once
#include <array>

enum class PieceType { I, O, T, S, Z, L, J };

class Piece {
public:
    Piece(PieceType type);
    void rotate();
    const std::array<std::array<int, 4>, 4>& getMatrix() const;
    PieceType getType();
private:
    PieceType type;
    std::array<std::array<int, 4>, 4> matrix;
    void setMatrix();
};

