//
// Created by guizo on 21/07/2022.
//

#ifndef FALLINGSAND_CELL_H
#define FALLINGSAND_CELL_H

#include <array>

enum class CellType{
    EMPTYCELL,
    SOLID,
    WATER,
    SAND,
    OIL,
    FIRE
};

enum class CellProp{
    STATIC,
    MOVE_DOWN,
    MOVE_DOWN_SIDE,
    MOVE_DOWN_DIAGONAL,
    GAS,
    FIRE

};

class Cell {
public:
    Cell();
    Cell(CellType _type);
    ~Cell();
    void RenderCell(int x, int y);
    void SetCell(CellType type_);
    void SetDensity(float density_);

    CellType GetType() { return this->type; }
    CellProp GetProp() { return this->prop; }

    float GetDensity() const { return this->density; }
    bool IsFlammable() const{ return this->flammable; }
    bool IsIgnited() const { return this->isIgnited; }

    bool hasMoved;
    int timesMoved;

private:
    CellType type;
    CellProp prop;
    int r, g, b, a;
    int heat;
    float density;
    bool flammable, isIgnited;
};


#endif //FALLINGSAND_CELL_H
