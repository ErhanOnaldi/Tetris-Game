#include "Piece.h"
#include <algorithm>

Piece::Piece(PieceType type) : type(type) {
    setMatrix();
}

void Piece::rotate() {
    std::array<std::array<int, 4>, 4> rotatedMatrix;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            rotatedMatrix[j][3 - i] = matrix[i][j];
        }
    }
    matrix = rotatedMatrix;
}


void Piece::setMatrix() {
    const std::array<std::array<int, 4>, 4> I_Piece =
    { {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    } };
    const std::array<std::array<int, 4>, 4> O_Piece =
    { {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    } };
    const std::array<std::array<int, 4>, 4> T_Piece =
    { {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    } };
    const std::array<std::array<int, 4>, 4> S_Piece =
    { {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    } };
    const std::array<std::array<int, 4>, 4> Z_Piece =
    { {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    } };
    const std::array<std::array<int, 4>, 4> L_Piece =
    { {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}
    } };
    const std::array<std::array<int, 4>, 4> J_Piece =
    { {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    } };

    switch (type) {
    case PieceType::I:
        matrix = I_Piece;
        break;
    case PieceType::O:
        matrix = O_Piece;
        break;
    case PieceType::T:
        matrix = T_Piece;
        break;
    case PieceType::S:
        matrix = S_Piece;
        break;
    case PieceType::Z:
        matrix = Z_Piece;
        break;
    case PieceType::L:
        matrix = L_Piece;
        break;
    case PieceType::J:
        matrix = J_Piece;
        break;
    }
}

const std::array<std::array<int, 4>, 4>& Piece::getMatrix() const {
    return matrix;
}

PieceType Piece::getType()
{
    return type;
}
