//
// Created by guizo on 21/07/2022.
//

#ifndef FALLINGSAND_SANDWORLD_H
#define FALLINGSAND_SANDWORLD_H

#include <SDL.h>
#include <iostream>
#include "Cell.h"
#include <array>


class SandWorld {
public:
    SandWorld();
    ~SandWorld();
    void DrawMatrix();
    void Step();
    void HandleEvents();

    std::array<std::array<Cell, 50>, 50> matrix;
    bool running;

private:
    void MoveCell(Cell& cell, int x, int y);
    void CreateCell(SDL_MouseButtonEvent& b);
    void GetKeyboard(SDL_KeyboardEvent& k);

    void MoveCellDown(Cell &cell, int x, int y);
    void MoveCellSide(Cell &cell, int x, int y);
    void MoveCellDiagonal(Cell &cell, int x, int y);
    void MoveGas(Cell &cell, int x, int y);

    CellType currType;
};


#endif //FALLINGSAND_SANDWORLD_H
